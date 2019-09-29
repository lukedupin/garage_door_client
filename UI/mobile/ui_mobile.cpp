#include "ui_mobile.h"

#include <Net/api.h>

#include <QtCore/QTextStream>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>
#include <QRandomGenerator64>
#include <QJsonDocument>
#include <QClipboard>

    //Register singleton types with QML
#define REGISTER_SINGLETON( x, inst ) \
    qmlRegisterSingletonType<x>("GarageDoor", x::MAJOR, x::MINOR, #x, \
        [](QQmlEngine*, QJSEngine*) -> QObject* { return inst; })
#define REGISTER_SINGLETON_CUSTOM( x, name, inst ) \
    qmlRegisterSingletonType<x>("GarageDoor", x::MAJOR, x::MINOR, name, \
        [](QQmlEngine*, QJSEngine*) -> QObject* { return inst; })

using namespace std;

static ApiInterface* _api = nullptr;
static MailboxQml* _mailboxQml = nullptr;
static SharedState* _sharedState = nullptr;

UiMobile::UiMobile()
{
}

int UiMobile::runUi( SharedState* shared_state )
{
    QVariantMap parameters;
    QStringList args(QCoreApplication::arguments());

    //Setup the clipboard
    auto clipboard = qApp->clipboard();
    QObject::connect( shared_state->Mail, &Mailbox::copyToClipboard,
                      [=](QString msg) { clipboard->setText( msg ); });

    //Register to know when the UI exists
    QObject::connect( shared_state->Mail, &Mailbox::uiLoaded,
                      this, &UiMobile::onUiLoaded );

    //Create my QML engine object
    QQmlApplicationEngine engine;
    _engine = &engine;

    //Register static qml types
    qmlRegisterModule("GarageDoor", 1, 0);

    //Register my singletons
    _mailboxQml = shared_state->MailQml;
    _sharedState = shared_state;
    _api = shared_state->Api;
    REGISTER_SINGLETON_CUSTOM( MailboxQml, "Mailbox", _mailboxQml );
    REGISTER_SINGLETON( SharedState, _sharedState );
    REGISTER_SINGLETON( ApiInterface, _api );

    //Load the JS engine into the api, this allows access for QML to use the api
    _sharedState->Api->loadEngine( _engine );
    _sharedState->MailQml->loadEngine( _engine );

    //Configure the QML engine
    _engine->addImportPath(QStringLiteral(":/imports"));
    _engine->load(QUrl(QStringLiteral("qrc:///mobile.qml")));
    QObject::connect(_engine, SIGNAL(quit()), qApp, SLOT(quit()));

    QObject *item = _engine->rootObjects().first();
    Q_ASSERT(item);

    //Setup my context
    _engine->rootContext()->setContextProperty("ui_common", this );

    //Run the application loop
    auto result = qApp->exec();

    qDebug("App has completed its run and exiting the QT loop");

    //clean up and return the result
    _engine = nullptr;
    return result;
}

void UiMobile::onUiLoaded()
{
}
