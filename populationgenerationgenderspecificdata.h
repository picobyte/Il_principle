#ifndef POPULATIONGENERATIONGENDERSPECIFICDATA_H
#define POPULATIONGENERATIONGENDERSPECIFICDATA_H
#include "json_macros.h"

class PopulationGenerationGenderSpecificData {
public:
	Gender Gender;
	SizeRange BreastSize;
	SizeRange StomachSize;
	SizeRange VaginaSize;
	SizeRange PenisSize;
	SizeRange TesticleSize;
	SizeRange AnalSize;
	SizeRange HeadFileRange;
	GaussianDistribution LikesMale;
	GaussianDistribution LikesFemale;
	GaussianDistribution LikesFutanari;

	PopulationGenerationGenderSpecificData(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//Gender Gender
			//SizeRange BreastSize
			//SizeRange StomachSize
			//SizeRange VaginaSize
			//SizeRange PenisSize
			//SizeRange TesticleSize
			//SizeRange AnalSize
			//SizeRange HeadFileRange
			//GaussianDistribution LikesMale
			//GaussianDistribution LikesFemale
			//GaussianDistribution LikesFutanari
		}
	}
};

#endif // POPULATIONGENERATIONGENDERSPECIFICDATA_H
