#ifndef RULEEFFECT_H
#define RULEEFFECT_H
#include "json_macros.h"

class RuleEffect {
public:
	QString ApplyTo;
	QList<Gender> Genders;
	QList<StatChange> StatChanges;
	QList<BodySizeChange> BodySizeChanges;
	const QString get_ApplyTo() const {return ApplyTo;}
	void set_ApplyTo(QString& v) {ApplyTo = v;}

	RuleEffect(QJsonObject *d = NULL) : ApplyTo("")
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, ApplyTo, toString)
			else __IF_LIST_FROM_JSON_ENUM(it, Genders, Gender)
			else __IF_OBJLIST_FROM_JSON(it, StatChanges, StatChange)
			else __IF_OBJLIST_FROM_JSON(it, BodySizeChanges, BodySizeChange)
		}
	}
	bool ShouldSerializeGenders()
	{
		return Genders.Count > 0;
	}
	bool ShouldSerializeStatChanges()
	{
		return StatChanges.Count != 0;
	}
	bool ShouldSerializeBodySizeChanges()
	{
		return BodySizeChanges.Count != 0;
	}
	void ExecuteRuleForGroup()
	{
		if (ApplyTo.Contains("Student"))
		{
			for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values->begin();
					it != Game.OwnStudents.Values->end(); ++it)
			{
				Person Per = enumerator.Current;
				if (!Per.IsRogue)
				{
					ExecuteRuleForPerson(Per);
				}
			}
		}
		if (ApplyTo.Contains("Detention") && !ApplyTo.Contains("Student"))
		{
			for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values->begin();
					it != Game.OwnStudents.Values->end(); ++it)
			{
				Person Per2 = enumerator2.Current;
				if (Per2.HasDetention)
				{
					ExecuteRuleForPerson(Per2);
				}
			}
		}
		if (ApplyTo.Contains("Parent"))
		{
			for (QHash<QString, Person>::iterator it = Game.DictOfPersonNames.Values->begin();
					it != Game.DictOfPersonNames.Values->end(); ++it)
			{
				Person Per3 = enumerator3.Current;
				if (Per3.IsParent)
				{
					ExecuteRuleForPerson(Per3);
				}
			}
		}
		if (ApplyTo.Contains("Staff"))
		{
			if (ApplyTo.Contains("Parent"))
			{
				for (IEnumerator<Person>::iterator it = Game.HiredStaff.Values->begin();
						it != Game.HiredStaff.Values->end(); ++it)
				{
					Person Per4 = enumerator4.Current;
					if (!Per4.IsParent)
					{
						ExecuteRuleForPerson(Per4);
					}
				}
				goto IL_1B9;
			}
			for (IEnumerator<Person>::iterator it = Game.HiredStaff.Values->begin();
					it != Game.HiredStaff.Values->end(); ++it)
			{
				Person Per5 = enumerator5.Current;
				ExecuteRuleForPerson(Per5);
			}
		}
		IL_1B9:
		if (ApplyTo.Contains("Teacher") && !ApplyTo.Contains("Staff"))
		{
			if (ApplyTo.Contains("Parent"))
			{
				for (IEnumerator<Person>::iterator it = Game.HiredTeacher.Values->begin();
						it != Game.HiredTeacher.Values->end(); ++it)
				{
					Person Per6 = enumerator6.Current;
					if (!Per6.IsParent)
					{
						ExecuteRuleForPerson(Per6);
					}
				}
				goto IL_275;
			}
			for (IEnumerator<Person>::iterator it = Game.HiredTeacher.Values->begin();
					it != Game.HiredTeacher.Values->end(); ++it)
			{
				Person Per7 = enumerator7.Current;
				ExecuteRuleForPerson(Per7);
			}
		}
		IL_275:
		if (ApplyTo.Contains("Principal"))
		{
			ExecuteRuleForPerson(Game.HeadTeacher);
		}
	}
	void ExecuteRuleForPerson(Person Per)
	{
		if (Genders.Contains(Per.Gender))
			AdjustPerson(Per);
	}
	void AdjustPerson(Person Per)
	{
		if (Per != NULL)
		{
			for (QList<StatChange>::iterator it = StatChanges->begin();
					it != StatChanges->end(); ++it)
			{
				enumerator.Current.AdjustStat(Per);
			}
			for (QList<BodySizeChange>::iterator it = BodySizeChanges->begin();
					it != BodySizeChanges->end(); ++it)
			{
				BodySizeChange BSC = enumerator2.Current;
				Per.ApplyBodySizeChange(BSC);
			}
		}
	}
	object Clone()
	{
		return (RuleEffect)MemberwiseClone();
	}
};

#endif // RULEEFFECT_H
