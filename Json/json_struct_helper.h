#ifndef JSON_STRUCT_HELPER_h
#define JSON_STRUCT_HELPER_h

#include <QVariantList>
#include <QList>
#include <QString>
#include <QJSEngine>
#include <QJsonObject>
#include <QJsonArray>

#define JSON_STRUCT_HELPER( klass ) \
    public: \
    static klass fromJson( QJsonObject&& obj, bool* complete = nullptr ); \
    static klass fromJson( QJsonObject* obj, bool* complete = nullptr ); \
    static QList<klass> fromJsonList( QList<QJsonObject>&& obj, bool* complete = nullptr ); \
    static QList<klass> fromJsonList( QList<QJsonObject>* obj, bool* complete = nullptr ); \
    static klass fromQJSValue( QJSValue* obj, bool* complete = nullptr ); \
    static QJsonArray toArray( QList<klass>* obj ); \
    QJsonObject describeObject(); \
    QJsonObject toJson();
    //QJSValue toQJSValue( QJSEngine* engine );

template <typename T>
class Primitive
{
    public:
    static QVariantList toArray( QList<T>* ary )
    {
        QVariantList list;
        for ( auto& entry : *ary )
            list.append( entry );
        return list;
    }
};

#endif
