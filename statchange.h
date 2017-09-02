#ifndef STATCHANGE_H
#define STATCHANGE_H
#include "json_macros.h"
#include "person.h"

class StatChange {
public:
	QString Stat;
	double Change;
	double Minimum;
	double Maximum;
	bool ShouldSerializeMinimum()
	{
		return Minimum != 0.0;
	}
	bool ShouldSerializeMaximum()
	{
		return Maximum != 0.0;
	}
	bool WithinRange(double Value)
	{
		return Value >= 1.0 && (Minimum == 0.0 || Value >= Minimum) && (Maximum == 0.0 || Value <= Maximum);
	}
    void AdjustStat(Person *Per)
	{
        /*if (WithinRange(Per.GetStat(Stat)))
		{
			Per.AddStat(Stat, Change);
			if (Minimum != 0.0 && Per.GetStat(Stat) < Minimum)
			{
				Per.SetStat(Stat, Minimum);
				return;
			}
			if (Maximum != 0.0 && Per.GetStat(Stat) > Maximum)
			{
				Per.SetStat(Stat, Maximum);
			}
        }*/
	}

    StatChange(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
	{
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            //BodyPart BodyPart
            __IF_VAR_FROM_JSON_AS(it, Stat, toString);
            __IF_VAR_FROM_JSON_AS(it, Change, toDouble);
            __IF_VAR_FROM_JSON_AS(it, Minimum, toDouble);
            __IF_VAR_FROM_JSON_AS(it, Maximum, toDouble);
        }
	}
};

#endif // STATCHANGE_H
