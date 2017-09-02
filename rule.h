#ifndef RULE_H
#define RULE_H
#include "json_macros.h"

class Rule {
	ObservableCollection<RuleChoice> RuleChoices;
public:
	QString Name;
	QString Description;
	RuleStatus Status;
	int ActiveRuleChoiceIndex;

	const RuleChoice get_ActiveRuleChoice() const
	{
		RuleChoice ActiveRuleChoice;
		if (Status == RuleStatus.Available && ActiveRuleChoiceIndex > -1 && ActiveRuleChoiceIndex < RuleChoices.Count)
		{
			ActiveRuleChoice = RuleChoices[ActiveRuleChoiceIndex];
		}
		else
		{
			ActiveRuleChoice = NULL;
		}
		return ActiveRuleChoice;
	}
	void set_ActiveRuleChoice(RuleChoice& v)
	{
		if (RuleChoices.Contains(value) && value.Status == RuleStatus.Available)
		{
			VisualEventManager.ExecuteNativeEvent(ActiveRuleChoice.Name + "_Deactivated.ve.xml");
			ActiveRuleChoiceIndex = RuleChoices.IndexOf(value);
			VisualEventManager.ExecuteNativeEvent(ActiveRuleChoice.Name + "_Activated.ve.xml");
		}
	}
	const int get_AllowedRuleChoiceCount() const
	{
		checked
		{
			int AllowedRuleChoiceCount;
			if (Status != RuleStatus.Available)
			{
				AllowedRuleChoiceCount = 0;
			}
			else
			{
				int count = 0;
				try
				{
					IEnumerator<RuleChoice> enumerator = RuleChoices.GetEnumerator();
					while (enumerator.MoveNext())
					{
						if (enumerator.Current.Status == RuleStatus.Available)
						{
							count++;
						}
					}
				}
				finally {}
				AllowedRuleChoiceCount = count;
			}
			return AllowedRuleChoiceCount;
		}
	}

	Rule(QJsonObject *d = NULL) : Name(""), Description("")
	{
		if (d) init(d);
		RuleChoices = new ObservableCollection<RuleChoice>();
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, Description, toString)
			else __IF_OBJ_FROM_JSON_AS(it, Status)
			else __IF_VAR_FROM_JSON_AS(it, ActiveRuleChoiceIndex, toInt)
			//ObservableCollection<RuleChoice> RuleChoices
		}
	}
	bool ShouldSerializeStatus()
	{
		return Status > RuleStatus.Available;
	}
	bool ShouldSerializeActiveRuleChoiceIndex()
	{
		return ActiveRuleChoiceIndex != 0 && ActiveRuleChoiceIndex < RuleChoices.Count;
	}
	QString ToString()
	{
		return "Rule: " + Name;
	}
};

#endif // RULE_H
