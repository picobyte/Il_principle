#ifndef POPULATIONGENERATOR_H
#define POPULATIONGENERATOR_H
#include "json_macros.h"

class PopulationGenerator {
public:
	QString[] GirlNames;
	QString[] BoyNames;
	QString[] Surnames;
	int PopulationOffset;
	QList<int> AdultHeads;
	QList<int> StudentHeads;
	QList<SchoolSubject> availableSubjects;
	const int StudentIndex() const
	{
		return Game.ScenarioConfig.PopulationTag.IndexOf("Student");
	}

	PopulationGenerator(QJsonObject *d = NULL)
	{
		if (d) init(d);
		AdultHeads = new QList<int>();
		StudentHeads = new QList<int>();
		availableSubjects = new QList<SchoolSubject>();
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_VAR_FROM_JSON_AS(it, PopulationOffset, toInt)
			else __IF_LIST_FROM_JSON_TYPED(it, AdultHeads, toInt)
			else __IF_LIST_FROM_JSON_TYPED(it, StudentHeads, toInt)
			else __IF_OBJLIST_FROM_JSON(it, availableSubjects, SchoolSubject)
			// *INDENT-ON*
		}
	}
	void LoadNames()
	{
		// checked {
		// try {
		GirlNames = File.ReadAllLines(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "PopulationData", "girlname.txt"));
		int num = GirlNames.Length - 1;
		for (int i = 0; i <= num; i++)
		{
			GirlNames[i] = GirlNames[i].Trim();
		}
		BoyNames = File.ReadAllLines(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "PopulationData", "boyname.txt"));
		int num2 = BoyNames.Length - 1;
		for (int j = 0; j <= num2; j++)
		{
			BoyNames[j] = BoyNames[j].Trim();
		}
		Surnames = File.ReadAllLines(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "PopulationData", "lastname.txt"));
		int num3 = Surnames.Length - 1;
		for (int k = 0; k <= num3; k++)
		{
			Surnames[k] = Surnames[k].Trim();
		}
		// }
		catch (Exception expr_109)
		{
			ProjectData.SetProjectError(expr_109);
			Exception e = expr_109;
			ExceptionHandler.HandleException(e);
			System.Windows.Application.Current.Shutdown();
			ProjectData.ClearProjectError();
		}
		// }
	}
	QString GetForename(Gender G)
	{
		QString GetForename;
		if (G == Gender.Male)
		{
			if (BoyNames == NULL)
			{
				LoadNames();
			}
			GetForename = BoyNames[Game.RNG.Next(0, BoyNames.Length)];
		}
		else
		{
			if (GirlNames == NULL)
			{
				LoadNames();
			}
			GetForename = GirlNames[Game.RNG.Next(0, GirlNames.Length)];
		}
		return GetForename;
	}
	QString GetLastname()
	{
		if (Surnames == NULL)
		{
			LoadNames();
		}
		return Surnames[Game.RNG.Next(0, Surnames.Length)];
	}
	DateTime GetRandomDateForAge(int Age, DateTime ReferenceDate)
	{
		return ReferenceDate.AddYears(checked(0 - (Age + 1))).AddDays((double)Game.RNG.Next(365));
	}
	int GetAdultHeadIndex()
	{
		// checked {
		if (AdultHeads.count() == 0)
		{
			int i = 0;
			do
			{
				AdultHeads.Add(i);
				i++;
			}
			while (i <= 99);
		}
		int index = Game.RNG.Next(AdultHeads.count());
		int arg_52_0 = AdultHeads[index];
		AdultHeads.RemoveAt(index);
		return arg_52_0;
		// }
	}
	int GetStudentHeadIndex()
	{
		// checked {
		if (StudentHeads.count() == 0)
		{
			int i = 0;
			do
			{
				StudentHeads.Add(i);
				i++;
			}
			while (i <= 99);
		}
		int index = Game.RNG.Next(StudentHeads.count());
		int arg_52_0 = StudentHeads[index];
		StudentHeads.RemoveAt(index);
		return arg_52_0;
		// }
	}
	void ClearPopulation()
	{
		Game.DictOfPersonIDs.Clear();
		Game.DictOfPersonNames.Clear();
		Game.HiredStaff.Clear();
		Game.AvailableStaff.Clear();
		Game.HiredTeacher.Clear();
		Game.NotHiredTeacher.Clear();
		Game.OwnStudents.Clear();
		Game.OtherStudents.Clear();
		Game.ListOfPTA.Clear();
	}
	void CreatePopulation(int count)
	{
		// checked {
		count += Game.DictOfPersonIDs.count();
		while (Game.DictOfPersonIDs.count() < count)
		{
			CreateFamily(NULL);
		}
		// }
	}
	void CreateFamily(IList<Person> outList = NULL)
	{
		QString familyName = GetLastname();
		QList<Person> children = new QList<Person>();
		Person mother;
		Person father;
		Location home;
		// checked {
		do
		{
			Person student = new Person();
			student.Job = "Student";
			student.Birthday = Game.SchoolCalendar.TodayDate.AddDays((double)Game.RNG.Next(365));
			int AgeGoal = Game.RNG.Next(Game.ScenarioConfig.PopulationGenerationData[StudentIndex].AgeRange.Min, Game.ScenarioConfig.PopulationGenerationData[StudentIndex].AgeRange.Max);
			AgeGoal = Math.Max(Game.ScenarioConfig.MinimumAge, AgeGoal);
			while (student.Age < AgeGoal)
			{
				student.Birthday = student.Birthday.AddYears(-1);
			}
			student.Virgin = (Game.RNG.Next(50) >= 1);
			student.Gender = Game.ScenarioConfig.GetGenderForIndex(StudentIndex);
			SetGenderPreferences(student, StudentIndex);
			SetGenderSizes(student, StudentIndex, "Students");
			student.Lastname = familyName;
			do
			{
				student.Forename = GetForename(student.Gender);
			}
			while (!PersonNameIsUnique(student));
			GenerateStatsFor(student, StudentIndex);
			AddFavoriteSubject(student);
			AddSubjectExperience(student);
			int z = 0;
			do
			{
				if (Game.RNG.Next(100) >= 70)
				{
					student.AddFetish((Fetish)Game.RNG.Next(1, Enum.GetNames(typeof(Fetish)).count()<QString>()));
				}
				z++;
			}
			while (z <= 2);
			children.Add(student);
			// try {
			Game.DictOfPersonIDs.Add(student.UID, student);
			Game.DictOfPersonNames.Add(student.Name, student);
			Game.OtherStudents.Add(student.Name, student);
			// }
			catch (ArgumentException expr_1F1)
			{
				ProjectData.SetProjectError(expr_1F1);
				ArgumentException ex = expr_1F1;
				throw new PopulationGeneratorException(QString.Format("Error registering {0} in the dictionary: {1}", student.Name, ex.Message), ex);
			}
		}
		while (Game.RNG.Next(children.count() * children.count() + 3) < 1);
		int highestChildrenAge = 0;
		// try {
		for (QList<Person>::iterator it = children.begin();
				it != children.end(); ++it)
		{
			Person stud = enumerator.Current;
			if (stud.Age > highestChildrenAge)
			{
				highestChildrenAge = stud.Age;
			}
		}
		// }
		mother = NULL;
		if (Game.RNG.Next(100) > 3)
		{
			mother = new Person();
			mother.Birthday = Game.SchoolCalendar.TodayDate.AddDays((double)Game.RNG.Next(365));
			int AgeMin = Math.Max(Game.ScenarioConfig.PopulationGenerationData[0].AgeRange.Min, highestChildrenAge + 14);
			int AgeGoal2 = Game.RNG.Next(AgeMin, Game.ScenarioConfig.PopulationGenerationData[0].AgeRange.Max);
			AgeGoal2 = Math.Max(Game.ScenarioConfig.MinimumAge, AgeGoal2);
			while (mother.Age < AgeGoal2)
			{
				mother.Birthday = mother.Birthday.AddYears(-1);
			}
			if ((double)Game.RNG.Next(100) < Game.ScenarioConfig.PopulationGenerationData[0].FutanariPercentage)
			{
				MakeFuta(mother);
			}
			else
			{
				mother.Gender = Gender.Female;
			}
			SetGenderSizes(mother, 0, "Adult");
			mother.Virgin = false;
			mother.Lastname = familyName;
			do
			{
				mother.Forename = GetForename(mother.Gender);
			}
			while (!PersonNameIsUnique(mother));
			mother.Job = "";
			SetGenderPreferences(mother, 0);
			GenerateStatsFor(mother, 0);
			mother.SetStat("Education", (double)Game.RNG.Next(30, 70));
			mother.SetStat("Lust", (double)Game.RNG.Next(30, 70));
			int z2 = 0;
			do
			{
				if (Game.RNG.Next(100) >= 70)
				{
					mother.AddFetish((Fetish)Game.RNG.Next(1, Enum.GetNames(typeof(Fetish)).count()<QString>()));
				}
				z2++;
			}
			while (z2 <= 5);
			if (mother.HasFetish(Fetish.Exhibitionism))
			{
				mother.AddStat("Inhibition", -15.0);
			}
			// try {
			Game.DictOfPersonIDs.Add(mother.UID, mother);
			Game.DictOfPersonNames.Add(mother.Name, mother);
			// }
			catch (ArgumentException expr_489)
			{
				ProjectData.SetProjectError(expr_489);
				ArgumentException ex2 = expr_489;
				throw new PopulationGeneratorException(QString.Format("Error registering {0} in the dictionary: {1}", mother.Name, ex2.Message), ex2);
			}
		}
		father = NULL;
		if (mother == NULL || Game.RNG.Next(100) > 3)
		{
			father = new Person();
			father.Birthday = Game.SchoolCalendar.TodayDate.AddDays((double)Game.RNG.Next(365));
			int AgeGoal3;
			if (mother != NULL)
			{
				AgeGoal3 = (int)Math.Round(unchecked((double)mother.Age + Game.RNG.NextGaussian(0.0, 5.0)));
				AgeGoal3 = Math.Max(AgeGoal3, highestChildrenAge + 14);
			}
			else
			{
				int AgeMin2 = Math.Max(Game.ScenarioConfig.PopulationGenerationData[0].AgeRange.Min, highestChildrenAge + 14);
				AgeGoal3 = Game.RNG.Next(AgeMin2, Game.ScenarioConfig.PopulationGenerationData[0].AgeRange.Max);
			}
			AgeGoal3 = Math.Max(Game.ScenarioConfig.MinimumAge, AgeGoal3);
			while (father.Age < AgeGoal3)
			{
				father.Birthday = father.Birthday.AddYears(-1);
			}
			if ((double)Game.RNG.Next(100) < Game.ScenarioConfig.PopulationGenerationData[0].FutanariPercentage)
			{
				MakeFuta(father);
			}
			else
			{
				father.Gender = Gender.Male;
				father.AnalVirgin = (Game.RNG.Next(15) >= 1);
			}
			SetGenderSizes(father, 0, "Adult");
			father.Virgin = false;
			father.Lastname = familyName;
			do
			{
				father.Forename = GetForename(father.Gender);
			}
			while (!PersonNameIsUnique(father));
			father.Job = "";
			SetGenderPreferences(father, 0);
			GenerateStatsFor(father, 0);
			father.SetStat("Education", (double)Game.RNG.Next(30, 70));
			father.SetStat("Lust", (double)Game.RNG.Next(30, 70));
			int z3 = 0;
			do
			{
				if (Game.RNG.Next(100) >= 70)
				{
					father.AddFetish((Fetish)Game.RNG.Next(1, Enum.GetNames(typeof(Fetish)).count()<QString>()));
				}
				z3++;
			}
			while (z3 <= 5);
			if (father.HasFetish(Fetish.Exhibitionism))
			{
				father.AddStat("Inhibition", -15.0);
			}
			// try {
			Game.DictOfPersonIDs.Add(father.UID, father);
			Game.DictOfPersonNames.Add(father.Name, father);
			// }
			catch (ArgumentException expr_735)
			{
				ProjectData.SetProjectError(expr_735);
				ArgumentException ex3 = expr_735;
				throw new PopulationGeneratorException(QString.Format("Error registering {0} in the dictionary: {1}", father.Name, ex3.Message), ex3);
			}
		}
		home = Game.GetLocation("General Home");
		if (mother != NULL)
		{
			mother.Home = home;
			if (father == NULL && mother.SexualOrientation != SexualPref.Bisexual && (double)Game.RNG.Next(100) < mother.GetGenderPreference(Gender.Female))
			{
				mother.AddGenderPreference(Gender.Female, 50.0);
				mother.AnalVirgin = (Game.RNG.Next(20) >= 1);
			}
			mother.AnalVirgin = (Game.RNG.Next((father != NULL && father.HasFetish(Fetish.Anal)) ? 3 : 15) >= 1);
			AssignPersonFetishStats(mother);
		}
		if (father != NULL)
		{
			father.Home = home;
			if (mother == NULL && father.SexualOrientation != SexualPref.Bisexual)
			{
				if ((double)Game.RNG.Next(100) < father.GetGenderPreference(Gender.Male))
				{
					father.AddGenderPreference(Gender.Male, 50.0);
					father.AnalVirgin = false;
				}
				else
				{
					father.AnalVirgin = (Game.RNG.Next(20) >= 1);
				}
			}
			AssignPersonFetishStats(father);
		}
		// }
		// try {
		for (QList<Person>::iterator it = children.begin();
				it != children.end(); ++it)
		{
			Person stud2 = enumerator2.Current;
			stud2.Home = home;
			if (mother != NULL)
			{
				mother.Children.Add(stud2.Name);
				stud2.Mother = mother;
				Game.RelationshipDatabase.SetRelationshipValue(stud2, mother, Game.RNG.NextDouble() * 25.0 + 50.0);
				Game.RelationshipDatabase.SetRelationshipValue(mother, stud2, Game.RNG.NextDouble() * 25.0 + 50.0);
			}
			if (father != NULL)
			{
				father.Children.Add(stud2.Name);
				stud2.Father = father;
				Game.RelationshipDatabase.SetRelationshipValue(stud2, father, Game.RNG.NextDouble() * 25.0 + 50.0);
				Game.RelationshipDatabase.SetRelationshipValue(father, stud2, Game.RNG.NextDouble() * 25.0 + 50.0);
			}
			QList<Person> siblings = stud2.GetSiblings();
			// try {
			for (QList<Person>::iterator it = siblings.begin();
					it != siblings.end(); ++it)
			{
				Person S = enumerator3.Current;
				Game.RelationshipDatabase.SetRelationshipValue(stud2, S, Game.RNG.NextDouble() * 20.0 + 60.0);
			}
			// }
		}
		// }
		if (mother != NULL && father != NULL)
		{
			AssignPersonFetishStats(mother, father);
			AssignPersonFetishStats(father, mother);
		}
		// try {
		for (QList<Person>::iterator it = children.begin();
				it != children.end(); ++it)
		{
			Person stud3 = enumerator4.Current;
			if (mother != NULL)
			{
				AssignParentChildFetishStats(mother, stud3);
			}
			if (father != NULL)
			{
				AssignParentChildFetishStats(father, stud3);
			}
			AssignPersonFetishStats(stud3);
		}
		// }
		// checked {
		if (mother != NULL)
		{
			mother.AddStat("Fertility", (double)(10 * children.count()));
		}
		if (father != NULL)
		{
			father.AddStat("Fertility", (double)(10 * children.count()));
		}
		if (outList != NULL)
		{
			outList.AddIfNotNull(mother);
			outList.AddIfNotNull(father);
			// try {
			for (QList<Person>::iterator it = children.begin();
					it != children.end(); ++it)
			{
				Person c = enumerator5.Current;
				outList.AddIfNotNull(c);
			}
			// }
		}
		// }
	}
	void AssignPersonFetishStats(Person per)
	{
		if (per.HasFetish(Fetish.Exhibitionism))
		{
			per.AddStat("Inhibition", -15.0);
		}
		if (per.HasFetish(Fetish.Incest))
		{
			// try {
			QList<Person>.Enumerator enumerator = per.GetSiblings().GetEnumerator();
			while (enumerator.MoveNext())
			{
				Person S = enumerator.Current;
				Game.RelationshipDatabase.AddRelationshipValue(per, S, Game.RNG.NextDouble() * 10.0 + 10.0);
				S.AddStat("Lust", 5.0);
			}
			// }
			per.AddStat("Lust", 10.0);
		}
	}
	void AssignPersonFetishStats(Person p1, Person p2)
	{
		if (p1.HasFetish(Fetish.Sadism) && p2.HasFetish(Fetish.Masochism))
		{
			p1.AddStat("Corruption", 10.0);
			p1.AddStat("Lust", 15.0);
			p1.AddStat("Authority", 10.0);
			p2.AddStat("Corruption", 5.0);
			p2.AddStat("Lust", 15.0);
			p2.AddStat("Willpower", -10.0);
		}
		if (p1.HasFetish(Fetish.Voyeurism) && p2.HasFetish(Fetish.Exhibitionism))
		{
			p1.AddStat("Lust", 5.0);
			p2.AddStat("Lust", 5.0);
			p2.AddStat("Inhibition", -5.0);
		}
	}
	void AssignParentChildFetishStats(Person parent, Person child)
	{
		if ((parent.HasFetish(Fetish.Shota) && child.Gender == Gender.Male) || (parent.HasFetish(Fetish.Loli) && child.Gender == Gender.Female) || ((parent.HasFetish(Fetish.Futa) || parent.HasFetish(Fetish.Shota) || parent.HasFetish(Fetish.Loli)) && child.Gender == Gender.Futanari))
		{
			parent.AddStat("Corruption", 5.0);
			child.AddStat("Happiness", -5.0);
			child.AddStat("Lust", 5.0);
		}
		if (parent.HasFetish(Fetish.Incest))
		{
			parent.AddStat("Corruption", 10.0);
			child.AddStat("Happiness", -10.0);
			child.AddStat("Lust", 5.0);
			child.AddStat("Corruption", 5.0);
			if (child.HasFetish(Fetish.Incest))
			{
				if (child.LikesGender(parent.Gender))
				{
					child.AddStat("Happiness", 15.0);
					return;
				}
				child.AddStat("Happiness", 10.0);
				child.AddGenderPreference(parent.Gender, 25.0);
			}
		}
	}
	void AssignHead(Person Per)
	{
		int index;
		QString folder;
		if (Per.Job.Equals("Student"))
		{
			index = GetStudentHeadIndex();
			folder = Path.Combine("Images", "People", "Students");
		}
		else
		{
			index = GetAdultHeadIndex();
			folder = Path.Combine("Images", "People", "Adult");
		}
		Per.MaleHeadFileName = Path.Combine(folder, "Heads", "M_Head" + Conversions.ToString(index) + ".png");
		Per.FemaleHeadFileName = Path.Combine(folder, "Heads", "F_Head" + Conversions.ToString(index) + ".png");
	}
	void AddFavoriteSubject(Person Per)
	{
		// checked {
		if (Game.RNG.Next(10) == 0 && Game.DictOfSubjects.count() > 0)
		{
			SchoolSubject favSubject = Game.DictOfSubjects.Values.ElementAtOrDefault(Game.RNG.Next(Game.DictOfSubjects.count()));
			Per.GoodInSubject = favSubject.Name;
			switch (favSubject.SubjectFamily)
			{
			case SchoolSubjectFamily.Mathematics:
				Per.AddStat("Intelligence", (double)Game.RNG.Next(7, 12));
				break;
			case SchoolSubjectFamily.LifeScience:
				Per.AddStat("Intelligence", (double)Game.RNG.Next(2, 5));
				Per.AddStat("Inhibition", (double)(0 - Game.RNG.Next(2, 5)));
				return;
			case SchoolSubjectFamily.NaturalScience:
				Per.AddStat("Intelligence", (double)Game.RNG.Next(6, 13));
				return;
			case SchoolSubjectFamily.SocialScience:
				Per.AddStat("Intelligence", (double)Game.RNG.Next(2, 5));
				Per.AddStat("Loyalty", (double)Game.RNG.Next(4, 8));
				return;
			case SchoolSubjectFamily.ComputerStudies:
				Per.AddStat("Intelligence", (double)Game.RNG.Next(5, 10));
				Per.AddStat("Happiness", (double)Game.RNG.Next(2, 4));
				return;
			case SchoolSubjectFamily.Humanities:
				Per.AddStat("Happiness", (double)Game.RNG.Next(4, 8));
				Per.AddStat("Loyalty", (double)Game.RNG.Next(2, 5));
				return;
			case SchoolSubjectFamily.LanguageArts:
				Per.AddStat("Education", (double)Game.RNG.Next(4, 8));
				Per.AddStat("Charisma", (double)Game.RNG.Next(2, 5));
				return;
			case SchoolSubjectFamily.FineArts:
				Per.AddStat("Charisma", (double)Game.RNG.Next(4, 8));
				Per.AddStat("Inhibition", (double)(0 - Game.RNG.Next(2, 5)));
				return;
			case SchoolSubjectFamily.PhysicalEducation:
				Per.AddStat("Stamina", (double)Game.RNG.Next(4, 8));
				Per.AddStat("Appearance", (double)Game.RNG.Next(2, 5));
				return;
			case SchoolSubjectFamily.SexualEducation:
				Per.AddStat("Corruption", (double)Game.RNG.Next(1, 4));
				Per.AddStat("Lust", (double)Game.RNG.Next(2, 5));
				Per.AddStat("Inhibition", (double)(0 - Game.RNG.Next(2, 5)));
				return;
			default:
				return;
			}
		}
		// }
	}
	void AddSubjectExperience(Person Per)
	{
		if (availableSubjects.count() == 0)
		{
			// try {
			for (QHash<QString, SchoolSubject>::iterator it = Game.DictOfSubjects.Values.begin();
					it != Game.DictOfSubjects.Values.end(); ++it)
			{
				SchoolSubject s = enumerator.Current;
				if (s.CanBeTaught && s.GetAvailableLessonLocations().count() > 0)
				{
					availableSubjects.Add(s);
				}
			}
			// }
		}
		if (Per.Job.Equals("Teacher"))
		{
			// try {
			for (QHash<QString, SchoolSubject>::iterator it = Game.DictOfSubjects.Values.begin();
					it != Game.DictOfSubjects.Values.end(); ++it)
			{
				enumerator2.Current.AddSubjectExp(Per, Game.RNG.NextDouble() * 5.0);
			}
			return;
			// }
		}
		// try {
		for (QList<SchoolSubject>::iterator it = availableSubjects.begin();
				it != availableSubjects.end(); ++it)
		{
			SchoolSubject expr_D9 = enumerator3.Current;
			if (expr_D9.Name.Equals(Per.GoodInSubject))
			{
				Per.AddSubjectInstanceExp(Per.GoodInSubject, 10.0);
			}
			expr_D9.AddSubjectExp(Per, Game.RNG.NextDouble() * 5.0);
		}
		// }
		if (!Per.Virgin || !Per.AnalVirgin)
		{
			Per.AddSubjectFamilyExp(SchoolSubjectFamily.SexualEducation, 3.0 + Game.RNG.NextDouble() * 4.0);
		}
	}
	void MakeFuta(Person Per)
	{
		Per.Gender = Gender.Futanari;
		Per.ImageLocation = Path.Combine(Game.TheSchool.FolderLocation, "Images", "Female");
	}
	void SetGenderSizes(Person NewPerson, int index, QString folder)
	{
		AssignHead(NewPerson);
		// checked {
		// try {
		QList<PopulationGenerationGenderSpecificData>.Enumerator enumerator = Game.ScenarioConfig.PopulationGenerationData[index].GenderSpecific.GetEnumerator();
		while (enumerator.MoveNext())
		{
			PopulationGenerationGenderSpecificData gend = enumerator.Current;
			if (NewPerson.Gender == gend.Gender)
			{
				NewPerson.PenisSize = (BodySize)Game.RNG.Next(gend.PenisSize.Min, gend.PenisSize.Max);
				NewPerson.intTesticleSize = (double)Game.RNG.Next(gend.TesticleSize.Min, gend.TesticleSize.Max);
				NewPerson.BreastSize = (BodySize)Game.RNG.Next(gend.BreastSize.Min, gend.BreastSize.Max);
				NewPerson.StomachSize = (BodySize)Game.RNG.Next(gend.StomachSize.Min, gend.StomachSize.Max);
				NewPerson.VaginaSize = (BodySize)Game.RNG.Next(gend.VaginaSize.Min, gend.VaginaSize.Max);
				NewPerson.AnalSize = (BodySize)Game.RNG.Next(gend.AnalSize.Min, gend.AnalSize.Max);
				break;
			}
		}
		// }
		// }
	}
	void SetGenderPreferences(Person NewPerson, int index)
	{
		PopulationGenerationGenderSpecificData genderSpecific = Game.ScenarioConfig.GetGenderSpecificDataForIndex(index, NewPerson.Gender);
		NewPerson.SetGenderPreference(Gender.Male, Game.RNG.NextGaussian(genderSpecific.LikesMale.Mean, genderSpecific.LikesMale.StdDev));
		NewPerson.SetGenderPreference(Gender.Female, Game.RNG.NextGaussian(genderSpecific.LikesFemale.Mean, genderSpecific.LikesFemale.StdDev));
		NewPerson.SetGenderPreference(Gender.Futanari, Game.RNG.NextGaussian(genderSpecific.LikesFutanari.Mean, genderSpecific.LikesFutanari.StdDev));
	}
	bool PersonNameIsUnique(Person P)
	{
		return !Game.DictOfPersonNames.ContainsKey(P.Name);
	}
	void GenerateStatsFor(Person P, int Index)
	{
		// try {
		QList<StatRange>.Enumerator enumerator = Game.ScenarioConfig.PopulationGenerationData[Index].StatRanges.GetEnumerator();
		while (enumerator.MoveNext())
		{
			StatRange stat = enumerator.Current;
			P.SetStat(stat.Stat, (double)checked(Game.RNG.Next((int)Math.Round(stat.Range.Min), (int)Math.Round(stat.Range.Max))));
		}
		// }
	}
};

#endif // POPULATIONGENERATOR_H
