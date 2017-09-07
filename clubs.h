#ifndef CLUBS_H
#define CLUBS_H
#include <QString>
#include <QList>
#include "json_macros.h"
#include "person.h"
#include "statchange.h"
#include "bodysizechange.h"
#include "timedata.h"

class Location;
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
    const QString EditorName() const
    {
        if (intEditorName.isNull() || intEditorName.contains(QRegExp("^\\s*$")))
            return Name;

        return intEditorName;
    }
    void EditorName(QString& v)
    {
        intEditorName = v;
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
    bool ShouldSerializeintEditorName()
    {
        return !(intEditorName.isNull() || intEditorName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeForGender()
    {
        return ForGender.count() > 0;
    }
    bool ShouldSerializeImportantStat()
    {
        return ImportantStat == "Happiness";
    }
    bool ShouldSerializeImportantStatInverted()
    {
        return ImportantStatInverted;
    }
    bool ShouldSerializeCorruptionLevel()
    {
        return CorruptionLevel != 0;
    }
    bool ShouldSerializeWeeklyAccount()
    {
        return WeeklyAccount != 0.0;
    }
    bool ShouldSerializeDescription()
    {
        return !(Description.isNull() || Description.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeImagePath()
    {
        return !(ImagePath.isNull() || ImagePath.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeClubRoom()
    {
        return ClubRoom != "Normal School";
    }
    bool ShouldSerializeStatChanges()
    {
        return StatChanges.count() != 0;
    }
    bool ShouldSerializeBodySizeChanges()
    {
        return BodySizeChanges.count() != 0;
    }
    void OpenAccount();
    void CloseAccount();
    void ClubMeeting();
    QString ToString()
    {
        return Name;
    }
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

    int CurrentClubLevelIndex() const;
    void CurrentClubLevelIndex(int v);
    ClubLevel* CurrentClubLevel() const;
    Location* ClubRoom() const;
    void ClubRoom(Location* v);
    bool ShouldSerializeAutomaticJoiningEnabled();
    bool ShouldSerializeHideFromManagementPanel();
    bool ShouldSerializeActive();
    bool ShouldSerializeCanBeChosen();
    bool ShouldSerializeClubPresident();
    bool ShouldSerializePreferredPresident();
    bool ShouldSerializeMemberCount();
    bool ShouldSerializeCurrentClubLevelIndex();
    bool ShouldSerializeClubLevels();
    void ValidateMembers();
    void AddMember(Person& Per);
    void RemoveMember(Person& Per, bool ValidatePresidency = true);
    void ChoosePresident(bool AllowCoups = false);
    void SetRandomPresident();
    void ClubMeeting();
    void AdjustClubSize();
    void AdjustAllClubSizes();
    int IndexOf(ClubLevel& clubLevel);
    QString ToString();
};

#endif // CLUBS_H
