#ifndef SHARED_STATE_H
#define SHARED_STATE_H

#include <Net/api.h>
#include <Shared/mailbox.h>
#include <UI/ui_common.h>

#include <QObject>
#include <QGuiApplication>
#include <Json/json_struct.h>

//Holds the shared state
class SharedState : public QObject
{
    Q_OBJECT

    public:
    static const int MAJOR = 1;
    static const int MINOR = 0;

    public:
    Mailbox* Mail = nullptr;
    MailboxQml* MailQml = nullptr;
    ApiInterface* Api = nullptr;
    JSession Sess;

    //Create a shared state
    SharedState( Mailbox* mailbox, MailboxQml* mailbox_qml, ApiInterface* api );

    public:
    Q_INVOKABLE QVariant getSession();

    private:
    //Session logic
    bool loadSession();
    bool saveSession();

    private slots:
    void onUpdateSession( JSession sess );
};

#endif
