// Generated file.
// Edit CodeGenerators/mailbox.py, then run ./export_mailbox.py ..

#include "mailbox.h"
#include "mailbox_qml.h"
#include <QJsonDocument>
#include <QTimer>
        
MailboxQml::MailboxQml( QObject *parent) : 
    QObject(parent)
{}


void MailboxQml::loadEngine( QJSEngine* engine )
{
    _engine = engine;
}

void MailboxQml::loadSibling( Mailbox* sibling )
{
    _sibling = sibling;
}


//*** System

void MailboxQml::emitApplicationStateChanged( bool online )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitApplicationStateChanged( online );
    }
    else
        qDebug("No sibling loaded: emitApplicationStateChanged()");
}


//*** Network

void MailboxQml::emitPacketLossDetected( int count )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitPacketLossDetected( count );
    }
    else
        qDebug("No sibling loaded: emitPacketLossDetected()");
}

void MailboxQml::emitNetworkStatusChanged( bool online )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitNetworkStatusChanged( online );
    }
    else
        qDebug("No sibling loaded: emitNetworkStatusChanged()");
}


//*** UI

void MailboxQml::emitUiLoaded(  )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitUiLoaded(  );
    }
    else
        qDebug("No sibling loaded: emitUiLoaded()");
}

void MailboxQml::emitCopyToClipboard( QString msg )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitCopyToClipboard( msg );
    }
    else
        qDebug("No sibling loaded: emitCopyToClipboard()");
}

void MailboxQml::emitUpdateSession( QJSValue sess )
{
    if ( _sibling != nullptr ) {

        //Pass to CPP mailbox to actually deliver the message.
        _sibling->emitUpdateSession( JSession::fromQJSValue( &sess ) );
    }
    else
        qDebug("No sibling loaded: emitUpdateSession()");
}


//*** Mobile

void MailboxQml::emitPushForm( QString qml_file, QJSValue args )
{
    if ( Debug ) qDebug("MAILBOX -> pushForm( qml_file{%s}, args{variant} )", qml_file.toUtf8().data());

    emit this->pushForm( qml_file, args );
}

void MailboxQml::emitReplaceForm( QString qml_file, QJSValue args )
{
    if ( Debug ) qDebug("MAILBOX -> replaceForm( qml_file{%s}, args{variant} )", qml_file.toUtf8().data());

    emit this->replaceForm( qml_file, args );
}

void MailboxQml::emitPopForm(  )
{
    if ( Debug ) qDebug("MAILBOX -> popForm(  )");

    emit this->popForm(  );
}

void MailboxQml::emitCurrentForm( QString qml_file )
{
    if ( Debug ) qDebug("MAILBOX -> currentForm( qml_file{%s} )", qml_file.toUtf8().data());

    emit this->currentForm( qml_file );
}

void MailboxQml::emitToast( QString msg, int duration )
{
    if ( Debug ) qDebug("MAILBOX -> toast( msg{%s}, duration{%d} )", msg.toUtf8().data(), duration);

    emit this->toast( msg, duration );
}

