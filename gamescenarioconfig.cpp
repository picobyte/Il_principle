#include "game.h"
#include "gamescenarioconfig.h"

int GameScenarioConfig::GetAgeForIndex(int Index)
{
    return std::max(MinimumAge, Game::RNG().Next(popGenData[Index].AgeRange.Min, popGenData[Index].AgeRange.Max));
}
Gender GameScenarioConfig::GetGenderForIndex(int Index)
{
    int randomnum = Game::RNG.Next(0, round(popGenData[Index].MalePercentage + popGenData[Index].FemalePercentage +
                                            popGenData[Index].FutanariPercentage));

    if ((double)randomnum < popGenData[Index].MalePercentage)
        return Gender::Male;

    if ((double)randomnum < popGenData[Index].MalePercentage + popGenData[Index].FemalePercentage)
        return Gender::Female;

    return Gender::Futanari;
}
