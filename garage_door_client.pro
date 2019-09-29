TARGET = garage_door_client
TEMPLATE = app

QT += qml network quick networkauth sql

android: {
    QT += androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/Android
}

CONFIG += c++14 -Werror
QMAKE_CXXFLAGS += -std=c++14

#DESTDIR = build
OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui

SOURCES += \
    Core/system.cpp \
    Json/json_struct.cpp \
    Json/json_struct_helper.cpp \
    Net/net_api.cpp \
    Net/api.cpp \
    Net/network_http.cpp \
    Shared/mailbox.cpp \
    Shared/mailbox_qml.cpp \
    Shared/shared_state.cpp \
    Storage/json_storage.cpp \
    Util/util.cpp \
    Util/lock.cpp \
    UI/ui_common.cpp \
    UI/mobile/ui_mobile.cpp \
    Util/api_util.cpp \
    Util/stopwatch.cpp \
    main.cpp

HEADERS += \
    Core/system.h \
    Json/json_struct.h \
    Json/json_struct_helper.h \
    Net/api.h \
    Net/net_api.h \
    Net/network_http.h \
    Shared/mailbox.h \
    Shared/mailbox_qml.h \
    Shared/shared_state.h \
    Storage/json_storage.h \
    UI/ui_common.h \
    UI/mobile/ui_mobile.h \
    Util/api_util.h \
    Util/lock.h \
    Util/util.h \
    Util/stopwatch.h \
    main.h

RESOURCES += \
    UI/mobile/mobile.qrc

OTHER_FILES +=\
    UI/mobile/mobile.qml \
    UI/mobile/Main.qml \
    UI/mobile/helpers/Toast.qml \
    UI/mobile/helpers/ToastManager.qml \
    UI/mobile/helper.js
