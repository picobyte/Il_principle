#ifndef BODYSIZECHANGE_H
#define BODYSIZECHANGE_H
#include "json_macros.h"

enum BodyPart
{
    Anal,
    Breast,
    Penis,
    Stomach,
    Testicle,
    Vagina
};

class BodySizeChange {
public:
    BodyPart bodyPart;
	double Change;
	double Minimum;
	double Maximum;

    BodySizeChange(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
	{
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, bodyPart, BodyPart)
            else __IF_VAR_FROM_JSON_AS(it, Change, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, Minimum, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, Maximum, toDouble)
		}
	}
};

#endif // BODYSIZECHANGE_H
