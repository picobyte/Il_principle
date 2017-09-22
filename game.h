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
#include <random>

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
#include "theworld.h"

#include "classroomassignments.h"
#include "gamecalendar.h"
#include "notificationmanager.h"
#include "personrelationshipdatabase.h"
#include "populationgenerator.h"
#include "statisticsmanager.h"
#include "gtime.h"
#include "personschedulehandler.h"
#include "gamescenarioconfig.h"

class RandomGen {
    static std::default_random_engine roll;
public:
    static int Next(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(roll);
    }
    static int Next(int max)
    {
        return Next(0, max);
    }
    static int NextGaussian(double mean, double stdev)
    {
        std::normal_distribution<> d(mean, stdev);
        return d(roll);
    }
    static double NextDouble() {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        return dis(roll);
    }
};

namespace Game {
    RandomGen RNG;
    //int seed = Environment.TickCount;
    //ThreadLocal<Random> _rng = new ThreadLocal<Random>(new Func<Random>(_ClosureS__.SI._LambdaS__0_0));
    QMap<QString, Account> DictOfAccounts;
    QMap<QString, Clubs> ListOfClubs;
    QHash<long, Person*> DictOfPersonIDs;
    QHash<QString, Person*> DictOfPersonNames;
    QMap<QString, Person*> HiredTeacher;
    QMap<QString, Person*> NotHiredTeacher;
    QMap<QString, Person*> AvailableStaff;
    QMap<QString, Person*> HiredStaff;
    QHash<QString, Person*> OwnStudents;
    QHash<QString, Person*> OtherStudents;
    QHash<QString, Person*> ListOfPTA;
    QHash<QString, Person*> UnemployedPersons;
    QList<Person> occupandlist;
    QList<SchoolClass> ListSchoolClasses;
    QHash<QString, StatusEffect> DictOfStatusEffects;
    QHash<QString, Stat> DictOfStats;
    QHash<QString, Skill> DictOfSkills;
    QList<QString> ListOfJobs;
    QList<SchoolUpgrade> ListOfSchoolUpgrades;
    QMap<QString, Rule> ListOfRules;
    QHash<QString, Item> ListOfBaseItems;
    QHash<QString, SchoolSubject> DictOfSubjects;
    QList<PersonScheduleHandler> ListOfScheduleHandlers;
    QHash<QString, double> CachedGlobalStats;
    QList<QPushButton> lstbutton;
    QSet<long> FavoriteStudentList;
    QLocale GameCulture = QString("en-GB"); //orig: CultureInfo GameCulture;
    StatisticsManager statisticsManager;
    EventStructManager StructManager;
    NotificationManager NotifyManager;
    PersonRelationshipDatabase RelationshipDatabase;
    ClassroomAssignments ClassAssignments;
    GameCalendar SchoolCalendar;
    gTime GameTime;
    Person* HeadTeacher;

    QString GamePath;
    QString inteventlog;
    bool EventLogflag = false;
    int DesiredNumSchoolClasses = 2;
    SchoolClass SpareStudentsClass;
    GameScenarioConfig ScenarioConfig;
    PopulationGenerator PopulationManager;
    int TickCount = 0;
    int helpercounter;
    QString LastWorldLocationPath = "";
    bool GameInitialized = false;
    bool GameLoading = false;
    int LastAutosaveDay = 1;
    bool CheatsUsed = false;

    Location* PlayerLocation();
    Person* GetPerson(long PerID)
    {
        if (DictOfPersonIDs.contains(PerID))
            return DictOfPersonIDs[PerID];

        return NULL;
    }
    Person* GetPerson(QString PerName)
    {
        if (DictOfPersonNames.contains(PerName))
            return DictOfPersonNames[PerName];

        return NULL;
    }
    QString GetPersonDisplayName(QString& PerName);
    Location* GetLocation(QString LocName)
    {
        if (TheWorld::DictOfLocation.contains(LocName))
            return &TheWorld::DictOfLocation[LocName];

        return NULL;
    }
    Location* GetWorkForJob(QString& JobName);
    Clubs* GetClub(QString ClubName)
    {
        if (ClubName.isEmpty())
            return NULL;

        if (ListOfClubs.contains(ClubName))
            return &ListOfClubs[ClubName];

        // try {
        for (QMap<QString, Clubs>::iterator Club = ListOfClubs.begin();
                Club != ListOfClubs.end(); ++Club) {
            // try {
            for (QList<ClubLevel>::iterator it2 = Club->ClubLevels.begin();
                 it2 != Club->ClubLevels.end(); ++it2) {
                if (it2->Name == ClubName)
                    return &(*Club);
            }
        }
        // }
        return NULL;
    }
    SchoolSubject* GetSubject(QString SubjName)
    {
        if (DictOfSubjects.contains(SubjName))
            return &DictOfSubjects[SubjName];

        return NULL;
    }
    void RecalculateStaffSalary();
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
        SpareStudentsClass = SchoolClass();
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
    void RecalculateBuildingMaintenance()
    {
        int Total = 0;
        QList<SchoolUpgrade>::iterator it;
        for (it = ListOfSchoolUpgrades.begin(); it != ListOfSchoolUpgrades.end(); ++it)
            Total -= it->MaintenanceCost();

        if (!DictOfAccounts.contains("Building Maintenance"))
        {
            Account ac("Building Maintenance", 0, Payperiode::Weekly, false, true);
            DictOfAccounts.insert(ac.Name, ac);
        }
        DictOfAccounts["Building Maintenance"].Payment = Total;
    }
};
#endif // GAME_H
