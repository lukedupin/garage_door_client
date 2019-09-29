// Generated file.
// Edit Scripts/json.py, then run ./export_struct.py ..

#ifndef JSON_STRUCT_H
#define JSON_STRUCT_H

#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJSValue>
#include "json_struct_helper.h"

class JErr
{
    JSON_STRUCT_HELPER( JErr )

    bool successful = false;
    QString reason;
};

class JEmpty
{
    JSON_STRUCT_HELPER( JEmpty )

};

class JMagicKey
{
    JSON_STRUCT_HELPER( JMagicKey )

    QString magic_key;
};

class JChallenge
{
    JSON_STRUCT_HELPER( JChallenge )

    QString challenge;
};

class JDoorStatus
{
    JSON_STRUCT_HELPER( JDoorStatus )

    bool status = false;
};

class JSession
{
    JSON_STRUCT_HELPER( JSession )

    QString magic_key;
};

void apiStructRegister();

#endif
