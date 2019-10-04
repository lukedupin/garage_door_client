#include <QUrl>
#include <QStringList>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStringList>

#include "network_http.h"
#include <Util/stopwatch.h>

  //Create my network
NetworkHttp::NetworkHttp( Mailbox* mailbox ) :
    _mailbox( mailbox )
{
    //Connect my signals and slots
    QObject::connect( &_gateway, &QNetworkAccessManager::finished,
                      this, &NetworkHttp::replyFinished );
    QObject::connect( &_timer, &QTimer::timeout,
                      this, &NetworkHttp::timeout );

    QObject::connect( &_gateway ,&QNetworkAccessManager::networkAccessibleChanged,
                      [&] (QNetworkAccessManager::NetworkAccessibility access ) {
                            switch ( access )
                            {
                                default:
                                case QNetworkAccessManager::UnknownAccessibility:
                                    qDebug("The network accessibility cannot be determined. [ %d ]", access);
                                    break;

                                case QNetworkAccessManager::NotAccessible:
                                   qDebug("The network is not currently accessible.");
                                   break;

                                case QNetworkAccessManager::Accessible:
                                    qDebug("Network is accessible");
                                    break;
                            }

                            //Update the accessibility
                            _gateway.setNetworkAccessible(QNetworkAccessManager::Accessible);
                      });

    //Start the timer running once a second
    _timer.start(1000);
}

void NetworkHttp::setHost( QString host, quint16 port )
{
    _remoteHost = host;
    _port = port;
}

void NetworkHttp::setTimeout( int timeout )
{
    _timeout = timeout;
}

  //Get a request from the user
bool NetworkHttp::get( QString addr, QJsonObject vars,
                       std::function<void (QJsonObject&)> success,
                       std::function<void (QJsonObject&)> failed,
                       std::function<void ()> timeout )
{
    QString url = QString("http://%1:%2%3").arg(_remoteHost).arg(_port).arg(addr);
    if ( vars.size() > 0 )
        url.append( QString("?%1").arg( convertData( vars)));

    //No add actions, everything is in the url
    QByteArray data;

    return handleMessage( GET, url, data, success, failed, timeout );
}

  //Post a request to the server
bool NetworkHttp::post( QString addr, QJsonObject vars,
                        std::function<void (QJsonObject&)> success,
                        std::function<void (QJsonObject&)> failed,
                        std::function<void ()> timeout )
{
    QString url = QString("http://%1:%2%3").arg(_remoteHost).arg(_port).arg(addr);

    //Push on the variables
    QByteArray data;
    if ( vars.size() > 0 )
        data = convertData( vars ).toLatin1();

    return handleMessage( POST, url, data, success, failed, timeout );
}

bool NetworkHttp::handleMessage(Method method, QString url, QByteArray &data,
                                std::function<void (QJsonObject &)> success,
                                std::function<void (QJsonObject &)> failed,
                                std::function<void ()> timeout)
{
    //build my request
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    //Setup my callbacks
    Callback callback;
    {
        callback.Url = url;
        callback.Success = success;
        callback.Failed = failed;
        callback.Timeout = timeout;
        callback.Timestamp.start();
    }

    //Required block
    {
        ScopeLock( _lock );

        //Handle the methods
        switch ( method )
        {
            default:
            case GET:
                _responseHash.insert( _gateway.get( request ), callback );
                break;

            case POST:
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
                _responseHash.insert( _gateway.post(request, data), callback );
                break;
        }
    }

    return true;
}

  //Convert a value to string
QString NetworkHttp::valueToString( const QJsonValue& v )
{
    //Based on the json type return the value inside a string
  if ( v.isBool() )
    return QString( v.toBool() ? "true": "false" );
  if ( v.isDouble() )
    return QString::number( v.toDouble(), 'f', 8 );
  if ( v.isString() )
    return v.toString();

    //If we have bulk objects, drop them into json strings and go
  if ( v.isArray() )
    return QString( QJsonDocument( v.toArray()).toJson( QJsonDocument::Compact));
  if ( v.isObject() )
    return QString( QJsonDocument( v.toObject()).toJson( QJsonDocument::Compact));

  return QString("");
}

  //Convert orm_light data to url data
QString NetworkHttp::convertData( QJsonObject& vars )
{
  QStringList list;

     //If the user passed some vars, then write out a url ready var
  if ( vars.size() <= 0 )
    return QString("");

    //Go through each item
  for ( auto key : vars.keys() )
  {
    QJsonValue value = vars[key];

      //Allow one level of objects
    /*
    if ( value.isObject() )
    {
      QJsonObject vars2 = value.toObject();
      QStringList keys2 = vars.keys();
      for ( int r = 0; r < keys2.length(); r++ )
        list.push_back(
          QString("%1%%5B%2%%5D=%3").
            arg( QString( QUrl::toPercentEncoding( key))).
            arg( QString( QUrl::toPercentEncoding( keys2[r]))).
            arg( QString( QUrl::toPercentEncoding( valueToString( vars2[ keys2[r]])))) );
    }

      //Dump the value of the array
    else if ( value.isArray() )
    {
      QJsonArray ary = value.toArray();
      for ( int r = 0; r < ary.size(); r++ )
        list.push_back(
          QString("%1[%2]=%3").
            arg( QString( QUrl::toPercentEncoding( key))).
            arg( r).
            arg( QString( QUrl::toPercentEncoding( valueToString( ary[r])))) );
    }

      //Single value entry
    else
    */
    {
      QString str = QString("%1=%2").
          arg( QString( QUrl::toPercentEncoding( key))).
          arg( QString( QUrl::toPercentEncoding( valueToString( value))));
      //qDebug("%s", str.toLatin1().data());
      list.push_back( str );
    }
  }

  return list.join("&");
}

  //Called by my gateway
void NetworkHttp::replyFinished( QNetworkReply* reply )
{
    if ( reply == nullptr )
        return;

    //Required block
    NetworkHttp::Callback response;
    {
        ScopeLock( _lock );

        //Reclaim memory, this will happen on the UI thread, so we can still use this
        reply->deleteLater();

        //If we do have this key then we emit that data is ready to the user
        if ( !_responseHash.contains( reply ) )
            return;

        //Remove the reply from out list of outstanding requests
        response = _responseHash.take( reply );
    }

    //Pull the data, and then attempt to give the user's callbacks a go
    auto data = reply->readAll();
    auto raw = QJsonDocument::fromJson( data );

    //Even though this is really an error, we want to treat it like a timeout
    //Timeout will cause us to re-connect, and in almost all cases
    //We are hitting this because the server is unreachable
    if ( !raw.isObject() )
    {
        qDebug("%s at %s unreachable error, firing timeout", response.Url.toUtf8().data(), _remoteHost.toUtf8().data() );
        qDebug("Data: %s", data.data());

        if ( response.Timeout != nullptr )
            response.Timeout();
        else
            qDebug("Didn't understand response: %s -> %s",
                         response.Url.toLatin1().data(),
                         data.data());

        //Fire off another packet loss detection
        _packetLossCount++;
        _mailbox->emitPacketLossDetected( _packetLossCount );
        return;
    }

    //We got a response that made sense, must not be a timeout
    if ( _packetLossCount > 0 )
        _mailbox->emitPacketLossDetected( 0 );
    _packetLossCount = 0;

    //Grab the object, if it was a failed request, then send out failed
    auto obj = raw.object();
    if (!obj["successful"].toBool())
    {
        if ( response.Failed != nullptr )
            response.Failed( obj );
        else
            qDebug("Failed reply with no callback");

        return;
    }

    //Successful response!
    if ( response.Success != nullptr )
        response.Success( obj );
}

//Check for timeouts
void NetworkHttp::timeout()
{
    auto&& urls = QStringList();

    int packet_loss = _packetLossCount;

    //Required block
    {
        ScopeLock( _lock );

        //Check for timeouts
        for ( auto key : _responseHash.keys() )
        {
            Stopwatch time;
            time.start();

            //not timed out!
            if ( _responseHash[key].Timestamp.elapsed() < _timeout )
                continue;

            _packetLossCount++;

            //We have timed out, attempt to let teh world know
            if ( _responseHash[key].Timeout != nullptr )
                _responseHash[key].Timeout();
            else
                qDebug("Request timed out without callback");

            urls.append( QString("%1[%2]").arg(_responseHash[key].Url).arg(time.elapsed()) );
            _responseHash.remove(key);
        }
    }

    //Did our packet loss change?
    if ( packet_loss != _packetLossCount )
        _mailbox->emitPacketLossDetected( _packetLossCount );
}
