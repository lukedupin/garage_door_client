#ifndef UI_MOBILE_H
#define UI_MOBILE_H

#include <UI/ui_common.h>
#include <Shared/shared_state.h>
#include <Shared/mailbox_qml.h>

#include <functional>
#include <QString>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

class UiMobile : public UiCommon
{
    Q_OBJECT
    QQmlApplicationEngine* _engine = nullptr;

    public:
    //Setup the object!
    UiMobile();

    //Run the UI
    int runUi( SharedState* shared_state );

    public slots:
    //The ui is loaded
    void onUiLoaded();
};

#endif
