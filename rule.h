#ifndef RULE_H
#define RULE_H
#include <QList>
#include "json_macros.h"
#include "rulechoice.h"

class Rule {
    QList<RuleChoice> RuleChoices;
public:
    QString Name;
    QString Description;
    RuleStatus Status;
    int ActiveRuleChoiceIndex;

    RuleChoice const*const get_ActiveRuleChoice() const
	{
        if (Status == RuleStatus::Available && ActiveRuleChoiceIndex > -1 &&
                ActiveRuleChoiceIndex < RuleChoices.count())
            return &RuleChoices[ActiveRuleChoiceIndex];

        return NULL;
	}
    void set_ActiveRuleChoice(RuleChoice& value)
	{
        /*if (RuleChoices.contains(value) && value.Status == RuleStatus::Available)
		{
            RuleChoice const *const arlc = get_ActiveRuleChoice();
            VisualEventManager.ExecuteNativeEvent(arlc->Name + "_Deactivated.ve.xml");
			ActiveRuleChoiceIndex = RuleChoices.IndexOf(value);
            VisualEventManager.ExecuteNativeEvent(arlc->Name + "_Activated.ve.xml");
        }*/
	}
    const int get_AllowedRuleChoiceCount() const
    {
        int count = 0;
        /*if (Status == RuleStatus::Available)
            for(QList<RuleChoice>::iterator it = RuleChoices.begin(); it != RuleChoices.end(); ++it)
                if (it->Status == RuleStatus::Available)
                    ++count;*/
        return count;
    }

	Rule(QJsonObject *d = NULL) : Name(""), Description("")
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_ENUM_FROM_JSON_AS(it, Status, RuleStatus)
			else __IF_VAR_FROM_JSON_AS(it, ActiveRuleChoiceIndex, toInt)
			//ObservableCollection<RuleChoice> RuleChoices
		}
	}
	bool ShouldSerializeStatus()
	{
        return Status > RuleStatus::Available;
	}
	bool ShouldSerializeActiveRuleChoiceIndex()
	{
        return ActiveRuleChoiceIndex != 0 && ActiveRuleChoiceIndex < RuleChoices.count();
	}
	QString ToString()
	{
		return "Rule: " + Name;
	}
};

#endif // RULE_H
