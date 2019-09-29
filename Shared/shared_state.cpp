#include "shared_state.h"

#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

static const char* filename = "settings.json";

SharedState::SharedState( Mailbox* mailbox,
                          MailboxQml* mailbox_qml,
                          ApiInterface* api ) :
    Mail( mailbox ),
    MailQml( mailbox_qml ),
    Api( api )
{
    QObject::connect( Mail, &Mailbox::updateSession, this, &SharedState::onUpdateSession );

    //Load the session
    loadSession();
}


QVariant SharedState::getSession()
{
    return QVariant( Sess.toJson() );
}

//Setup the session object
bool SharedState::loadSession()
{
    QString path = QStandardPaths::standardLocations( QStandardPaths::AppDataLocation ).value(0);

    //iOS happy
    QDir myDir(path);
    if (!myDir.exists()) {
        myDir.mkpath(path);
    }
    QDir::setCurrent(path);

    //Load up the file
    auto&& file = QFile( filename );
    if ( !file.open(QIODevice::ReadOnly))
        return false;

    auto&& json = QJsonDocument::fromJson( file.readAll() );
    if ( !json.isObject() )
        return false;

    //Load up the object
    auto&& pin = json.object();
    Sess = JSession::fromJson( &pin );

    return !Sess.magic_key.isEmpty();
}

bool SharedState::saveSession()
{
    auto data = QJsonDocument( Sess.toJson() ).toJson();

    //Open files
    auto&& file = QFile( filename );
    if ( !file.open(QIODevice::WriteOnly))
        return false;

    //Write out the data
    return file.write( data.data(), data.length() ) == data.length();
}


//*** Slots

void SharedState::onUpdateSession( JSession sess )
{
    auto&& pin = sess.toJson();
    Sess = JSession::fromJson( &pin );
    saveSession();
}
