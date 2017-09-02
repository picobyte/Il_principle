#ifndef SCHOOLUPGRADE_H
#define SCHOOLUPGRADE_H
#include "json_macros.h"
#include "locationpropertychange.h"
#include "rulechange.h"
#include "location.h"

class SchoolUpgradeLevel {
    QList<QString> ActivateRules;
    QList<RuleChange> ChangeRuleList;
public:
    QString Name;
    QString Description;
    QString ImagePath;
    QString NewLocationName;
    QString NewLocationImageFolder;
    QString NewLocationDescription;
    LocationPropertyChange PropertyChange;
    bool CanBeChosen;
    int Cost;
    int MaintenanceCost;
    SchoolUpgradeLevel(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
                    else __IF_VAR_FROM_JSON_AS(it, Description, toString)
                    else __IF_VAR_FROM_JSON_AS(it, ImagePath, toString)
                    else __IF_VAR_FROM_JSON_AS(it, NewLocationName, toString)
                    else __IF_VAR_FROM_JSON_AS(it, NewLocationImageFolder, toString)
                    else __IF_VAR_FROM_JSON_AS(it, NewLocationDescription, toString)
                    //LocationPropertyChange PropertyChange
                    else __IF_VAR_FROM_JSON_AS(it, CanBeChosen, toBool)
                    else __IF_VAR_FROM_JSON_AS(it, Cost, toInt)
                    else __IF_VAR_FROM_JSON_AS(it, MaintenanceCost, toInt)
                    QList<QString> ActivateRules;
            //QList<RuleChange> ChangeRuleList
        }
    }
};

class SchoolUpgrade {
    QList<SchoolUpgradeLevel> ListUpgradeLevels;
    static size_t schoolupgradeCounter;
    size_t thisSchoolUpgradeNr;
public:
    QString Name;
    QString LocationName;
    int CurrentLevel;
    /*const Location get_Location() const
    {
        return Game.GetLocation(LocationName);
    }*/
    void set_Location(Location* v = NULL)
    {
        LocationName = v ? v->Name : "";
    }
    SchoolUpgradeLevel const*const get_CurrentLevelObject() const
    {
        if (CurrentLevel > -1 && CurrentLevel < ListUpgradeLevels.count())
            return &ListUpgradeLevels[CurrentLevel];

        return NULL;
    }
    SchoolUpgradeLevel const*const get_NextLevelObject() const
    {
        int next = CurrentLevel + 1;
        if (next > -1 && next < ListUpgradeLevels.count() && ListUpgradeLevels[next].CanBeChosen)
            return &ListUpgradeLevels[next];

        return NULL;
    }
    const QString get_DisplayName() const
    {
        SchoolUpgradeLevel const*const clo = get_CurrentLevelObject();
        SchoolUpgradeLevel const*const nlo = get_NextLevelObject();
        if (clo == NULL)
            return nlo ? "Purchase " + nlo->Name : "Nothing;";

        if (nlo == NULL)
            return clo->Name;
        return "Upgrade " + clo->Name + " to " + nlo->Name;
    }
    const QString get_CurrentName() const
    {
        SchoolUpgradeLevel const*const clo = get_CurrentLevelObject();
        return clo ? clo->Name : "Nothing";
    }
    const QString get_UpgradeName() const
    {
        SchoolUpgradeLevel const*const nlo = get_NextLevelObject();
        return nlo ? nlo->Name : "No upgrade available";
    }
    const QString get_Description() const
    {
        SchoolUpgradeLevel const*const clo = get_CurrentLevelObject();
        return clo ? clo->Description : "";
    }
    const QString get_UpgradeDescription() const
    {
        SchoolUpgradeLevel const*const nlo = get_NextLevelObject();
        return nlo ? nlo->Description : "";
    }
    const int get_MaintenanceCost() const
    {
        SchoolUpgradeLevel const*const clo = get_CurrentLevelObject();
        return clo ? clo->MaintenanceCost : 0;
    }
    const int get_UpgradeCost() const
    {
        SchoolUpgradeLevel const*const nlo = get_NextLevelObject();
        return nlo ? nlo->Cost : -1;
    }
    SchoolUpgrade(QJsonObject *d = NULL) : thisSchoolUpgradeNr(schoolupgradeCounter++)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, LocationName, toString)
            else __IF_VAR_FROM_JSON_AS(it, CurrentLevel, toInt)
            //QList<SchoolUpgradeLevel> ListUpgradeLevels
        }
    }
    size_t get_thisSchoolUpgradeNr() const {
        return thisSchoolUpgradeNr;
    }
};

inline size_t qHash(const SchoolUpgrade &su) {
    return su.get_thisSchoolUpgradeNr();
}

inline bool operator==(const SchoolUpgrade su1, const SchoolUpgrade su2){
    return su1.get_thisSchoolUpgradeNr() == su2.get_thisSchoolUpgradeNr();
}

#endif // SCHOOLUPGRADE_H
