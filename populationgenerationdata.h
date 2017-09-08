#ifndef POPULATIONGENERATIONDATA_H
#define POPULATIONGENERATIONDATA_H
#include "json_macros.h"
#include "range.h"

struct StatRange
{
    QString Stat;
    Range range;
};

class SizeRange {
public:
        int Min;
        int Max;

        SizeRange(QJsonObject *d = NULL)
        {
                if (d) init(d);
        }
        void init(QJsonObject *d)
        {
                for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
                        // *INDENT-OFF*
                        __IF_VAR_FROM_JSON_AS(it, Min, toInt)
                        else __IF_VAR_FROM_JSON_AS(it, Max, toInt)
                        // *INDENT-ON*
                }
        }
};

class GaussianDistribution {
public:
        double Mean;
        double StdDev;

        GaussianDistribution(QJsonObject *d = NULL)
        {
                if (d) init(d);
        }
        void init(QJsonObject *d)
        {
                for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
                        // *INDENT-OFF*
                        __IF_VAR_FROM_JSON_AS(it, Mean, toDouble)
                        else __IF_VAR_FROM_JSON_AS(it, StdDev, toDouble)
                        // *INDENT-ON*
                }
        }
};

class PopulationGenerationGenderSpecificData {
public:
    Gender gender;
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
    bool ShouldSerializePGBreastSize()
    {
        return BreastSize.Min != 0 || BreastSize.Max != 8;
    }
    bool ShouldSerializePGStomachSize()
    {
        return StomachSize.Min != 0 || StomachSize.Max != 8;
    }
    bool ShouldSerializePGVaginaSize()
    {
        return VaginaSize.Min != 0 || VaginaSize.Max != 8;
    }
    bool ShouldSerializePGPenisSize()
    {
        return PenisSize.Min != 0 || PenisSize.Max != 8;
    }
    bool ShouldSerializePGTesticleSize()
    {
        return TesticleSize.Min != 0 || TesticleSize.Max != 8;
    }
    bool ShouldSerializePGAnalSize()
    {
        return AnalSize.Min != 0 || AnalSize.Max != 8;
    }

    PopulationGenerationGenderSpecificData(QJsonObject *d = NULL)
    {
        if (d) init(d);

    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
            else __IF_OBJ_FROM_JSON(it, BreastSize)
            else __IF_OBJ_FROM_JSON(it, StomachSize)
            else __IF_OBJ_FROM_JSON(it, VaginaSize)
            else __IF_OBJ_FROM_JSON(it, PenisSize)
            else __IF_OBJ_FROM_JSON(it, TesticleSize)
            else __IF_OBJ_FROM_JSON(it, AnalSize)
            else __IF_OBJ_FROM_JSON(it, HeadFileRange)
            else __IF_OBJ_FROM_JSON(it, LikesMale)
            else __IF_OBJ_FROM_JSON(it, LikesFemale)
            else __IF_OBJ_FROM_JSON(it, LikesFutanari)
            // *INDENT-ON*
        }
    }
};


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
