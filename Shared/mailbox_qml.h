// Generated file.
// Edit CodeGenerators/mailbox.py, then run ./export_mailbox.py ..

#ifndef MAILBOX_QML_H
#define MAILBOX_QML_H

#include <Json/json_struct.h>

#include <QJSValue>
#include <QObject>
#include <QVariantList>
#include <QTcpSocket>

class Mailbox;

class MailboxQml : public QObject
{
    Q_OBJECT

    public:
    static const int MAJOR = 1;
    static const int MINOR = 0;
    
    //Set to true for message logging
    bool Debug = false;
    
    private:
    Mailbox* _sibling = nullptr;
    QJSEngine* _engine = nullptr;

    public:
    explicit MailboxQml( QObject *parent = nullptr);
    
    void loadSibling( Mailbox* sibling );
    
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
    void _emitUpdateSession( QJSValue sess );


    //*** Private Mobile

    void _emitPushForm( QString qml_file, QJSValue args );
    void _emitReplaceForm( QString qml_file, QJSValue args );
    void _emitPopForm(  );
    void _emitCurrentForm( QString qml_file );
    void _emitToast( QString msg, int duration );

    public slots:

    //*** System

    void emitApplicationStateChanged( bool online );


    //*** Network

    void emitPacketLossDetected( int count );
    void emitNetworkStatusChanged( bool online );


    //*** UI

    void emitUiLoaded(  );
    void emitCopyToClipboard( QString msg );
    void emitUpdateSession( QJSValue sess );


    //*** Mobile

    void emitPushForm( QString qml_file, QJSValue args );
    void emitReplaceForm( QString qml_file, QJSValue args );
    void emitPopForm(  );
    void emitCurrentForm( QString qml_file );
    void emitToast( QString msg, int duration );


    signals:

    //*** System

    void applicationStateChanged( bool online );

    //*** Network

    void packetLossDetected( int count );
    void networkStatusChanged( bool online );

    //*** UI

    void uiLoaded(  );
    void copyToClipboard( QString msg );
    void updateSession( QVariant sess );

    //*** Mobile

    void pushForm( QString qml_file, QJSValue args );
    void replaceForm( QString qml_file, QJSValue args );
    void popForm(  );
    void currentForm( QString qml_file );
    void toast( QString msg, int duration );
};

#endif
