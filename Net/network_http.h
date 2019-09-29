#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QPointer>
#include <QTimer>
#include <QMutex>

#include <Shared/mailbox.h>
#include <Util/lock.h>
#include <Util/stopwatch.h>

namespace NetworkHttpStateTypes
{
    Q_NAMESPACE
    enum NetworkHttpStateType
    {
        DISCONNECTED,
        ONLINE,
    };
}

  //! \brief My connection to the server
class NetworkHttp : public QObject
{
    Q_OBJECT

    public:
    //Callback information
    struct Callback
    {
        QString Url;
        std::function<void ( QJsonObject& )> Success = nullptr;
        std::function<void ( QJsonObject& )> Failed = nullptr;
        std::function<void ()> Timeout = nullptr;
        Stopwatch Timestamp;
    };

    //Define the method
    enum Method {
        GET,
        POST
    };

    //How many packet misses can happen before we are considered offline
    static const int PACKET_LOSS_MAX = 2;

    private:
    //! \brief The remote host server I talk to
    QString _remoteHost;
    quint16 _port = 80;
    //Timeout check
    QTimer _timer;
    //Mutex!
    QMutex _lock;
    Mailbox* _mailbox = nullptr;

    //Milla seconds
    int _timeout = 10000;
    int _packetLossCount = 0;

    // My gateway to the server
    QNetworkAccessManager _gateway;
    // a hash of all my network reply requests
    QHash<QNetworkReply*, Callback> _responseHash;

    public:
    // init my object
    NetworkHttp( Mailbox* mailbox );

    //Setup the host name
    void setHost( QString host, quint16 port = 80 );

    //Set the timeout
    void setTimeout( int timeout );

    // Send a get request
    bool get( QString addr, QJsonObject json = QJsonObject(),
              std::function<void (QJsonObject&)> success = nullptr,
              std::function<void (QJsonObject&)> failed = nullptr,
              std::function<void ()> timeout = nullptr );

    // Send a post request
    bool post( QString addr, QJsonObject json = QJsonObject(),
               std::function<void (QJsonObject&)> success = nullptr,
               std::function<void (QJsonObject&)> failed = nullptr,
               std::function<void ()> timeout = nullptr );

    private:
    // Handle network actions
    bool handleMessage( Method method, QString url, QByteArray& data,
                        std::function<void (QJsonObject&)> success,
                        std::function<void (QJsonObject&)> failed,
                        std::function<void ()> timeout );

    // Return a java value inside a qstring no matter what type it was
    QString valueToString( const QJsonValue& value );
    // Convert orm to url ready data
    QString convertData( QJsonObject& json );

    protected slots:
    // called when I got a new response back
    void replyFinished( QNetworkReply* reply );

    //Check for timeouts
    void timeout();
};

#endif
