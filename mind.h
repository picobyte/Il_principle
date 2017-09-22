#ifndef MIND_H
#define MIND_H
#include "json_macros.h"
#include "adjustment.h"

class Mind {
    QList<Adjustment> AdjustStatList;
public:
    Mind(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it)
            __IF_OBJLIST_FROM_JSON(it, AdjustStatList, Adjustment)
    }
    bool ShouldSerializeAdjustStatList()
    {
        return AdjustStatList.count() > 0;
    }
    Adjustment* AdjustmentByStat(QString& Stat)
    {
        for (QList<Adjustment>::iterator it = AdjustStatList.begin(); it != AdjustStatList.end(); ++it)
            if (it->StatName == Stat)
                return &(*it); //yes, it's an iterator.
        return NULL;
    }
};

#endif // MIND_H
