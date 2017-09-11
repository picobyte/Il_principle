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

Person* PopulationGenerator::initPerson(const QString& familyName, Location* home, const int index)
{
    Person* p = new Person();
    p->Gender = Game::ScenarioConfig.GetGenderForIndex(index);

    p->Lastname = familyName;
    do {
        p->Forename = GetForename(p->Gender);
    } while (!PersonNameIsUnique(p));

    student->Job = index ? "Student" : "";

    SetGenderPreferences(p, index);
    GenerateStatsFor(p, StudentIndex);

    Game::DictOfPersonIDs.add(p->UID, p);
    Game::DictOfPersonNames.add(p->Name, p);

    SetGenderSizes(p, index, index ? "Students" : "Adult");
    p->Home = home;

    return p;
}
void AssignPersonFetishStats(Person* per)
{
    if (per.HasFetish(Fetish::Incest))
    {
        // try {
        QList<Person>.Enumerator enumerator = per.GetSiblings().GetEnumerator();
        while (enumerator.MoveNext())
        {
            Person S = enumerator.Current;
            Game::RelationshipDatabase.AddRelationshipValue(per, S, Game::RNG.NextDouble() * 10.0 + 10.0);
            S.AddStat("Lust", 5.0);
        }
        // }
        per.AddStat("Lust", 10.0);
    }
}

void PopulationGenerator::completeParent(Person* x, int education, int lust)
{
    x->Virgin = false;
    x->SetStat("Education", education);
    x->SetStat("Lust", lust);

    if (x->HasFetish(Fetish::Exhibitionism))
        x->AddStat("Inhibition", -15.0);

    AssignPersonFetishStats(x);
}

void PopulationGenerator::CreateFamily(QList<Person>* outList = NULL)
{
    QString familyName = GetLastname();
    QList<Person> children;
    Person* mother = NULL;
    Person* father = NULL;
    Location* home = Game::GetLocation("General Home");

    QList<PopulationGenerationData>& popData = Game::ScenarioConfig.PopulationGenerationData;
    GameCalendar& calendar = Game::SchoolCalendar;

    std::default_random_engine roll;
    std::uniform_int_distribution<int> d100(0, 100);

    std::uniform_int_distribution<int> studentDaysSinceBorn(
                popData[StudentIndex()].AgeRange.Min * 365,
                popData[StudentIndex].AgeRange.Max * 365);

    std::uniform_int_distribution<Fetish> pickFetish(Fetish::Anal, Fetish::Yuri);
    std::uniform_real_distribution<double> SiblingRelation(60.0, 80.0);

    int firstChild = 0;
    do {
        Person* student = initPerson(familyName, home, StudentIndex);

        student->Birthday = calendar.TodayDate.addDays(-studentDaysSinceBorn(roll));
        student->Virgin = d100(roll) > 50;

        AddFavoriteSubject(student);
        AddSubjectExperience(student);

        for (int i = 0; i < 2; ++i)
            if (d100(roll) > 70)
                student->AddFetish(pickFetish(roll));

        children.Add(student);
        Game::OtherStudents.add(student->Name, student);

        if (student->Age > firstChild)
            firstChild = student->Age;

        for (QList<Person>::iterator child = children.begin(); child != children.end(); ++child) {
            Game::RelationshipDatabase.SetRelationshipValue(*child, *student, SiblingRelation(roll));
            Game::RelationshipDatabase.SetRelationshipValue(*student, *child, SiblingRelation(roll));
        }
        outList.add(student);

    } while (Game::RNG.Next(children.count() * children.count() + 3) < 1);

    SizeRange& ageRange = popData[0].AgeRange;

    std::uniform_int_distribution<int> parentDaysSinceBorn(std::max(ageRange.Min, firstChild + 14) * 365, ageRange.Max * 365);
    std::uniform_int_distribution<int> range_30_70(30, 70);

    std::uniform_real_distribution<double> childParentRelation(50.0, 75.0);
    std::uniform_real_distribution<double> parentalRelation(40.0, 95.0);

    if (d100(roll) > 3) {

        mother = initPerson(familyName, home, 0);
        mother->Birthday = calendar.TodayDate.addDays(-parentDaysSinceBorn(roll));

        if (d100(roll) < popData[0].FutanariPercentage)
            MakeFuta(mother);
        else
            mother->Gender = Gender::Female;

        for (int i = 0; i < 5; ++i)
            if (d100(roll) > 70)
                mother->AddFetish(pickFetish(roll));

        completeParent(mother, range_30_70(roll), range_30_70(roll));
        if (outList) outList->add(mother);
    }
    if (mother == NULL || d100(roll) > 3)
    {
        father = initPerson(familyName, home, 0);
        father->Birthday = calendar.TodayDate.addDays(-parentDaysSinceBorn(roll));

        if (d100(roll) < popData[0].FutanariPercentage) {
            MakeFuta(father);
        } else {
            father->Gender = Gender::Male;
            father->AnalVirgin = d100(roll) >= 6;
        }
        for (int i = 0; i < 5; ++i)
            if (d100(roll) > 70)
                father->AddFetish(pickFetish(roll));

        completeParent(father, range_30_70(roll), range_30_70(roll));

        if (mother) {
            mother->AnalVirgin = d100(roll) > (father->HasFetish(Fetish.Anal) ? 33 : 7);
            AssignPersonFetishStats(mother, father);
            AssignPersonFetishStats(father, mother);
            Game::RelationshipDatabase.SetRelationshipValue(*mother, *father, parentalRelation(roll));
            Game::RelationshipDatabase.SetRelationshipValue(*father, *mother, parentalRelation(roll));

        } else if (d100(roll) < father->GetGenderPreference(Gender::Male)) {

            father->AddGenderPreference(Gender::Male, 50.0);
            father->AnalVirgin = false;
        } else {
            father->AnalVirgin = d100(roll) > 5;
        }
        for (QList<Person>::iterator child = children.begin(); child != children.end(); ++child) {
            child->Father = father;
            father->Children.Add(child->Name);
            Game::RelationshipDatabase.SetRelationshipValue(*child, *father, childParentRelation(roll));
            Game::RelationshipDatabase.SetRelationshipValue(*father, *child, childParentRelation(roll));
            AssignParentChildFetishStats(*father, *child);
        }
        father->AddStat("Fertility", 10 * children.count());
        if (outList) outList->add(father);

    } else if (mother) {

        if (mother->SexualOrientation != SexualPref.Bisexual && d100(roll) < mother->GetGenderPreference(Gender::Female)) {

            mother->AddGenderPreference(Gender::Female, 50.0);
            mother->AnalVirgin = d100(roll) > 5;
        }
        for (QList<Person>::iterator child = children.begin(); child != children.end(); ++child) {
            child->Mother = mother;
            mother->Children.Add(child->Name);
            Game::RelationshipDatabase.SetRelationshipValue(*stud2, *mother, childParentRelation(roll));
            Game::RelationshipDatabase.SetRelationshipValue(*mother, *stud2, childParentRelation(roll));
            AssignParentChildFetishStats(*mother, *child);
        }
        mother->AddStat("Fertility", 10 * children.count());
    }
}


