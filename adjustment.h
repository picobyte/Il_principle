#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H
#include "json_macros.h"
#include "range.h"

class Adjustment {
public:
    QString StatName;
    Range range;
    double lowMagnitude;
    double highMagnitude;

    Adjustment(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, StatName, toString)
            else __IF_OBJ_FROM_JSON(it, range)
            else __IF_VAR_FROM_JSON_AS(it, lowMagnitude, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, highMagnitude, toDouble)
        }
    }
};

#endif // ADJUSTMENT_H
