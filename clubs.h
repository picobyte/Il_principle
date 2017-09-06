#ifndef CLUBS_H
#define CLUBS_H
#include <QString>
#include <QList>
#include "json_macros.h"
#include "person.h"
#include "statchange.h"
#include "bodysizechange.h"
#include "timedata.h"

class ClubLevel {
public:
    ClubLevel(QJsonObject *d = NULL):
        ImportantStat("Happiness"),
        ClubRoom("Normal School"),
        StartTime(16),
        EndTime(16)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, intEditorName, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImportantStat, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImportantStatInverted, toBool)
            else __IF_VAR_FROM_JSON_AS(it, CorruptionLevel, toInt)
            else __IF_VAR_FROM_JSON_AS(it, WeeklyAccount, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImagePath, toString)
            else __IF_VAR_FROM_JSON_AS(it, ClubRoom, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, ForGender, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, ClubEventDirectories, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, ClubEventIDs, toInt)
            else __IF_EASY_OBJLIST_FROM_JSON(it, StatChange)
            else __IF_EASY_OBJLIST_FROM_JSON(it, BodySizeChange)
            else __IF_OBJ_FROM_JSON(it, StartTime)
            else __IF_OBJ_FROM_JSON(it, EndTime)
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
    TimeData StartTime;
    TimeData EndTime;
    QList<QString> ClubEventDirectories;
    QList<uint> ClubEventIDs;
    QList<StatChange> StatChanges;
    QList<BodySizeChange> BodySizeChanges;
};

class Clubs {
public:
    Clubs(QJsonObject *d = NULL):
        AutomaticJoiningEnabled(true),
        HideFromManagementPanel(false)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
        //QList<Person> UnassignedStudents;,
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
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
            else __IF_EASY_OBJLIST_FROM_JSON(it, ClubLevel)
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
