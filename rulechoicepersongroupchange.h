#ifndef RULECHOICEPERSONGROUPCHANGE_H
#define RULECHOICEPERSONGROUPCHANGE_H
#include "json_macros.h"
#include "generic.h"
#include "statchange.h"
#include "bodysizechange.h"

class RuleChoicePersonGroupChange {
public:
	QString ApplyTo;
	QList<Gender> Genders;
	QList<StatChange> NewStatChanges;
	QList<BodySizeChange> NewBodySizeChanges;
	const QString get_ApplyTo() const {return ApplyTo;}
	void set_ApplyTo(QString& v) {ApplyTo = v;}

	RuleChoicePersonGroupChange(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, ApplyTo, toString)
			else __IF_LIST_FROM_JSON_ENUM(it, Genders, Gender)
            else __IF_OBJLIST_FROM_JSON(it, NewStatChanges, StatChange)
            else __IF_OBJLIST_FROM_JSON(it, NewBodySizeChanges, BodySizeChange)
		}
	}
};

#endif // RULECHOICEPERSONGROUPCHANGE_H
