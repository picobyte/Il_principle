#ifndef LOCATIONPROPERTYCHANGE_H
#define LOCATIONPROPERTYCHANGE_H
#include "json_macros.h"
#include "statchange.h"

class LocationPropertyChange {
    QList<StatChange> Changes;
public:
    QString AffectedPersons;
    LocationPropertyChange(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, AffectedPersons, toString)
            else __IF_OBJLIST_FROM_JSON(it, Changes, StatChange)
        }
    }
};

#endif // LOCATIONPROPERTYCHANGE_H
