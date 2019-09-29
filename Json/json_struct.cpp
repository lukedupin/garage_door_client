// Generated file.
// Edit Scripts/json.py, then run ./export_struct.py ..

#include <Json/json_struct.h>
#include <Util/api_util.h>

JErr JErr::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JErr JErr::fromJson( QJsonObject* obj, bool* successful )
{
    JErr result;
    int hits = 0;

    if ( obj->contains( "successful" ) )
    {
        hits++;
        result.successful = (*obj)["successful"].toBool();
    }
    if ( obj->contains( "reason" ) )
    {
        hits++;
        result.reason = (*obj)["reason"].toString();
    }

    if ( successful != nullptr ) *successful = (hits == 2);

    return result;
}

JErr JErr::fromQJSValue( QJSValue* obj, bool* successful )
{
    JErr result;
    int hits = 0;

    if ( obj->hasProperty( "successful" ) )
    {
        hits++;
        result.successful = obj->property("successful").toBool();
    }
    if ( obj->hasProperty( "reason" ) )
    {
        hits++;
        result.reason = obj->property("reason").toString();
    }

    if ( successful != nullptr ) *successful = (hits == 2);

    return result;
}

QList<JErr> JErr::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JErr> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JErr::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JErr> JErr::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JErr> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JErr::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JErr::toArray( QList<JErr>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JErr::toJson()
{
    QJsonObject result;

    result.insert( "successful", QJsonValue(successful) );
    result.insert( "reason", QJsonValue(reason) );

    return result;
}
QJsonObject JErr::describeObject()
{
    QJsonObject result;

    result.insert( "successful", QJsonValue("bool") );
    result.insert( "reason", QJsonValue("QString") );

    return result;
}

JEmpty JEmpty::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JEmpty JEmpty::fromJson( QJsonObject* obj, bool* successful )
{
    JEmpty result;
    int hits = 0;

    Q_UNUSED(obj)

    if ( successful != nullptr ) *successful = (hits == 0);

    return result;
}

JEmpty JEmpty::fromQJSValue( QJSValue* obj, bool* successful )
{
    JEmpty result;
    int hits = 0;

    Q_UNUSED(obj)

    if ( successful != nullptr ) *successful = (hits == 0);

    return result;
}

QList<JEmpty> JEmpty::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JEmpty> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JEmpty::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JEmpty> JEmpty::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JEmpty> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JEmpty::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JEmpty::toArray( QList<JEmpty>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JEmpty::toJson()
{
    QJsonObject result;


    return result;
}
QJsonObject JEmpty::describeObject()
{
    QJsonObject result;


    return result;
}

JMagicKey JMagicKey::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JMagicKey JMagicKey::fromJson( QJsonObject* obj, bool* successful )
{
    JMagicKey result;
    int hits = 0;

    if ( obj->contains( "magic_key" ) )
    {
        hits++;
        result.magic_key = (*obj)["magic_key"].toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

JMagicKey JMagicKey::fromQJSValue( QJSValue* obj, bool* successful )
{
    JMagicKey result;
    int hits = 0;

    if ( obj->hasProperty( "magic_key" ) )
    {
        hits++;
        result.magic_key = obj->property("magic_key").toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

QList<JMagicKey> JMagicKey::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JMagicKey> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JMagicKey::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JMagicKey> JMagicKey::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JMagicKey> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JMagicKey::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JMagicKey::toArray( QList<JMagicKey>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JMagicKey::toJson()
{
    QJsonObject result;

    result.insert( "magic_key", QJsonValue(magic_key) );

    return result;
}
QJsonObject JMagicKey::describeObject()
{
    QJsonObject result;

    result.insert( "magic_key", QJsonValue("QString") );

    return result;
}

JChallenge JChallenge::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JChallenge JChallenge::fromJson( QJsonObject* obj, bool* successful )
{
    JChallenge result;
    int hits = 0;

    if ( obj->contains( "challenge" ) )
    {
        hits++;
        result.challenge = (*obj)["challenge"].toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

JChallenge JChallenge::fromQJSValue( QJSValue* obj, bool* successful )
{
    JChallenge result;
    int hits = 0;

    if ( obj->hasProperty( "challenge" ) )
    {
        hits++;
        result.challenge = obj->property("challenge").toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

QList<JChallenge> JChallenge::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JChallenge> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JChallenge::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JChallenge> JChallenge::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JChallenge> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JChallenge::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JChallenge::toArray( QList<JChallenge>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JChallenge::toJson()
{
    QJsonObject result;

    result.insert( "challenge", QJsonValue(challenge) );

    return result;
}
QJsonObject JChallenge::describeObject()
{
    QJsonObject result;

    result.insert( "challenge", QJsonValue("QString") );

    return result;
}

JDoorStatus JDoorStatus::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JDoorStatus JDoorStatus::fromJson( QJsonObject* obj, bool* successful )
{
    JDoorStatus result;
    int hits = 0;

    if ( obj->contains( "status" ) )
    {
        hits++;
        result.status = (*obj)["status"].toBool();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

JDoorStatus JDoorStatus::fromQJSValue( QJSValue* obj, bool* successful )
{
    JDoorStatus result;
    int hits = 0;

    if ( obj->hasProperty( "status" ) )
    {
        hits++;
        result.status = obj->property("status").toBool();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

QList<JDoorStatus> JDoorStatus::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JDoorStatus> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JDoorStatus::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JDoorStatus> JDoorStatus::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JDoorStatus> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JDoorStatus::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JDoorStatus::toArray( QList<JDoorStatus>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JDoorStatus::toJson()
{
    QJsonObject result;

    result.insert( "status", QJsonValue(status) );

    return result;
}
QJsonObject JDoorStatus::describeObject()
{
    QJsonObject result;

    result.insert( "status", QJsonValue("bool") );

    return result;
}

JSession JSession::fromJson( QJsonObject&& obj, bool* successful )
{
    return fromJson( &obj, successful );
}
JSession JSession::fromJson( QJsonObject* obj, bool* successful )
{
    JSession result;
    int hits = 0;

    if ( obj->contains( "magic_key" ) )
    {
        hits++;
        result.magic_key = (*obj)["magic_key"].toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

JSession JSession::fromQJSValue( QJSValue* obj, bool* successful )
{
    JSession result;
    int hits = 0;

    if ( obj->hasProperty( "magic_key" ) )
    {
        hits++;
        result.magic_key = obj->property("magic_key").toString();
    }

    if ( successful != nullptr ) *successful = (hits == 1);

    return result;
}

QList<JSession> JSession::fromJsonList( QList<QJsonObject>&& ary, bool* successful )
{
    QList<JSession> result;
    bool succ = true;

    for ( auto& entry : ary ) {
        bool tmp = false;
        result.append( JSession::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QList<JSession> JSession::fromJsonList( QList<QJsonObject>* ary, bool* successful )
{
    QList<JSession> result;
    bool succ = true;

    for ( auto& entry : *ary ) {
        bool tmp = false;
        result.append( JSession::fromJson( &entry, &tmp ) );
        succ &= tmp;
    }

    if ( successful != nullptr ) *successful = succ;

    return result;
}

QJsonArray JSession::toArray( QList<JSession>* ary )
{
    QVariantList result;

    for ( auto& entry : *ary )
        result.append( entry.toJson() );

    return QJsonArray::fromVariantList( result );
}

QJsonObject JSession::toJson()
{
    QJsonObject result;

    result.insert( "magic_key", QJsonValue(magic_key) );

    return result;
}
QJsonObject JSession::describeObject()
{
    QJsonObject result;

    result.insert( "magic_key", QJsonValue("QString") );

    return result;
}

void apiStructRegister()
{
    qRegisterMetaType<JErr>( "JErr" );
    qRegisterMetaType<QList<JErr>>( "QList<JErr>" );
    qRegisterMetaType<JEmpty>( "JEmpty" );
    qRegisterMetaType<QList<JEmpty>>( "QList<JEmpty>" );
    qRegisterMetaType<JMagicKey>( "JMagicKey" );
    qRegisterMetaType<QList<JMagicKey>>( "QList<JMagicKey>" );
    qRegisterMetaType<JChallenge>( "JChallenge" );
    qRegisterMetaType<QList<JChallenge>>( "QList<JChallenge>" );
    qRegisterMetaType<JDoorStatus>( "JDoorStatus" );
    qRegisterMetaType<QList<JDoorStatus>>( "QList<JDoorStatus>" );
    qRegisterMetaType<JSession>( "JSession" );
    qRegisterMetaType<QList<JSession>>( "QList<JSession>" );
}

