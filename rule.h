#ifndef RULE_H
#define RULE_H
#include "json_macros.h"

class Rule {
public:
    enum class Status
    {
        Available,
        ProposalNeeded,
        UpgradeNeeded,
        Blocked
    };
    QString Name;
    QString Description;
    Status RuleStatus;
    int ActiveRuleChoiceIndex;
    //ObservableCollection<RuleChoice> RuleChoices;

    Rule(QJsonObject *d = NULL): Name(""), Description("")
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_ENUM_FROM_JSON_AS(it, RuleStatus, Status)
            else __IF_VAR_FROM_JSON_AS(it, ActiveRuleChoiceIndex, toInt)
            //ObservableCollection<RuleChoice> RuleChoices
        }
    }

};

#endif // RULE_H
