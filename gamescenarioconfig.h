#ifndef GAMESCENARIOCONFIG_H
#define GAMESCENARIOCONFIG_H
#include "json_macros.h"
#include "populationgenerationdata.h"
#include "mind.h"
#include <math.h>

class GameScenarioConfig {
    QList<QString> PopulationTag;
    QList<PopulationGenerationData> PopulationGenerationData;
public:
    QList<Mind> MindData;
    QString ConfigName;
    QString StartEventName;
    int MinimumAge;
    GameScenarioConfig(QJsonObject *d = NULL)
    {
        if (d) init(d);
        StartEventName = "StartEvent";
        MinimumAge = 18;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, ConfigName, toString)
            else __IF_VAR_FROM_JSON_AS(it, StartEventName, toString)
            else __IF_VAR_FROM_JSON_AS(it, MinimumAge, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, PopulationTag, toString)
            else __IF_OBJLIST_FROM_JSON(it, PopulationGenerationData, PopulationGenerationData)
            else __IF_OBJLIST_FROM_JSON(it, MindData, Mind)
            // *INDENT-ON*
        }
    }
    int GetAgeForIndex(int Index)
    {
        return std::max(MinimumAge,
                        Game::RNG.Next(PopulationGenerationData[Index].AgeRange.Min,
                                       PopulationGenerationData[Index].AgeRange.Max));
    }
    Gender GetGenderForIndex(int Index)
    {
        int randomnum = Game.RNG.Next(0, round(PopulationGenerationData[Index].MalePercentage + PopulationGenerationData[Index].FemalePercentage + PopulationGenerationData[Index].FutanariPercentage))));

        if ((double)randomnum < PopulationGenerationData[Index].MalePercentage)
            return Gender::Male;

        if ((double)randomnum < PopulationGenerationData[Index].MalePercentage + PopulationGenerationData[Index].FemalePercentage)
            return Gender::Female;

        return Gender::Futanari;
    }
    PopulationGenerationGenderSpecificData GetGenderSpecificDataForIndex(int Index, Gender Gender)
    {
        return PopulationGenerationData[Index].GenderSpecific.First((PopulationGenerationGenderSpecificData gs) => gs.Gender == Gender);
    }
    QString ToString()
    {
        return "ScenarioConfig: " + ConfigName;
    }
    int GetHashCode()
    {
        return qHash(ConfigName);
    }
};

#endif // GAMESCENARIOCONFIG_H
