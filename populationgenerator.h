#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H
#include "json_macros.h"
#include "game.h"

class PopulationGenerator {
public:
    QList<QString> GirlNames;
    QList<QString> BoyNames;
    QList<QString> Surnames;
    int PopulationOffset;
    QList<int> AdultHeads;
    QList<int> StudentHeads;
    QList<SchoolSubject> availableSubjects;
    int StudentIndex() const;

    PopulationGenerator(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, PopulationOffset, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, GirlNames, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, BoyNames, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, Surnames, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, AdultHeads, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, StudentHeads, toInt)
            else __IF_OBJLIST_FROM_JSON(it, availableSubjects, SchoolSubject)
            // *INDENT-ON*
        }
        LoadNames();
        for (int i = 0; i < 100; ++i) {
            AdultHeads.append(i); // is this really necessary?
            StudentHeads.append(i);
        }
    }
    void LoadNames();
    QString GetForename(Gender G) const
    {
        if (G == Gender::Male)
            return BoyNames[qrand() % BoyNames.length()];
        else
            return GirlNames[qrand() % GirlNames.length()];
    }
    QString GetLastname() const
    {
        return Surnames[qrand() % Surnames.length()];
    }
    QDate GetRandomDateForAge(int Age, QDate& ReferenceDate)
    {
        return ReferenceDate.addYears(-(Age + 1)).addDays(qrand() % 365);
    }
    int GetAdultHeadIndex()
    {
        return AdultHeads.takeAt(qrand() % AdultHeads.count());
    }
    int GetStudentHeadIndex()
    {
        return StudentHeads.takeAt(qrand() % StudentHeads.count());
    }
    void CreatePopulation(int count);
    Person* initPerson(const QString&, Location*, const int);
    void completeParent(Person*, int, int);

    void CreateFamily(QList<Person>* outList = NULL);
    void AssignPersonFetishStats(Person* per);
    void AssignPersonFetishStats(Person p1, Person p2)
    {
        if (p1.HasFetish(Fetish::Sadism) && p2.HasFetish(Fetish::Masochism))
        {
            p1.AddStat("Corruption", 10.0);
            p1.AddStat("Lust", 15.0);
            p1.AddStat("Authority", 10.0);
            p2.AddStat("Corruption", 5.0);
            p2.AddStat("Lust", 15.0);
            p2.AddStat("Willpower", -10.0);
        }
        if (p1.HasFetish(Fetish::Voyeurism) && p2.HasFetish(Fetish::Exhibitionism))
        {
            p1.AddStat("Lust", 5.0);
            p2.AddStat("Lust", 5.0);
            p2.AddStat("Inhibition", -5.0);
        }
    }
    void AssignParentChildFetishStats(Person parent, Person child)
    {
        if ((parent.HasFetish(Fetish::Shota) && child.Gender == Gender::Male) || (parent.HasFetish(Fetish::Loli) && child.Gender == Gender::Female) || ((parent.HasFetish(Fetish::Futa) || parent.HasFetish(Fetish::Shota) || parent.HasFetish(Fetish::Loli)) && child.Gender == Gender::Futanari))
        {
            parent.AddStat("Corruption", 5.0);
            child.AddStat("Happiness", -5.0);
            child.AddStat("Lust", 5.0);
        }
        if (parent.HasFetish(Fetish::Incest))
        {
            parent.AddStat("Corruption", 10.0);
            child.AddStat("Happiness", -10.0);
            child.AddStat("Lust", 5.0);
            child.AddStat("Corruption", 5.0);
            if (child.HasFetish(Fetish::Incest))
            {
                if (child.LikesGender(parent.Gender))
                {
                    child.AddStat("Happiness", 15.0);
                    return;
                }
                child.AddStat("Happiness", 10.0);
                child.AddGenderPreference(parent.Gender, 25.0);
            }
        }
    }
    void AssignHead(Person Per)
    {
        int index;
        QString folder;
        if (Per.Job.Equals("Student"))
        {
            index = GetStudentHeadIndex();
            folder = Path.Combine("Images", "People", "Students");
        }
        else
        {
            index = GetAdultHeadIndex();
            folder = Path.Combine("Images", "People", "Adult");
        }
        Per.MaleHeadFileName = Path.Combine(folder, "Heads", "M_Head" + Conversions.ToString(index) + ".png");
        Per.FemaleHeadFileName = Path.Combine(folder, "Heads", "F_Head" + Conversions.ToString(index) + ".png");
    }
    void AddFavoriteSubject(Person Per)
    {
        // checked {
        if (Game::RNG.Next(10) == 0 && Game::DictOfSubjects.count() > 0)
        {
            SchoolSubject favSubject = Game::DictOfSubjects.Values.ElementAtOrDefault(Game::RNG.Next(Game::DictOfSubjects.count()));
            Per.GoodInSubject = favSubject.Name;
            switch (favSubject.SubjectFamily)
            {
            case SchoolSubjectFamily.Mathematics:
                Per.AddStat("Intelligence", (double)Game::RNG.Next(7, 12));
                break;
            case SchoolSubjectFamily.LifeScience:
                Per.AddStat("Intelligence", (double)Game::RNG.Next(2, 5));
                Per.AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
                return;
            case SchoolSubjectFamily.NaturalScience:
                Per.AddStat("Intelligence", (double)Game::RNG.Next(6, 13));
                return;
            case SchoolSubjectFamily.SocialScience:
                Per.AddStat("Intelligence", (double)Game::RNG.Next(2, 5));
                Per.AddStat("Loyalty", (double)Game::RNG.Next(4, 8));
                return;
            case SchoolSubjectFamily.ComputerStudies:
                Per.AddStat("Intelligence", (double)Game::RNG.Next(5, 10));
                Per.AddStat("Happiness", (double)Game::RNG.Next(2, 4));
                return;
            case SchoolSubjectFamily.Humanities:
                Per.AddStat("Happiness", (double)Game::RNG.Next(4, 8));
                Per.AddStat("Loyalty", (double)Game::RNG.Next(2, 5));
                return;
            case SchoolSubjectFamily.LanguageArts:
                Per.AddStat("Education", (double)Game::RNG.Next(4, 8));
                Per.AddStat("Charisma", (double)Game::RNG.Next(2, 5));
                return;
            case SchoolSubjectFamily.FineArts:
                Per.AddStat("Charisma", (double)Game::RNG.Next(4, 8));
                Per.AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
                return;
            case SchoolSubjectFamily.PhysicalEducation:
                Per.AddStat("Stamina", (double)Game::RNG.Next(4, 8));
                Per.AddStat("Appearance", (double)Game::RNG.Next(2, 5));
                return;
            case SchoolSubjectFamily.SexualEducation:
                Per.AddStat("Corruption", (double)Game::RNG.Next(1, 4));
                Per.AddStat("Lust", (double)Game::RNG.Next(2, 5));
                Per.AddStat("Inhibition", (double)(0 - Game::RNG.Next(2, 5)));
                return;
            default:
                return;
            }
        }
        // }
    }
    void AddSubjectExperience(Person Per)
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
        if (Per.Job.Equals("Teacher"))
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
            if (expr_D9.Name.Equals(Per.GoodInSubject))
            {
                Per.AddSubjectInstanceExp(Per.GoodInSubject, 10.0);
            }
            expr_D9.AddSubjectExp(Per, Game::RNG.NextDouble() * 5.0);
        }
        // }
        if (!Per.Virgin || !Per.AnalVirgin)
        {
            Per.AddSubjectFamilyExp(SchoolSubjectFamily.SexualEducation, 3.0 + Game::RNG.NextDouble() * 4.0);
        }
    }
    void MakeFuta(Person Per)
    {
        Per.Gender = Gender::Futanari;
        Per.ImageLocation = Path.Combine(Game::TheSchool.FolderLocation, "Images", "Female");
    }
    void SetGenderSizes(Person NewPerson, int index, QString folder)
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
    void SetGenderPreferences(Person NewPerson, int index)
    {
        PopulationGenerationGenderSpecificData genderSpecific = Game::ScenarioConfig.GetGenderSpecificDataForIndex(index, NewPerson.Gender);
        NewPerson.SetGenderPreference(Gender::Male, Game::RNG.NextGaussian(genderSpecific.LikesMale.Mean, genderSpecific.LikesMale.StdDev));
        NewPerson.SetGenderPreference(Gender::Female, Game::RNG.NextGaussian(genderSpecific.LikesFemale.Mean, genderSpecific.LikesFemale.StdDev));
        NewPerson.SetGenderPreference(Gender::Futanari, Game::RNG.NextGaussian(genderSpecific.LikesFutanari.Mean, genderSpecific.LikesFutanari.StdDev));
    }
    bool PersonNameIsUnique(Person P)
    {
        return !Game::DictOfPersonNames.ContainsKey(P.Name);
    }
    void GenerateStatsFor(Person P, int Index)
    {
        // try {
        QList<StatRange>.Enumerator enumerator = Game::ScenarioConfig.PopulationGenerationData[Index].StatRanges.GetEnumerator();
        while (enumerator.MoveNext())
        {
            StatRange stat = enumerator.Current;
            P.SetStat(stat.Stat, (double)checked(Game::RNG.Next((int)Math.Round(stat.Range.Min), (int)Math.Round(stat.Range.Max))));
        }
        // }
    }
};

#endif // POPULATIONGENERATOR_H
