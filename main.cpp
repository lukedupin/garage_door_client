#include "Shared/mailbox.h"
#include "Shared/mailbox_qml.h"
#include "Net/network_http.h"
#include "Shared/shared_state.h"
#include "Core/system.h"
#include "Util/util.h"
#include "main.h"

#include <UI/mobile/ui_mobile.h>

#include <QtCore/QTextStream>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>
#include <QRandomGenerator64>
#include <QJsonDocument>
#include <QClipboard>
#include <QSslSocket>

#ifdef Q_OS_IOS
#include "IOS/qtappdelegate-c-interface.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication application(argc, argv);

    auto font_name = QString( "Helvetica" );
    auto font = QFont( font_name, 16 );
    application.setFont( font );

    //Register my json types
    apiStructRegister();

#if QT_CONFIG(library)
    const QByteArray additionalLibraryPaths = qgetenv("QTLOCATION_EXTRA_LIBRARY_PATH");
    for (const QByteArray &p : additionalLibraryPaths.split(':'))
        QCoreApplication::addLibraryPath(QString(p));
#endif

    //Message passing interface
    auto mailbox = new Mailbox;
    auto mailbox_qml = new MailboxQml;
    mailbox->loadSibling( mailbox_qml );
    mailbox_qml->loadSibling( mailbox );

    //Setup the network
    auto network = new NetworkHttp( mailbox );

    //Setup the shared state, all of these need to be dynamic since they might be loaded into the qml render engine
    //If they aren't dynamically allocated, the program will crash on exit when the engine attempts to free static memory
    auto api = new ApiInterface( network, mailbox );
    auto shared_state = new SharedState( mailbox, mailbox_qml, api );

    network->setHost("x.x.x.x", 80);

    //Setup the system monitor object
    System system( shared_state );

    //Run the UI
    auto ui = new UiMobile; //Change this for different UIs
    return ui->runUi( shared_state );
}
