#ifndef SCHOOLSUBJECT_H
#define SCHOOLSUBJECT_H
#include "json_macros.h"

enum class SubjectFamily
{
    NONE,
    Mathematics,
    LifeScience,
    NaturalScience,
    SocialScience,
    ComputerStudies,
    Humanities,
    LanguageArts,
    FineArts,
    PhysicalEducation,
    SexualEducation
};

class SchoolSubjectInfluence_Stat {
public:
    double InfluenceFactor;
    QString statName;
    double BaseValue;
    SchoolSubjectInfluence_Stat(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, InfluenceFactor, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, statName, toString)
            else __IF_VAR_FROM_JSON_AS(it, BaseValue, toDouble)
            else qWarning(it.key().append(": unhandled.").toUtf8());
        }
    }
};

class SchoolSubjectInfluence_Family {
public:
    double InfluenceFactor;
    SubjectFamily subjectFamily;
    SchoolSubjectInfluence_Family(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, InfluenceFactor, toDouble)
            else __IF_ENUM_FROM_JSON_AS(it, subjectFamily, SubjectFamily)
            else qWarning(it.key().append(": unhandled.").toUtf8());
        }
    }
};

class SchoolSubjectInfluence {
public:
    double InfluenceFactor;
    SubjectFamily subjectFamily;
    QList<SchoolSubjectInfluence_Stat> stat;
    QList<SchoolSubjectInfluence_Family> family;
    SchoolSubjectInfluence(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            if (it.key() == "SchoolSubjectInfluence_Stat") {
                __OBJLIST_FROM_JSON(it.value(), stat, SchoolSubjectInfluence_Stat)
            } else if (it.key() == "SchoolSubjectInfluence_Family") {
                __OBJLIST_FROM_JSON(it.value(), family, SchoolSubjectInfluence_Family)
            } else {
                qWarning(it.key().append(": unhandled.").toUtf8());
            }
        }
    }
};

class SchoolSubject {
public:

	QString Name;
	QString Description;
    SubjectFamily subjectFamily;
	QString ImageIconPath;
	bool CanBeTaught;
	QList<QString> LessonLocations;
	double SubjectExperienceRatio;
    SchoolSubjectInfluence EvaluationInfluence;
    SchoolSubjectInfluence ImprovementInfluence;
    SchoolSubjectInfluence LearningBoostInfluence;

    SchoolSubject(QJsonObject *d = NULL):
            Name(""),
            Description(""),
            subjectFamily(SubjectFamily::NONE),
            ImageIconPath(""),
            CanBeTaught(true),
            SubjectExperienceRatio(1.0)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			__IF_VAR_FROM_JSON_AS(it, Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_ENUM_FROM_JSON_AS(it, subjectFamily, SubjectFamily)
			else __IF_VAR_FROM_JSON_AS(it, ImageIconPath, toString)
			else __IF_VAR_FROM_JSON_AS(it, CanBeTaught, toBool)
            else __IF_LIST_FROM_JSON_TYPED(it, LessonLocations, toString)
			else __IF_VAR_FROM_JSON_AS(it, SubjectExperienceRatio, toDouble)
            else __IF_OBJ_FROM_JSON(it, EvaluationInfluence)
            else __IF_OBJ_FROM_JSON(it, ImprovementInfluence)
            else __IF_OBJ_FROM_JSON(it, LearningBoostInfluence)
            else qWarning(it.key().append(": unhandled.").toUtf8());
		}
	}
};

#endif // SCHOOLSUBJECT_H
