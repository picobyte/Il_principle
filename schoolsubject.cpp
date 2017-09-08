#include "person.h"
#include "schoolsubject.h"

double SchoolSubjectInfluence_Stat::GetInfluencedValue(Person* Per)
{
    return (Per->GetStat(StatName) - BaseValue) * InfluenceFactor;
}
void SchoolSubjectInfluence_Stat::SetInfluencedValue(Person* Per, double Value)
{
    Per->AddStat(StatName, Value * InfluenceFactor);
}



double SchoolSubjectInfluence_Family::GetInfluencedValue(Person* Per)
{
    return Per.GetSubjectFamilyExp(SubjectFamily) * InfluenceFactor;
}
void SchoolSubjectInfluence_Family::SetInfluencedValue(Person* Per, double Value)
{
    Per.AddSubjectFamilyExp(SubjectFamily, Value * InfluenceFactor);
}



bool SchoolSubject::is_teachers_subject(Person& t) /* formerly _LambdaS__26_0 */
{
    return t.TeacherSubjects.contains(Name);
}

int TotalTeacherNumber() const
{
    int ct = 0;
    for (QMap<QString, Person&>::iterator it = Game::HiredTeacher.begin(); it != Game::HiredTeacher.end(); ++it)
        if (it.value().TeacherSubjects.contains(Name))
            ++ct;

    return ct;
}

double SchoolSubject::GetSubjectExp(Person Per)
{
    return Per.GetSubjectInstanceExp(Name) * SubjectExperienceRatio + GetEvaluationInfluence(Per) * (1.0 - SubjectExperienceRatio);
}
void SchoolSubject::AddSubjectExp(Person Per, double Value)
{
    Per.AddSubjectInstanceExp(Name, Value);
    ApplyImprovementInfluence(Per, Value);
}
double SchoolSubject::GetEvaluationInfluence(Person Per)
{
    double result = 0.0;
    // try {
    for (QList<SchoolSubjectInfluence>::iterator it = EvaluationInfluence.begin();
         it != EvaluationInfluence.end(); ++it)
    {
        SchoolSubjectInfluence inf = enumerator.Current;
        result += inf.GetInfluencedValue(Per);
    }
    // }
    return result;
}
void SchoolSubject::ApplyImprovementInfluence(Person Per, double Value)
{
    // try {
    for (QList<SchoolSubjectInfluence>::iterator it = ImprovementInfluence.begin();
         it != ImprovementInfluence.end(); ++it)
    {
        enumerator.Current.SetInfluencedValue(Per, Value);
    }
    // }
}
double SchoolSubject::GetLearningBoostInfluence(Person Per)
{
    double result = 0.0;
    // try {
    for (QList<SchoolSubjectInfluence>::iterator it = LearningBoostInfluence.begin();
         it != LearningBoostInfluence.end(); ++it)
    {
        SchoolSubjectInfluence inf = enumerator.Current;
        result += inf.GetInfluencedValue(Per);
    }
    // }
    return result * 0.01;
}
