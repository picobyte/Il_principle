#ifndef GAME_H
#define GAME_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QStringList>
#include <QCoreApplication>
#include <QDirIterator>
#include <QStringList>
#include <QString>
#include <QSet>
#include <QTime>
#include <QList>
#include <QLocale>
#include <QHash>
#include "person.h"
#include "account.h"
#include "clubs.h"
#include "stat.h"
#include "skill.h"
#include "rule.h"
#include "schoolsubject.h"
#include "item.h"
#include "statuseffect.h"
#include "schoolupgrade.h"
#include "rule.h"
#include "eventstructmanager.h"

//#include


class Game {
    //int seed = Environment.TickCount;
    //ThreadLocal<Random> _rng = new ThreadLocal<Random>(new Func<Random>(_ClosureS__.SI._LambdaS__0_0));
    QMap<QString, Account> DictOfAccounts;
    QMap<QString, Clubs> ListOfClubs;
    QHash<long, Person> DictOfPersonIDs;
    QHash<QString, Person> DictOfPersonNames;
    QMap<QString, Person> HiredTeacher;
    QMap<QString, Person> NotHiredTeacher;
    QMap<QString, Person> AvailableStaff;
    QMap<QString, Person> HiredStaff;
    QHash<QString, Person> OwnStudents;
    QHash<QString, Person> OtherStudents;
    QHash<QString, Person> ListOfPTA;
    QHash<QString, Person> UnemployedPersons;
    QList<Person> occupandlist;
    QList<SchoolClass> ListSchoolClasses;
    QHash<QString, StatusEffect> DictOfStatusEffects;
    QHash<QString, Stat> DictOfStats;
    QHash<QString, Skill> DictOfSkills;
    QList<QString> _ListOfJobs;
    ObservableCollection<SchoolUpgrade> ListOfSchoolUpgrades;
    QMap<QString, Rule> ListOfRules;
    QHash<QString, Item> ListOfBaseItems;
    QHash<QString, SchoolSubject> DictOfSubjects;
    QList<PersonScheduleHandler> ListOfScheduleHandlers;
    QHash<QString, double> CachedGlobalStats;
    QList<Button> lstbutton;
    QList<long> FavoriteStudentList;
public:
    QLocale GameCulture; //orig: CultureInfo GameCulture;
    StatisticsManager StatisticsManager;
    EventStructManager StructManager;
    NotificationManager NotifyManager;
    PersonRelationshipDatabase RelationshipDatabase;
    TheWorld TheSchool;
    ClassroomAssignments ClassAssignments;
    GameCalendar SchoolCalendar;
    Time GameTime;
    Person HeadTeacher;

    QString GamePath;
    QString inteventlog;
    bool EventLogflag;
    int DesiredNumSchoolClasses;
    SchoolClass SpareStudentsClass;
    GameScenarioConfig ScenarioConfig;
    PopulationGenerator PopulationManager;
    int TickCount;
    int helpercounter;
    QString LastWorldLocationPath;
    bool GameInitialized;
    bool GameLoading;
    int LastAutosaveDay;
    bool CheatsUsed;
    const Random RNG() const
    {
        return _rng.Value;
    }
    const Location PlayerLocation() const
    {
        Location PlayerLocation;
        if (HeadTeacher == NULL)
        {
            return NULL;
                }
                return HeadTeacher.CurrentLocation;
    }
    Person GetPerson(long PerID)
    {
        Person GetPerson;
        if (DictOfPersonIDs.ContainsKey(PerID))
            return DictOfPersonIDs[PerID];

        return NULL;
    }
    Person GetPerson(QString PerName)
    {
        Person GetPerson;
        if (!$1.isEmpty() && DictOfPersonNames.ContainsKey(PerName))
            return DictOfPersonNames[PerName];

        return NULL;
    }
    QString GetPersonDisplayName(QString PerName)
    {
        Person per = GetPerson(PerName);
        QString GetPersonDisplayName;
        if (per != NULL)
            return per.DisplayName;

        return PerName;
    }
    Location GetLocation(QString LocName)
    {
        Location GetLocation;
        if (!$1.isEmpty() && TheSchool.DictOfLocation.ContainsKey(LocName))
            return TheSchool.DictOfLocation[LocName];

        return NULL;
    }
    Location GetWorkForJob(QString JobName)
    {
        Predicate<LocationJobDetails> SI1 = (LocationJobDetails j) => JobName.Equals(j.JobTitle) && !j.IsFullyStaffed();
        return TheSchool.DictOfLocation.Values.FirstOrDefault((Location loc) => loc.AssociatedJobs.Exists(SI1));
    }
    Clubs* GetClub(QString ClubName)
    {
        if (ClubName.isEmpty())
            return NULL;

        if (ListOfClubs.ContainsKey(ClubName))
            return ListOfClubs[ClubName];

        // try {
        for (IEnumerator<Clubs>::iterator it = ListOfClubs.Values.begin();
                it != ListOfClubs.Values.end(); ++it) {
            // try {
            for (QList<ClubLevel>::iterator it2 = Club->ClubLevels.begin();
                    it2 != Club->ClubLevels.end(); ++it2)
                if (enumerator2.Current.Name.Equals(ClubName))
                    return *Club;
            // }
        }
        // }
        return NULL;
    }
    SchoolSubject* GetSubject(QString SubjName)
    {
        if (DictOfSubjects.ContainsKey(SubjName))
            return &DictOfSubjects[SubjName];

        return NULL;
    }
    void RecalculateStaffSalary()
    {
        // checked {
        int Total = 0;
        // try {
        for (IEnumerator<Person>::iterator it = HiredStaff.Values.begin();
                it != HiredStaff.Values.end(); ++it)
        {
            Person Per = enumerator.Current;
            Total -= Per.Salary;
        }
        // }
        if (!DictOfAccounts.ContainsKey("Staff Salary"))
        {
            Account ac = new Account
            {
                Name = "Staff Salary",
                PayPeriode = Payperiode.Monthly,
                Active = true
            };
            DictOfAccounts.Add(ac.Name, ac);
        }
        DictOfAccounts["Staff Salary"].Payment = Total;
        // }
    }
    void ClearAllLists()
    {
        DictOfAccounts.clear();
        ListOfClubs.clear();
        DictOfPersonIDs.clear();
        DictOfPersonNames.clear();
        HiredTeacher.clear();
        NotHiredTeacher.clear();
        AvailableStaff.clear();
        HiredStaff.clear();
        OwnStudents.clear();
        OtherStudents.clear();
        ListOfPTA.clear();
        UnemployedPersons.clear();
        occupandlist.clear();
        ListSchoolClasses.clear();
        SpareStudentsClass = new SchoolClass();
        DictOfStatusEffects.clear();
        DictOfStats.clear();
        DictOfSkills.clear();
        ListOfJobs.clear();
        ListOfSchoolUpgrades.clear();
        ListOfRules.clear();
        ListOfBaseItems.clear();
        DictOfSubjects.clear();
        ListOfScheduleHandlers.clear();
        FavoriteStudentList.clear();
    }

    Game(QJsonObject *d = NULL)
    {
        if (d) init(d);

    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJ_FROM_JSON(it, GameCulture)
            else __IF_OBJ_FROM_JSON(it, StatisticsManager)
            else __IF_OBJ_FROM_JSON(it, StructManager)
            else __IF_OBJ_FROM_JSON(it, NotifyManager)
            else __IF_OBJ_FROM_JSON(it, RelationshipDatabase)
            else __IF_OBJ_FROM_JSON(it, TheSchool)
            else __IF_OBJ_FROM_JSON(it, ClassAssignments)
            else __IF_OBJ_FROM_JSON(it, SchoolCalendar)
            else __IF_OBJ_FROM_JSON(it, GameTime)
            else __IF_OBJ_FROM_JSON(it, HeadTeacher)
            else __IF_VAR_FROM_JSON_AS(it, GamePath, toString)
            else __IF_VAR_FROM_JSON_AS(it, inteventlog, toString)
            else __IF_VAR_FROM_JSON_AS(it, EventLogflag, toBool)
            else __IF_OBJLIST_FROM_JSON(it, occupandlist, Person)
            else __IF_OBJLIST_FROM_JSON(it, ListSchoolClasses, SchoolClass)
            else __IF_VAR_FROM_JSON_AS(it, DesiredNumSchoolClasses, toInt)
            else __IF_OBJ_FROM_JSON(it, SpareStudentsClass)
            else __IF_LIST_FROM_JSON_TYPED(it, ListOfJobs, toString)
            else __IF_OBJLIST_FROM_JSON(it, ListOfScheduleHandlers, PersonScheduleHandler)
            else __IF_OBJ_FROM_JSON(it, ScenarioConfig)
            else __IF_OBJLIST_FROM_JSON(it, lstbutton, Button)
            else __IF_OBJ_FROM_JSON(it, PopulationManager)
            else __IF_VAR_FROM_JSON_AS(it, TickCount, toInt)
            else __IF_OBJLIST_FROM_JSON(it, FavoriteStudentList, long)
            else __IF_VAR_FROM_JSON_AS(it, helpercounter, toInt)
            else __IF_VAR_FROM_JSON_AS(it, LastWorldLocationPath, toString)
            else __IF_VAR_FROM_JSON_AS(it, GameInitialized, toBool)
            else __IF_VAR_FROM_JSON_AS(it, GameLoading, toBool)
            else __IF_VAR_FROM_JSON_AS(it, LastAutosaveDay, toInt)
            else __IF_VAR_FROM_JSON_AS(it, CheatsUsed, toBool)
            // *INDENT-ON*
        }
    }
};
#endif // GAME_H
