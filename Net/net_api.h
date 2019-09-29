// Generated file.
// Edit CodeGenerators/api.py, then run ./export_api.py ..

#ifndef NET_API_H
#define NET_API_H

#include <Json/json_struct.h>
#include <Net/network_http.h>
#include <QJSValue>

class ApiControl
{
    private:
    NetworkHttp* _http = nullptr;

    public:
    ApiControl( NetworkHttp* http );

    void request_challenge(
             std::function<void (JChallenge&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    void download_magic_key( QString challenge,
             std::function<void (JMagicKey&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    void toggle_door( QString challenge_response,
             std::function<void (JEmpty&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );

    void door_status( QString challenge_response,
             std::function<void (JDoorStatus&)> success = nullptr,
             std::function<void (JErr&, bool)> failed = nullptr );
};

class ApiControlQml : public QObject
{
    Q_OBJECT

    private:
    NetworkHttp* _http = nullptr;
    QJSEngine* _engine = nullptr;

    public:

    void loadEngine( NetworkHttp* http, QJSEngine* engine );

    Q_INVOKABLE void request_challenge(
                             QJSValue success = QJSValue(), QJSValue failed = QJSValue() );

    Q_INVOKABLE void download_magic_key( QString challenge,
                             QJSValue success = QJSValue(), QJSValue failed = QJSValue() );

    Q_INVOKABLE void toggle_door( QString challenge_response,
                             QJSValue success = QJSValue(), QJSValue failed = QJSValue() );

    Q_INVOKABLE void door_status( QString challenge_response,
                             QJSValue success = QJSValue(), QJSValue failed = QJSValue() );
};

class ApiInterface : public QObject
{
    Q_OBJECT

    private:
    NetworkHttp* _http = nullptr;
    bool _networkOnline = false;

    public:

    static const int MAJOR = 1;
    static const int MINOR = 0;

    ApiInterface( NetworkHttp* http, Mailbox* mailbox );

    void loadEngine( QJSEngine* engine );

    Q_INVOKABLE bool isOnline();

    ApiControl Control;

    Q_PROPERTY( ApiControlQml* Control READ _control )
    ApiControlQml _controlQml;
    ApiControlQml* _control();

    private slots:

    void onNetworkStatusChanged( bool online );
};

#endif
