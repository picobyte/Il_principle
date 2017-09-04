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
//#include


class Game {
    //int seed = Environment.TickCount;
    //ThreadLocal<Random> _rng = new ThreadLocal<Random>(new Func<Random>(Game._ClosureS__.SI._LambdaS__0_0));
    QMap<QString, Account> _DictOfAccounts;
    QMap<QString, Clubs> _ListOfClubs;
    QHash<long, Person> _DictOfPersonIDs;
    QHash<QString, Person> _DictOfPersonNames;
    QMap<QString, Person> _HiredTeacher;
    QMap<QString, Person> _NotHiredTeacher;
    QMap<QString, Person> _AvailableStaff;
    QMap<QString, Person> _HiredStaff;
    QHash<QString, Person> _OwnStudents;
    QHash<QString, Person> _OtherStudents;
    QHash<QString, Person> _ListOfPTA;
    QHash<QString, Person> _UnemployedPersons;
    QList<Person> _occupandlist;
    QList<SchoolClass> _ListSchoolClasses;
    QHash<QString, StatusEffect> _DictOfStatusEffects;
    QHash<QString, Stat> _DictOfStats;
    QHash<QString, Skill> _DictOfSkills;
    QList<QString> _ListOfJobs;
    ObservableCollection<SchoolUpgrade> _ListOfSchoolUpgrades;
    QMap<QString, Rule> _ListOfRules;
    QHash<QString, Item> _ListOfBaseItems;
    QHash<QString, SchoolSubject> _DictOfSubjects;
    QList<PersonScheduleHandler> _ListOfScheduleHandlers;
    QHash<QString, double> _CachedGlobalStats;
    QList<Button> _lstbutton;
    QList<long> _FavoriteStudentList;
public:
    CultureInfo _GameCulture;
    StatisticsManager _StatisticsManager;
    EventStructManager _StructManager;
    NotificationManager _NotifyManager;
    PersonRelationshipDatabase _RelationshipDatabase;
    TheWorld _TheSchool;
    ClassroomAssignments _ClassAssignments;
    GameCalendar _SchoolCalendar;
    Time _GameTime;
    Person _HeadTeacher;

    QString _GamePath;
    QString inteventlog;
    bool _EventLogflag;
    int _DesiredNumSchoolClasses;
    SchoolClass _SpareStudentsClass;
    GameScenarioConfig _ScenarioConfig;
    PopulationGenerator _PopulationManager;
    int _TickCount;
    int _helpercounter;
    QString _LastWorldLocationPath;
    bool _GameInitialized;
    bool _GameLoading;
    int _LastAutosaveDay;
    bool _CheatsUsed;
    const Random RNG() const
    {
        return Game._rng.Value;
    }
    const Location PlayerLocation() const
    {
        Location PlayerLocation;
        if (Game.HeadTeacher == NULL)
        {
            return NULL;
                }
                return Game.HeadTeacher.CurrentLocation;
    }
    Person GetPerson(long PerID)
    {
        Person GetPerson;
        if (Game.DictOfPersonIDs.ContainsKey(PerID))
            return Game.DictOfPersonIDs[PerID];

        return NULL;
    }
    Person GetPerson(QString PerName)
    {
        Person GetPerson;
        if (!$1.isEmpty() && Game.DictOfPersonNames.ContainsKey(PerName))
            return Game.DictOfPersonNames[PerName];

        return NULL;
    }
    QString GetPersonDisplayName(QString PerName)
    {
        Person per = Game.GetPerson(PerName);
        QString GetPersonDisplayName;
        if (per != NULL)
            return per.DisplayName;

        return PerName;
    }
    Location GetLocation(QString LocName)
    {
        Location GetLocation;
        if (!$1.isEmpty() && Game.TheSchool.DictOfLocation.ContainsKey(LocName))
            return Game.TheSchool.DictOfLocation[LocName];

        return NULL;
    }
    Location GetWorkForJob(QString JobName)
    {
        Predicate<LocationJobDetails> SI1 = (LocationJobDetails j) => JobName.Equals(j.JobTitle) && !j.IsFullyStaffed();
        return Game.TheSchool.DictOfLocation.Values.FirstOrDefault((Location loc) => loc.AssociatedJobs.Exists(SI1));
    }
    Clubs GetClub(QString ClubName)
    {
        Clubs GetClub;
        if (!$1.isEmpty())
        {
            if (Game.ListOfClubs.ContainsKey(ClubName))
            {
                GetClub = Game.ListOfClubs[ClubName];
            }
            else
            {
                // try {
                for (IEnumerator<Clubs>::iterator it = Game.ListOfClubs.Values.begin();
                        it != Game.ListOfClubs.Values.end(); ++it)
                {
                    Clubs Club = enumerator.Current;
                    // try {
                    for (QList<ClubLevel>::iterator it2 = Club.ClubLevels.begin();
                            it2 != Club.ClubLevels.end(); ++it2)
                    {
                        if (enumerator2.Current.Name.Equals(ClubName))
                        {
                            GetClub = Club;
                            return GetClub;
                        }
                    }
                    // }
                }
                // }
                GetClub = NULL;
            }
        }
        else
        {
            GetClub = NULL;
        }
        return GetClub;
    }
    SchoolSubject GetSubject(QString SubjName)
    {
        SchoolSubject GetSubject;
        if (Game.DictOfSubjects.ContainsKey(SubjName))
            return Game.DictOfSubjects[SubjName];

        return NULL;
    }
    void RecalculateStaffSalary()
    {
        // checked {
        int Total = 0;
        // try {
        for (IEnumerator<Person>::iterator it = Game.HiredStaff.Values.begin();
                it != Game.HiredStaff.Values.end(); ++it)
        {
            Person Per = enumerator.Current;
            Total -= Per.Salary;
        }
        // }
        if (!Game.DictOfAccounts.ContainsKey("Staff Salary"))
        {
            Account ac = new Account
            {
                Name = "Staff Salary",
                PayPeriode = Payperiode.Monthly,
                Active = true
            };
            Game.DictOfAccounts.Add(ac.Name, ac);
        }
        Game.DictOfAccounts["Staff Salary"].Payment = Total;
        // }
    }
    void ClearAllLists()
    {
        Game.DictOfAccounts.Clear();
        Game.ListOfClubs.Clear();
        Game.DictOfPersonIDs.Clear();
        Game.DictOfPersonNames.Clear();
        Game.HiredTeacher.Clear();
        Game.NotHiredTeacher.Clear();
        Game.AvailableStaff.Clear();
        Game.HiredStaff.Clear();
        Game.OwnStudents.Clear();
        Game.OtherStudents.Clear();
        Game.ListOfPTA.Clear();
        Game.UnemployedPersons.Clear();
        Game.occupandlist.Clear();
        Game.ListSchoolClasses.Clear();
        Game.SpareStudentsClass = new SchoolClass();
        Game.DictOfStatusEffects.Clear();
        Game.DictOfStats.Clear();
        Game.DictOfSkills.Clear();
        Game.ListOfJobs.Clear();
        Game.ListOfSchoolUpgrades.Clear();
        Game.ListOfRules.Clear();
        Game.ListOfBaseItems.Clear();
        Game.DictOfSubjects.Clear();
        Game.ListOfScheduleHandlers.Clear();
        Game.FavoriteStudentList.Clear();
    }

    Game(QJsonObject *d = NULL)
    {
        if (d) init(d);

    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJ_FROM_JSON_AS(it, _GameCulture)
            else __IF_OBJ_FROM_JSON_AS(it, _StatisticsManager)
            else __IF_OBJ_FROM_JSON_AS(it, _StructManager)
            else __IF_OBJ_FROM_JSON_AS(it, _NotifyManager)
            else __IF_OBJ_FROM_JSON_AS(it, _RelationshipDatabase)
            else __IF_OBJ_FROM_JSON_AS(it, _TheSchool)
            else __IF_OBJ_FROM_JSON_AS(it, _ClassAssignments)
            else __IF_OBJ_FROM_JSON_AS(it, _SchoolCalendar)
            else __IF_OBJ_FROM_JSON_AS(it, _GameTime)
            else __IF_OBJ_FROM_JSON_AS(it, _HeadTeacher)
            else __IF_VAR_FROM_JSON_AS(it, _GamePath, toString)
            else __IF_VAR_FROM_JSON_AS(it, inteventlog, toString)
            else __IF_VAR_FROM_JSON_AS(it, _EventLogflag, toBool)
            else __IF_OBJLIST_FROM_JSON(it, _occupandlist, Person)
            else __IF_OBJLIST_FROM_JSON(it, _ListSchoolClasses, SchoolClass)
            else __IF_VAR_FROM_JSON_AS(it, _DesiredNumSchoolClasses, toInt)
            else __IF_OBJ_FROM_JSON_AS(it, _SpareStudentsClass)
            else __IF_LIST_FROM_JSON_TYPED(it, _ListOfJobs, toString)
            else __IF_OBJLIST_FROM_JSON(it, _ListOfScheduleHandlers, PersonScheduleHandler)
            else __IF_OBJ_FROM_JSON_AS(it, _ScenarioConfig)
            else __IF_OBJLIST_FROM_JSON(it, _lstbutton, Button)
            else __IF_OBJ_FROM_JSON_AS(it, _PopulationManager)
            else __IF_VAR_FROM_JSON_AS(it, _TickCount, toInt)
            else __IF_OBJLIST_FROM_JSON(it, _FavoriteStudentList, long)
            else __IF_VAR_FROM_JSON_AS(it, _helpercounter, toInt)
            else __IF_VAR_FROM_JSON_AS(it, _LastWorldLocationPath, toString)
            else __IF_VAR_FROM_JSON_AS(it, _GameInitialized, toBool)
            else __IF_VAR_FROM_JSON_AS(it, _GameLoading, toBool)
            else __IF_VAR_FROM_JSON_AS(it, _LastAutosaveDay, toInt)
            else __IF_VAR_FROM_JSON_AS(it, _CheatsUsed, toBool)
            // *INDENT-ON*
        }
    }

#endif // GAME_H
