// Generated file.
// Edit CodeGenerators/api.py, then run ./export_api.py ..

#ifdef API_PICKER
#include <functional>
#include <Net/net_api.h>
#include <Json/json_struct.h>
#include <Util/api_util.h>
#include <QQmlEngine>

ApiControl::ApiControl( NetworkHttp* network ) : _http( network ) {}

void ApiControl::request_challenge(
                std::function<void (JChallenge&)> success,
                std::function<void (JErr&, bool)> failed )
{
    auto&& data = QJsonObject();
    _http->post( "/control/request_challenge/", data,
                 [=](QJsonObject& js) {
                     auto json_result = false;
                     auto resp = JChallenge::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/request_challenge/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed != nullptr )
                             failed( err, false );
                         else if ( err_result )
                             qDebug("Error on /control/request_challenge/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/request_challenge/");
                         return;
                     }
                     if ( success != nullptr )
                         success( resp );
                     else
                         qDebug("Successful: /control/request_challenge/" );
                 },
                 [=](QJsonObject& js ) {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed != nullptr )
                         failed( err, false );
                     else if ( err_result )
                         qDebug("Error on /control/request_challenge/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/request_challenge/");
                 },
                 [=]() {
                     if ( failed != nullptr )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         failed( err, true );
                     }
                     else
                         qDebug("Timeout without callback on /control/request_challenge/");
                 } );
}

void ApiControl::download_magic_key( QString challenge,
                std::function<void (JMagicKey&)> success,
                std::function<void (JErr&, bool)> failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge", challenge);
    _http->post( "/control/download_magic_key/", data,
                 [=](QJsonObject& js) {
                     auto json_result = false;
                     auto resp = JMagicKey::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/download_magic_key/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed != nullptr )
                             failed( err, false );
                         else if ( err_result )
                             qDebug("Error on /control/download_magic_key/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/download_magic_key/");
                         return;
                     }
                     if ( success != nullptr )
                         success( resp );
                     else
                         qDebug("Successful: /control/download_magic_key/" );
                 },
                 [=](QJsonObject& js ) {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed != nullptr )
                         failed( err, false );
                     else if ( err_result )
                         qDebug("Error on /control/download_magic_key/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/download_magic_key/");
                 },
                 [=]() {
                     if ( failed != nullptr )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         failed( err, true );
                     }
                     else
                         qDebug("Timeout without callback on /control/download_magic_key/");
                 } );
}

void ApiControl::toggle_door( QString challenge_response,
                std::function<void (JEmpty&)> success,
                std::function<void (JErr&, bool)> failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge_response", challenge_response);
    _http->post( "/control/toggle_door/", data,
                 [=](QJsonObject& js) {
                     auto json_result = false;
                     auto resp = JEmpty::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/toggle_door/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed != nullptr )
                             failed( err, false );
                         else if ( err_result )
                             qDebug("Error on /control/toggle_door/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/toggle_door/");
                         return;
                     }
                     if ( success != nullptr )
                         success( resp );
                     else
                         qDebug("Successful: /control/toggle_door/" );
                 },
                 [=](QJsonObject& js ) {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed != nullptr )
                         failed( err, false );
                     else if ( err_result )
                         qDebug("Error on /control/toggle_door/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/toggle_door/");
                 },
                 [=]() {
                     if ( failed != nullptr )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         failed( err, true );
                     }
                     else
                         qDebug("Timeout without callback on /control/toggle_door/");
                 } );
}

void ApiControl::door_status( QString challenge_response,
                std::function<void (JDoorStatus&)> success,
                std::function<void (JErr&, bool)> failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge_response", challenge_response);
    _http->post( "/control/door_status/", data,
                 [=](QJsonObject& js) {
                     auto json_result = false;
                     auto resp = JDoorStatus::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/door_status/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed != nullptr )
                             failed( err, false );
                         else if ( err_result )
                             qDebug("Error on /control/door_status/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/door_status/");
                         return;
                     }
                     if ( success != nullptr )
                         success( resp );
                     else
                         qDebug("Successful: /control/door_status/" );
                 },
                 [=](QJsonObject& js ) {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed != nullptr )
                         failed( err, false );
                     else if ( err_result )
                         qDebug("Error on /control/door_status/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/door_status/");
                 },
                 [=]() {
                     if ( failed != nullptr )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         failed( err, true );
                     }
                     else
                         qDebug("Timeout without callback on /control/door_status/");
                 } );
}

void ApiControlQml::loadEngine( NetworkHttp* http, QJSEngine* engine )
{
    _http = http;
    _engine = engine;
}

void ApiControlQml::request_challenge(
                QJSValue success,
                QJSValue failed )
{
    auto&& data = QJsonObject();
    _http->post( "/control/request_challenge/", data,
                 [=](QJsonObject& js) mutable {
                     auto json_result = false;
                     JChallenge::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/request_challenge/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed.isCallable() )
                             callQJSValue( failed, _engine, QJsonValue( js ) );
                         else if ( err_result )
                             qDebug("Error on /control/request_challenge/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/request_challenge/");
                         return;
                     }
                     if ( success.isCallable() )
                         callQJSValue( success, _engine, QJsonValue( js ) );
                 },
                 [=](QJsonObject& js ) mutable {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed.isCallable() )
                         callQJSValue( failed, _engine, QJsonValue( js ), QJsonValue( false ) );
                     else if ( err_result )
                         qDebug("Error on /control/request_challenge/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/request_challenge/");
                 },
                 [=]() mutable {
                     if ( failed.isCallable() )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         callQJSValue( failed, _engine, QJsonValue( err.toJson() ), QJsonValue( true ) );
                     }
                     else
                         qDebug("Timeout without callback on /control/request_challenge/");
                 } );
}

void ApiControlQml::download_magic_key( QString challenge,
                QJSValue success,
                QJSValue failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge", challenge);
    _http->post( "/control/download_magic_key/", data,
                 [=](QJsonObject& js) mutable {
                     auto json_result = false;
                     JMagicKey::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/download_magic_key/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed.isCallable() )
                             callQJSValue( failed, _engine, QJsonValue( js ) );
                         else if ( err_result )
                             qDebug("Error on /control/download_magic_key/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/download_magic_key/");
                         return;
                     }
                     if ( success.isCallable() )
                         callQJSValue( success, _engine, QJsonValue( js ) );
                 },
                 [=](QJsonObject& js ) mutable {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed.isCallable() )
                         callQJSValue( failed, _engine, QJsonValue( js ), QJsonValue( false ) );
                     else if ( err_result )
                         qDebug("Error on /control/download_magic_key/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/download_magic_key/");
                 },
                 [=]() mutable {
                     if ( failed.isCallable() )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         callQJSValue( failed, _engine, QJsonValue( err.toJson() ), QJsonValue( true ) );
                     }
                     else
                         qDebug("Timeout without callback on /control/download_magic_key/");
                 } );
}

void ApiControlQml::toggle_door( QString challenge_response,
                QJSValue success,
                QJSValue failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge_response", challenge_response);
    _http->post( "/control/toggle_door/", data,
                 [=](QJsonObject& js) mutable {
                     auto json_result = false;
                     JEmpty::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/toggle_door/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed.isCallable() )
                             callQJSValue( failed, _engine, QJsonValue( js ) );
                         else if ( err_result )
                             qDebug("Error on /control/toggle_door/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/toggle_door/");
                         return;
                     }
                     if ( success.isCallable() )
                         callQJSValue( success, _engine, QJsonValue( js ) );
                 },
                 [=](QJsonObject& js ) mutable {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed.isCallable() )
                         callQJSValue( failed, _engine, QJsonValue( js ), QJsonValue( false ) );
                     else if ( err_result )
                         qDebug("Error on /control/toggle_door/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/toggle_door/");
                 },
                 [=]() mutable {
                     if ( failed.isCallable() )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         callQJSValue( failed, _engine, QJsonValue( err.toJson() ), QJsonValue( true ) );
                     }
                     else
                         qDebug("Timeout without callback on /control/toggle_door/");
                 } );
}

void ApiControlQml::door_status( QString challenge_response,
                QJSValue success,
                QJSValue failed )
{
    auto&& data = QJsonObject();
    data.insert("challenge_response", challenge_response);
    _http->post( "/control/door_status/", data,
                 [=](QJsonObject& js) mutable {
                     auto json_result = false;
                     JDoorStatus::fromJson( &js, &json_result );
                     if ( !json_result ) {
                         qDebug("Failed to map json /control/door_status/");
                         auto err_result = false;
                         auto err = JErr::fromJson( &js, &err_result );
                         if ( failed.isCallable() )
                             callQJSValue( failed, _engine, QJsonValue( js ) );
                         else if ( err_result )
                             qDebug("Error on /control/door_status/: %s", err.reason.toLatin1().data());
                         else
                             qDebug("Error without callback on /control/door_status/");
                         return;
                     }
                     if ( success.isCallable() )
                         callQJSValue( success, _engine, QJsonValue( js ) );
                 },
                 [=](QJsonObject& js ) mutable {
                     auto err_result = false;
                     auto err = JErr::fromJson( &js, &err_result );
                     if ( failed.isCallable() )
                         callQJSValue( failed, _engine, QJsonValue( js ), QJsonValue( false ) );
                     else if ( err_result )
                         qDebug("Error on /control/door_status/: %s", err.reason.toLatin1().data());
                     else
                         qDebug("Error without callback on /control/door_status/");
                 },
                 [=]() mutable {
                     if ( failed.isCallable() )
                     {
                         JErr err;
                         err.successful = false;
                         err.reason = "Timeout occurred";
                         callQJSValue( failed, _engine, QJsonValue( err.toJson() ), QJsonValue( true ) );
                     }
                     else
                         qDebug("Timeout without callback on /control/door_status/");
                 } );
}

ApiInterface::ApiInterface( NetworkHttp* http, Mailbox* mailbox ) : 
    _http( http ),
    Control( http )
{
    QObject::connect( mailbox, &Mailbox::networkStatusChanged, this, &ApiInterface::onNetworkStatusChanged );
}

void ApiInterface::loadEngine( QJSEngine* engine )
{
    qmlRegisterType<ApiControlQml>( "GarageDoor", 1, 0, "ApiControlQml");
    _controlQml.loadEngine( _http, engine );
}

bool ApiInterface::isOnline()
{
    return _networkOnline;
}

ApiControlQml* ApiInterface::_control()
{
    return &_controlQml;
}

void ApiInterface::onNetworkStatusChanged( bool online )
{
    _networkOnline = online;
}
#endif
