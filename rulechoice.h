#ifndef RULECHOICE_H
#define RULECHOICE_H
#include <QList>
#include "json_macros.h"
#include "ruleeffect.h"
#include "theworld.h"

class RuleChoice {
    QList<RuleEffect> RuleEffects;
public:
    QString Name;
    QString Description;
    RuleStatus Status;
    QString NeedRoom;
    double RuleReputation;
    bool NudeOutfit;
    bool NudeSwimsuit;

    RuleChoice(QJsonObject *d = NULL) :
            Name(""), Description(""), Status(RuleStatus::Available), NeedRoom("")
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_ENUM_FROM_JSON_AS(it, Status, RuleStatus)
            else __IF_VAR_FROM_JSON_AS(it, NeedRoom, toString)
            else __IF_VAR_FROM_JSON_AS(it, RuleReputation, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, NudeOutfit, toBool)
            else __IF_VAR_FROM_JSON_AS(it, NudeSwimsuit, toBool)
            else __IF_OBJLIST_FROM_JSON(it, RuleEffects, RuleEffect)
        }
    }
    bool ShouldSerializeStatus()
    {
        return Status > RuleStatus::Available;
    }
    bool ShouldSerializeNeedRoom()
    {
        return !NeedRoom.isEmpty();
    }
    bool ShouldSerializeRuleReputation()
    {
        return RuleReputation != 0.0;
    }
    bool ShouldSerializeNudeOutfit()
    {
        return NudeOutfit;
    }
    bool ShouldSerializeNudeSwimsuit()
    {
        return NudeSwimsuit;
    }
    void ExecuteRule()
    {
        /*if (Game.HiredTeacher.count() > 0)
        {
            for (QList<RuleEffect>::iterator it = RuleEffects.begin();
                    it != RuleEffects.end(); ++it)
                it->ExecuteRuleForGroup();

            TheWorld *theSchool = &Game.TheSchool;
            theSchool->Reputation = theSchool->Reputation + RuleReputation / 5.0;
        }*/
    }
    QString ToString()
    {
        return "RuleChoice: " + Name;
    }
};

#endif // RULECHOICE_H
