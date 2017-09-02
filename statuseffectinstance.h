#ifndef STATUSEFFECTINSTANCE_H
#define STATUSEFFECTINSTANCE_H
#include "json_macros.h"
#include "gametime.h"

class StatusEffectInstance {
public:
	QString Name;
	int StartTimestamp;
	int Duration;
	bool IsExpired()
	{
                return GameTime::CurrentTimestamp > StartTimestamp + Duration;
	}

	StatusEffectInstance(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, StartTimestamp, toInt)
			else __IF_VAR_FROM_JSON_AS(it, Duration, toInt)
		}
	}
};

#endif // STATUSEFFECTINSTANCE_H
