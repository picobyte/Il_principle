#ifndef POPULATIONGENERATIONDATA_H
#define POPULATIONGENERATIONDATA_H
#include "json_macros.h"

class PopulationGenerationData {
public:
	SizeRange AgeRange;
	QList<PopulationGenerationGenderSpecificData> GenderSpecific;
	double MalePercentage;
	double FemalePercentage;
	double FutanariPercentage;
	QList<StatRange> StatRanges;

	PopulationGenerationData(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//SizeRange AgeRange
			//QList<PopulationGenerationGenderSpecificData> GenderSpecific
			__IF_VAR_FROM_JSON_AS(it, MalePercentage, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, FemalePercentage, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, FutanariPercentage, toDouble)
			//QList<StatRange> StatRanges
		}
	}
};

#endif // POPULATIONGENERATIONDATA_H
