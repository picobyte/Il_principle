#ifndef JSON_MACROS_H
#define JSON_MACROS_H
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>
#include "generic.h"

#define __IF_VAR_FROM_JSON_AS(it, _key, _toType) if (it.key() == #_key) { _key = it.value()._toType(); }
#define __IF_ENUM_FROM_JSON_AS(it, _key, _enum) if (it.key() == #_key) { _key = static_cast<_enum>(it.value().toInt()); }

//suitable only if nested object has the same key (1), but without an s.



#define __OBJLIST_FROM_JSON_RESOLVED(_ref, _var, _class) \
    if (_ref.isArray()) {\
        foreach (const QJsonValue &el, _ref.toArray()) {\
            QJsonObject v = el.toObject();\
            _var.append(_class(&v));\
        }\
    } else {\
        QJsonObject v = _ref.toObject();\
        _var.append(_class(&v));\
    }

#define __IF_OBJLIST_FROM_JSON(_ref, _var, _class) \
    if (it.key() == #_class) {\
        __OBJLIST_FROM_JSON_RESOLVED(it.value(), _var, _class)\
    }

#define __IF_EASY_OBJLIST_FROM_JSON(it, _class) \
    if (it.key() == #_class "s") { \
        QJsonObject obj = it.value().toObject();\
        if (obj.length() != 1) qFatal("Expected one element");\
        QJsonValueRef ref = obj[#_class];\
        __OBJLIST_FROM_JSON_RESOLVED(ref, _class ## s, _class) \
    }

#define __IF_LIST_FROM_JSON_TYPE_RESOLVED(it, _arr, _var, _var_resolved) \
if (it.key() == #_arr) { \
    QJsonObject obj = it.value().toObject();\
    if (obj.length() != 1) qFatal("Expected one element");\
    foreach (const QJsonValue & _var, obj["string"].toArray())\
        _arr.append(_var_resolved);\
}

#define __IF_LIST_FROM_JSON_TYPED(it, _arr, _toType) \
    __IF_LIST_FROM_JSON_TYPE_RESOLVED(it, _arr, value, value._toType())

#define __IF_LIST_FROM_JSON_ENUM(it, _arr, _cast) \
    __IF_LIST_FROM_JSON_TYPE_RESOLVED(it, _arr, value, _cast(value.toInt()))

#define __IF_OBJ_FROM_JSON(it, _instance) \
if (it.key() == #_instance) {\
    QJsonObject v = it.value().toObject();\
    _instance.init(&v);\
}

#define __IF_HASH_FROM_JSON_TYPED(it, _hash, _toType)\
if (it.key() == #_hash) {\
    QJsonObject v = it.value().toObject();\
    for (QJsonObject::iterator oit = v->begin(); oit != v->end(); ++oit)\
        _hash.insert(oit.key(), oit.value()._toType());\
}

#endif // JSON_MACROS_H
