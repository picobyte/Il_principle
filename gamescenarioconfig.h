#ifndef GAMESCENARIOCONFIG_H
#define GAMESCENARIOCONFIG_H
#include "json_macros.h"

class GameScenarioConfig {
public:
	QString ConfigName;
	QString StartEventName;
	int MinimumAge;
	QList<QString> PopulationTag;
	QList<PopulationGenerationData> PopulationGenerationData;
	QList<Mind> MindData;

	GameScenarioConfig(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, ConfigName, toString)
			else __IF_VAR_FROM_JSON_AS(it, StartEventName, toString)
			else __IF_VAR_FROM_JSON_AS(it, MinimumAge, toInt)
QList<string> PopulationTag;
			//QList<PopulationGenerationData> PopulationGenerationData
			//QList<Mind> MindData
		}
	}
};

#endif // GAMESCENARIOCONFIG_H
