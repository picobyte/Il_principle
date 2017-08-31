#ifndef STATCHANGE_H
#define STATCHANGE_H
#include "json_macros.h"

class StatChange {
public:
	QString Stat;
	double Change;
	double Minimum;
	double Maximum;

    StatChange(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
	{
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            //BodyPart BodyPart
            __IF_VAR_FROM_JSON_AS(it, Stat, toString);
            __IF_VAR_FROM_JSON_AS(it, Change, toDouble);
            __IF_VAR_FROM_JSON_AS(it, Minimum, toDouble);
            __IF_VAR_FROM_JSON_AS(it, Maximum, toDouble);
        }
	}
};

#endif // STATCHANGE_H
