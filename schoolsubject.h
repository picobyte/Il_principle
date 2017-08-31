#ifndef SCHOOLSUBJECT_H
#define SCHOOLSUBJECT_H
#include "json_macros.h"

class SchoolSubject {
public:
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
	QString Name;
	QString Description;
    SubjectFamily SubjectFamily;
	QString ImageIconPath;
	bool CanBeTaught;
	QList<QString> LessonLocations;
	double SubjectExperienceRatio;
    //QList<SchoolSubjectInfluence> EvaluationInfluence;
    //QList<SchoolSubjectInfluence> ImprovementInfluence;
    //QList<SchoolSubjectInfluence> LearningBoostInfluence;

    SchoolSubject(QJsonObject *d = NULL):
            Name(""),
            Description(""),
            SubjectFamily(SubjectFamily::NONE),
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
            //SubjectFamily subjectFamily
			else __IF_VAR_FROM_JSON_AS(it, ImageIconPath, toString)
			else __IF_VAR_FROM_JSON_AS(it, CanBeTaught, toBool)
                        //QList<string> LessonLocations;
			else __IF_VAR_FROM_JSON_AS(it, SubjectExperienceRatio, toDouble)
			//QList<SchoolSubjectInfluence> EvaluationInfluence
			//QList<SchoolSubjectInfluence> ImprovementInfluence
			//QList<SchoolSubjectInfluence> LearningBoostInfluence
		}
	}
};

#endif // SCHOOLSUBJECT_H
