#ifndef POPULATIONGENERATIONDATA_H
#define POPULATIONGENERATIONDATA_H
#include "json_macros.h"

class PopulationGenerationData {
	QList<PopulationGenerationGenderSpecificData> GenderSpecific;
	QList<StatRange> StatRanges;
public:
	SizeRange AgeRange;
	double MalePercentage;
	double FemalePercentage;
	double FutanariPercentage;
	PopulationGenerationData(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_OBJ_FROM_JSON(it, AgeRange)
			else __IF_OBJLIST_FROM_JSON(it, GenderSpecific, PopulationGenerationGenderSpecificData)
			else __IF_VAR_FROM_JSON_AS(it, MalePercentage, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, FemalePercentage, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, FutanariPercentage, toDouble)
			else __IF_OBJLIST_FROM_JSON(it, StatRanges, StatRange)
			// *INDENT-ON*
		}
	}
};
#endif // POPULATIONGENERATIONDATA_H
