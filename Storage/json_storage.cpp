#include "json_storage.h"
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QRegExp>
#include <QSqlQuery>
#include <QSqlError>

#include <QUuid>

//List all collections
QList<QString> JsonStorage::listCollections( QString collection )
{
    QString base = baseFolder( collection );

    //Create the collection
    QDir path(base);
    return path.entryList( QDir::Files );
}


QString JsonStorage::baseFolder( QString collection )
{
    //Get the collection filename
    return QString("%1/%2").
                        arg( QStandardPaths::standardLocations( QStandardPaths::AppDataLocation ).value(0)).
                        arg(collection);
}

JsonStorage::~JsonStorage()
{
   close();
}

bool JsonStorage::loadCollection( QString collection, QString uid )
{
    //If we're already open, close it
    if ( isOpen() )
        close();

    //Setup the collection
    if ( uid.isEmpty() )
        return false;

    //Get the collection filename
    auto&& base = baseFolder( collection );
    auto&& path = QString( "%1/%2.sql" ).arg(base).arg(uid.replace(".sql", ""));

    //Create the collection
    QDir col(base);
    if (!col.exists())
        return false;

    //Create the collection
    QFile dir(path);
    if ( !dir.exists() )
        return false;

    //Setup the database
    _collection = collection;
    _uid = uid;
    _connectionName = QUuid::createUuid().toString(QUuid::WithoutBraces);
    _db = QSqlDatabase::addDatabase( "QSQLITE", _connectionName );
    _db.setDatabaseName(path);
    //_db.setDatabaseName(":memory:");

    //Ensure our connection is valid
    if ( !_db.isValid() )
        return false;

    //Open the database
    if ( !_db.open() )
        return false;

    //Get ready for schema!
    _schema.clear();

    //Download the schema
    QSqlQuery query( _db );
    query.exec("SELECT table_name, field, data_type FROM meta_info");
    while ( query.next() )
    {
        auto table = query.value(0).toString();
        auto field = query.value(1).toString();
        auto data_type = query.value(2).toString();

        //Build out the schema
        if ( !_schema.contains( table ) )
            _schema.insert( table, QHash<QString, DataType>() );
        _schema[table].insert( field, toDataType(data_type) );
    }

    return true;
}


bool JsonStorage::createCollection( QString collection, QHash<QString, QJsonObject> tables, QString uid )
{
    //If we're already open, close it
    if ( isOpen() )
        close();

    //Setup the collection
    if ( uid.isEmpty() )
        uid = QUuid::createUuid().toString(QUuid::WithoutBraces);

    //Get the collection filename
    auto&& base = baseFolder( collection );
    auto&& path = QString( "%1/%2.sql" ).arg(base).arg(uid);

    //Create the collection
    QDir col(base);
    if (!col.exists())
        col.mkpath(base);

    //Create the collection
    QFile dir(path);
    if (dir.exists())
        return false;

    //Setup the database
    _collection = collection;
    _uid = uid;
    _connectionName = QUuid::createUuid().toString(QUuid::WithoutBraces);
    _db = QSqlDatabase::addDatabase( "QSQLITE", _connectionName );
    _db.setDatabaseName(path);
    //_db.setDatabaseName(":memory:");

    //Ensure our connection is valid
    if ( !_db.isValid() )
        return false;

    //Open the database
    if ( !_db.open() )
        return false;

    //Setup the schema stuff
    _schema.clear();

    QSqlQuery query( _db );

    //Set the mode to be Write ahead log
    query.exec("PRAGMA journal_mode=WAL");

    //Create the database tables
    query.exec("create table meta_info (table_name varchar(64), field varchar(64), data_type varchar(64))");
    for ( auto& table : tables.keys() )
        createTable( table, tables[table] );

    return true;
}


//*** instance methods

bool JsonStorage::isOpen()
{
    return _db.isOpen();
}


void JsonStorage::close()
{
    if ( !isOpen() )
        return;

    _db.close();
    _schema.clear();

    _db = QSqlDatabase();
    QSqlDatabase::removeDatabase( _connectionName );
    _connectionName = "";
}


bool JsonStorage::deleteCollection()
{
    ScopeLock( _lock );

    close();

    //Get the collection filename
    auto&& base = baseFolder( _collection );
    auto&& path = QString( "%1/%2.sql" ).arg(base).arg(_uid);

    //Kill the collection
    QFile::remove( path );

    //Close and return our result
    return true;
}


int JsonStorage::count( QString table )
{
    ScopeLock( _lock );

    if ( !isOpen() )
        return -1;

    QString sql = QString("SELECT COUNT(*) FROM %1;").arg(table);
    QSqlQuery query( _db );
    query.exec(sql);

    //Attempt to send out the info!
    if ( !query.next())
    {
        qDebug("Sql err: %s", query.lastError().text().toUtf8().data());
        return -1;
    }

    return query.value(0).toInt();
}


bool JsonStorage::rowExists( QString table, qint64 id )
{
    ScopeLock( _lock );

    if ( !isOpen() )
        return false;

    //Can't possibly be valid
    if ( id <= 0 )
        return false;

    QString sql = QString("SELECT COUNT(*) FROM %1 where rowid = %2;").arg(table).arg(id);
    QSqlQuery query( _db );
    query.exec(sql);

    //Attempt to send out the info!
    if ( !query.next())
    {
        qDebug("Sql err: %s", query.lastError().text().toUtf8().data());
        return false;
    }

    return query.value(0).toInt() == 1;
}


bool JsonStorage::insert( QString table, QJsonObject obj, QString foreign_key, qint64 parent_id )
{
    if ( !isOpen() )
        return false;

    if ( !_schema.contains(table) )
        return false;

    if ( !foreign_key.isEmpty() && parent_id > 0 )
        obj.insert( foreign_key, parent_id );

    auto&& raw_keys = obj.keys();
    QStringList keys;

    //Build up the keys, safely
    for ( auto key : raw_keys )
        if ( _schema[table].contains(key) &&
             _schema[table][key] != SINGLE &&
             _schema[table][key] != MANY )
            keys.append(key);

    //Build up values
    auto&& values = QStringList();
    for ( auto i = 0; i < keys.length(); i++ )
        values.append("?");

    auto result = false;
    auto last_id = 0;
    {
        ScopeLock( _lock );

        //Insert the data
        auto&& query = QSqlQuery( _db );
        auto&& sql = QString("INSERT INTO %1 (%2) VALUES (%3)").
                        arg(table).
                        arg(keys.join(",")).
                        arg(values.join(","));
        query.prepare( sql );
        for ( auto i = 0; i < keys.length(); i++ )
            query.bindValue( i, toVariant( _schema[table][keys[i]], obj.value( keys[i] ) ) );

        result = query.exec();
        if ( !result )
            return false;

        //Grab the ID, we'll need it for inserting children
        auto last_raw = query.lastInsertId();
        if ( !last_raw.isValid() )
        {
            qDebug( "Couldn't retreive the inserted id" );
            return false;
        }

        last_id = last_raw.toInt();
    }

    //Recursive
    for ( auto key : raw_keys )
    {
        auto deplorable = depluralizer(key);
        if ( _schema[table].contains(key) && (_schema[table][key] == SINGLE || _schema[table][key] == MANY))
        {
            if ( obj[key].isObject() && _schema[table][key] == SINGLE )
                result &= insert( key, obj[key].toObject(), QString("%1_id").arg(table), last_id );
            else if ( obj[key].isArray() && _schema[table][key] == MANY )
                result &= bulkInsert( deplorable, obj[key].toArray(), QString("%1_id").arg(table), last_id );
        }
    }

    return true;
}


bool JsonStorage::bulkInsert(QString table, QJsonArray ary, QString foreign_key, qint64 parent_id )
{
    //Todo, implement an actual bulk!

    auto status = true;
    for ( auto i = 0; i < ary.count(); i++ )
    {
        auto&& obj = ary.at(i).toObject();
        status &= insert( table, obj, foreign_key, parent_id );
    }

    return status;
}


bool JsonStorage::update( QString table, qint64 id, QJsonObject obj, QString foreign_key, qint64 parent_id )
{
    if ( !isOpen() )
        return false;

    //Deal with the foreign key
    if ( !foreign_key.isEmpty() && parent_id > 0 )
    {
        //Find the
        auto&& ary = selectSql( table, QString("%1 = %2").arg(foreign_key).arg(parent_id), -1, -1, false);
        if ( ary.length() == 1 )
            id = ary[0]["rowid"].toInt();
    }

    //Should we actually insert?
    if ( !rowExists( table, id ))
        return insert( table, obj, foreign_key, parent_id );

    bool result = false;
    auto&& raw_keys = obj.keys();
    QStringList keys;

    //Required lock
    {
        ScopeLock( _lock );

        //Build up the keys, safely
        for ( auto key : raw_keys )
            if ( _schema[table].contains(key) &&
                 _schema[table][key] != SINGLE &&
                 _schema[table][key] != MANY )
                keys.append(key);

        //Run an update
        auto&& values = QStringList();
        for ( auto i = 0; i < keys.length(); i++ )
            values.append(QString("%1 = ?").arg(keys[i]));

        auto&& query = QSqlQuery( _db );
        auto&& sql = QString("UPDATE %1 SET %2 WHERE rowid = %3").
                        arg(table).
                        arg(values.join(",")).
                        arg(id);
        query.prepare( sql );
        for ( auto i = 0; i < keys.length(); i++ )
            query.bindValue( i, toVariant( _schema[table][keys[i]], obj.value( keys[i] ) ));

        result = query.exec();
        if ( !result )
            return false;
    }

    //Recursive
    for ( auto key : raw_keys )
        if ( _schema[table].contains(key) && _schema.contains(key))
        {
            if ( _schema[table][key] == SINGLE && obj[key].isObject() )
                result &= update( key, -1, obj[key].toObject(), QString("%1_id").arg(table), id );

            /* Can't safely update an array because we wont know which elements are the same with an ID
            else if ( obj[key].isArray() )
                result &= bulkInsert( key, obj[key].toArray(), QString("%1_id").arg(table), id );
                */
        }

    return result;

}


QList<QJsonObject> JsonStorage::all( QString table, int limit, int offset, bool recursive )
{
    ScopeLock( _lock );

    return selectSql( table, QString(), limit, offset, recursive );
}


QList<QJsonObject> JsonStorage::filter( QString table, QString where, int limit, int offset, bool recursive )
{
    ScopeLock( _lock );

    return selectSql( table, where, limit, offset, recursive );
}


QJsonObject JsonStorage::getById(QString table, qint64 id, bool* successful, bool recursive)
{
    ScopeLock( _lock );

    auto&& results = selectSql( table, QString("rowid = %1").arg(id), 1, -1, recursive );
    if ( successful != nullptr )
        *successful = (results.count() == 1);

    return (results.count() == 1)? results.at(0): QJsonObject();
}

//Actually run sql statements
QList<QJsonObject> JsonStorage::selectSql(QString table, QString where, int limit, int offset, bool recursive)
{
    auto&& result = QList<QJsonObject>();

    if ( !isOpen() )
        return std::move( result );

    //Ensure we ahve a schema for this table
    if ( !_schema.contains(table))
        return std::move( result );

    auto&& singles = QStringList();
    auto&& manys = QStringList();
    auto&& fields = QStringList();
    for ( auto& key : _schema[table].keys() )
    {
        switch ( _schema[table][key] )
        {
            case SINGLE:
                if ( recursive )
                    singles.append(key);
                break;
            case MANY:
                if ( recursive )
                    manys.append(key);
                break;

            case INVALID:
                break;

                //All other fields
            default:
                fields.append( key );
                break;
        }
    }

    //Query the data
    QSqlQuery query( _db );
    QString sql;
    if ( where.isNull() || where.isEmpty() )
        sql = QString("SELECT rowid,%1 FROM %2").arg(fields.join(", ")).arg(table);
    else
        sql = QString("SELECT rowid,%1 FROM %2 WHERE %3").
                    arg(fields.join(", ")).
                    arg(table).
                    arg(where);
    if ( limit > 0 )
        sql += QString(" LIMIT %1").arg(limit);
    if ( offset > 0 )
        sql += QString(" OFFSET %1").arg(offset);

    //Run the query, and store the data
    query.exec( sql );
    while ( query.next() )
    {
        QJsonObject obj;
        auto row_id = query.value(0).toInt();
        obj.insert("rowid", row_id);

        //Run through loading fields
        for ( auto i = 0; i < fields.length(); i++ )
        {
            auto& field = fields[i];
            obj.insert( field, toJsonValue( _schema[table][field], query.value(i+1) ));
        }

        //Implement a single object expansion
        for ( auto i = 0; i < singles.length(); i++ )
        {
            auto& single = singles[i];
            auto&& ary = selectSql(single, QString("%1_id = %2").arg(table).arg(row_id), 1, -1, true);
            if ( ary.count() == 1 )
                obj.insert( single, ary[0] );
        }

        //Implement multi object expansion
        for ( auto i = 0; i < manys.length(); i++ )
        {
            auto many = manys[i];
            auto&& ary = selectSql( depluralizer( many ), QString("%1_id = %2").arg(table).arg(row_id), -1, -1, true);

            //Convert the data
            QJsonArray json_ary;
            for ( auto& a : ary )
                json_ary.append(a);

            obj.insert( many, json_ary );
        }

        result.append( obj );
    }

    return std::move( result );
}

bool JsonStorage::destroyById(QString table, qint64 id)
{
    return destroyWhere( table, QString("rowid = %1").arg(id));
}

bool JsonStorage::destroyByIds(QString table, QList<qint64> ids)
{
    auto&& ary = QStringList();
    for ( auto id : ids )
        ary.append( QString::number(id) );

    return destroyWhere( table, QString("rowid in (%1)").arg(ary.join(", ")));
}

bool JsonStorage::destroyWhere(QString table, QString where )
{
    ScopeLock( _lock );

    if ( !isOpen() )
        return false;

    //Ensure we ahve a schema for this table
    if ( !_schema.contains(table))
        return false;

    //Query the data
    QSqlQuery query( _db );
    auto sql = QString("DELETE FROM %1 WHERE %2").
                    arg(table).
                    arg(where);

    //Run the query, and store the data
    return query.exec( sql );
}

bool JsonStorage::destroyCount(QString table, int count)
{
    auto&& objects = all( table, count );

    QList<qint64> ids;
    for ( auto& entry : objects )
        ids.append( entry["rowid"].toInt() );

    return destroyByIds( table, ids );
}

void JsonStorage::createTable(QString table, QJsonObject obj, QString foreign_key )
{
    QSqlQuery query( _db );
    QStringList fields;

    //Foreign key?  Insert it into the object to be created
    if ( !foreign_key.isEmpty() )
        obj.insert(foreign_key, "int");

    //Rip through foreign keys
    for ( auto& field : obj.keys() )
    {
        auto data_type = DataType::INVALID;

        //Is this an object? recurse!
        if	( obj[field].isObject() )
        {
            data_type = DataType::SINGLE;
            createTable( field, obj[field].toObject(), QString("%1_id").arg(table) );
        }
        else if	( obj[field].isArray() && obj[field].toArray().count() >= 1 )
        {
            auto&& tmp = obj[field].toArray().at(0).toObject();
            data_type = DataType::MANY;
            createTable( depluralizer( field ), tmp, QString("%1_id").arg(table) );
        }
        else
        {
            data_type = fromJObjToDataType( obj[field].toString() );
            if ( data_type == INVALID )
                continue;

            fields.append(QString("%1 %2").arg(field).arg(toSqlType(data_type)));
        }

        //Build up the meta info and the table info
        query.exec(QString("insert into meta_info ('table_name', 'field', 'data_type') values ('%1', '%2', '%3')").
                        arg(table).
                        arg(field).
                        arg(fromDataType(data_type)));

        //Build out the schema
        if ( !_schema.contains( table ) )
            _schema.insert( table, QHash<QString, DataType>() );
        _schema[table].insert( field, data_type );
    }

    //Create the table!
    query.exec( QString("create table %1 (%2)").arg(table).arg(fields.join(", ")));
}

QJsonValue JsonStorage::toJsonValue(DataType type, QVariant value )
{
    switch ( type )
    {
        case INT:
            return QJsonValue( value.toInt() );

        case BOOL:
            return QJsonValue( value.toBool() );

        case DOUBLE:
            return QJsonValue( value.toDouble() );

        case STRING:
            return QJsonValue( value.toString() );

        case LONG:
            return QJsonValue( value.toLongLong() );

        default:
            return QJsonValue();
    }
}

QVariant JsonStorage::toVariant(DataType type, QJsonValue value )
{
    switch ( type )
    {
        case INT:
            return QVariant( value.toInt() );

        case BOOL:
            return QVariant( value.toBool() );

        case DOUBLE:
            return QVariant( value.toDouble() );

        case STRING:
            return QVariant( value.toString() );

        case LONG:
            return QVariant( static_cast<qint64>( value.toDouble() ));

        default:
            return QVariant();
    }
}

JsonStorage::DataType JsonStorage::fromJObjToDataType(QString name)
{
    //Create entries
    if 		( name == "int")
        return INT;

    else if ( name == "bool" )
        return BOOL;

    else if ( name == "double" )
        return DOUBLE;

    else if ( name == "QString" )
        return STRING;

    else if ( name == "qint64" )
        return LONG;

    else
        return INVALID;
}

JsonStorage::DataType JsonStorage::toDataType(QString name)
{
    //Create entries
    if 		( name == "INT")
        return INT;

    else if ( name == "BOOL" )
        return BOOL;

    else if ( name == "DOUBLE" )
        return DOUBLE;

    else if ( name == "STRING" )
        return STRING;

    else if ( name == "LONG" )
        return LONG;

    else if ( name == "SINGLE" )
        return SINGLE;

    else if ( name == "MANY" )
        return MANY;

    else
        return INVALID;
}

QString JsonStorage::fromDataType(JsonStorage::DataType data_type )
{
    //Create entries
    switch (data_type)
    {
        case INT:
            return "INT";

        case BOOL:
            return "BOOL";

        case DOUBLE:
            return "DOUBLE";

        case STRING:
            return "STRING";

        case LONG:
            return "LONG";

        case SINGLE:
            return "SINGLE";

        case MANY:
            return "MANY";

        default:
            return "INVALID";
    }
}

QString JsonStorage::toSqlType(DataType data_type)
{
    switch ( data_type )
    {
        case INT:
            return "INTEGER";

        case BOOL:
            return "TINYINT";

        case DOUBLE:
            return "DOUBLE";

        case STRING:
            return "VARCHAR(64)";

        case LONG:
            return "BIGINT";

        default:
            return QString();
    }
}

QString JsonStorage::depluralizer( QString plural )
{
    if ( plural == "people" )
        return "person";
    else
    {
        plural.chop(1);
        return plural;
    }
}
