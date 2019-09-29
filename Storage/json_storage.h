#ifndef JSON_STORAGE_H
#define JSON_STORAGE_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QDir>
#include <QSqlDatabase>
#include <Util/lock.h>

#include <Json/json_struct.h>
#include <functional>

//Allows the user to storage arrays of json objects
class JsonStorage
{
    private:
    enum DataType
    {
        INT,
        BOOL,
        DOUBLE,
        STRING,
        LONG,
        SINGLE,
        MANY,

        INVALID
    };

    QSqlDatabase _db;
    QHash<QString, QHash<QString, DataType>> _schema;
    QMutex _lock;
    QString _collection;
    QString _uid;
    QString _connectionName;

    public:
    //List all collections
    static QList<QString> listCollections( QString collection );

    //Base folder path
    static QString baseFolder( QString collection );

    public:
    ~JsonStorage();

    //Set the collectio name
    bool loadCollection( QString collection, QString uid );

    //Set the collectio name
    bool createCollection( QString collection, QHash<QString, QJsonObject> table, QString uid = QString() );

    //Are we open?
    bool isOpen();

    //Close the capture
    void close();

    //Delete the collection
    bool deleteCollection();

    //Get the number of records for a table
    int count( QString table );

    //True if the row exists
    bool rowExists( QString table, qint64 id );

    //Write out the header
    bool insert( QString table, QJsonObject obj, QString foreign_key = QString(), qint64 parent_id = -1 );
    bool bulkInsert( QString table, QJsonArray obj, QString foreign_key = QString(), qint64 parent_id = -1 );

    //Update data
    bool update( QString table, qint64 id, QJsonObject obj, QString foreign_key = QString(), qint64 parent_id = -1 );

    //Read data!
    QList<QJsonObject> all( QString table, int limit = -1, int offset = -1, bool recursive = true );
    QList<QJsonObject> filter( QString table, QString where, int limit = -1, int offset = -1, bool recursive = true);
    QJsonObject getById( QString table, qint64 id, bool* successful = nullptr, bool recursive = true );

    private:
    //Handles all select statements
    QList<QJsonObject> selectSql( QString table, QString where, int limit = -1, int offset = -1, bool recursive = true);

    public:

    //Delete data
    bool destroyById( QString table, qint64 id );
    bool destroyByIds( QString table, QList<qint64> ids );
    bool destroyWhere( QString table, QString where );
    bool destroyCount( QString table, int count );

    private:
    //Recursively create table logic
    void createTable( QString table, QJsonObject obj, QString foreign_key = QString() );

    private:
    //Convert from qvariant to qjsonvalue, which is a different type of variant
    static QJsonValue toJsonValue( DataType type, QVariant raw );

    //Convert from qvariant to qjsonvalue, which is a different type of variant
    static QVariant toVariant( DataType type, QJsonValue raw );

    //Convert a JsonStruct name into a Datatype
    static DataType toDataType( QString name );

    //Convert a JsonStruct name into a Datatype
    static QString fromDataType( DataType type );

    //Convert a JsonStruct name into a Datatype
    static DataType fromJObjToDataType( QString name );

    //Data type to sql type
    static QString toSqlType( DataType data_type );

    //Depluralization
    static QString depluralizer( QString plural );
};

#endif
