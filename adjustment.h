#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H
#include "json_macros.h"

class Adjustment {
public:
	QString StatName;
	Range Range;
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
			//Range Range
			else __IF_VAR_FROM_JSON_AS(it, lowMagnitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, highMagnitude, toDouble)
		}
	}
};

#endif // ADJUSTMENT_H
