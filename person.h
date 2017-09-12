#ifndef PERSON_H
#define PERSON_H

#include <math.h>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDateTime>
#include <QTextStream>
#include "json_macros.h"
#include "clubs.h"
#include "location.h"
#include "stat.h"
#include "schoolsubject.h"
#include "statuseffect.h"
#include "inventorycollection.h"
#include "locationjobdetails.h"
#include "mind.h"
#include "visualevent.h"

class Game;
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
        // try {
        for (QHash<QString, Stat>::iterator it = Game::DictOfStats.begin();
                it != Game::DictOfStats.end(); ++it)
            SetStat(*it, 0.0);
        // }
        if (!Game::GameLoading)
            UIDManager.AssignUID(this);
    }
    long UID;
    QString Forename;
    QString Lastname;
    QString CustomForename;
    Gender gender;
    QDate Birthday;
    bool SpecialPerson;
    QString TextColor;
    QString InitParams;
    QHash<Gender, double> GenderPreferences;
    QList<Fetish> fetish;
    bool Virgin;
    bool AnalVirgin;
    QString Job;
    int intJobSlot;
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
    QHash<SchoolSubjectFamily, double> SubjectFamilyExp;
    QHash<QString, double> SubjectInstanceExp;
    //readonly object subjectStatLock;
    QHash<QString, double> DictProposalSupport;
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
    QHash<QString, double> dictStats;
    QList<StatusEffectInstance> StatusEffects;
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
    InventoryCollection Inventory;
    QString Trait;
    QHash<QString, int> Skills;
    QList<uint> AttachedEventIDs;
    const static char TRAIT_SEPARATOR_CHAR;
    QString Name() const
    {
        if (Lastname.isNull() || Lastname.contains(QRegExp("^\\s*$")))
            return Forename;

        if (Forename.isNull() || Forename.contains(QRegExp("^\\s*$")))
            return Lastname;

        return Forename + " " + Lastname;
    }
    QString DisplayForename() const
    {
        if (CustomForename.isNull() || CustomForename.contains(QRegExp("^\\s*$")))
            return Forename;

        return CustomForename;
    }
    QString DisplayName() const
    {
        QString displayForename = DisplayForename();
        if (Lastname.isNull() || Lastname.contains(QRegExp("^\\s*$")))
            return displayForename;

        if (displayForename.isNull() || displayForename.contains(QRegExp("^\\s*$")))
            return Lastname;

        return displayForename + " " + Lastname;
    }
    QString NameAndTitle() const
    {
        QString sb = DisplayName();
        QTextStream(&sb) << " (" << Age() << ")";

        if (!Job.isEmpty())
            sb.append(", ").append(Job);

        if (HasTrait("PTA"))
            sb.append(", PTA");

        if (IsParent())
            sb.append(", Parent");

        return sb;
    }
    int Age() const
    {
        // checked {
        int age = Game::SchoolCalendar.TodayDate.Year - Birthday.Year;

        if (DateTime.Compare(Birthday, Game::SchoolCalendar.TodayDate.AddYears(0 - age)) > 0)
            --age;

        return age;
        // }
    }
    SexualPref SexualOrientation() const
    {
        double likesMale = GetGenderPreference(Gender::Male);
        double likesFemale = GetGenderPreference(Gender::Female);
        double likesFuta = GetGenderPreference(Gender::Futanari);
        double maleAttraction = likesMale + 0.3 * likesFuta;
        double femaleAttraction = likesFemale + 0.3 * likesFuta;

        if (likesMale < 25.0 && likesFemale < 25.0 && likesFuta < 25.0)
            return SexualPref::Asexual;

        switch (gender) {

        case Gender::Male:
            if (fabs(likesMale - likesFemale) < 10.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
                return SexualPref::Bisexual;
            if (maleAttraction > femaleAttraction)
                return SexualPref::Homosexual;
        case Gender::Female:
            if (fabs(likesMale - likesFemale) < 10.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
                return SexualPref::Bisexual;
            if (femaleAttraction > maleAttraction)
                return SexualPref::Homosexual;
        case Gender::Futanari:
            if (fabs(likesMale - likesFemale) < 15.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
                return SexualPref::Bisexual;
            if (likesFuta > (likesMale + likesFemale) * 0.75)
                return SexualPref::Homosexual;
        default:
            return SexualPref::Asexual;
        }
        return SexualPref::Heterosexual;
    }
    LocationJobDetails* JobDetails() const
    {
        Location* w = Work();

        if (w && w->AssociatedJobs.count() > intJobSlot)
            return &w->AssociatedJobs[intJobSlot];

        return NULL;
    }
    Person* Father() const
    {
        if (Game::DictOfPersonNames.contains(intFather))
            return Game::DictOfPersonNames[intFather];

        return NULL;
    }
    void Father(Person *v)
    {
        intFather = v ? v->Name() : "";
    }
    Person* Mother() const
    {
        if (Game::DictOfPersonNames.contains(intMother))
            return Game::DictOfPersonNames[intMother];

        return NULL;
    }
    void Mother(Person *v)
    {
        intMother = v ? v->Name() : "";
    }
    Person* Love() const
    {
        if (intLove == "Principal")
            return Game::HeadTeacher;

        if (Game::DictOfPersonNames.contains(intLove))
            return Game::DictOfPersonNames[intLove];

        return NULL;
    }
    void Love(Person *v)
    {
        intLove = v ? (v == Game::HeadTeacher ? "Principal" : intLove = v->Name()) : "";
    }
    bool IsCouple() const
    {
        return !intLove.isEmpty();
    }
    bool IsParent() const
    {
        return Children.count() > 0;
    }
    bool IsFavorite() const
    {
        return Game::FavoriteStudentList.contains(UID);
    }
    void IsFavorite(bool& value)
    {
        if (value) {
            if (!IsFavorite())
                Game::FavoriteStudentList.insert(UID);
        } else {
            Game::FavoriteStudentList.remove(UID);
        }
    }
    double ProposalSupport(QString& ProposalName) const
    {
        if (DictProposalSupport.contains(ProposalName))
            return DictProposalSupport[ProposalName];
        else
            return 0.0;
    }
    void ProposalSupport(QString& ProposalName, double& value)
    {
        if (value == 0.0) {
            if (DictProposalSupport.contains(ProposalName))
                DictProposalSupport.remove(ProposalName);
        } else {
            DictProposalSupport[ProposalName] = value;
        }
    }
    Clubs* Club() const
    {
        return Game::GetClub(ClubMember);
    }
    void Club(Clubs *v)
    {
        ClubMember = v ? v->Name : "";
    }
    Body::Size BreastSize() const
    {
        return static_cast<Body::Size>(round(intBreastSize < 0.0 ? 0.0 : (intBreastSize > 10.0 ? 10.0 : intBreastSize)));
    }
    void BreastSize(Body::Size& value)
    {
        if (gender == Gender::Male)
            intBreastSize = 0.0;
        else
            intBreastSize = static_cast<double>(value);
    }
    Body::Size StomachSize() const
    {
        return static_cast<Body::Size>(round(intStomachSize < 0.0 ? 0.0 : (intStomachSize > 10.0 ? 10.0 : intStomachSize)));
    }
    void StomachSize(Body::Size& value)
    {
        if (gender == Gender::Male)
            intStomachSize = 0.0;
        else
            intStomachSize = static_cast<double>(value);
    }
    Body::Size PenisSize() const
    {
        return static_cast<Body::Size>(round(intPenisSize < 0.0 ? 0.0 : (intPenisSize > 10.0 ? 10.0 : intPenisSize)));
    }
    void PenisSize(Body::Size& value)
    {
        if (gender == Gender::Female)
            intPenisSize = 0.0;
        else
            intPenisSize = value < Body::Size::Tiny ? 1.0 : static_cast<double>(value);
    }
    Body::Size TesticleSize() const
    {
        return static_cast<Body::Size>(round(intTesticleSize < 0.0 ? 0.0 : (intTesticleSize > 10.0 ? 10.0 : intTesticleSize)));
    }
    void TesticleSize(Body::Size& value)
    {
        if (gender == Gender::Female)
            intTesticleSize = 0.0;
        else
            intTesticleSize = value < Body::Size::Tiny ?1.0 : static_cast<double>(value);
    }
    Body::Size VaginaSize() const
    {
        return static_cast<Body::Size>(round(intVaginaSize < 0.0 ? 0.0 : (intVaginaSize > 10.0 ? 10.0 : intVaginaSize)));
    }
    void VaginaSize(Body::Size& value)
    {
        intVaginaSize = (gender == Gender::Male ? 0.0 : (value < Body::Size::Tiny ? 1.0 : static_cast<double>(value)));
    }
    Body::Size AnalSize() const
    {
        return static_cast<Body::Size>(round(intAnalSize < 0.0 ? 0.0 : (intAnalSize > 10.0 ? 10.0 : intAnalSize)));
    }
    void AnalSize(Body::Size& value)
    {
        intAnalSize = value < Body::Size::Tiny ? 1.0 : static_cast<double>(value);
    }
    Location* CurrentLocation() const
    {
        if (intLoc.isEmpty())
            return NULL;

        return Game::GetLocation(intLoc);
    }
    void CurrentLocation(Location* value)
    {
        intOldLoc = intLoc;

        if (value == NULL) {
            if (!intLoc.isEmpty()) {
                Game::GetLocation(intLoc)->OccupantLeave(this);
                intLoc = "";
            }
        } else {
            if (!intLoc.isEmpty())
                Game::GetLocation(intLoc)->OccupantLeave(this);

            intLoc = value->Name;
            Game::GetLocation(intLoc)->OccupantEnter(this);
        }
    }
    Location* OldLocation() const
    {
        if (!intOldLoc.isEmpty())
            return Game::GetLocation(intOldLoc);

        return NULL;
    }
    void OldLocation(Location *v)
    {
        intOldLoc = ((v == NULL) ? "" : v->Name);
    }
    Location* Home() const
    {
        if (intHome.isEmpty())
            return Game::GetLocation("General Home");

        return Game::GetLocation(intHome);
    }
    void Home(Location *v)
    {
        if (v == NULL)
            intHome = "";
        else
            intHome = v->Name;
    }
    Location* Bedroom() const
    {
        if (intBedroom.isEmpty())
            return Game::GetLocation("General Home");

        return Game::GetLocation(intBedroom);
    }
    void Bedroom(Location *v)
    {
        if (v == NULL) {
            intBedroom = "";
            return;
        }
        intBedroom = v->Name;
    }
    bool IsHome() const
    {
        return CurrentLocation() == Home() || CurrentLocation() == Bedroom();
    }
    Location* Work() const
    {
        if (intWork.isEmpty())
            return NULL;

        return Game::GetLocation(intWork);
    }
    void Work(Location *value)
    {
        if (value == NULL) {
            intWork = "";
            return;
        }
        intWork = value->Name;
    }
    QString InventoryName() const
    {
        return DisplayName();
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJ_FROM_JSON(it, UID)
            else __IF_VAR_FROM_JSON_AS(it, Forename, toString)
            else __IF_VAR_FROM_JSON_AS(it, Lastname, toString)
            else __IF_VAR_FROM_JSON_AS(it, CustomForename, toString)
            else __IF_ENUM_FROM_JSON_AS(it, Gender, Gender)
            else __IF_OBJ_FROM_JSON(it, Birthday)
            else __IF_VAR_FROM_JSON_AS(it, SpecialPerson, toBool)
            else __IF_VAR_FROM_JSON_AS(it, TextColor, toString)
            else __IF_VAR_FROM_JSON_AS(it, InitParams, toString)
            //QHash<Gender, double> GenderPreferences
            else __IF_LIST_FROM_JSON_ENUM(it, Fetish, Fetish)
            else __IF_VAR_FROM_JSON_AS(it, Virgin, toBool)
            else __IF_VAR_FROM_JSON_AS(it, AnalVirgin, toBool)
            else __IF_VAR_FROM_JSON_AS(it, Job, toString)
            else __IF_VAR_FROM_JSON_AS(it, intJobSlot, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Salary, toInt)
            //readonly object unemployedListLock = RuntimeHelpers.GetObjectValue(new object())
            //readonly object jobLock = RuntimeHelpers.GetObjectValue(new object())
            else __IF_LIST_FROM_JSON_TYPED(it, Children, toString)
            else __IF_VAR_FROM_JSON_AS(it, intFather, toString)
            else __IF_VAR_FROM_JSON_AS(it, intMother, toString)
            else __IF_VAR_FROM_JSON_AS(it, intLove, toString)
            else __IF_VAR_FROM_JSON_AS(it, Autoenroll, toBool)
            else __IF_VAR_FROM_JSON_AS(it, Schoolclass, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Subject, toString)
            else __IF_VAR_FROM_JSON_AS(it, GoodInSubject, toString)
            else __IF_LIST_FROM_JSON_TYPED(it, TeacherSubjects, toString)
            //else __IF_OBJHASH_FROM_JSON_TYPED(it, subjectStatLock)
            //QHash<SchoolSubjectFamily, double> SubjectFamilyExp
            else __IF_HASH_FROM_JSON_TYPED(it, SubjectInstanceExp, toDouble)
            //else __IF_OBJ_FROM_JSON(it, subjectStatLock)
            else __IF_OBJ_FROM_JSON(it, DictProposalSupport)
            else __IF_VAR_FROM_JSON_AS(it, HasDetention, toBool)
            else __IF_VAR_FROM_JSON_AS(it, IsRogue, toBool)
            else __IF_VAR_FROM_JSON_AS(it, ClubMember, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImageLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, PaperDollEventFileName, toString)
            else __IF_ENUM_FROM_JSON_AS(it, FaceExpression, FacialExpressions)
            else __IF_VAR_FROM_JSON_AS(it, MaleHeadFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, FemaleHeadFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, BodyFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, StomachFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, BreastFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, PenisFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, TesticleFileName, toString)
            else __IF_VAR_FROM_JSON_AS(it, OutfitLevel, toInt)
            else __IF_ENUM_FROM_JSON_AS(it, CurrentOutfit, OutfitType)
            else __IF_VAR_FROM_JSON_AS(it, OutfitName, toString)
            else __IF_VAR_FROM_JSON_AS(it, OutfitUseEverywhere, toBool)
            else __IF_HASH_FROM_JSON_TYPED(it, dictStats, toDouble)
            else __IF_OBJLIST_FROM_JSON(it, StatusEffects, StatusEffectInstance)
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
            else __IF_OBJ_FROM_JSON(it, Inventory)
            else __IF_VAR_FROM_JSON_AS(it, Trait, toString)
            else __IF_HASH_FROM_JSON_TYPED(it, Skills, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, AttachedEventIDs, toInt)
            // *INDENT-ON*
        }
    }
    bool ShouldSerializeCustomForename()
    {
        return !(CustomForename.isNull() || CustomForename.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeSpecialPerson()
    {
        return SpecialPerson;
    }
    bool ShouldSerializeTextColor()
    {
        return !(TextColor.isNull() || TextColor.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeInitParams()
    {
        return !(InitParams.isNull() || InitParams.contains(QRegExp("^\\s*$")));
    }
    bool HasBirthday()
    {
        QDate today = Game::SchoolCalendar.TodayDate();
        return (Birthday.day() == today.day() && Birthday.month() == today.month()) ||
                (Birthday.day() == 29 && today.day() == 1 && today.addDays(-1).day() == 28);
    }
    QString ToString()
    {
        return Name().prepend("Person: ");
    }
    double GetGenderPreference(Gender genderName) const
    {
        double retVal = GenderPreferences.contains(genderName) ? GenderPreferences[genderName] : 0.0;
        double minVal = 0.0;
        double maxVal = 100.0;
        //object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::const_iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se) {

            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi) {

                if (*modi is Modifier_AddGenderPrefValue) {

                    Modifier_AddGenderPrefValue addConstMod = (Modifier_AddGenderPrefValue)*modi;
                    if (addConstMod.gender == genderName)
                        retVal += addConstMod.GetValue(*se);

                } else if (*modi is Modifier_MinGenderPrefValue) {

                    Modifier_MinGenderPrefValue minValMod = (Modifier_MinGenderPrefValue)*modi;
                    if (minValMod.gender == genderName && minValMod.GetValue(*se) > minVal)
                        minVal = minValMod.GetValue(*se);

                } else if (*modi is Modifier_MaxGenderPrefValue) {

                    Modifier_MaxGenderPrefValue maxValMod = (Modifier_MaxGenderPrefValue)*modi;
                    if (maxValMod.gender == genderName && maxValMod.GetValue(*se) < maxVal)
                        minVal = maxValMod.GetValue(*se);
                }
            }
            // }
        }
        // }
        // }
        return retVal < minVal ? minVal : (retVal > maxVal ? maxVal : retVal);
    }
    void SetGenderPreference(Gender genderName, double value)
    {
        GenderPreferences[genderName] = value < 0.0 ? 0.0 : (value > 100.0 ? 100.0 : value);
    }
    void AddGenderPreference(Gender genderName, double value)
    {
        double addValue = value;
        // object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se)
        {
            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi)
            {
                if (*modi is Modifier_IncreaseGenderPrefMultiplier)
                {
                    Modifier_IncreaseGenderPrefMultiplier scaleMod = (Modifier_IncreaseGenderPrefMultiplier)*modi;
                    if (genderName == scaleMod.Gender && value > 0.0)
                    {
                        addValue *= scaleMod.GetScaleFactor(*se);
                    }
                }
                else if (*modi is Modifier_DecreaseGenderPrefMultiplier)
                {
                    Modifier_DecreaseGenderPrefMultiplier scaleMod2 = (Modifier_DecreaseGenderPrefMultiplier)*modi;
                    if (genderName == scaleMod2.Gender && value < 0.0)
                    {
                        addValue *= scaleMod2.GetScaleFactor(*se);
                    }
                }
            }
            // }
        }
        // }
        // }
        GenderPreferences[genderName] = (GenderPreferences.contains(genderName) ? GenderPreferences[genderName] : 0.0) + addValue < 0.0 ? 0.0 : ((GenderPreferences.contains(genderName) ? GenderPreferences[genderName] : 0.0) + addValue > 100.0 ? 100.0 : (GenderPreferences.contains(genderName) ? GenderPreferences[genderName] : 0.0) + addValue);
    }
    bool LikesGender(Gender Gend) const
    {
        return GetGenderPreference(Gend) >= 50.0;
    }
    bool LikesPenis() const
    {
        double likesMale = GetGenderPreference(Gender::Male);
        if (likesMale > 50.0)
            return true;

        double likesFuta = GetGenderPreference(Gender::Futanari);
        return (likesFuta > 65.0 || likesMale + likesFuta > 80.0);
    }
    bool LikesVagina() const
    {
        double likesFemale = GetGenderPreference(Gender::Female);
        if (likesFemale > 50.0)
            return true;

        double likesFuta = GetGenderPreference(Gender::Futanari);
        return (likesFuta > 65.0 || likesFemale + likesFuta > 80.0);
    }
    bool LikesBreast() const
    {
        double likesFemale = GetGenderPreference(Gender::Female);
        if (likesFemale > 50.0)
            return true;

        double likesFuta = GetGenderPreference(Gender::Futanari);
        return (likesFuta > 50.0 || likesFemale + likesFuta > 70.0);
    }
    bool HasPenis() const
    {
        return gender == Gender::Male || gender == Gender::Futanari;
    }
    bool HasVagina() const
    {
        return gender == Gender::Female || gender == Gender::Futanari;
    }
    bool HasBreasts() const
    {
        return gender == Gender::Female || gender == Gender::Futanari;
    }
    bool ShouldSerializeFetish()
    {
        return fetish.count() > 0;
    }
    void AddFetish(Fetish F)
    {
        if (!fetish.contains(F) && F != hhs_.Fetish.None)
            fetish.Add(F);
    }
    bool HasFetish(Fetish F) const
    {
        return fetish.contains(F);
    }
    bool ShouldSerializeVirgin() const
    {
        return !Virgin;
    }
    bool ShouldSerializeAnalVirgin() const
    {
        return !AnalVirgin;
    }
    bool ShouldSerializeJob() const
    {
        return !Job.isEmpty();
    }
    bool ShouldSerializeintJobSlot() const
    {
        return !intWork.isEmpty();
    }
    bool ShouldSerializeSalary() const
    {
        return Job.contains(QRegExp("(?:Teacher|Librarian|School (?:Secretary|Doctor))"));
    }
    void AssignWork(Location *Room, LocationJobDetails jb)
    {
        UnassignWork();
        //object obj = Person.jobLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (Room != NULL && Room->AssociatedJobs.contains(jb) && jb.CanEmploy(this))
        {
            jb.Staff.insert(Name());
            intJobSlot = (unsigned)Room->AssociatedJobs.indexOf(jb);
            if (Job.isEmpty())
                Job = jb.JobTitle;

            //object obj2 = Person.unemployedListLock;
            //ObjectFlowControl.CheckForSyncLockOnValueType(obj2);
            // lock (obj2) {
            Game::UnemployedPersons.remove(Name());
            // }
        }
        // }
    }
    void UnassignWork()
    {
        //object obj = Person.jobLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        LocationJobDetails *jb = JobDetails();
        if (jb != NULL)
            jb->Staff.remove(Name());

        Work(NULL);
        intJobSlot = 0u;
        if (Job != "Teacher" && Job != "Student" && !Trait.contains("Staff"))
        {
            //object obj2 = Person.unemployedListLock;
            //ObjectFlowControl.CheckForSyncLockOnValueType(obj2);
            // lock (obj2) {
            if (Game::UnemployedPersons.contains(Name()))
                Game::UnemployedPersons[Name()] = this;
            else
                Game::UnemployedPersons.add(Name(), this);
            // }
        }
        // }
    }
    bool ShouldSerializeChildren() const
    {
        return Children.count() > 0;
    }
    bool ShouldSerializeintFather()
    {
        return !intFather.isEmpty();
    }
    bool ShouldSerializeintMother()
    {
        return !intMother.isEmpty();
    }
    bool ShouldSerializeintLove()
    {
        return !intLove.isEmpty();
    }
    bool ShouldSerializeAutoenroll()
    {
        return Autoenroll;
    }
    bool ShouldSerializeSchoolclass()
    {
        return Schoolclass != 0 && Job == "Student";
    }
    void ResetSchoolclass()
    {
        Schoolclass = 0;
    }
    bool ShouldSerializeSubject()
    {
        return !Subject.isEmpty() && (Job == "Student" || Job == "Teacher");
    }
    void ResetSubject()
    {
        Subject = "";
    }
    bool ShouldSerializeGoodInSubject()
    {
        return !GoodInSubject.isEmpty() && (Job == "Student" || Job == "Teacher");
    }
    void ResetGoodInSubject()
    {
        GoodInSubject = "";
    }
    bool ShouldSerializeTeacherSubjects()
    {
        return Job == "Teacher";
    }
    void ResetTeacherSubjects()
    {
        TeacherSubjects.clear();
    }
    double GetSubjectExp(QString SubjectInstanceName)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        SchoolSubject* s = Game::GetSubject(SubjectInstanceName);
        if (s != NULL)
            return s->GetSubjectExp(this);

        return 0.0;
        // }
    }
    void AddSubjectExp(QString SubjectInstanceName, double Value)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        SchoolSubject* s = Game::GetSubject(SubjectInstanceName);
        if (s != NULL)
            s->AddSubjectExp(this, Value);
        // }
    }
    double GetSubjectFamilyExp(SchoolSubjectFamily SubjectFamily)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        double GetSubjectFamilyExp;
        // lock (obj) {
        double retVal = SubjectFamilyExp.contains(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0;
        double minVal = 0.0;
        double maxVal = 100.0;
        //object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se) {

            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi) {

                if (*modi is Modifier_AddSubjectFamilyValue)
                {
                    Modifier_AddSubjectFamilyValue addConstMod = (Modifier_AddSubjectFamilyValue)*modi;
                    if (addConstMod.SubjectFamilyName == SubjectFamily)
                        retVal += addConstMod.GetValue(*se);
                }
                else if (*modi is Modifier_MinSubjectFamilyValue)
                {
                    Modifier_MinSubjectFamilyValue minValMod = (Modifier_MinSubjectFamilyValue)*modi;
                    if (minValMod.SubjectFamilyName == SubjectFamily && minValMod.GetValue(*se) > minVal)
                        minVal = minValMod.GetValue(*se);
                }
                else if (*modi is Modifier_MaxSubjectFamilyValue)
                {
                    Modifier_MaxSubjectFamilyValue maxValMod = (Modifier_MaxSubjectFamilyValue)*modi;
                    if (maxValMod.SubjectFamilyName == SubjectFamily && maxValMod.GetValue(*se) < maxVal)
                        minVal = maxValMod.GetValue(*se);
                }
            }
            // }
        }
        // }
        // }
        GetSubjectFamilyExp = retVal < minVal ? minVal : (retVal > maxVal ? maxVal : retVal);
        // }
        return GetSubjectFamilyExp;
    }
    double GetSubjectInstanceExp(QString SubjectInstanceName)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (SubjectInstanceExp.contains(SubjectInstanceName))
            return SubjectInstanceExp[SubjectInstanceName];

        return 0.0;
        // }
    }
    void SetSubjectFamilyExp(SchoolSubjectFamily SubjectFamily, double Value)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        Value = Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value);
        if (SubjectFamilyExp.contains(SubjectFamily))
            SubjectFamilyExp[SubjectFamily] = Value;
        else
            SubjectFamilyExp.insert(SubjectFamily, Value);
        // }
    }
    void SetSubjectInstanceExp(QString SubjectInstanceName, double Value)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        Value = Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value);
        if (SubjectInstanceExp.contains(SubjectInstanceName))
            SubjectInstanceExp[SubjectInstanceName] = Value;
        else
            SubjectInstanceExp.insert(SubjectInstanceName, Value);
        // }
    }
    void AddSubjectFamilyExp(SchoolSubjectFamily SubjectFamily, double Value)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        double addValue = Value;
        //object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se) {

            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi) {

                if (*modi is Modifier_IncreaseSubjectFamilyMultiplier)
                {
                    Modifier_IncreaseSubjectFamilyMultiplier scaleMod = (Modifier_IncreaseSubjectFamilyMultiplier)*modi;
                    if (SubjectFamily == scaleMod.SubjectFamilyName && Value > 0.0)
                        addValue *= scaleMod.GetScaleFactor(this, *se);
                }
                else if (*modi is Modifier_DecreaseSubjectFamilyMultiplier)
                {
                    Modifier_DecreaseSubjectFamilyMultiplier scaleMod2 = (Modifier_DecreaseSubjectFamilyMultiplier)*modi;
                    if (SubjectFamily == scaleMod2.SubjectFamilyName && Value < 0.0)
                        addValue *= scaleMod2.GetScaleFactor(this, *se);
                }
            }
            // }
        }
        // }
        // }
        SubjectFamilyExp[SubjectFamily] = (SubjectFamilyExp.contains(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0) + addValue < 0.0 ? 0.0 : ((SubjectFamilyExp.contains(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0) + addValue > 100.0 ? 100.0 : (SubjectFamilyExp.contains(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0) + addValue);
        // }
    }
    void AddSubjectInstanceExp(QString SubjectInstanceName, double Value)
    {
        // object obj = subjectStatLock;
        // ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (SubjectInstanceExp.contains(SubjectInstanceName))
            SubjectInstanceExp[SubjectInstanceName] = SubjectInstanceExp[SubjectInstanceName] + Value < 0.0 ? 0.0 : (SubjectInstanceExp[SubjectInstanceName] + Value > 100.0 ? 100.0 : SubjectInstanceExp[SubjectInstanceName] + Value);
        else
            SubjectInstanceExp.insert(SubjectInstanceName, Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value));
        // }
    }
    bool ShouldSerializeProposalSupport()
    {
        return (Job == "Teacher" || HasTrait("PTA")) && DictProposalSupport.count() > 0;
    }
    bool ShouldSerializeHasDetention()
    {
        return HasDetention;
    }
    bool ShouldSerializeIsRogue()
    {
        return IsRogue && Job == "Student";
    }
    bool ShouldSerializeClubMember()
    {
        return !(ClubMember.isNull() || ClubMember.contains(QRegExp("^\\s*$")));
    }
    void ResetClubMember()
    {
        ClubMember = "";
    }
    bool ShouldSerializeImageLocation()
    {
        return (Name() == Game::HeadTeacher.Name() || SpecialPerson) && !ImageLocation.isEmpty();
    }
    bool ShouldSerializeOutfitLevel()
    {
        return OutfitLevel != 0;
    }
    bool ShouldSerializeOutfitName()
    {
        return !(OutfitName.isNull() || OutfitName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeOutfitUseEverywhere()
    {
        return OutfitUseEverywhere;
    }
    void UpdatePaperDollImage(OutfitType Outfit = OutfitType::DefaultOutfit)
    {
        if (CurrentLocation() == NULL || Outfit != OutfitType::DefaultOutfit)
            CurrentOutfit = Outfit;

        else if (!OutfitName.isEmpty())
            CurrentOutfit = OutfitType::ClothingItem;

        else if (Club() != NULL && Game::GameTime.IsTimeForClub(Club()) && CurrentLocation().Name() == Club()->ClubRoom)
            CurrentOutfit = OutfitType::Club;

        else if (CurrentLocation()->GetActualSpecialOutfit() != OutfitType::DefaultOutfit)
            CurrentOutfit = CurrentLocation()->GetActualSpecialOutfit();

        else if (IsAsleep())
            CurrentOutfit = OutfitType::Sleep;

        else if (IsWorking())
            CurrentOutfit = OutfitType::Work;
        else
            CurrentOutfit = OutfitType::DefaultOutfit;

        VisualEvent* pdev = VisualEventManager.GetEventByFilename(PaperDollEventFileName, VisualEventKind.PaperDollHandler);
        if (pdev != NULL)
            pdev.Execute(this);
    }
    void UpdateOutfitLevel()
    {
        VisualEventManager.ExecuteNativeEvent("UpdateOutfitLevel", this);
    }
    double GetStat(QString statName)
    {
        Stat arg_31_0 = Game::DictOfStats[statName];
        double retVal = dictStats.contains(statName) ? dictStats[statName] : 0.0;
        double minVal = arg_31_0.MinValue;
        double maxVal = arg_31_0.MaxValue;
        //object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se) {

            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi) {

                if (*modi is Modifier_AddStatValue) {

                    Modifier_AddStatValue addConstMod = (Modifier_AddStatValue)*modi;
                    if (addConstMod.StatName == statName)
                        retVal += addConstMod.GetValue(*se);

                } else if (*modi is Modifier_MinStatValue) {

                    Modifier_MinStatValue minValMod = (Modifier_MinStatValue)*modi;
                    if (minValMod.StatName == statName && minValMod.GetValue(*se) > minVal)
                        minVal = minValMod.GetValue(*se);

                } else if (*modi is Modifier_MaxStatValue) {

                    Modifier_MaxStatValue maxValMod = (Modifier_MaxStatValue)*modi;
                    if (maxValMod.StatName == statName && maxValMod.GetValue(*se) < maxVal)
                        minVal = maxValMod.GetValue(*se);
                }
            }
            // }
        }
        // }
        // }
        return retVal < minVal ? minVal : (retVal > maxVal ? maxVal : retVal);
    }
    void SetStat(QString statName, double value)
    {
        if (Game::DictOfStats.contains(statName))
        {
            Stat statBase = Game::DictOfStats[statName];
            dictStats[statName] = value < statBase.MinValue ? statBase.MinValue : (value > statBase.MaxValue ? statBase.MaxValue : value);
        }
    }
    void AddStat(QString statName, double value)
    {
        if (Game::DictOfStats.contains(statName))
        {
            Stat statBase = Game::DictOfStats[statName];
            double addValue = value;
            //object statusEffects = StatusEffects;
            // lock (statusEffects) {
            // try {
            for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                    se != StatusEffects.end(); ++se)
            {
                StatusEffect effect = Game::DictOfStatusEffects[se->Name];
                // try {
                for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                        modi != effect.Modifiers.end(); ++modi)
                {
                    if (*modi is Modifier_IncreaseStatMultiplier)
                    {
                        Modifier_IncreaseStatMultiplier scaleMod = (Modifier_IncreaseStatMultiplier)*modi;
                        if (statName == scaleMod.StatName && value > 0.0)
                            addValue *= scaleMod.GetScaleFactor(this, *se);
                    }
                    else if (*modi is Modifier_DecreaseStatMultiplier)
                    {
                        Modifier_DecreaseStatMultiplier scaleMod2 = (Modifier_DecreaseStatMultiplier)*modi;
                        if (statName == scaleMod2.StatName && value < 0.0)
                            addValue *= scaleMod2.GetScaleFactor(this, *se);
                    }
                }
                // }
            }
            // }
            // }
            dictStats[statName] = (dictStats.contains(statName) ? dictStats[statName] : 0.0) + addValue < statBase.MinValue ? statBase.MinValue : ((dictStats.contains(statName) ? dictStats[statName] : 0.0) + addValue > statBase.MaxValue ? statBase.MaxValue : (dictStats.contains(statName) ? dictStats[statName] : 0.0) + addValue);
        }
    }
    void AdjustStatsByMind()
    {
        int popTagIndex = Game::ScenarioConfig.PopulationTag.indexOf(Job);
        Mind GameMind;
        if (popTagIndex >= 0)
            GameMind = Game::ScenarioConfig.MindData[popTagIndex];
        else
            GameMind = Game::ScenarioConfig.MindData[0];

        // try {
        QList<QString> MindStats = GameMind.GetStats();
        MindStats.Remove("Arousal");
        MindStats.Remove("Authority");
        MindStats.Remove("Inhibition");
        // try {
        for (QList<QString>::iterator it = MindStats.begin();
                it != MindStats.end(); ++it)
            AdjustStat(GameMind, *it;
        // }
        if (GetStat("Arousal") < GetStat("Lust"))
            AddStat("Arousal", 0.05 * (GetStat("Lust") - GetStat("Arousal")));

        double CorLust = (GetStat("Corruption") + GetStat("Lust")) * 0.5;
        AddStat("Inhibition", -(0.005 * (CorLust - (100.0 - GetStat("Inhibition")))));

        if (GetStat("Willpower") > GetStat("Authority"))
            AddStat("Authority", 0.01 * (GetStat("Willpower") - GetStat("Authority")));
        else
            AddStat("Authority", -(0.1 * (GetStat("Authority") - GetStat("Willpower"))));

        AdjustStat(GameMind, "Arousal");
        AdjustStat(GameMind, "Authority");
        AdjustStat(GameMind, "Inhibition");
        // }
        /*catch (Exception expr_1CB)
        {
            ProjectData.SetProjectError(expr_1CB);
            Exception e = expr_1CB;
            ExceptionHandler.HandleException(e);
            ProjectData.ClearProjectError();
        }*/
    }
    void AdjustStat(Mind mind, QString SE)
    {
        Adjustment adj = mind.AdjustmentByStat(SE);
        if (adj != NULL)
        {
            double stat = GetStat(SE);
            if (stat < adj.Range.Min) {
                if (adj.lowMagnitude > 0.0) {
                    double dif = adj.Range.Min - stat;
                    AddStat(SE, dif * (adj.lowMagnitude * 0.0004));
                }
            } else if (stat > adj.Range.Max && adj.highMagnitude > 0.0) {
                double dif2 = stat - adj.Range.Max;
                AddStat(SE, -dif2 * (adj.highMagnitude * 0.0004));
            }
            ApplyFuzziness(SE);
        }
    }
    void ApplyFuzziness(QString SE)
    {
        AddStat(SE, (Game::RNG.NextDouble() - 0.5) * 0.3);
    }
    void RandomizeArousalAndEnergy()
    {
        if (this != Game::HeadTeacher)
        {
            AddStat("Arousal", (double)Game::RNG.Next(-20, 20));
            AddStat("Energy", (double)Game::RNG.Next((int)round(Math.Truncate(GetStat("Stamina")) * 2.0), (int)round(Game::DictOfStats["Energy"].MaxValue)));
        }
    }
    void AddStatusEffect(QString effectName)
    {
        StatusEffect effect = Game::DictOfStatusEffects[effectName];
        object statusEffects = StatusEffects;
        // lock (statusEffects) {
        switch (effect.AccumulationType) {
        case StatusEffectAccumulationType.None:
            if (!StatusEffects.Exists((StatusEffectInstance se) => se.Name == effect.Name))
                StatusEffects.Add(effect.GetInstance());
            break;
        case StatusEffectAccumulationType.Refresh:
            StatusEffects.RemoveAll((StatusEffectInstance se) => se.Name == effect.Name);
            StatusEffects.Add(effect.GetInstance());
            break;
        case StatusEffectAccumulationType.Stack:
            StatusEffects.Add(effect.GetInstance());
        }
        // }
    }
    void RemoveStatusEffect(QString effectName)
    {
        object statusEffects = StatusEffects;
        // lock (statusEffects) {
        StatusEffects.RemoveAll((StatusEffectInstance se) => se.Name == effectName);
        // }
    }
    QString GetPersonalityArchetype()
    {
        QString personality = "";
        QString archetype = "";
        object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
                it != StatusEffects.end(); ++it)
        {
            StatusEffectInstance se = enumerator.Current;
            if (se.Name.startsWith("Personality"))
                personality = Game::DictOfStatusEffects[se.Name].DisplayName;

            else if (se.Name.startsWith("Archetype"))
                archetype = Game::DictOfStatusEffects[se.Name].DisplayName;
        }
        // }
        // }
        if (Operators.CompareString(personality, "", false) != 0)
        {
            if (Operators.CompareString(archetype, "", false) != 0)
                return personality + " " + archetype;

            return personality;
        }
        return archetype;
    }
    void ClearExpiredStatusEffects()
    {
        object statusEffects = StatusEffects;
        QList<StatusEffectInstance> expiredEffects;
        // lock (statusEffects) {
        expiredEffects = StatusEffects.Where((Person._ClosureS__.SI297_0 == NULL) ? (Person._ClosureS__.SI297_0 = new Func<StatusEffectInstance, bool>(Person._ClosureS__.SI._LambdaS__297_0)) : Person._ClosureS__.SI297_0).ToList<StatusEffectInstance>();
        // }
        // try {
        for (QList<StatusEffectInstance>::iterator it = expiredEffects.begin();
                it != expiredEffects.end(); ++it) {

            StatusEffectInstance se = *it;
            StatusEffect effect = Game::DictOfStatusEffects[se.Name];
            // try {
            for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
                    it2 != effect.Modifiers.end(); ++it2) {

                ModifierBase modi = *it2;
                if (modi is Modifier_ExpirationEvent)
                    VisualEventManager.GetEventByFilename(((Modifier_ExpirationEvent)modi).EventPath, VisualEventKind.NONE).Execute(this);
            }
            // }
        }
        // }
        object statusEffects2 = StatusEffects;
        // lock (statusEffects2) {
        // try {
        for (QList<StatusEffectInstance>::iterator it = expiredEffects.begin();
                it != expiredEffects.end(); ++it) {

            StatusEffectInstance se2 = *it;
            StatusEffects.Remove(se2);
        }
        // }
        // }
    }
    void ApplyStatusEffectBodyChanges()
    {
        object statusEffects = StatusEffects;
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
                it != StatusEffects.end(); ++it) {

            StatusEffectInstance se = *it;
            StatusEffect effect = Game::DictOfStatusEffects[se.Name];
            // try {
            for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
                    it2 != effect.Modifiers.end(); ++it2) {

                ModifierBase modi = *it2;
                if (modi is Modifier_BodySizeChange) {

                    Modifier_BodySizeChange change = (Modifier_BodySizeChange)modi;
                    ApplyBodySizeChange(change);
                }
            }
            // }
        }
        // }
        // }
    }
    void ApplyBodySizeChange(BodySizeChange& BSC)
    {
        double minValue = (BSC.Minimum < 1.0) ? 1.0 : Math.Min(10.0, BSC.Minimum);
        double maxValue = (BSC.Maximum == 0.0 || BSC.Maximum > 10.0) ? 10.0 : Math.Max(1.0, BSC.Maximum);
        switch (BSC.BodyPart)
        {
        case BodyPart.Anal:
            if (BSCWithinRange(BSC, intAnalSize))
            {
                intAnalSize += BSC.Change;
                if (intAnalSize < minValue)
                    intAnalSize = minValue;

                else if (intAnalSize > maxValue)
                    intAnalSize = maxValue;
            }
            break;
        case BodyPart.Breast:
            if ((gender == Gender::Female || gender == Gender::Futanari) && BSCWithinRange(BSC, intBreastSize))
            {
                intBreastSize += BSC.Change;
                minValue = ((BSC.Minimum < 0.0) ? 0.0 : Math.Min(10.0, BSC.Minimum));
                if (intBreastSize < minValue)
                    intBreastSize = minValue;

                else if (intBreastSize > maxValue)
                    intBreastSize = maxValue;
            }
            break;
        case BodyPart.Penis:
            if ((gender == Gender::Male || gender == Gender::Futanari) && BSCWithinRange(BSC, intPenisSize))
            {
                intPenisSize += BSC.Change;
                if (intPenisSize < minValue)
                    intPenisSize = minValue;

                else if (intPenisSize > maxValue)
                    intPenisSize = maxValue;
            }
            break;
        case BodyPart.Stomach:
            if ((gender == Gender::Male || gender == Gender::Futanari) && BSCWithinRange(BSC, intPenisSize))
            {
                intStomachSize += BSC.Change;
                minValue = ((BSC.Minimum < 0.0) ? 0.0 : Math.Min(10.0, BSC.Minimum));
                if (intStomachSize < minValue)
                    intStomachSize = minValue;

                else if (intStomachSize > maxValue)
                    intStomachSize = maxValue;

            }
            break;
        case BodyPart.Testicle:
            if ((gender == Gender::Male || gender == Gender::Futanari) && BSCWithinRange(BSC, intTesticleSize))
            {
                intTesticleSize += BSC.Change;
                if (intTesticleSize < minValue)
                    intTesticleSize = minValue;

                else if (intTesticleSize > maxValue)
                    intTesticleSize = maxValue;
            }
            break;
        case BodyPart.Vagina:
            if ((gender == Gender::Female || gender == Gender::Futanari) && BSCWithinRange(BSC, intVaginaSize))
            {
                intVaginaSize += BSC.Change;
                if (intVaginaSize < minValue)
                    intVaginaSize = minValue;

                else if (intVaginaSize > maxValue)
                    intVaginaSize = maxValue;
            }
            break;
        default:
            return;
        }
    }
    bool BSCWithinRange(BodySizeChange& BSC, double Value)
    {
        double Minimum = (BSC.Minimum < 1.0) ? 1.0 : Math.Min(10.0, BSC.Minimum);
        double Maximum = (BSC.Maximum == 0.0 || BSC.Maximum > 10.0) ? 10.0 : Math.Max(1.0, BSC.Maximum);
        if (BSC.BodyPart == BodyPart.Breast || BSC.BodyPart == BodyPart.Stomach)
        {
            Minimum = ((BSC.Minimum < 0.0) ? 0.0 : Math.Min(10.0, BSC.Minimum));
        }
        return Value <= Maximum && Value >= Minimum;
    }
    bool ShouldSerializeintHome()
    {
        return !intHome.isEmpty();
    }
    bool ShouldSerializeintBedroom()
    {
        return !intBedroom.isEmpty();
    }
    bool ShouldSerializeintWork()
    {
        return !intWork.isEmpty();
    }
    bool ShouldSerializeOutLateTonight()
    {
        return OutLateTonight;
    }
    bool ShouldSerializeOutLateLastNight()
    {
        return OutLateLastNight;
    }
    bool ShouldSerializeUpEarly()
    {
        return UpEarly;
    }
    bool IsWorkTime()
    {
        LocationJobDetails jb = JobDetails;
        if (jb != NULL && !Game::SchoolCalendar.IsHoliday)
        {
            if (Game::SchoolCalendar.IsWeekend) {
                if (jb.WeekendShift && Game::GameTime.IsWeekendWorkTime)
                    return true;
            }
            else if ((jb.SchoolShift && Game::GameTime.IsSchoolTime) || (jb.WeekdayShift && Game::GameTime.IsStandardWorkTime) || (jb.EveningShift && Game::GameTime.IsEveningWorkTime))
                return true;
        }
        return false;
    }
    bool IsAsleep()
    {
        return CurrentLocation == Bedroom && Game::GameTime.IsSleepTime;
    }
    bool IsWorking()
    {
        return (CurrentLocation == Work && IsWorkTime()) || ((Job == "Student" || Trait.contains("Staff")) && CurrentLocation.Region == Region.School);
    }
    void RandomizeSchedule()
    {
        OutLateLastNight = OutLateTonight;
        UpEarly = false;
        OutLateTonight = false;
        int randomNumber = Game::RNG.Next(100);
        if (Job == "Student")
        {
            if (randomNumber < 25)
            {
                OutLateTonight = true;
                return;
            }
            if (randomNumber < 35 && !OutLateLastNight)
            {
                UpEarly = true;
                return;
            }
        }
        else
        {
            if (randomNumber < 35)
            {
                OutLateTonight = true;
                return;
            }
            if (randomNumber < 65 && !OutLateLastNight)
            {
                UpEarly = true;
            }
        }
    }
    bool ShouldSerializeInventory()
    {
        return !Inventory.isEmpty;
    }
    bool ShouldSerializeTrait()
    {
        return !Trait.isEmpty();
    }
    void AddTrait(QString TraitName)
    {
        if (Trait.Length == 0) {
            Trait = TraitName;
            return;
        }
        if (!HasTrait(TraitName))
            Trait.append(TRAIT_SEPARATOR_CHAR).append(TraitName);
    }
    void RemoveTrait(QString TraitName)
    {
        Trait = Trait.split(TRAIT_SEPARATOR_CHAR).filter(TraitName).join(TRAIT_SEPARATOR_CHAR);
    }
    bool HasTrait(QString TraitName) const
    {
        return Trait.split(TRAIT_SEPARATOR_CHAR).contains(TraitName);
    }
    bool HasTraitFromList(QString TraitList) const
    {
        QStringList TraitListIn = TraitList.Split(TRAIT_SEPARATOR_CHAR);
        QStringList MyTraitList = Trait.Split(TRAIT_SEPARATOR_CHAR);
        for (QStringList::iterator it = TraitListIn.begin(); it != TraitListIn.end(); ++it)
            if (MyTraitList.contains(*it))
                return true;

        return false;
    }
    bool ShouldSerializeSkills()
    {
        return Skills.count() > 0;
    }
    bool HasSkill(QString skillName) const
    {
        return Skills.contains(skillName);
    }
    int GetSkill(QString skillName) const
    {
        CheckSkill(skillName);
        Skill arg_30_0 = Game::DictOfSkills[skillName];
        int retVal = Skills.contains(skillName) ? Skills[skillName] : 0;
        int minVal = arg_30_0.MinValue;
        int maxVal = arg_30_0.MaxValue;
        object statusEffects = StatusEffects;
        // checked {
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator se = StatusEffects.begin();
                se != StatusEffects.end(); ++se) {

            StatusEffect effect = Game::DictOfStatusEffects[se->Name];
            // try {
            for (QList<ModifierBase>::iterator modi = effect.Modifiers.begin();
                    modi != effect.Modifiers.end(); ++modi) {

                if (*modi is Modifier_AddSkillValue) {
                    Modifier_AddSkillValue addConstMod = (Modifier_AddSkillValue)*modi;
                    if (addConstMod.SkillName == skillName)
                        retVal += addConstMod.GetValue(*se);
                }
                else if (*modi is Modifier_MinSkillValue)
                {
                    Modifier_MinSkillValue minValMod = (Modifier_MinSkillValue)*modi;
                    if (minValMod.SkillName == skillName && minValMod.GetValue(*se) > minVal)
                        minVal = minValMod.GetValue(*se);
                }
                else if (*modi is Modifier_MaxSkillValue)
                {
                    Modifier_MaxSkillValue maxValMod = (Modifier_MaxSkillValue)*modi;
                    if (maxValMod.SkillName == skillName && maxValMod.GetValue(*se) < maxVal)
                        minVal = maxValMod.GetValue(*se);
                }
            }
            // }
        }
        // }
        // }
        return retVal < minVal ? minVal : (retVal > maxVal ? maxVal : retVal);
        // }
    }
    void SetSkill(QString skillName, int value)
    {
        CheckSkill(skillName);
        Skill baseSkill = Game::DictOfSkills[skillName];
        int oldValue = Skills.contains(skillName) ? Skills[skillName] : 0;
        int newValue = value < baseSkill.MinValue ? baseSkill.MinValue : (value > baseSkill.MaxValue ? baseSkill.MaxValue : value);
        Skills[skillName] = newValue;
        Game::NotifyManager.HandleSkillNotification(this, skillName, newValue - oldValue);
    }
    void AddSkill(QString skillName, int value)
    {
        CheckSkill(skillName);
        Skill baseSkill = Game::DictOfSkills[skillName];
        int oldValue = Skills.contains(skillName) ? Skills[skillName] : 0;
        int addValue = value;
        object statusEffects = StatusEffects;
        // checked {
        // lock (statusEffects) {
        // try {
        for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
                it != StatusEffects.end(); ++it) {

            StatusEffectInstance se = enumerator.Current;
            StatusEffect effect = Game::DictOfStatusEffects[se.Name];
            // try {
            for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
                    it2 != effect.Modifiers.end(); ++it2) {

                ModifierBase modi = enumerator2.Current;
                if (modi is Modifier_IncreaseSkillMultiplier) {
                    Modifier_IncreaseSkillMultiplier scaleMod = (Modifier_IncreaseSkillMultiplier)modi;
                    if (skillName == scaleMod.SkillName && value > 0)
                        addValue = (int)round((double)addValue * scaleMod.GetScaleFactor(this, se));

                } else if (modi is Modifier_DecreaseSkillMultiplier) {

                    Modifier_DecreaseSkillMultiplier scaleMod2 = (Modifier_DecreaseSkillMultiplier)modi;
                    if (skillName == scaleMod2.SkillName && value < 0)
                        addValue = (int)round((double)addValue * scaleMod2.GetScaleFactor(this, se));
                }
            }
            // }
        }
        // }
        // }
        int newValue = oldValue + addValue < baseSkill.MinValue ? baseSkill.MinValue : (oldValue + addValue > baseSkill.MaxValue ? baseSkill.MaxValue : oldValue + addValue);
        Skills[skillName] = newValue;
        Game::NotifyManager.HandleSkillNotification(this, skillName, newValue - oldValue);
        // }
    }
    void CheckSkill(QString skillName)
    {
        if (!Game::DictOfSkills.contains(skillName))
        {
            throw new ArgumentException(skillName.prepend("'") + "' was not declared as valid skill for the current scenario!"));
        }
    }
    bool ShouldSerializeAttachedEventIDs()
    {
        return AttachedEventIDs.count() > 0;
    }
    int CompareByLastname(Person& x, Person& y)
    {
        return QString::compare(x.Lastname + " " + x.DisplayForename, y.Lastname + " " + y.DisplayForename);
    }
    int CompareByFirstname(Person& x, Person& y)
    {
        return QString::compare(x.DisplayForename, y.DisplayForename);
    }
    int CompareForPublicArea(Person& x, Person& y)
    {
        int CompareForPublicArea;

        if (x.IsWorking() && !y.IsWorking())
            return -1;

        if (y.IsWorking() && !x.IsWorking())
            return 1;

        if (x.IsFavorite() && !y.IsFavorite())
            return -1;

        if (y.IsFavorite() && !x.IsFavorite())
            return 1;

        return QString::compare(x.DisplayName, y.DisplayName);
    }
    int CompareForSchoolRoom(Person& x, Person& y)
    {
        if (x.Job == "Teacher") {

            if (y.Job == "Teacher")
                return QString::compare(x.DisplayName, y.DisplayName);

            return -1;
        }
        if (y.Job == "Teacher")
            return 1;

        return CompareForPublicArea(x, y);
    }
};

#endif // PERSON_H
