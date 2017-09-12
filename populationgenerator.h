#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H
#include "json_macros.h"
#include "game.h"

class PopulationGenerator {
    std::default_random_engine roll;
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
    void AssignPersonFetishStats(Person* p1, Person* p2);
    void AssignParentChildFetishStats(Person* parent, Person* child);
    void AssignHead(Person* Per);
    void AddFavoriteSubject(Person* Per);
    void AddSubjectExperience(Person* Per);
    void MakeFuta(Person* Per);
    void SetGenderSizes(Person* NewPerson, int index, QString& folder);
    void SetGenderPreferences(Person* NewPerson, int index);
    bool PersonNameIsUnique(Person* P);
    void GenerateStatsFor(Person* P, int Index);
};

#endif // POPULATIONGENERATOR_H
