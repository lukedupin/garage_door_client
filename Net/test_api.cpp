// Generated file.
// Edit CodeGenerators/api.py, then run ./export_api.py ..

#ifdef API_PICKER
#include <functional>
#include <Net/test_api.h>
#include <Json/json_struct.h>
#include <Util/api_util.h>
#include <QtTest>

TestApiControl::TestApiControl( QQueue<QString>* queue) : _queue( queue ) {}

void TestApiControl::resetTestCallbacks()
{
    request_challengeCallback = nullptr;
    download_magic_keyCallback = nullptr;
    toggle_doorCallback = nullptr;
    door_statusCallback = nullptr;
}

void TestApiControl::request_challenge(
                std::function<void (JChallenge&)> success,
                std::function<void (JErr&, bool)> failed )
{
    _queue->enqueue("Control->request_challenge");

    if ( request_challengeCallback != nullptr )
        request_challengeCallback( success, failed );
    else
        QVERIFY2(false, "No callback set for Control->request_challenge");
}

void TestApiControl::download_magic_key(
                std::function<void (JMagicKey&)> success,
                std::function<void (JErr&, bool)> failed )
{
    _queue->enqueue("Control->download_magic_key");

    if ( download_magic_keyCallback != nullptr )
        download_magic_keyCallback( success, failed );
    else
        QVERIFY2(false, "No callback set for Control->download_magic_key");
}

void TestApiControl::toggle_door( QString challenge,
                std::function<void (JEmpty&)> success,
                std::function<void (JErr&, bool)> failed )
{
    _queue->enqueue("Control->toggle_door");

    if ( toggle_doorCallback != nullptr )
        toggle_doorCallback( challenge, success, failed );
    else
        QVERIFY2(false, "No callback set for Control->toggle_door");
}

void TestApiControl::door_status( QString challenge,
                std::function<void (JDoorStatus&)> success,
                std::function<void (JErr&, bool)> failed )
{
    _queue->enqueue("Control->door_status");

    if ( door_statusCallback != nullptr )
        door_statusCallback( challenge, success, failed );
    else
        QVERIFY2(false, "No callback set for Control->door_status");
}

ApiInterface::ApiInterface( Mailbox* mailbox ) : 
    Control( &Actions )
{
    QObject::connect( mailbox, &Mailbox::networkStatusChanged, this, &ApiInterface::onNetworkStatusChanged );
}

void ApiInterface::resetTestCallbacks()
{
    Control.resetTestCallbacks();
}

bool ApiInterface::isOnline()
{
    return _networkOnline;
}

void ApiInterface::onNetworkStatusChanged( bool online )
{
    _networkOnline = online;
}
#endif
