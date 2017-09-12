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

void AssignPersonFetishStats(Person* p1, Person* p2)
{
    if (p1->HasFetish(Fetish::Sadism) && p2->HasFetish(Fetish::Masochism))
    {
        p1->AddStat("Corruption", 10.0);
        p1->AddStat("Lust", 15.0);
        p1->AddStat("Authority", 10.0);
        p2->AddStat("Corruption", 5.0);
        p2->AddStat("Lust", 15.0);
        p2->AddStat("Willpower", -10.0);
    }
    if (p1->HasFetish(Fetish::Voyeurism) && p2->HasFetish(Fetish::Exhibitionism))
    {
        p1->AddStat("Lust", 5.0);
        p2->AddStat("Lust", 5.0);
        p2->AddStat("Inhibition", -5.0);
    }
}

void AssignParentChildFetishStats(Person* parent, Person* child)
{
    if ((parent->HasFetish(Fetish::Shota) && child->Gender == Gender::Male) || (parent->HasFetish(Fetish::Loli) && child->Gender == Gender::Female) || ((parent->HasFetish(Fetish::Futa) || parent->HasFetish(Fetish::Shota) || parent->HasFetish(Fetish::Loli)) && child->Gender == Gender::Futanari))
    {
        parent->AddStat("Corruption", 5.0);
        child->AddStat("Happiness", -5.0);
        child->AddStat("Lust", 5.0);
    }
    if (parent->HasFetish(Fetish::Incest))
    {
        parent->AddStat("Corruption", 10.0);
        child->AddStat("Happiness", -10.0);
        child->AddStat("Lust", 5.0);
        child->AddStat("Corruption", 5.0);
        if (child->HasFetish(Fetish::Incest))
        {
            if (child->LikesGender(parent->Gender))
            {
                child->AddStat("Happiness", 15.0);
                return;
            }
            child->AddStat("Happiness", 10.0);
            child->AddGenderPreference(parent->Gender, 25.0);
        }
    }
}

void AssignHead(Person* Per)
{
    int index;
    QString folder;
    if (Per->Job.Equals("Student"))
    {
        index = GetStudentHeadIndex();
        folder = Path.Combine("Images", "People", "Students");
    }
    else
    {
        index = GetAdultHeadIndex();
        folder = Path.Combine("Images", "People", "Adult");
    }
    Per->MaleHeadFileName = Path.Combine(folder, "Heads", "M_Head" + Conversions.ToString(index) + ".png");
    Per->FemaleHeadFileName = Path.Combine(folder, "Heads", "F_Head" + Conversions.ToString(index) + ".png");
}

void AddFavoriteSubject(Person* Per)
{
    // checked {
    if (Game::RNG.Next(10) == 0 && Game::DictOfSubjects.count() > 0)
    {
        SchoolSubject favSubject = Game::DictOfSubjects.Values.ElementAtOrDefault(Game::RNG.Next(Game::DictOfSubjects.count()));
        Per->GoodInSubject = favSubject.Name;
        switch (favSubject.SubjectFamily)
        {
        case SchoolSubjectFamily.Mathematics:
            Per->AddStat("Intelligence", (double)Game::RNG.Next(7, 12));
            break;
        case SchoolSubjectFamily.LifeScience:
            Per->AddStat("Intelligence", (double)Game::RNG.Next(2, 5));
            Per->AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
            return;
        case SchoolSubjectFamily.NaturalScience:
            Per->AddStat("Intelligence", (double)Game::RNG.Next(6, 13));
            return;
        case SchoolSubjectFamily.SocialScience:
            Per->AddStat("Intelligence", (double)Game::RNG.Next(2, 5));
            Per->AddStat("Loyalty", (double)Game::RNG.Next(4, 8));
            return;
        case SchoolSubjectFamily.ComputerStudies:
            Per->AddStat("Intelligence", (double)Game::RNG.Next(5, 10));
            Per->AddStat("Happiness", (double)Game::RNG.Next(2, 4));
            return;
        case SchoolSubjectFamily.Humanities:
            Per->AddStat("Happiness", (double)Game::RNG.Next(4, 8));
            Per->AddStat("Loyalty", (double)Game::RNG.Next(2, 5));
            return;
        case SchoolSubjectFamily.LanguageArts:
            Per->AddStat("Education", (double)Game::RNG.Next(4, 8));
            Per->AddStat("Charisma", (double)Game::RNG.Next(2, 5));
            return;
        case SchoolSubjectFamily.FineArts:
            Per->AddStat("Charisma", (double)Game::RNG.Next(4, 8));
            Per->AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
            return;
        case SchoolSubjectFamily.PhysicalEducation:
            Per->AddStat("Stamina", (double)Game::RNG.Next(4, 8));
            Per->AddStat("Appearance", (double)Game::RNG.Next(2, 5));
            return;
        case SchoolSubjectFamily.SexualEducation:
            Per->AddStat("Corruption", (double)Game::RNG.Next(1, 4));
            Per->AddStat("Lust", (double)Game::RNG.Next(2, 5));
            Per->AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
            return;
        default:
            return;
        }
    }
    // }
}
void AddSubjectExperience(Person* Per)
{
    if (availableSubjects.count() == 0)
    {
        // try {
        for (QHash<QString, SchoolSubject>::iterator it = Game::DictOfSubjects.Values.begin();
                it != Game::DictOfSubjects.Values.end(); ++it)
        {
            SchoolSubject s = enumerator.Current;
            if (s.CanBeTaught && s.GetAvailableLessonLocations().count() > 0)
            {
                availableSubjects.Add(s);
            }
        }
        // }
    }
    if (Per->Job.Equals("Teacher"))
    {
        // try {
        for (QHash<QString, SchoolSubject>::iterator it = Game::DictOfSubjects.Values.begin();
                it != Game::DictOfSubjects.Values.end(); ++it)
        {
            enumerator2.Current.AddSubjectExp(Per, Game::RNG.NextDouble() * 5.0);
        }
        return;
        // }
    }
    // try {
    for (QList<SchoolSubject>::iterator it = availableSubjects.begin();
            it != availableSubjects.end(); ++it)
    {
        SchoolSubject expr_D9 = enumerator3.Current;
        if (expr_D9.Name.Equals(Per->GoodInSubject))
        {
            Per->AddSubjectInstanceExp(Per->GoodInSubject, 10.0);
        }
        expr_D9.AddSubjectExp(Per, Game::RNG.NextDouble() * 5.0);
    }
    // }
    if (!Per->Virgin || !Per->AnalVirgin)
    {
        Per->AddSubjectFamilyExp(SchoolSubjectFamily.SexualEducation, 3.0 + Game::RNG.NextDouble() * 4.0);
    }
}
void MakeFuta(Person* Per)
{
    Per->Gender = Gender::Futanari;
    Per->ImageLocation = Path.Combine(Game::TheSchool.FolderLocation, "Images", "Female");
}
void SetGenderSizes(Person* NewPerson, int index, QString& folder)
{
    AssignHead(NewPerson);
    // checked {
    // try {
    QList<PopulationGenerationGenderSpecificData>.Enumerator enumerator = Game::ScenarioConfig.PopulationGenerationData[index].GenderSpecific.GetEnumerator();
    while (enumerator.MoveNext())
    {
        PopulationGenerationGenderSpecificData gend = enumerator.Current;
        if (NewPerson.Gender == gend.Gender)
        {
            NewPerson.PenisSize = (BodySize)Game::RNG.Next(gend.PenisSize.Min, gend.PenisSize.Max);
            NewPerson.intTesticleSize = (double)Game::RNG.Next(gend.TesticleSize.Min, gend.TesticleSize.Max);
            NewPerson.BreastSize = (BodySize)Game::RNG.Next(gend.BreastSize.Min, gend.BreastSize.Max);
            NewPerson.StomachSize = (BodySize)Game::RNG.Next(gend.StomachSize.Min, gend.StomachSize.Max);
            NewPerson.VaginaSize = (BodySize)Game::RNG.Next(gend.VaginaSize.Min, gend.VaginaSize.Max);
            NewPerson.AnalSize = (BodySize)Game::RNG.Next(gend.AnalSize.Min, gend.AnalSize.Max);
            break;
        }
    }
    // }
    // }
}

void SetGenderPreferences(Person* NewPerson, int index)
{
    PopulationGenerationGenderSpecificData genderSpecific = Game::ScenarioConfig.GetGenderSpecificDataForIndex(index, NewPerson.Gender);
    NewPerson.SetGenderPreference(Gender::Male, Game::RNG.NextGaussian(genderSpecific.LikesMale.Mean, genderSpecific.LikesMale.StdDev));
    NewPerson.SetGenderPreference(Gender::Female, Game::RNG.NextGaussian(genderSpecific.LikesFemale.Mean, genderSpecific.LikesFemale.StdDev));
    NewPerson.SetGenderPreference(Gender::Futanari, Game::RNG.NextGaussian(genderSpecific.LikesFutanari.Mean, genderSpecific.LikesFutanari.StdDev));
}
bool PersonNameIsUnique(Person* P)
{
    return !Game::DictOfPersonNames.ContainsKey(P->Name);
}
void GenerateStatsFor(Person* P, int Index)
{
    for(QList<StatRange>::iterator* stat = Game::ScenarioConfig.PopulationGenerationData[Index].StatRanges.begin();
            stat != Game::ScenarioConfig.PopulationGenerationData[Index].StatRanges.end(); ++stat)
        P->SetStat(stat.Stat, Game::RNG.Next(round(stat.Range.Min), round(stat.Range.Max)));
}
