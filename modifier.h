#ifndef MODIFIERBASE_H
#define MODIFIERBASE_H
#include "json_macros.h"
#include <math.h>
#include "generic.h"
#include "schoolsubject.h"
#include "statuseffectinstance.h"

class ModifierBase {
public:
	ModifierBase(QJsonObject *d = NULL) {}
};

class Modifier_AddGenderPrefValue : public ModifierBase {
public:
	Gender gender;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_AddGenderPrefValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_ENUM_FROM_JSON_AS(it, gender, Gender)
                        else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_AddSkillValue : public ModifierBase {
public:
	QString SkillName;
	int Value;
	int GetValue()
	{
		return Value;
	}

	Modifier_AddSkillValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, SkillName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toInt)
		}
	}
};

class Modifier_AddStatValue : public ModifierBase {
public:
	QString StatName;
	double Value;
	virtual double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_AddStatValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, StatName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_AddStatValueLerp : public Modifier_AddStatValue {
public:
	double EndValue;
	 double GetValue(Person per, StatusEffectInstance instance)
	{
        return Value + ModifierBase.GetAlphaFromElapsedTime(instance) * (EndValue - Value);
	}

	Modifier_AddStatValueLerp(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EndValue, toDouble)
		}
	}
};

class Modifier_AddStatValueSine : public Modifier_AddStatValue {
public:
	double Amplitude;
	double Period;
	double TimeOffset;
    double GetValue(Person per, StatusEffectInstance instance)
	{
        return sin(((double)(Game.GameTime.CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
	}

	Modifier_AddStatValueSine(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Amplitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Period, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, TimeOffset, toDouble)
		}
	}
};

class Modifier_AddSubjectFamilyValue : public ModifierBase {
public:
    SchoolSubjectFamily SubjectFamilyName;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_AddSubjectFamilyValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//SchoolSubjectFamily SubjectFamilyName
			__IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_BodySizeChange : public ModifierBase {
public:
    BodyPart bodyPart;
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
	virtual double GetValue(Person per, StatusEffectInstance instance)
	{
		return Change;
	}

	Modifier_BodySizeChange(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, bodyPart, BodyPar)
            else __IF_VAR_FROM_JSON_AS(it, Change, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Minimum, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Maximum, toDouble)
		}
	}
};

class Modifier_DecreaseGenderPrefMultiplier : public ModifierBase {
public:
    Gender gender;
	double ScaleFactor;
	Modifier_DecreaseGenderPrefMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_DecreaseGenderPrefMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
            else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_DecreaseSkillMultiplier : public ModifierBase {
public:
	QString SkillName;
	double ScaleFactor;
	Modifier_DecreaseSkillMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_DecreaseSkillMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, SkillName, toString)
			else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_DecreaseStatMultiplier : public ModifierBase {
public:
	QString StatName;
	double ScaleFactor;
	Modifier_DecreaseStatMultiplier()
	{
		ScaleFactor = 1.0;
	}
	virtual double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_DecreaseStatMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, StatName, toString)
			else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_DecreaseStatMultiplierLerp : public Modifier_DecreaseStatMultiplier {
public:
	double EndScaleFactor;
	 double GetScaleFactor()
	{
		return base.ScaleFactor + ModifierBase.GetAlphaFromElapsedTime(instance) * (EndScaleFactor - base.ScaleFactor);
	}

	Modifier_DecreaseStatMultiplierLerp(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EndScaleFactor, toDouble)
		}
	}
};

class Modifier_DecreaseStatMultiplierSine : public Modifier_DecreaseStatMultiplier {
public:
	double Amplitude;
	double Period;
	double TimeOffset;
	 double GetScaleFactor()
	{
        return sin(((double)(Game.GameTime.CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + base.ScaleFactor;
	}

	Modifier_DecreaseStatMultiplierSine(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Amplitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Period, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, TimeOffset, toDouble)
		}
	}
};

class Modifier_DecreaseSubjectFamilyMultiplier : public ModifierBase {
public:
    SchoolSubjectFamily subjectFamilyName;
	double ScaleFactor;
	Modifier_DecreaseSubjectFamilyMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_DecreaseSubjectFamilyMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, schoolSubjectFamily, SubjectFamilyNam)
            else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_ExpirationEvent : public ModifierBase {
public:
	QString EventPath;

	Modifier_ExpirationEvent(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EventPath, toString)
		}
	}
};

class Modifier_IncreaseGenderPrefMultiplier : public ModifierBase {
public:
    Gender gender;
	double ScaleFactor;
	Modifier_IncreaseGenderPrefMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_IncreaseGenderPrefMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
            else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_IncreaseSkillMultiplier : public ModifierBase {
public:
	QString SkillName;
	double ScaleFactor;
	Modifier_IncreaseSkillMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_IncreaseSkillMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, SkillName, toString)
			else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_IncreaseStatMultiplier : public ModifierBase {
public:
	QString StatName;
	double ScaleFactor;
	Modifier_IncreaseStatMultiplier()
	{
		ScaleFactor = 1.0;
	}
	virtual double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_IncreaseStatMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, StatName, toString)
			else __IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_IncreaseStatMultiplierLerp : public Modifier_IncreaseStatMultiplier {
public:
	double EndScaleFactor;
	 double GetScaleFactor()
	{
		return base.ScaleFactor + ModifierBase.GetAlphaFromElapsedTime(instance) * (EndScaleFactor - base.ScaleFactor);
	}

	Modifier_IncreaseStatMultiplierLerp(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EndScaleFactor, toDouble)
		}
	}
};

class Modifier_IncreaseStatMultiplierSine : public Modifier_IncreaseStatMultiplier {
public:
	double Amplitude;
	double Period;
	double TimeOffset;
	 double GetScaleFactor()
	{
        return sin(((double)(Game.GameTime.CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + base.ScaleFactor;
	}

	Modifier_IncreaseStatMultiplierSine(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Amplitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Period, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, TimeOffset, toDouble)
		}
	}
};

class Modifier_IncreaseSubjectFamilyMultiplier : public ModifierBase {
public:
	SchoolSubjectFamily SubjectFamilyName;
	double ScaleFactor;
	Modifier_IncreaseSubjectFamilyMultiplier()
	{
		ScaleFactor = 1.0;
	}
	double GetScaleFactor()
	{
		return ScaleFactor;
	}

	Modifier_IncreaseSubjectFamilyMultiplier(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//SchoolSubjectFamily SubjectFamilyName
			__IF_VAR_FROM_JSON_AS(it, ScaleFactor, toDouble)
		}
	}
};

class Modifier_MaxGenderPrefValue : public ModifierBase {
public:
    Gender gender;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MaxGenderPrefValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
            else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_MaxSkillValue : public ModifierBase {
public:
	QString SkillName;
	int Value;
	int GetValue()
	{
		return Value;
	}

	Modifier_MaxSkillValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, SkillName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toInt)
		}
	}
};

class Modifier_MaxStatValue : public ModifierBase {
public:
	QString StatName;
	double Value;
	virtual double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MaxStatValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, StatName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_MaxStatValueLerp : public Modifier_MaxStatValue {
public:
	double EndValue;
	 double GetValue(Person per, StatusEffectInstance instance)
	{
        return Value + ModifierBase.GetAlphaFromElapsedTime(instance) * (EndValue - Value);
	}

	Modifier_MaxStatValueLerp(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EndValue, toDouble)
		}
	}
};

class Modifier_MaxStatValueSine : public Modifier_MaxStatValue {
public:
	double Amplitude;
	double Period;
	double TimeOffset;
	 double GetValue(Person per, StatusEffectInstance instance)
	{
        return sin(((double)(Game.GameTime.CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
	}

	Modifier_MaxStatValueSine(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Amplitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Period, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, TimeOffset, toDouble)
		}
	}
};

class Modifier_MaxSubjectFamilyValue : public ModifierBase {
public:
	SchoolSubjectFamily SubjectFamilyName;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MaxSubjectFamilyValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//SchoolSubjectFamily SubjectFamilyName
			__IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_MinGenderPrefValue : public ModifierBase {
public:
    Gender gender;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MinGenderPrefValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
            else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_MinSkillValue : public ModifierBase {
public:
	QString SkillName;
	int Value;
	int GetValue()
	{
		return Value;
	}

	Modifier_MinSkillValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, SkillName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toInt)
		}
	}
};

class Modifier_MinStatValue : public ModifierBase {
public:
	QString StatName;
	double Value;
	virtual double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MinStatValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, StatName, toString)
			else __IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_MinStatValueLerp : public Modifier_MinStatValue {
public:
	double EndValue;
	 double GetValue(Person per, StatusEffectInstance instance)
	{
        return Value + ModifierBase.GetAlphaFromElapsedTime(instance) * (EndValue - Value);
	}

	Modifier_MinStatValueLerp(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, EndValue, toDouble)
		}
	}
};

class Modifier_MinStatValueSine : public Modifier_MinStatValue {
public:
	double Amplitude;
	double Period;
	double TimeOffset;
	 double GetValue(Person per, StatusEffectInstance instance)
	{
        return sin(((double)(Game.GameTime.CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
	}

	Modifier_MinStatValueSine(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Amplitude, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, Period, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, TimeOffset, toDouble)
		}
	}
};

class Modifier_MinSubjectFamilyValue : public ModifierBase {
public:
	SchoolSubjectFamily SubjectFamilyName;
	double Value;
	double GetValue(Person per, StatusEffectInstance instance)
	{
		return Value;
	}

	Modifier_MinSubjectFamilyValue(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//SchoolSubjectFamily SubjectFamilyName
			__IF_VAR_FROM_JSON_AS(it, Value, toDouble)
		}
	}
};

class Modifier_StatusFlag : public ModifierBase {
public:
	QString Flag;

	Modifier_StatusFlag(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Flag, toString)
		}
	}
};

#endif // MODIFIERBASE_H
