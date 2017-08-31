#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QList>
#include <QDateTime>
#include "json_macros.h"

class Person {
public:
    Person(QJsonObject *d = NULL):
        Forename(""),
        Lastname(""),
        CustomForename(""),
        SpecialPerson(false),
        TextColor(""),
        Virgin(true),
        AnalVirgin(true),
        Job(""),
        intFather(""),
        intMother(""),
        intLove(""),
        Subject(""),
        GoodInSubject(""),
        //subjectStatLock(RuntimeHelpers.GetObjectValue(new object())),
        ClubMember(""),
        ImageLocation(""),
        PaperDollEventFileName("PD_Default"),
        MaleHeadFileName(""),
        FemaleHeadFileName(""),
        BodyFileName(""),
        StomachFileName(""),
        BreastFileName(""),
        PenisFileName(""),
        TesticleFileName(""),
        CurrentOutfit(OutfitType::DefaultOutfit),
        OutfitName(""),
        intAnalSize(1.0),
        intLoc(""),
        intOldLoc(""),
        intHome(""),
        intBedroom(""),
        intWork(""),
        Trait("")
    {
            if (d) init(d);
    }
    long UID;
    QString Forename;
    QString Lastname;
    QString CustomForename;
    Gender gender;
    QDateTime Birthday;
    bool SpecialPerson;
    QString TextColor;
    QString InitParams;
    //SerializableAttributeDictionary<Gender, double> GenderPreferences;
    QList<Fetish> fetish;
    bool Virgin;
    bool AnalVirgin;
    QString Job;
    uint intJobSlot;
    int Salary;
    //static readonly object unemployedQListLock = RuntimeHelpers.GetObjectValue(new object());
    //static readonly object jobLock = RuntimeHelpers.GetObjectValue(new object());
    QList<QString> Children;
    QString intFather;
    QString intMother;
    QString intLove;
    bool Autoenroll;
    int Schoolclass;
    QString Subject;
    QString GoodInSubject;
    QList<QString> TeacherSubjects;
    //SerializableAttributeDictionary<SchoolSubjectFamily, double> SubjectFamilyExp;
    //SerializableAttributeDictionary<QString, double> SubjectInstanceExp;
    //readonly object subjectStatLock;
    //SerializableStringToDoubleDict DictProposalSupport;
    bool HasDetention;
    bool IsRogue;
    QString ClubMember;
    QString ImageLocation;
    QString PaperDollEventFileName;
    FacialExpressions FaceExpression;
    QString MaleHeadFileName;
    QString FemaleHeadFileName;
    QString BodyFileName;
    QString StomachFileName;
    QString BreastFileName;
    QString PenisFileName;
    QString TesticleFileName;
    int OutfitLevel;
    OutfitType CurrentOutfit;
    QString OutfitName;
    bool OutfitUseEverywhere;
    //SerializableAttributeDictionary<QString, double> dictStats;
    //QList<StatusEffectInstance> StatusEffects;
    double intBreastSize;
    double intStomachSize;
    double intPenisSize;
    double intTesticleSize;
    double intVaginaSize;
    double intAnalSize;
    QString intLoc;
    QString intOldLoc;
    QString intHome;
    QString intBedroom;
    QString intWork;
    bool OutLateTonight;
    bool OutLateLastNight;
    bool UpEarly;
    //InventoryCollection Inventory;
    QString Trait;
    //SerializableAttributeDictionary<QString, int> Skills;
    QList<uint> AttachedEventIDs;
    const static char TRAIT_SEPARATOR_CHAR = ',';
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//long UID
			__IF_VAR_FROM_JSON_AS(it, Forename, toString)
			else __IF_VAR_FROM_JSON_AS(it, Lastname, toString)
			else __IF_VAR_FROM_JSON_AS(it, CustomForename, toString)
            else __IF_ENUM_FROM_JSON_AS(it, gender, Gender)
			//DateTime Birthday
			else __IF_VAR_FROM_JSON_AS(it, SpecialPerson, toBool)
			else __IF_VAR_FROM_JSON_AS(it, TextColor, toString)
			else __IF_VAR_FROM_JSON_AS(it, InitParams, toString)
            //SerializableAttributeQHash<Gender, double> GenderPreferences;
            else __IF_LIST_FROM_JSON_ENUM(it, fetish, static_cast<Fetish>)
            else __IF_VAR_FROM_JSON_AS(it, Virgin, toBool)
			else __IF_VAR_FROM_JSON_AS(it, AnalVirgin, toBool)
			else __IF_VAR_FROM_JSON_AS(it, Job, toString)
            else __IF_VAR_FROM_JSON_AS(it, intJobSlot, toInt)
			else __IF_VAR_FROM_JSON_AS(it, Salary, toInt)
			// readonly object unemployedQListLock = RuntimeHelpers.GetObjectValue(new object())
			// readonly object jobLock = RuntimeHelpers.GetObjectValue(new object())
            else __IF_LIST_FROM_JSON_TYPED(it, Children, toString)
			else __IF_VAR_FROM_JSON_AS(it, intFather, toString)
			else __IF_VAR_FROM_JSON_AS(it, intMother, toString)
			else __IF_VAR_FROM_JSON_AS(it, intLove, toString)
			else __IF_VAR_FROM_JSON_AS(it, Autoenroll, toBool)
			else __IF_VAR_FROM_JSON_AS(it, Schoolclass, toInt)
			else __IF_VAR_FROM_JSON_AS(it, Subject, toString)
			else __IF_VAR_FROM_JSON_AS(it, GoodInSubject, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, TeacherSubjects, toString)
            //SerializableAttributeQHash<SchoolSubjectFamily, double> SubjectFamilyExp;
            //SerializableAttributeQHash<string, double> SubjectInstanceExp;
			//readonly object subjectStatLock
			//SerializableStringToDoubleDict DictProposalSupport
			else __IF_VAR_FROM_JSON_AS(it, HasDetention, toBool)
			else __IF_VAR_FROM_JSON_AS(it, IsRogue, toBool)
			else __IF_VAR_FROM_JSON_AS(it, ClubMember, toString)
			else __IF_VAR_FROM_JSON_AS(it, ImageLocation, toString)
			else __IF_VAR_FROM_JSON_AS(it, PaperDollEventFileName, toString)
			//FacialExpressions FaceExpression
			else __IF_VAR_FROM_JSON_AS(it, MaleHeadFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, FemaleHeadFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, BodyFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, StomachFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, BreastFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, PenisFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, TesticleFileName, toString)
			else __IF_VAR_FROM_JSON_AS(it, OutfitLevel, toInt)
			//OutfitType CurrentOutfit
			else __IF_VAR_FROM_JSON_AS(it, OutfitName, toString)
			else __IF_VAR_FROM_JSON_AS(it, OutfitUseEverywhere, toBool)
            //SerializableAttributeQHash<string, double> dictStats;
			//QList<StatusEffectInstance> StatusEffects
			else __IF_VAR_FROM_JSON_AS(it, intBreastSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intStomachSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intPenisSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intTesticleSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intVaginaSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intAnalSize, toDouble)
			else __IF_VAR_FROM_JSON_AS(it, intLoc, toString)
			else __IF_VAR_FROM_JSON_AS(it, intOldLoc, toString)
			else __IF_VAR_FROM_JSON_AS(it, intHome, toString)
			else __IF_VAR_FROM_JSON_AS(it, intBedroom, toString)
			else __IF_VAR_FROM_JSON_AS(it, intWork, toString)
			else __IF_VAR_FROM_JSON_AS(it, OutLateTonight, toBool)
			else __IF_VAR_FROM_JSON_AS(it, OutLateLastNight, toBool)
			else __IF_VAR_FROM_JSON_AS(it, UpEarly, toBool)
			//InventoryCollection Inventory
			else __IF_VAR_FROM_JSON_AS(it, Trait, toString)
            //SerializableAttributeQHash<string, int> Skills;
            else __IF_LIST_FROM_JSON_TYPED(it, AttachedEventIDs, toInt)
		}
	}
};

#endif // PERSON_H
