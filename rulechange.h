#ifndef RULECHANGE_H
#define RULECHANGE_H
#include "json_macros.h"
#include "rulechoicepersongroupchange.h"

class RuleChange {
public:
    QString RuleChoice;
    bool ChangeReputation;
    double RuleReputation;
    bool ChangeNeededRoom;
    QString RuleNeededRoom;
    RuleChoicePersonGroupChange RuleStats;
    RuleChange(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, RuleChoice, toString)
            else __IF_VAR_FROM_JSON_AS(it, ChangeReputation, toBool)
            else __IF_VAR_FROM_JSON_AS(it, RuleReputation, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, ChangeNeededRoom, toBool)
            else __IF_VAR_FROM_JSON_AS(it, RuleNeededRoom, toString)
            //RuleChoicePersonGroupChange RuleStats
        }
    }
};

#endif // RULECHANGE_H
