#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include "json_macros.h"
#include "modifier.h"

class StatusEffect {
public:
	enum class StatusEffectAccumulationType
	{
		None,
		Refresh,
		Stack
	};
	QString Name;
	QString DisplayName;
	StatusEffectAccumulationType AccumulationType;
	int Duration;
	QList<ModifierBase> Modifiers;

	StatusEffect(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, DisplayName, toString)
			else __IF_ENUM_FROM_JSON_AS(it, AccumulationType, StatusEffectAccumulationType)
			else __IF_VAR_FROM_JSON_AS(it, Duration, toInt)
			//QList<ModifierBase> Modifiers
		}
	}
};

#endif // STATUSEFFECT_H
