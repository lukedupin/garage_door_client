// Generated file.
// Edit CodeGenerators/mailbox.py, then run ./export_mailbox.py ..

#include "mailbox.h"
#include "mailbox_qml.h"
#include <QJsonDocument>
#include <QTimer>
        
Mailbox::Mailbox( QObject *parent) : 
    QObject(parent)
{}


void Mailbox::loadEngine( QJSEngine* engine )
{
    _engine = engine;
}

void Mailbox::loadSibling( MailboxQml* sibling )
{
    _sibling = sibling;
}


//*** System

void Mailbox::_emitApplicationStateChanged( bool online )
{
    if ( _sibling != nullptr ) {

        emit _sibling->applicationStateChanged( online );
    }
    emit this->applicationStateChanged( online );
}
void Mailbox::emitApplicationStateChanged( bool online )
{ _emitApplicationStateChanged( online ); }


//*** Network

void Mailbox::_emitPacketLossDetected( int count )
{
    if ( _sibling != nullptr ) {

        emit _sibling->packetLossDetected( count );
    }
    emit this->packetLossDetected( count );
}
void Mailbox::emitPacketLossDetected( int count )
{ _emitPacketLossDetected( count ); }

void Mailbox::_emitNetworkStatusChanged( bool online )
{
    if ( _sibling != nullptr ) {

        emit _sibling->networkStatusChanged( online );
    }
    emit this->networkStatusChanged( online );
}
void Mailbox::emitNetworkStatusChanged( bool online )
{ _emitNetworkStatusChanged( online ); }


//*** UI

void Mailbox::_emitUiLoaded(  )
{
    if ( _sibling != nullptr ) {

        emit _sibling->uiLoaded(  );
    }
    emit this->uiLoaded(  );
}
void Mailbox::emitUiLoaded(  )
{ _emitUiLoaded(); }

void Mailbox::_emitCopyToClipboard( QString msg )
{
    if ( _sibling != nullptr ) {

        emit _sibling->copyToClipboard( msg );
    }
    emit this->copyToClipboard( msg );
}
void Mailbox::emitCopyToClipboard( QString msg )
{ _emitCopyToClipboard( msg ); }

void Mailbox::_emitUpdateSession( JSession sess )
{
    if ( _sibling != nullptr ) {

        emit _sibling->updateSession( QVariant( sess.toJson() ) );
    }
    emit this->updateSession( sess );
}
void Mailbox::emitUpdateSession( JSession sess )
{ _emitUpdateSession( sess ); }


//*** Mobile

