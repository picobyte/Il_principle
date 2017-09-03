
#include "person.h"
#include "modifier.h"

double Modifier_AddGenderPrefValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

int Modifier_AddSkillValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_AddStatValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_AddStatValueLerp::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}

double Modifier_AddStatValueSine::GetValue(Person& per, StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_AddSubjectFamilyValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_BodySizeChange::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Change;
}

double Modifier_DecreaseStatMultiplierLerp::GetScaleFactor(Person& per, StatusEffectInstance& instance)
{
    return ScaleFactor + GetAlphaFromElapsedTime(instance) * (EndScaleFactor - ScaleFactor);
}

double Modifier_DecreaseStatMultiplierSine::GetScaleFactor(Person& per, StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + ScaleFactor;
}

double Modifier_IncreaseStatMultiplierLerp::GetScaleFactor(Person& per, StatusEffectInstance& instance)
{
    return ScaleFactor + GetAlphaFromElapsedTime(instance) * (EndScaleFactor - ScaleFactor);
}

double Modifier_IncreaseStatMultiplierSine::GetScaleFactor(Person& per, StatusEffectInstance& instance)
{
   return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + ScaleFactor;
}

double Modifier_MaxGenderPrefValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MaxStatValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MaxStatValueLerp::GetValue(Person&, StatusEffectInstance&)
{
    return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}


double  Modifier_MaxStatValueSine::GetValue(Person& per, StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_MaxSubjectFamilyValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MinGenderPrefValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

virtual double Modifier_MinStatValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MinStatValueLerp::GetValue(Person& per, StatusEffectInstance& instance)
{
   return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}

double Modifier_MinStatValueSine::GetValue(Person& per, StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_MinSubjectFamilyValue::GetValue(Person& per, StatusEffectInstance& instance)
{
    return Value;
}



















