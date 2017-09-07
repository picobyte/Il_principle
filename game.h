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
#include <QPushButton>

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
#include "schoolclass.h"
#include "eventstructmanager.h"

#include "classroomassignments.h"
#include "gamecalendar.h"
#include "notificationmanager.h"
#include "personrelationshipdatabase.h"
#include "populationgenerator.h"
#include "statisticsmanager.h"
#include "gtime.h"
#include "personschedulehandler.h"
#include "gamescenarioconfig.h"



class Game {
public:
    //int seed = Environment.TickCount;
    //ThreadLocal<Random> _rng = new ThreadLocal<Random>(new Func<Random>(_ClosureS__.SI._LambdaS__0_0));
    static QMap<QString, Account> DictOfAccounts;
    static QMap<QString, Clubs> ListOfClubs;
    static QHash<long, Person> DictOfPersonIDs;
    static QHash<QString, Person> DictOfPersonNames;
    static QMap<QString, Person> HiredTeacher;
    static QMap<QString, Person> NotHiredTeacher;
    static QMap<QString, Person> AvailableStaff;
    static QMap<QString, Person> HiredStaff;
    static QHash<QString, Person> OwnStudents;
    static QHash<QString, Person> OtherStudents;
    static QHash<QString, Person> ListOfPTA;
    static QHash<QString, Person> UnemployedPersons;
    static QList<Person> occupandlist;
    static QList<SchoolClass> ListSchoolClasses;
    static QHash<QString, StatusEffect> DictOfStatusEffects;
    static QHash<QString, Stat> DictOfStats;
    static QHash<QString, Skill> DictOfSkills;
    static QList<QString> _ListOfJobs;
    static QList<SchoolUpgrade> ListOfSchoolUpgrades;
    static QMap<QString, Rule> ListOfRules;
    static QHash<QString, Item> ListOfBaseItems;
    static QHash<QString, SchoolSubject> DictOfSubjects;
    static QList<PersonScheduleHandler> ListOfScheduleHandlers;
    static QHash<QString, double> CachedGlobalStats;
    static QList<QPushButton> lstbutton;
    static QSet<long> FavoriteStudentList;
    static QLocale GameCulture; //orig: CultureInfo GameCulture;
    static StatisticsManager statisticsManager;
    static EventStructManager StructManager;
    static NotificationManager NotifyManager;
    static PersonRelationshipDatabase RelationshipDatabase;
    static TheWorld TheSchool;
    static ClassroomAssignments ClassAssignments;
    static GameCalendar SchoolCalendar;
    static gTime GameTime;
    static Person* HeadTeacher;

    static QString GamePath;
    static QString inteventlog;
    static bool EventLogflag;
    static int DesiredNumSchoolClasses;
    static SchoolClass SpareStudentsClass;
    static GameScenarioConfig ScenarioConfig;
    static PopulationGenerator PopulationManager;
    static int TickCount;
    static int helpercounter;
    static QString LastWorldLocationPath;
    static bool GameInitialized;
    static bool GameLoading;
    static int LastAutosaveDay;
    static bool CheatsUsed;
    const Random RNG() const
    {
        return _rng.Value;
    }
    Location* PlayerLocation() const
    {
        if (HeadTeacher == NULL)
            return NULL;

        return &HeadTeacher->CurrentLocation;
    }
    Person* GetPerson(long PerID)
    {
        if (DictOfPersonIDs.contains(PerID))
            return &DictOfPersonIDs[PerID];

        return NULL;
    }
    Person* GetPerson(QString PerName)
    {
        if (DictOfPersonNames.contains(PerName))
            return &DictOfPersonNames[PerName];

        return NULL;
    }
    QString GetPersonDisplayName(QString PerName)
    {
        Person* per = GetPerson(PerName);
        if (per != NULL)
            return per->DisplayName;

        return PerName;
    }
    static Location* GetLocation(QString LocName)
    {
        if (TheSchool.DictOfLocation.contains(LocName))
            return &TheSchool.DictOfLocation[LocName];

        return NULL;
    }
    Location* GetWorkForJob(QString JobName)
    {
        Predicate<LocationJobDetails> SI1 = (LocationJobDetails j) => JobName.Equals(j.JobTitle) && !j.IsFullyStaffed();
        return &TheSchool.DictOfLocation.Values.FirstOrDefault((Location loc) => loc.AssociatedJobs.Exists(SI1));
    }
    Clubs* GetClub(QString ClubName)
    {
        if (ClubName.isEmpty())
            return NULL;

        if (ListOfClubs.contains(ClubName))
            return &ListOfClubs[ClubName];

        // try {
        for (IEnumerator<Clubs>::iterator it = ListOfClubs.Values.begin();
                it != ListOfClubs.Values.end(); ++it) {
            // try {
            for (QList<ClubLevel>::iterator it2 = Club->ClubLevels.begin();
                    it2 != Club->ClubLevels.end(); ++it2)
                if (enumerator2.Current.Name.Equals(ClubName))
                    return &(*Club);
            // }
        }
        // }
        return NULL;
    }
    static SchoolSubject* GetSubject(QString SubjName)
    {
        if (DictOfSubjects.contains(SubjName))
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
        if (!DictOfAccounts.contains("Staff Salary"))
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
