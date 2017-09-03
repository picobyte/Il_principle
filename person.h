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
	const QString get_Name() const
	{
		if (Lastname.isNull() || Lastname.contains(QRegExp("^\\s*$")))
			return Forename;

		if (Forename.isNull() || Forename.contains(QRegExp("^\\s*$")))
			return Lastname;

		return Forename + " " + Lastname;
	}
	const QString get_DisplayForename() const
	{
		if (CustomForename.isNull() || CustomForename.contains(QRegExp("^\\s*$")))
			return Forename;

		return CustomForename;
	}
	const QString get_DisplayName() const
	{
		if (Lastname.isNull() || Lastname.contains(QRegExp("^\\s*$")))
			return DisplayForename;

		if (DisplayForename.isNull() || DisplayForename.contains(QRegExp("^\\s*$")))
			return Lastname;

		return DisplayForename + " " + Lastname;
	}
	const QString get_NameAndTitle() const
	{
		StringBuilder sb = new StringBuilder();
		sb.AppendFormat("{0} ({1})", DisplayName, Age);
		if (!QString.IsNullOrEmpty(Job))
			sb.append(", " + Job);

		if (HasTrait("PTA"))
			sb.append(", PTA");

		if (IsParent)
			sb.append(", Parent");

		return sb.ToString();
	}
	const int get_Age() const
	{
		// checked {
		int age = Game.SchoolCalendar.TodayDate.Year - Birthday.Year;

		if (DateTime.Compare(Birthday, Game.SchoolCalendar.TodayDate.AddYears(0 - age)) > 0)
			--age;

		return age;
		// }
	}
	const SexualPref get_SexualOrientation() const
	{
		double likesMale = GetGenderPreference(Gender.Male);
		double likesFemale = GetGenderPreference(Gender.Female);
		double likesFuta = GetGenderPreference(Gender.Futanari);
		double maleAttraction = likesMale + 0.3 * likesFuta;
		double femaleAttraction = likesFemale + 0.3 * likesFuta;

		if (likesMale < 25.0 && likesFemale < 25.0 && likesFuta < 25.0)
			return SexualPref.Asexual;

		switch (Gender)
		{
		case Gender.Male:
			if (Math.Abs(likesMale - likesFemale) < 10.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
				return SexualPref.Bisexual;
			if (maleAttraction > femaleAttraction)
				return SexualPref.Homosexual;
		case Gender.Female:
			if (Math.Abs(likesMale - likesFemale) < 10.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
				return SexualPref.Bisexual;
			if (femaleAttraction > maleAttraction)
				return SexualPref.Homosexual;
		case Gender.Futanari:
			if (Math.Abs(likesMale - likesFemale) < 15.0 || (maleAttraction > 80.0 && femaleAttraction > 80.0))
				return SexualPref.Bisexual;
			if (likesFuta > (likesMale + likesFemale) * 0.75)
				return SexualPref.Homosexual;
		default:
			return SexualPref.Asexual;
		}
		return SexualPref.Heterosexual;
	}
	const LocationJobDetails get_JobDetails() const
	{
		LocationJobDetails JobDetails;
		if (Work != NULL && (long)Work.AssociatedJobs.count() > (long)((ulong)intJobSlot))
			return Work.AssociatedJobs[checked((int)intJobSlot)];
		else
			return NULL;
	}
	const Person get_Father() const
	{
		Person Father;
		if (Game.DictOfPersonNames.ContainsKey(intFather))
			return Game.DictOfPersonNames[intFather];

		return NULL;
	}
	void set_Father(Person& v)
	{
		if (value == NULL)
		{
			intFather = "";
			return;
		}
		intFather = value.Name;
	}
	const Person get_Mother() const
	{
		Person Mother;
		if (Game.DictOfPersonNames.ContainsKey(intMother))
			return Game.DictOfPersonNames[intMother];

		return NULL;
	}
	void set_Mother(Person& v)
	{
		if (value == NULL)
		{
			intMother = "";
			return;
		}
		intMother = value.Name;
	}
	const Person get_Love() const
	{
		Person Love;
		if (QString.Equals(intLove, "Principal"))
			return Game.HeadTeacher;

		if (Game.DictOfPersonNames.ContainsKey(intLove))
			return Game.DictOfPersonNames[intLove];

		return NULL;
	}
	void set_Love(Person& v)
	{
		if (value == NULL)
		{
			intLove = "";
			return;
		}
		if (value == Game.HeadTeacher)
		{
			intLove = "Principal";
			return;
		}
		intLove = value.Name;
	}
	const bool get_IsCouple() const
	{
		return !QString.IsNullOrEmpty(intLove);
	}
	const bool get_IsParent() const
	{
		return Children.count() > 0;
	}
	const bool get_IsFavorite() const
	{
		return Game.FavoriteStudentList.contains(UID);
	}
	void set_IsFavorite(bool& v)
	{
		if (value) {
			if (!IsFavorite) {
				Game.FavoriteStudentList.Add(UID);
				return;
			}
		} else {
			Game.FavoriteStudentList.Remove(UID);
		}
	}
	const double get_ProposalSupport() const
	{
		double ProposalSupport;
		if (DictProposalSupport.ContainsKey(ProposalName))
			return DictProposalSupport[ProposalName];
		else
			return 0.0;
	}
	void set_ProposalSupport(double& v)
	{
		if (value == 0.0) {
			if (DictProposalSupport.ContainsKey(ProposalName)) {
				DictProposalSupport.Remove(ProposalName);
				return;
			}
		} else {
			DictProposalSupport[ProposalName] = value;
		}
	}
	const Clubs get_Club() const
	{
		return Game.GetClub(ClubMember);
	}
	void set_Club(Clubs& v)
	{
		if (value == NULL) {
			ClubMember = "";
			return;
		}
		ClubMember = value.Name;
	}
	const BodySize get_BreastSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intBreastSize < 0.0 ? 0.0 : (intBreastSize > 10.0 ? 10.0 : intBreastSize), 0)));
	}
	void set_BreastSize(BodySize& v)
	{
		if (Gender == Gender.Male) {
			intBreastSize = 0.0;
			return;
		}
		intBreastSize = (double)UtilityClass.Clamp((int)value, 0, 10);
	}
	const BodySize get_StomachSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intStomachSize < 0.0 ? 0.0 : (intStomachSize > 10.0 ? 10.0 : intStomachSize), 0)));
	}
	void set_StomachSize(BodySize& v)
	{
		if (Gender == Gender.Male) {
			intStomachSize = 0.0;
			return;
		}
		intStomachSize = (double)UtilityClass.Clamp((int)value, 0, 10);
	}
	const BodySize get_PenisSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intPenisSize < 0.0 ? 0.0 : (intPenisSize > 10.0 ? 10.0 : intPenisSize), 0)));
	}
	void set_PenisSize(BodySize& v)
	{
		if (Gender == Gender.Female) {
			intPenisSize = 0.0;
			return;
		}
		intPenisSize = (double)UtilityClass.Clamp((int)value, 1, 10);
	}
	const BodySize get_TesticleSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intTesticleSize < 0.0 ? 0.0 : (intTesticleSize > 10.0 ? 10.0 : intTesticleSize), 0)));
	}
	void set_TesticleSize(BodySize& v)
	{
		if (Gender == Gender.Female) {
			intTesticleSize = 0.0;
			return;
		}
		intTesticleSize = (double)UtilityClass.Clamp((int)value, 1, 10);
	}
	const BodySize get_VaginaSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intVaginaSize < 0.0 ? 0.0 : (intVaginaSize > 10.0 ? 10.0 : intVaginaSize), 0)));
	}
	void set_VaginaSize(BodySize& v)
	{
		if (Gender == Gender.Male) {
			intVaginaSize = 0.0;
			return;
		}
		intVaginaSize = (double)UtilityClass.Clamp((int)value, 1, 10);
	}
	const BodySize get_AnalSize() const
	{
		return checked((BodySize)Math.Round(Math.Round(intAnalSize < 0.0 ? 0.0 : (intAnalSize > 10.0 ? 10.0 : intAnalSize), 0)));
	}
	void set_AnalSize(BodySize& v)
	{
		intAnalSize = (double)UtilityClass.Clamp((int)value, 1, 10);
	}
	const Location get_CurrentLocation() const
	{
		Location CurrentLocation;
		if (QString.IsNullOrEmpty(intLoc))
			return NULL;

		return Game.GetLocation(intLoc);
	}
	void set_CurrentLocation(Location& v)
	{
		if (Operators.CompareString(intLoc, intOldLoc, false) != 0)
			intOldLoc = intLoc;

		if (value == NULL) {
			if (!QString.IsNullOrEmpty(intLoc)) {
				Game.GetLocation(intLoc).OccupantLeave(this);
				intLoc = "";
				return;
			}
		} else {
			if (!QString.IsNullOrEmpty(intLoc))
				Game.GetLocation(intLoc).OccupantLeave(this);

			intLoc = value.Name;
			Game.GetLocation(intLoc).OccupantEnter(this);
		}
	}
	const Location get_OldLocation() const
	{
		if (!QString.IsNullOrEmpty(intOldLoc))
			return Game.GetLocation(intOldLoc);

		return NULL;
	}
	void set_OldLocation(Location& v)
	{
		intOldLoc = ((value == NULL) ? "" : value.Name);
	}
	const Location get_Home() const
	{
		Location Home;
		if (QString.IsNullOrEmpty(intHome))
			return Game.GetLocation("General Home");
		else
			return Game.GetLocation(intHome);
	}
	void set_Home(Location& v)
	{
		if (value == NULL) {
			intHome = "";
			return;
		}
		intHome = value.Name;
	}
	const Location get_Bedroom() const
	{
		Location Bedroom;
		if (QString.IsNullOrEmpty(intBedroom))
			return Game.GetLocation("General Home");

		return Game.GetLocation(intBedroom);
	}
	void set_Bedroom(Location& v)
	{
		if (value == NULL) {
			intBedroom = "";
			return;
		}
		intBedroom = value.Name;
	}
	const bool get_IsHome() const
	{
		return CurrentLocation == Home || CurrentLocation == Bedroom;
	}
	const Location get_Work() const
	{
		Location Work;
		if (QString.IsNullOrEmpty(intWork))
			return NULL;

		return Game.GetLocation(intWork);
	}
	void set_Work(Location& v)
	{
		if (value == NULL) {
			intWork = "";
			return;
		}
		intWork = value.Name;
	}
	const QString get_InventoryName() const
	{
		return DisplayName;
	}
	Person(QJsonObject *d = NULL)
	{
		if (d) init(d);
		Forename = "";
		Lastname = "";
		CustomForename = "";
		SpecialPerson = false;
		TextColor = "";
		GenderPreferences = new SerializableAttributeDictionary<Gender, double>();
		Fetish = new QList<Fetish>();
		Virgin = true;
		AnalVirgin = true;
		Job = "";
		Children = new QList<QString>();
		intFather = "";
		intMother = "";
		intLove = "";
		Subject = "";
		GoodInSubject = "";
		SubjectFamilyExp = new SerializableAttributeDictionary<SchoolSubjectFamily, double>();
		SubjectInstanceExp = new SerializableAttributeDictionary<QString, double>();
		subjectStatLock = RuntimeHelpers.GetObjectValue(new object());
		DictProposalSupport = new SerializableStringToDoubleDict();
		ClubMember = "";
		ImageLocation = "";
		PaperDollEventFileName = "PD_Default";
		MaleHeadFileName = "";
		FemaleHeadFileName = "";
		BodyFileName = "";
		StomachFileName = "";
		BreastFileName = "";
		PenisFileName = "";
		TesticleFileName = "";
		CurrentOutfit = OutfitType.DefaultOutfit;
		OutfitName = "";
		dictStats = new SerializableAttributeDictionary<QString, double>();
		StatusEffects = new QList<StatusEffectInstance>();
		intAnalSize = 1.0;
		intLoc = "";
		intOldLoc = "";
		intHome = "";
		intBedroom = "";
		intWork = "";
		Inventory = new InventoryCollection();
		Trait = "";
		Skills = new SerializableAttributeDictionary<QString, int>();
		AttachedEventIDs = new QList<unsigned>();
		// try {
		for (QHash<QString, Stat>::iterator it = Game.DictOfStats.Keys.begin();
				it != Game.DictOfStats.Keys.end(); ++it) {
			QString stat = enumerator.Current;
			SetStat(stat, 0.0);
		}
		// }
		if (!Game.GameLoading)
			UIDManager.AssignUID(this);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_OBJ_FROM_JSON_AS(it, UID)
			else __IF_VAR_FROM_JSON_AS(it, Forename, toString)
			else __IF_VAR_FROM_JSON_AS(it, Lastname, toString)
			else __IF_VAR_FROM_JSON_AS(it, CustomForename, toString)
			else __IF_ENUM_FROM_JSON_AS(it, Gender, Gender)
			else __IF_OBJ_FROM_JSON_AS(it, Birthday)
			else __IF_VAR_FROM_JSON_AS(it, SpecialPerson, toBool)
			else __IF_VAR_FROM_JSON_AS(it, TextColor, toString)
			else __IF_VAR_FROM_JSON_AS(it, InitParams, toString)
			//SerializableAttributeDictionary<Gender, double> GenderPreferences
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
			//SerializableAttributeDictionary<SchoolSubjectFamily, double> SubjectFamilyExp
			//SerializableAttributeDictionary<QString, double> SubjectInstanceExp
			else __IF_OBJ_FROM_JSON_AS(it, subjectStatLock)
			else __IF_OBJ_FROM_JSON_AS(it, DictProposalSupport)
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
			//SerializableAttributeDictionary<QString, double> dictStats
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
			else __IF_OBJ_FROM_JSON_AS(it, Inventory)
			//char TRAIT_SEPARATOR_CHAR = ','
			else __IF_VAR_FROM_JSON_AS(it, Trait, toString)
			//SerializableAttributeDictionary<QString, int> Skills
			else __IF_LIST_FROM_JSON_TYPED(it, AttachedEventIDs, toInt)
			else __IF_VAR_FROM_JSON_AS(it, ProposalName, toString)
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
		DateTime today = Game.SchoolCalendar.TodayDate;
		return (Birthday.Day == today.Day && Birthday.Month == today.Month) || (DateTime.IsLeapYear(Birthday.Year) && !DateTime.IsLeapYear(today.Year) && Birthday.Month == 2 && Birthday.Day == 29 && today.Month == 3 && today.Day == 1);
	}
	QString ToString()
	{
		return "Person: " + Name;
	}
	double GetGenderPreference(Gender genderName)
	{
		double retVal = GenderPreferences.ContainsKey(genderName) ? GenderPreferences[genderName] : 0.0;
		double minVal = 0.0;
		double maxVal = 100.0;
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it) {

			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2) {

				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_AddGenderPrefValue) {

					Modifier_AddGenderPrefValue addConstMod = (Modifier_AddGenderPrefValue)modi;
					if (addConstMod.Gender == genderName)
						retVal += addConstMod.GetValue(this, se);

				} else if (modi is Modifier_MinGenderPrefValue) {

					Modifier_MinGenderPrefValue minValMod = (Modifier_MinGenderPrefValue)modi;
					if (minValMod.Gender == genderName && minValMod.GetValue(this, se) > minVal)
						minVal = minValMod.GetValue(this, se);

				} else if (modi is Modifier_MaxGenderPrefValue) {

					Modifier_MaxGenderPrefValue maxValMod = (Modifier_MaxGenderPrefValue)modi;
					if (maxValMod.Gender == genderName && maxValMod.GetValue(this, se) < maxVal)
						minVal = maxValMod.GetValue(this, se);
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
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_IncreaseGenderPrefMultiplier)
				{
					Modifier_IncreaseGenderPrefMultiplier scaleMod = (Modifier_IncreaseGenderPrefMultiplier)modi;
					if (genderName == scaleMod.Gender && value > 0.0)
					{
						addValue *= scaleMod.GetScaleFactor(this, se);
					}
				}
				else if (modi is Modifier_DecreaseGenderPrefMultiplier)
				{
					Modifier_DecreaseGenderPrefMultiplier scaleMod2 = (Modifier_DecreaseGenderPrefMultiplier)modi;
					if (genderName == scaleMod2.Gender && value < 0.0)
					{
						addValue *= scaleMod2.GetScaleFactor(this, se);
					}
				}
			}
			// }
		}
		// }
		// }
		GenderPreferences[genderName] = UtilityClass.Clamp((GenderPreferences.ContainsKey(genderName) ? GenderPreferences[genderName] : 0.0) + addValue, 0.0, 100.0);
	}
	bool LikesGender(Gender Gend)
	{
		return GetGenderPreference(Gend) >= 50.0;
	}
	bool LikesPenis()
	{
		double likesMale = GetGenderPreference(Gender.Male);
		bool LikesPenis;
		if (likesMale > 50.0)
		{
			LikesPenis = true;
		}
		else
		{
			double likesFuta = GetGenderPreference(Gender.Futanari);
			LikesPenis = (likesFuta > 65.0 || likesMale + likesFuta > 80.0);
		}
		return LikesPenis;
	}
	bool LikesVagina()
	{
		double likesFemale = GetGenderPreference(Gender.Female);
		bool LikesVagina;
		if (likesFemale > 50.0)
		{
			LikesVagina = true;
		}
		else
		{
			double likesFuta = GetGenderPreference(Gender.Futanari);
			LikesVagina = (likesFuta > 65.0 || likesFemale + likesFuta > 80.0);
		}
		return LikesVagina;
	}
	bool LikesBreast()
	{
		double likesFemale = GetGenderPreference(Gender.Female);
		bool LikesBreast;
		if (likesFemale > 50.0)
		{
			LikesBreast = true;
		}
		else
		{
			double likesFuta = GetGenderPreference(Gender.Futanari);
			LikesBreast = (likesFuta > 50.0 || likesFemale + likesFuta > 70.0);
		}
		return LikesBreast;
	}
	bool HasPenis()
	{
		return Gender == Gender.Male || Gender == Gender.Futanari;
	}
	bool HasVagina()
	{
		return Gender == Gender.Female || Gender == Gender.Futanari;
	}
	bool HasBreasts()
	{
		return Gender == Gender.Female || Gender == Gender.Futanari;
	}
	bool ShouldSerializeFetish()
	{
		return Fetish.count() > 0;
	}
	void AddFetish(Fetish F)
	{
		if (!Fetish.contains(F) && F != hhs_.Fetish.None)
		{
			Fetish.Add(F);
		}
	}
	bool HasFetish(Fetish F)
	{
		return Fetish.contains(F);
	}
	bool ShouldSerializeVirgin()
	{
		return !Virgin;
	}
	bool ShouldSerializeAnalVirgin()
	{
		return !AnalVirgin;
	}
	bool ShouldSerializeJob()
	{
		return !QString.IsNullOrEmpty(Job);
	}
	bool ShouldSerializeintJobSlot()
	{
		return !QString.IsNullOrEmpty(intWork);
	}
	bool ShouldSerializeSalary()
	{
		QString job = Job;
		return Operators.CompareString(job, "Teacher", false) == 0 || Operators.CompareString(job, "School Secretary", false) == 0 || Operators.CompareString(job, "Librarian", false) == 0 || Operators.CompareString(job, "School Doctor", false) == 0;
	}
	void AssignWork(Location Room, LocationJobDetails jb)
	{
		UnassignWork();
		object obj = Person.jobLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (Room != NULL && Room.AssociatedJobs.contains(jb) && jb.CanEmploy(this))
		{
			jb.Staff.Add(Name);
			Work = Room;
			intJobSlot = checked((unsigned)Room.AssociatedJobs.IndexOf(jb));
			if (QString.IsNullOrEmpty(Job))
			{
				Job = jb.JobTitle;
			}
			object obj2 = Person.unemployedListLock;
			ObjectFlowControl.CheckForSyncLockOnValueType(obj2);
			// lock (obj2) {
			Game.UnemployedPersons.Remove(Name);
			// }
		}
		// }
	}
	void UnassignWork()
	{
		object obj = Person.jobLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		LocationJobDetails jb = JobDetails;
		if (jb != NULL)
			jb.Staff.Remove(Name);

		Work = NULL;
		intJobSlot = 0u;
		if (!QString.Equals(Job, "Teacher") && !QString.Equals(Job, "Student") && !Trait.contains("Staff"))
		{
			object obj2 = Person.unemployedListLock;
			ObjectFlowControl.CheckForSyncLockOnValueType(obj2);
			// lock (obj2) {
			if (Game.UnemployedPersons.ContainsKey(Name))
				Game.UnemployedPersons[Name] = this;
			else
				Game.UnemployedPersons.Add(Name, this);
			// }
		}
		// }
	}
	bool ShouldSerializeChildren()
	{
		return Children.count() > 0;
	}
	bool ShouldSerializeintFather()
	{
		return !QString.IsNullOrEmpty(intFather);
	}
	bool ShouldSerializeintMother()
	{
		return !QString.IsNullOrEmpty(intMother);
	}
	bool ShouldSerializeintLove()
	{
		return !QString.IsNullOrEmpty(intLove);
	}
	bool ShouldSerializeAutoenroll()
	{
		return Autoenroll;
	}
	bool ShouldSerializeSchoolclass()
	{
		return Schoolclass != 0 && Job.Equals("Student");
	}
	void ResetSchoolclass()
	{
		Schoolclass = 0;
	}
	bool ShouldSerializeSubject()
	{
		return !QString.IsNullOrEmpty(Subject) && (Job.Equals("Student") || Job.Equals("Teacher"));
	}
	void ResetSubject()
	{
		Subject = "";
	}
	bool ShouldSerializeGoodInSubject()
	{
		return !QString.IsNullOrEmpty(GoodInSubject) && (Job.Equals("Student") || Job.Equals("Teacher"));
	}
	void ResetGoodInSubject()
	{
		GoodInSubject = "";
	}
	bool ShouldSerializeTeacherSubjects()
	{
		return Job.Equals("Teacher");
	}
	void ResetTeacherSubjects()
	{
		TeacherSubjects = new QList<QString>();
	}
	double GetSubjectExp(QString SubjectInstanceName)
	{
		// object obj = subjectStatLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		SchoolSubject s = Game.GetSubject(SubjectInstanceName);
		if (s != NULL)
			return s.GetSubjectExp(this);

		return 0.0;
		// }
	}
	void AddSubjectExp(QString SubjectInstanceName, double Value)
	{
		// object obj = subjectStatLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		SchoolSubject s = Game.GetSubject(SubjectInstanceName);
		if (s != NULL)
			s.AddSubjectExp(this, Value);
		// }
	}
	double GetSubjectFamilyExp(SchoolSubjectFamily SubjectFamily)
	{
		// object obj = subjectStatLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		double GetSubjectFamilyExp;
		// lock (obj) {
		double retVal = SubjectFamilyExp.ContainsKey(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0;
		double minVal = 0.0;
		double maxVal = 100.0;
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_AddSubjectFamilyValue)
				{
					Modifier_AddSubjectFamilyValue addConstMod = (Modifier_AddSubjectFamilyValue)modi;
					if (addConstMod.SubjectFamilyName == SubjectFamily)
						retVal += addConstMod.GetValue(this, se);
				}
				else if (modi is Modifier_MinSubjectFamilyValue)
				{
					Modifier_MinSubjectFamilyValue minValMod = (Modifier_MinSubjectFamilyValue)modi;
					if (minValMod.SubjectFamilyName == SubjectFamily && minValMod.GetValue(this, se) > minVal)
						minVal = minValMod.GetValue(this, se);
				}
				else if (modi is Modifier_MaxSubjectFamilyValue)
				{
					Modifier_MaxSubjectFamilyValue maxValMod = (Modifier_MaxSubjectFamilyValue)modi;
					if (maxValMod.SubjectFamilyName == SubjectFamily && maxValMod.GetValue(this, se) < maxVal)
						minVal = maxValMod.GetValue(this, se);
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
		//// object obj = subjectStatLock;
		//// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (SubjectInstanceExp.ContainsKey(SubjectInstanceName))
			return SubjectInstanceExp[SubjectInstanceName];

		return 0.0;
		// }
	}
	void SetSubjectFamilyExp(SchoolSubjectFamily SubjectFamily, double Value)
	{
		//// object obj = subjectStatLock;
		//// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		Value = Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value);
		if (SubjectFamilyExp.ContainsKey(SubjectFamily))
			SubjectFamilyExp[SubjectFamily] = Value;
		else
			SubjectFamilyExp.Add(SubjectFamily, Value);
		// }
	}
	void SetSubjectInstanceExp(QString SubjectInstanceName, double Value)
	{
		//// object obj = subjectStatLock;
		//// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		Value = Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value);
		if (SubjectInstanceExp.ContainsKey(SubjectInstanceName))
			SubjectInstanceExp[SubjectInstanceName] = Value;
		else
			SubjectInstanceExp.Add(SubjectInstanceName, Value);
		// }
	}
	void AddSubjectFamilyExp(SchoolSubjectFamily SubjectFamily, double Value)
	{
		//// object obj = subjectStatLock;
		//// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		double addValue = Value;
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_IncreaseSubjectFamilyMultiplier)
				{
					Modifier_IncreaseSubjectFamilyMultiplier scaleMod = (Modifier_IncreaseSubjectFamilyMultiplier)modi;
					if (SubjectFamily == scaleMod.SubjectFamilyName && Value > 0.0)
						addValue *= scaleMod.GetScaleFactor(this, se);
				}
				else if (modi is Modifier_DecreaseSubjectFamilyMultiplier)
				{
					Modifier_DecreaseSubjectFamilyMultiplier scaleMod2 = (Modifier_DecreaseSubjectFamilyMultiplier)modi;
					if (SubjectFamily == scaleMod2.SubjectFamilyName && Value < 0.0)
						addValue *= scaleMod2.GetScaleFactor(this, se);
				}
			}
			// }
		}
		// }
		// }
		SubjectFamilyExp[SubjectFamily] = UtilityClass.Clamp((SubjectFamilyExp.ContainsKey(SubjectFamily) ? SubjectFamilyExp[SubjectFamily] : 0.0) + addValue, 0.0, 100.0);
		// }
	}
	void AddSubjectInstanceExp(QString SubjectInstanceName, double Value)
	{
		// object obj = subjectStatLock;
		// ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		// lock (obj) {
		if (SubjectInstanceExp.ContainsKey(SubjectInstanceName))
			SubjectInstanceExp[SubjectInstanceName] = SubjectInstanceExp[SubjectInstanceName] + Value < 0.0 ? 0.0 : (SubjectInstanceExp[SubjectInstanceName] + Value > 100.0 ? 100.0 : SubjectInstanceExp[SubjectInstanceName] + Value);
		else
			SubjectInstanceExp.Add(SubjectInstanceName, Value < 0.0 ? 0.0 : (Value > 100.0 ? 100.0 : Value));
		// }
	}
	bool ShouldSerializeProposalSupport()
	{
		return (Job.Equals("Teacher") || HasTrait("PTA")) && DictProposalSupport.count() > 0;
	}
	bool ShouldSerializeHasDetention()
	{
		return HasDetention;
	}
	bool ShouldSerializeIsRogue()
	{
		return IsRogue && Job.Equals("Student");
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
		return (Name.Equals(Game.HeadTeacher.Name) || SpecialPerson) && !QString.IsNullOrEmpty(ImageLocation);
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
	void UpdatePaperDollImage(OutfitType Outfit = OutfitType.DefaultOutfit)
	{
		if (CurrentLocation == NULL || Outfit != OutfitType.DefaultOutfit)
			CurrentOutfit = Outfit;

		else if (!QString.IsNullOrEmpty(OutfitName))
			CurrentOutfit = OutfitType.ClothingItem;

		else if (Club != NULL && Game.GameTime.IsTimeForClub(Club) && CurrentLocation.Name.Equals(Club.ClubRoom))
			CurrentOutfit = OutfitType.Club;

		else if (CurrentLocation.GetActualSpecialOutfit() != OutfitType.DefaultOutfit)
			CurrentOutfit = CurrentLocation.GetActualSpecialOutfit();

		else if (IsAsleep())
			CurrentOutfit = OutfitType.Sleep;

		else if (IsWorking())
			CurrentOutfit = OutfitType.Work;
		else
			CurrentOutfit = OutfitType.DefaultOutfit;

		VisualEvent pdev = VisualEventManager.GetEventByFilename(PaperDollEventFileName, VisualEventKind.PaperDollHandler);
		if (pdev != NULL)
			pdev.Execute(this);
	}
	void UpdateOutfitLevel()
	{
		VisualEventManager.ExecuteNativeEvent("UpdateOutfitLevel", this);
	}
	double GetStat(QString statName)
	{
		Stat arg_31_0 = Game.DictOfStats[statName];
		double retVal = dictStats.ContainsKey(statName) ? dictStats[statName] : 0.0;
		double minVal = arg_31_0.MinValue;
		double maxVal = arg_31_0.MaxValue;
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_AddStatValue)
				{
					Modifier_AddStatValue addConstMod = (Modifier_AddStatValue)modi;
					if (Operators.CompareString(addConstMod.StatName, statName, false) == 0)
						retVal += addConstMod.GetValue(this, se);
				}
				else if (modi is Modifier_MinStatValue)
				{
					Modifier_MinStatValue minValMod = (Modifier_MinStatValue)modi;
					if (Operators.CompareString(minValMod.StatName, statName, false) == 0 && minValMod.GetValue(this, se) > minVal)
						minVal = minValMod.GetValue(this, se);
				}
				else if (modi is Modifier_MaxStatValue)
				{
					Modifier_MaxStatValue maxValMod = (Modifier_MaxStatValue)modi;
					if (Operators.CompareString(maxValMod.StatName, statName, false) == 0 && maxValMod.GetValue(this, se) < maxVal)
						minVal = maxValMod.GetValue(this, se);
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
		if (Game.DictOfStats.ContainsKey(statName))
		{
			Stat statBase = Game.DictOfStats[statName];
			dictStats[statName] = value < statBase.MinValue ? statBase.MinValue : (value > statBase.MaxValue ? statBase.MaxValue : value);
		}
	}
	void AddStat(QString statName, double value)
	{
		if (Game.DictOfStats.ContainsKey(statName))
		{
			Stat statBase = Game.DictOfStats[statName];
			double addValue = value;
			object statusEffects = StatusEffects;
			// lock (statusEffects) {
			// try {
			for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
					it != StatusEffects.end(); ++it)
			{
				StatusEffectInstance se = enumerator.Current;
				StatusEffect effect = Game.DictOfStatusEffects[se.Name];
				// try {
				for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
						it2 != effect.Modifiers.end(); ++it2)
				{
					ModifierBase modi = enumerator2.Current;
					if (modi is Modifier_IncreaseStatMultiplier)
					{
						Modifier_IncreaseStatMultiplier scaleMod = (Modifier_IncreaseStatMultiplier)modi;
						if (Operators.CompareString(statName, scaleMod.StatName, false) == 0 && value > 0.0)
							addValue *= scaleMod.GetScaleFactor(this, se);
					}
					else if (modi is Modifier_DecreaseStatMultiplier)
					{
						Modifier_DecreaseStatMultiplier scaleMod2 = (Modifier_DecreaseStatMultiplier)modi;
						if (Operators.CompareString(statName, scaleMod2.StatName, false) == 0 && value < 0.0)
							addValue *= scaleMod2.GetScaleFactor(this, se);
					}
				}
				// }
			}
			// }
			// }
			dictStats[statName] = UtilityClass.Clamp((dictStats.ContainsKey(statName) ? dictStats[statName] : 0.0) + addValue, statBase.MinValue, statBase.MaxValue);
		}
	}
	void AdjustStatsByMind()
	{
		int popTagIndex = Game.ScenarioConfig.PopulationTag.IndexOf(Job);
		Mind GameMind;
		if (popTagIndex >= 0)
			GameMind = Game.ScenarioConfig.MindData[popTagIndex];
		else
			GameMind = Game.ScenarioConfig.MindData[0];

		// try {
		QList<QString> MindStats = GameMind.GetStats();
		MindStats.Remove("Arousal");
		MindStats.Remove("Authority");
		MindStats.Remove("Inhibition");
		// try {
		for (QList<QString>::iterator it = MindStats.begin();
				it != MindStats.end(); ++it)
		{
			QString Stat = enumerator.Current;
			AdjustStat(GameMind, Stat);
		}
		// }
		if (GetStat("Arousal") < GetStat("Lust"))
		{
			AddStat("Arousal", 0.05 * (GetStat("Lust") - GetStat("Arousal")));
		}
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
	void AdjustStat(Mind Mind, QString SE)
	{
		Adjustment adj = Mind.AdjustmentByStat(SE);
		if (adj != NULL)
		{
			double stat = GetStat(SE);
			if (stat < adj.Range.Min)
			{
				if (adj.lowMagnitude > 0.0)
				{
					double dif = adj.Range.Min - stat;
					AddStat(SE, dif * (adj.lowMagnitude * 0.0004));
				}
			}
			else if (stat > adj.Range.Max && adj.highMagnitude > 0.0)
			{
				double dif2 = stat - adj.Range.Max;
				AddStat(SE, -dif2 * (adj.highMagnitude * 0.0004));
			}
			ApplyFuzziness(SE);
		}
	}
	void ApplyFuzziness(QString SE)
	{
		AddStat(SE, (Game.RNG.NextDouble() - 0.5) * 0.3);
	}
	void RandomizeArousalAndEnergy()
	{
		if (this != Game.HeadTeacher)
		{
			AddStat("Arousal", (double)Game.RNG.Next(-20, 20));
			AddStat("Energy", (double)checked(Game.RNG.Next((int)Math.Round(unchecked(Math.Truncate(GetStat("Stamina")) * 2.0)), (int)Math.Round(Game.DictOfStats["Energy"].MaxValue))));
		}
	}
	void AddStatusEffect(QString effectName)
	{
		StatusEffect effect = Game.DictOfStatusEffects[effectName];
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		switch (effect.AccumulationType)
		{
		case StatusEffectAccumulationType.None:
			if (!StatusEffects.Exists((StatusEffectInstance se) => Operators.CompareString(se.Name, effect.Name, false) == 0))
				StatusEffects.Add(effect.GetInstance());
			break;
		case StatusEffectAccumulationType.Refresh:
			StatusEffects.RemoveAll((StatusEffectInstance se) => Operators.CompareString(se.Name, effect.Name, false) == 0);
			StatusEffects.Add(effect.GetInstance());
			break;
		case StatusEffectAccumulationType.Stack:
			StatusEffects.Add(effect.GetInstance());
			break;
		}
		// }
	}
	void RemoveStatusEffect(QString effectName)
	{
		object statusEffects = StatusEffects;
		// lock (statusEffects) {
		StatusEffects.RemoveAll((StatusEffectInstance se) => Operators.CompareString(se.Name, effectName, false) == 0);
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
			if (se.Name.StartsWith("Personality"))
				personality = Game.DictOfStatusEffects[se.Name].DisplayName;

			else if (se.Name.StartsWith("Archetype"))
				archetype = Game.DictOfStatusEffects[se.Name].DisplayName;
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
				it != expiredEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
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
				it != expiredEffects.end(); ++it)
		{
			StatusEffectInstance se2 = enumerator3.Current;
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
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_BodySizeChange)
				{
					Modifier_BodySizeChange change = (Modifier_BodySizeChange)modi;
					ApplyBodySizeChange(change);
				}
			}
			// }
		}
		// }
		// }
	}
	void ApplyBodySizeChange(IBodySizeChange BSC)
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
				{
					intAnalSize = minValue;
					return;
				}
				if (intAnalSize > maxValue)
				{
					intAnalSize = maxValue;
					return;
				}
			}
			break;
		case BodyPart.Breast:
			if (new Gender[]
			{
				Gender.Female,
				Gender.Futanari
			}.contains(Gender) && BSCWithinRange(BSC, intBreastSize))
			{
				intBreastSize += BSC.Change;
				minValue = ((BSC.Minimum < 0.0) ? 0.0 : Math.Min(10.0, BSC.Minimum));
				if (intBreastSize < minValue)
				{
					intBreastSize = minValue;
					return;
				}
				if (intBreastSize > maxValue)
				{
					intBreastSize = maxValue;
					return;
				}
			}
			break;
		case BodyPart.Penis:
			if (new Gender[]
			{
				Gender.Male,
				Gender.Futanari
			}.contains(Gender) && BSCWithinRange(BSC, intPenisSize))
			{
				intPenisSize += BSC.Change;
				if (intPenisSize < minValue)
				{
					intPenisSize = minValue;
					return;
				}
				if (intPenisSize > maxValue)
				{
					intPenisSize = maxValue;
					return;
				}
			}
			break;
		case BodyPart.Stomach:
			if (new Gender[]
			{
				Gender.Male,
				Gender.Futanari
			}.contains(Gender) && BSCWithinRange(BSC, intPenisSize))
			{
				intStomachSize += BSC.Change;
				minValue = ((BSC.Minimum < 0.0) ? 0.0 : Math.Min(10.0, BSC.Minimum));
				if (intStomachSize < minValue)
				{
					intStomachSize = minValue;
					return;
				}
				if (intStomachSize > maxValue)
				{
					intStomachSize = maxValue;
					return;
				}
			}
			break;
		case BodyPart.Testicle:
			if (new Gender[]
			{
				Gender.Male,
				Gender.Futanari
			}.contains(Gender) && BSCWithinRange(BSC, intTesticleSize))
			{
				intTesticleSize += BSC.Change;
				if (intTesticleSize < minValue)
				{
					intTesticleSize = minValue;
					return;
				}
				if (intTesticleSize > maxValue)
				{
					intTesticleSize = maxValue;
					return;
				}
			}
			break;
		case BodyPart.Vagina:
			if (new Gender[]
			{
				Gender.Female,
				Gender.Futanari
			}.contains(Gender) && BSCWithinRange(BSC, intVaginaSize))
			{
				intVaginaSize += BSC.Change;
				if (intVaginaSize < minValue)
				{
					intVaginaSize = minValue;
					return;
				}
				if (intVaginaSize > maxValue)
				{
					intVaginaSize = maxValue;
				}
			}
			break;
		default:
			return;
		}
	}
	bool BSCWithinRange(IBodySizeChange BSC, double Value)
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
		return !QString.IsNullOrEmpty(intHome);
	}
	bool ShouldSerializeintBedroom()
	{
		return !QString.IsNullOrEmpty(intBedroom);
	}
	bool ShouldSerializeintWork()
	{
		return !QString.IsNullOrEmpty(intWork);
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
		bool IsWorkTime;
		if (jb != NULL && !Game.SchoolCalendar.IsHoliday)
		{
			if (Game.SchoolCalendar.IsWeekend)
			{
				if (jb.WeekendShift && Game.GameTime.IsWeekendWorkTime)
				{
					IsWorkTime = true;
					return IsWorkTime;
				}
			}
			else if ((jb.SchoolShift && Game.GameTime.IsSchoolTime) || (jb.WeekdayShift && Game.GameTime.IsStandardWorkTime) || (jb.EveningShift && Game.GameTime.IsEveningWorkTime))
			{
				IsWorkTime = true;
				return IsWorkTime;
			}
		}
		IsWorkTime = false;
		return IsWorkTime;
	}
	bool IsAsleep()
	{
		return CurrentLocation == Bedroom && Game.GameTime.IsSleepTime;
	}
	bool IsWorking()
	{
		return (CurrentLocation == Work && IsWorkTime()) || ((Job.Equals("Student") || Trait.contains("Staff")) && CurrentLocation.Region == Region.School);
	}
	void RandomizeSchedule()
	{
		OutLateLastNight = OutLateTonight;
		UpEarly = false;
		OutLateTonight = false;
		int randomNumber = Game.RNG.Next(100);
		if (Job.Equals("Student"))
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
		return !Inventory.IsEmpty;
	}
	Task CheckAndUseInventoryItems()
	{
		Person.VB_StateMachine_409_CheckAndUseInventoryItems vB_StateMachine_409_CheckAndUseInventoryItems = default(Person.VB_StateMachine_409_CheckAndUseInventoryItems);
		vB_StateMachine_409_CheckAndUseInventoryItems.SVBSMe = this;
		vB_StateMachine_409_CheckAndUseInventoryItems.SState = -1;
		vB_StateMachine_409_CheckAndUseInventoryItems.SBuilder = AsyncTaskMethodBuilder.Create();
		vB_StateMachine_409_CheckAndUseInventoryItems.SBuilder.Start<Person.VB_StateMachine_409_CheckAndUseInventoryItems>(ref vB_StateMachine_409_CheckAndUseInventoryItems);
		return vB_StateMachine_409_CheckAndUseInventoryItems.SBuilder.Task;
	}
	Task CheckAndUseAutomaticItems()
	{
		Person.VB_StateMachine_410_CheckAndUseAutomaticItems vB_StateMachine_410_CheckAndUseAutomaticItems = default(Person.VB_StateMachine_410_CheckAndUseAutomaticItems);
		vB_StateMachine_410_CheckAndUseAutomaticItems.SVBSMe = this;
		vB_StateMachine_410_CheckAndUseAutomaticItems.SState = -1;
		vB_StateMachine_410_CheckAndUseAutomaticItems.SBuilder = AsyncTaskMethodBuilder.Create();
		vB_StateMachine_410_CheckAndUseAutomaticItems.SBuilder.Start<Person.VB_StateMachine_410_CheckAndUseAutomaticItems>(ref vB_StateMachine_410_CheckAndUseAutomaticItems);
		return vB_StateMachine_410_CheckAndUseAutomaticItems.SBuilder.Task;
	}
	bool ShouldSerializeTrait()
	{
		return !QString.IsNullOrEmpty(Trait);
	}
	void AddTrait(QString TraitName)
	{
		if (Trait.Length == 0)
		{
			Trait = TraitName;
			return;
		}
		if (!Trait.Split(new char[]
		{
			Person.TRAIT_SEPARATOR_CHAR
		}).contains(TraitName))
		{
			Trait = Trait + Conversions.ToString(Person.TRAIT_SEPARATOR_CHAR) + TraitName;
		}
	}
	void RemoveTrait(QString TraitName)
	{
		StringBuilder sb = new StringBuilder();
		QString[] array = Trait.Split(new char[]
		{
			Person.TRAIT_SEPARATOR_CHAR
		});
		// checked {
		for (int i = 0; i < array.Length; i++)
		{
			QString t = array[i];
			if (!t.Equals(TraitName))
			{
				sb.append(t);
				sb.append(Person.TRAIT_SEPARATOR_CHAR);
			}
		}
		if (sb.Length > 0 && sb[sb.Length - 1] == Person.TRAIT_SEPARATOR_CHAR)
		{
			sb.Remove(sb.Length - 1, 1);
		}
		Trait = sb.ToString();
		// }
	}
	bool HasTrait(QString TraitName)
	{
		return Trait.Split(new char[]
		{
			Person.TRAIT_SEPARATOR_CHAR
		}).contains(TraitName);
	}
	bool HasTraitFromList(QString TraitList)
	{
		QString[] TraitListIn = TraitList.Split(new char[]
		{
			Person.TRAIT_SEPARATOR_CHAR
		});
		QString[] MyTraitList = Trait.Split(new char[]
		{
			Person.TRAIT_SEPARATOR_CHAR
		});
		QString[] array = TraitListIn;
		// checked {
		bool HasTraitFromList;
		for (int i = 0; i < array.Length; i++)
		{
			QString T = array[i];
			if (MyTraitList.contains(T))
			{
				HasTraitFromList = true;
				return HasTraitFromList;
			}
		}
		HasTraitFromList = false;
		return HasTraitFromList;
		// }
	}
	bool ShouldSerializeSkills()
	{
		return Skills.count() > 0;
	}
	bool HasSkill(QString skillName)
	{
		return Skills.ContainsKey(skillName);
	}
	int GetSkill(QString skillName)
	{
		CheckSkill(skillName);
		Skill arg_30_0 = Game.DictOfSkills[skillName];
		int retVal = Skills.ContainsKey(skillName) ? Skills[skillName] : 0;
		int minVal = arg_30_0.MinValue;
		int maxVal = arg_30_0.MaxValue;
		object statusEffects = StatusEffects;
		// checked {
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_AddSkillValue)
				{
					Modifier_AddSkillValue addConstMod = (Modifier_AddSkillValue)modi;
					if (Operators.CompareString(addConstMod.SkillName, skillName, false) == 0)
					{
						retVal += addConstMod.GetValue(this, se);
					}
				}
				else if (modi is Modifier_MinSkillValue)
				{
					Modifier_MinSkillValue minValMod = (Modifier_MinSkillValue)modi;
					if (Operators.CompareString(minValMod.SkillName, skillName, false) == 0 && minValMod.GetValue(this, se) > minVal)
					{
						minVal = minValMod.GetValue(this, se);
					}
				}
				else if (modi is Modifier_MaxSkillValue)
				{
					Modifier_MaxSkillValue maxValMod = (Modifier_MaxSkillValue)modi;
					if (Operators.CompareString(maxValMod.SkillName, skillName, false) == 0 && maxValMod.GetValue(this, se) < maxVal)
					{
						minVal = maxValMod.GetValue(this, se);
					}
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
		Skill baseSkill = Game.DictOfSkills[skillName];
		int oldValue = Skills.ContainsKey(skillName) ? Skills[skillName] : 0;
		int newValue = value < baseSkill.MinValue ? baseSkill.MinValue : (value > baseSkill.MaxValue ? baseSkill.MaxValue : value);
		Skills[skillName] = newValue;
		Game.NotifyManager.HandleSkillNotification(this, skillName, checked(newValue - oldValue));
	}
	void AddSkill(QString skillName, int value)
	{
		CheckSkill(skillName);
		Skill baseSkill = Game.DictOfSkills[skillName];
		int oldValue = Skills.ContainsKey(skillName) ? Skills[skillName] : 0;
		int addValue = value;
		object statusEffects = StatusEffects;
		// checked {
		// lock (statusEffects) {
		// try {
		for (QList<StatusEffectInstance>::iterator it = StatusEffects.begin();
				it != StatusEffects.end(); ++it)
		{
			StatusEffectInstance se = enumerator.Current;
			StatusEffect effect = Game.DictOfStatusEffects[se.Name];
			// try {
			for (QList<ModifierBase>::iterator it2 = effect.Modifiers.begin();
					it2 != effect.Modifiers.end(); ++it2)
			{
				ModifierBase modi = enumerator2.Current;
				if (modi is Modifier_IncreaseSkillMultiplier)
				{
					Modifier_IncreaseSkillMultiplier scaleMod = (Modifier_IncreaseSkillMultiplier)modi;
					if (Operators.CompareString(skillName, scaleMod.SkillName, false) == 0 && value > 0)
					{
						addValue = (int)Math.Round(unchecked((double)addValue * scaleMod.GetScaleFactor(this, se)));
					}
				}
				else if (modi is Modifier_DecreaseSkillMultiplier)
				{
					Modifier_DecreaseSkillMultiplier scaleMod2 = (Modifier_DecreaseSkillMultiplier)modi;
					if (Operators.CompareString(skillName, scaleMod2.SkillName, false) == 0 && value < 0)
					{
						addValue = (int)Math.Round(unchecked((double)addValue * scaleMod2.GetScaleFactor(this, se)));
					}
				}
			}
			// }
		}
		// }
		// }
		int newValue = oldValue + addValue < baseSkill.MinValue ? baseSkill.MinValue : (oldValue + addValue > baseSkill.MaxValue ? baseSkill.MaxValue : oldValue + addValue);
		Skills[skillName] = newValue;
		Game.NotifyManager.HandleSkillNotification(this, skillName, newValue - oldValue);
		// }
	}
	void CheckSkill(QString skillName)
	{
		if (!Game.DictOfSkills.ContainsKey(skillName))
		{
			throw new ArgumentException(QString.Format("'{0}' was not declared as valid skill for the current scenario!", skillName));
		}
	}
	bool ShouldSerializeAttachedEventIDs()
	{
		return AttachedEventIDs.count() > 0;
	}
	int CompareByLastname(Person x, Person y)
	{
		return QString.Compare(x.Lastname + " " + x.DisplayForename, y.Lastname + " " + y.DisplayForename);
	}
	int CompareByFirstname(Person x, Person y)
	{
		return QString.Compare(x.DisplayForename, y.DisplayForename);
	}
	int CompareForPublicArea(Person x, Person y)
	{
		int CompareForPublicArea;
		if (x == NULL || y == NULL)
			return 0;

		if (x.IsWorking() && !y.IsWorking())
			return -1;

		if (y.IsWorking() && !x.IsWorking())
			return 1;

		if (x.IsFavorite && !y.IsFavorite)
			return -1;

		if (y.IsFavorite && !x.IsFavorite)
			return 1;

		return QString.Compare(x.DisplayName, y.DisplayName);
	}
	int CompareForSchoolRoom(Person x, Person y)
	{
		if (x == NULL || y == NULL)
			return 0;

		if (Operators.CompareString(x.Job, "Teacher", false) == 0) {

			if (Operators.CompareString(y.Job, "Teacher", false) == 0)
				return QString.Compare(x.DisplayName, y.DisplayName);

			return -1;
		}
		if (Operators.CompareString(y.Job, "Teacher", false) == 0)
			return 1;

		return Person.CompareForPublicArea(x, y);
	}
};

#endif // PERSON_H
