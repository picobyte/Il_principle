#ifndef STAT_H
#define STAT_H
#include "json_macros.h"

class Stat {
public:
	QString Name;
	double MinValue;
	double MaxValue;
	bool Reversed;

	Stat(QJsonObject *d = NULL):
			MinValue(0.0),
			MaxValue(100.0),
			Reversed(false)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, MinValue, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, MaxValue, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Reversed, toBool)
		}
	}
};

#endif // STAT_H
