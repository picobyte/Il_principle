#ifndef CLUBS_H
#define CLUBS_H
#include "person.h"
#include <QJsonObject>
#include "json_macros.h"

class ClubLevel {
public:
    ClubLevel() {}
    ClubLevel(QJsonObject &d)
        //Name(it["Name"].toString())
        //QList<QString> ForGender;
        //TimeData StartTime;
        //TimeData EndTime;
        //QList<QString> ClubEventDirectories;
        //QList<uint> ClubEventIDs;
        //QList<StatChange> StatChanges;
        //QList<BodySizeChange> BodySizeChanges;
    {
        QJsonObject::iterator it;
        for (it = d.begin(); it != d.end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, intEditorName, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImportantStat, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImportantStatInverted, toBool)
            else __IF_VAR_FROM_JSON_AS(it, CorruptionLevel, toInt)
            else __IF_VAR_FROM_JSON_AS(it, WeeklyAccount, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImagePath, toString)
            else __IF_VAR_FROM_JSON_AS(it, ClubRoom, toString)
            else qWarning(it.key().append(": unhandled.").toUtf8());
        }
    }
    QString Name;
    QString intEditorName;
    QList<QString> ForGender;
    QString ImportantStat;
    bool ImportantStatInverted;
    int CorruptionLevel;
    double WeeklyAccount;
    QString Description;
    QString ImagePath;
    QString ClubRoom;
    //TimeData StartTime;
    //TimeData EndTime;
    QList<QString> ClubEventDirectories;
    QList<uint> ClubEventIDs;
    //QList<StatChange> StatChanges;
    //QList<BodySizeChange> BodySizeChanges;
};

class Clubs {
public:
    Clubs() {}
    Clubs(QJsonObject &d)
        //Name(it["Name"].toString()),
        //QList<Person> UnassignedStudents;,
        //QList<ClubLevel> ClubLevels;
    {
        QJsonObject::iterator it;
        for (it = d.begin(); it != d.end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, MaxClubSize, toInt)
            else __IF_VAR_FROM_JSON_AS(it, MemberCount, toInt)
            else __IF_VAR_FROM_JSON_AS(it, DesiredCount, toInt)
            else __IF_VAR_FROM_JSON_AS(it, currentClubLevelIndex, toInt)
            else __IF_VAR_FROM_JSON_AS(it, AutomaticJoiningEnabled, toBool)
            else __IF_VAR_FROM_JSON_AS(it, HideFromManagementPanel, toBool)
            else __IF_VAR_FROM_JSON_AS(it, Active, toBool)
            else __IF_VAR_FROM_JSON_AS(it, CanBeChosen, toBool)
            else __IF_VAR_FROM_JSON_AS(it, ClubPresident, toString)
            else __IF_VAR_FROM_JSON_AS(it, PreferredPresident, toString)
            else __IF_OBJLIST_FROM_JSON_AS(it, ClubLevel)
            else qWarning(it.key().append(": unhandled.").toUtf8());
        }
    }
    int MaxClubSize;
    QList<Person> UnassignedStudents;
    QString Name;
    bool AutomaticJoiningEnabled;
    bool HideFromManagementPanel;
    bool Active;
    bool CanBeChosen;
    QString ClubPresident;
    QString PreferredPresident;
    int MemberCount;
    int DesiredCount;
    int currentClubLevelIndex;
    QList<ClubLevel> ClubLevels;
};

#endif // CLUBS_H
