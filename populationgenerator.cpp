#include "game.h"
#include "populationgenerator.h"

int PopulationGenerator::StudentIndex() const
{
    return Game::ScenarioConfig.PopulationTag.IndexOf("Student");
}

void PopulationGenerator::LoadNames()
{
    GirlNames = QFile(Game::GamePath+"/"+Game::TheSchool.FolderLocation+"/PopulationData/girlname.txt");

    for (int i = 0; i < GirlNames.length(); i++)
        GirlNames[i] = GirlNames[i].Trim();

    BoyNames = QFile(Game::GamePath+"/"+Game::TheSchool.FolderLocation+"/PopulationData/boyname.txt");

    for (int j = 0; j < BoyNames.length(); j++)
        BoyNames[j] = BoyNames[j].Trim();

    Surnames = QFile(Game::GamePath+"/"+Game::TheSchool.FolderLocation+"/PopulationData/lastname.txt");

    for (int k = 0; k < Surnames.length(); k++)
        Surnames[k] = Surnames[k].Trim();
}

void PopulationGenerator::CreatePopulation(int count)
{
    count += Game::DictOfPersonIDs.count();
    while (Game::DictOfPersonIDs.count() < count)
        CreateFamily(NULL);
}

