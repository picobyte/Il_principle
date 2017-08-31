#ifndef JSON_MACROS_H
#define JSON_MACROS_H
#include <QJsonObject>
#include <QJsonValueRef>
#include "generic.h"

#define __IF_VAR_FROM_JSON_AS(it, _key, _toType) if (it.key() == #_key) { _key = it.value()._toType(); }
#define __IF_ENUM_FROM_JSON_AS(it, _key, _enum) if (it.key() == #_key) { _key = static_cast<_enum>(it.value().toInt()); }

//suitable only if nested object has the same key (1), but without an s.
#define __IF_OBJLIST_FROM_JSON(it, _class) \
if (it.key() == #_class "s") { \
    QJsonObject obj = it.value().toObject();\
    if (obj.length() != 1) qFatal("Expected one element");\
    QJsonValueRef r = obj[#_class];\
    if (r.isArray()) {\
        foreach (const QJsonValue &el, r.toArray()) {\
            QJsonObject v = el.toObject();\
            _class##s.append(_class(&v));\
        }\
    } else {\
        QJsonObject v = r.toObject();\
        _class##s.append(_class(&v));\
    }\
}
#define __IF_LIST_FROM_JSON_TYPED(it, _arr, _toType) \
if (it.key() == #_arr) { \
    QJsonObject obj = it.value().toObject();\
    if (obj.length() != 1) qFatal("Expected one element");\
    foreach (const QJsonValue & value, obj["string"].toArray()) \
        _arr.append(value._toType());\
}
#define __IF_OBJ_FROM_JSON(it, _instance) \
if (it.key() == #_instance) {\
    QJsonObject v = it.value().toObject();\
    _instance.init(&v);\
}
#endif // JSON_MACROS_H
