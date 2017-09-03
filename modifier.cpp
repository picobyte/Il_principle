
#include "modifier.h"

double Modifier_AddGenderPrefValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

int Modifier_AddSkillValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_AddStatValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_AddStatValueLerp::GetValue(StatusEffectInstance& instance)
{
    return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}

double Modifier_AddStatValueSine::GetValue(StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_AddSubjectFamilyValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_BodySizeChange::GetValue(StatusEffectInstance& instance)
{
    return Change;
}

double Modifier_DecreaseStatMultiplierLerp::GetScaleFactor(StatusEffectInstance& instance)
{
    return ScaleFactor + GetAlphaFromElapsedTime(instance) * (EndScaleFactor - ScaleFactor);
}

double Modifier_DecreaseStatMultiplierSine::GetScaleFactor(StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + ScaleFactor;
}

double Modifier_IncreaseStatMultiplierLerp::GetScaleFactor(StatusEffectInstance& instance)
{
    return ScaleFactor + GetAlphaFromElapsedTime(instance) * (EndScaleFactor - ScaleFactor);
}

double Modifier_IncreaseStatMultiplierSine::GetScaleFactor(StatusEffectInstance& instance)
{
   return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + ScaleFactor;
}

double Modifier_MaxGenderPrefValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MaxStatValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MaxStatValueLerp::GetValue(int&, StatusEffectInstance&)
{
    return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}


double  Modifier_MaxStatValueSine::GetValue(StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_MaxSubjectFamilyValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MinGenderPrefValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

virtual double Modifier_MinStatValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

double Modifier_MinStatValueLerp::GetValue(StatusEffectInstance& instance)
{
   return Value + GetAlphaFromElapsedTime(instance) * (EndValue - Value);
}

double Modifier_MinStatValueSine::GetValue(StatusEffectInstance& instance)
{
    return sin(((double)(GameTime::CurrentTimestamp - instance.StartTimestamp) / Period - TimeOffset) * 2.0 * M_PI) * Amplitude + Value;
}

double Modifier_MinSubjectFamilyValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

int Modifier_MinSkillValue::GetValue(StatusEffectInstance& instance)
{
    return Value;
}

















