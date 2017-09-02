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


class Game
{
public:
    Game(const char*);
    bool jsonLoad(QString);
    bool jsonSave(QString) const;
private:
    QSet<QString> observed_keys;

    QLocale GameCulture;
    //StatisticsManager StatisticsManager;
    //EventStructManager StructManager;
    //NotificationManager NotifyManager;
    //PersonRelationshipDatabase RelationshipDatabase;
    //TheWorld TheSchool;
    //ClassroomAssignments ClassAssignments;
    //GameCalendar SchoolCalendar;
    Person HeadTeacher;
    QMap<QString, Account> DictOfAccounts;
    QMap<QString, Clubs> ListOfClubs;
    QString GamePath;
    QString inteventlog;
    bool EventLogflag;
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
    //QList<SchoolClass> ListSchoolClasses;
    int DesiredNumSchoolClasses;
    //SchoolClass SpareStudentsClass;
    QHash<QString, StatusEffect> DictOfStatusEffects;
    QHash<QString, Stat> DictOfStats;
    QHash<QString, Skill> DictOfSkills;
    QList<QString> ListOfJobs;
    QSet<SchoolUpgrade> ListOfSchoolUpgrades;
    QMap<QString, Rule> ListOfRules;
    QHash<QString, Item> ListOfBaseItems;
    QHash<QString, SchoolSubject> DictOfSubjects;
    //QList<PersonScheduleHandler> ListOfScheduleHandlers;
    QHash<QString, double> CachedGlobalStats;
    //GameScenarioConfig ScenarioConfig;
    //QList<Button> lstbutton;
    //PopulationGenerator PopulationManager;
    int TickCount;
    QList<long> FavoriteStudentList;
    int helpercounter;
    QString LastWorldLocationPath;
    bool GameInitialized;
    bool GameLoading;
    int LastAutosaveDay;
    bool CheatsUsed;
    QJsonObject data;
};

#endif // GAME_H
