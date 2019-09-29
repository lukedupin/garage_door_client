// Generated file.
// Edit CodeGenerators/mailbox.py, then run ./export_mailbox.py ..

#ifndef MAILBOX_H
#define MAILBOX_H

#include <Json/json_struct.h>

#include <QJSValue>
#include <QObject>
#include <QVariantList>
#include <QTcpSocket>

class MailboxQml;

class Mailbox : public QObject
{
    Q_OBJECT

    public:
    static const int MAJOR = 1;
    static const int MINOR = 0;
    
    //Set to true for message logging
    bool Debug = false;
    
    private:
    MailboxQml* _sibling = nullptr;
    QJSEngine* _engine = nullptr;

    public:
    explicit Mailbox( QObject *parent = nullptr);
    
    void loadSibling( MailboxQml* sibling );
    
    void loadEngine( QJSEngine* engine );
   
    private:

    //*** Private System

    void _emitApplicationStateChanged( bool online );


    //*** Private Network

    void _emitPacketLossDetected( int count );
    void _emitNetworkStatusChanged( bool online );


    //*** Private UI

    void _emitUiLoaded(  );
    void _emitCopyToClipboard( QString msg );
    void _emitUpdateSession( JSession sess );


    //*** Private Mobile


    public slots:

    //*** System

    void emitApplicationStateChanged( bool online );


    //*** Network

    void emitPacketLossDetected( int count );
    void emitNetworkStatusChanged( bool online );


    //*** UI

    void emitUiLoaded(  );
    void emitCopyToClipboard( QString msg );
    void emitUpdateSession( JSession sess );


    //*** Mobile



    signals:

    //*** System

    void applicationStateChanged( bool online );

    //*** Network

    void packetLossDetected( int count );
    void networkStatusChanged( bool online );

    //*** UI

    void uiLoaded(  );
    void copyToClipboard( QString msg );
    void updateSession( JSession sess );

    //*** Mobile

};

#endif
