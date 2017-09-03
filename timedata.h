#ifndef TIMEDATA_H
#define TIMEDATA_H
#include "json_macros.h"

class TimeData {
public:
	int Hour;
	int Minute;

	TimeData(int h, int m = 0): Hour(h), Minute(m) {}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Hour, toInt)
			else __IF_VAR_FROM_JSON_AS(it, Minute, toInt)
		}
	}
};

#endif // TIMEDATA_H
