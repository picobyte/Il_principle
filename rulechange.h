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
	const QString get_RuleChoice() const {return RuleChoice;}
	void set_RuleChoice(QString& v) {RuleChoice = v;}
	const bool get_ChangeReputation() const {return ChangeReputation;}
	void set_ChangeReputation(bool& v) {ChangeReputation = v;}
	const double get_RuleReputation() const {return RuleReputation;}
	void set_RuleReputation(double& v) {RuleReputation = v;}
	const bool get_ChangeNeededRoom() const {return ChangeNeededRoom;}
	void set_ChangeNeededRoom(bool& v) {ChangeNeededRoom = v;}
	const QString get_RuleNeededRoom() const {return RuleNeededRoom;}
	void set_RuleNeededRoom(QString& v) {RuleNeededRoom = v;}
	const RuleChoicePersonGroupChange get_RuleStats() const {return RuleStats;}
	void set_RuleStats(RuleChoicePersonGroupChange& v) {RuleStats = v;}

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
