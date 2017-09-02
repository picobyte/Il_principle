#ifndef RULECHOICE_H
#define RULECHOICE_H
#include "json_macros.h"

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
		return Status > RuleStatus.Available;
	}
	bool ShouldSerializeNeedRoom()
	{
		return !QString.isEmpty(NeedRoom);
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
		if (Game.HiredTeacher.Count > 0)
		{
			QList<RuleEffect>.Enumerator enumerator = RuleEffects.GetEnumerator();
			while (enumerator.MoveNext())
			{
				enumerator.Current.ExecuteRuleForGroup();
			}
			TheWorld theSchool;
			(theSchool = Game.TheSchool).Reputation = theSchool.Reputation + RuleReputation / 5.0;
		}
	}
	QString ToString()
	{
		return "RuleChoice: " + Name;
	}
};

#endif // RULECHOICE_H
