#ifndef JSON_MACROS_H
#define JSON_MACROS_H
#include <QObject>

#define __IF_VAR_FROM_JSON_AS(it, _key, toType) if (it.key() == #_key) { _key = it.value().toType(); }
#define __IF_OBJLIST_FROM_JSON_AS(it, _key) if (it.key() == #_key "s") { \
    QJsonObject obj = it.value().toObject();\
    QJsonObject::iterator oit;\
    for (oit = obj.begin(); oit != obj.end(); ++oit) {\
        if (oit.key() == #_key) {\
            QJsonObject v = oit.value().toObject();\
            _key##s.append(ClubLevel(v));\
        } else\
            qFatal(oit.key().append(": unexpected key").toUtf8());\
     }\
}
#define __UNHANDLED_KEY(it) qWarning(it.key().append(": unhandled.").toUtf8())

#endif // JSON_MACROS_H
