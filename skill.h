#ifndef SKILL_H
#define SKILL_H
#include "json_macros.h"

class Skill {
public:
	QString Name;
	int MinValue;
	int MaxValue;

	Skill(QJsonObject *d = NULL): MinValue(0), MaxValue(100)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, MinValue, toInt)
			else __IF_VAR_FROM_JSON_AS(it, MaxValue, toInt)
		}
	}
};

#endif // SKILL_H
