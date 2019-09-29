// Generated file.
// Edit CodeGenerators/api.py, then run ./export_api.py ..

#ifndef TEST_API_H
#define TEST_API_H

#include <Json/json_struct.h>
#include <Shared/mailbox.h>
#include <QQueue>

class TestApiControl
{
    private:
    QQueue<QString>* _queue;

    public:
    TestApiControl( QQueue<QString>* queue );

    void resetTestCallbacks();

    std::function<void (std::function<void (JChallenge&)>, std::function<void (JErr&, bool)>)> request_challengeCallback = nullptr;
    void request_challenge(
             std::function<void (JChallenge&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    std::function<void (QString, std::function<void (JMagicKey&)>, std::function<void (JErr&, bool)>)> download_magic_keyCallback = nullptr;
    void download_magic_key( QString challenge,
             std::function<void (JMagicKey&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    std::function<void (QString, std::function<void (JEmpty&)>, std::function<void (JErr&, bool)>)> toggle_doorCallback = nullptr;
    void toggle_door( QString challenge_response,
             std::function<void (JEmpty&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    std::function<void (QString, std::function<void (JDoorStatus&)>, std::function<void (JErr&, bool)>)> door_statusCallback = nullptr;
    void door_status( QString challenge_response,
             std::function<void (JDoorStatus&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );
};

class ApiInterface : public QObject
{
    Q_OBJECT

    private:
    bool _networkOnline = false;

    public:

    QQueue<QString> Actions;

    static const int MAJOR = 1;
    static const int MINOR = 0;

    ApiInterface( Mailbox* mailbox );

    void resetTestCallbacks();

    bool isOnline();

    TestApiControl Control;

    public slots:

    void onNetworkStatusChanged( bool online );
};

#endif
