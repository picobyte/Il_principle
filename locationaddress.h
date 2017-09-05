#ifndef LOCATIONADDRESS_H
#define LOCATIONADDRESS_H
#include <QPoint>
#include "json_macros.h"

class LocationAddress {
public:
    QString LocationName;
    QPoint DrawPosition;
    int TravelTime;
    QString ToString()
    {
        return "LocationAddress: " + LocationName;
    }
    LocationAddress(QJsonObject *d = NULL)
    {
        if (d) init(d);

    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, LocationName, toString)
            //else __IF_OBJ_FROM_JSON(it, _DrawPosition)
            else __IF_VAR_FROM_JSON_AS(it, TravelTime, toInt)
            // *INDENT-ON*
        }
    }
};
#endif // LOCATIONADDRESS_H
