#ifndef THEWORLD_H
#define THEWORLD_H
#include <QDateTime>

class TheWorld {
	double reputation;
	int money;
	QList<QString> GlobalStats;
	QList<UIProgressBarDefinition> ProgressBarStats;
	//object locationUpdateLock;
	ConcurrentDictionary<QString, Location> DictOfLocation;
	QList<Location> ListOfLocation;
	QList<Location> ListOfWorkplaces;
public:
	QString Name;
	QString Description;
	int SortOrder;
	QString FolderLocation;
	QString FilePath;
	int MaxGeneratedWorldPopulation;
	int MinEnrolledStudentCount;
	int MaxEnrolledStudentCount;
	QDateTime MinDate;
	QDateTime MaxDate;
	int MaxStartFetishes;
	QString StartLocationName;
	QString MapLocationName;

	const double get_Reputation() const
	{
		return reputation;
	}
	void set_Reputation(double& v)
	{
		reputation = value < 0.0 ? 0.0 : (value > 100.0 ? 100.0 : value);
	}
	const int get_Money() const
	{
		return money;
	}
	void set_Money(int& v)
	{
		money = value < -999999999 ? -999999999 : (value > 999999999 ? 999999999 : value);
        }
	TheWorld() : FilePath(""),
                MaxGeneratedWorldPopulation(1200),
                MinEnrolledStudentCount(75),
                MaxEnrolledStudentCount(400),
                MinDate(new QDateTime(2010, 2, 1)),
                MaxDate(new QDateTime(2012, 6, 30))
        {
	}
	void RecalculateBuildingMaintenance()
	{
		checked
		{
			int Total = 0;
			try
			{
				IEnumerator<SchoolUpgrade> enumerator = Game.ListOfSchoolUpgrades.GetEnumerator();
				while (enumerator.MoveNext())
				{
					SchoolUpgrade Upgrade = enumerator.Current;
					Total -= Upgrade.MaintenanceCost;
				}
			}
			finally {}
			if (!Game.DictOfAccounts.ContainsKey("Building Maintenance"))
			{
				Account ac = new Account
				{
					Name = "Building Maintenance",
					PayPeriode = Payperiode.Weekly,
					Active = true
				};
				Game.DictOfAccounts.Add(ac.Name, ac);
			}
			Game.DictOfAccounts["Building Maintenance"].Payment = Total;
		}
	}
	void ConvertToDict()
	{
		object obj = locationUpdateLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		lock (obj)
		{
			if (DictOfLocation.Count == 0)
			{
				ListOfWorkplaces.Clear();
				try
				{
					QList<Location>.Enumerator enumerator = ListOfLocation.GetEnumerator();
					while (enumerator.MoveNext())
					{
						Location Loc = enumerator.Current;
						DictOfLocation.TryAdd(Loc.Name, Loc);
						if (Loc.AssociatedJobs.Count > 0 && Loc.Region != Region.School)
						{
							ListOfWorkplaces.Add(Loc);
						}
						if (Loc.AllowedGenders.Count == 0)
						{
							Loc.AllowedGenders.AddRange(new Gender[]
							{
								Gender.Male,
								Gender.Female,
								Gender.Futanari
							});
						}
					}
				}
				finally {}
				ListOfLocation.Clear();
			}
		}
	}
	void ConvertToList()
	{
		object obj = locationUpdateLock;
		ObjectFlowControl.CheckForSyncLockOnValueType(obj);
		lock (obj)
		{
			if (ListOfLocation.Count != DictOfLocation.Values.Count)
			{
				ListOfLocation.Clear();
				ListOfLocation.AddRange(DictOfLocation.Values);
			}
		}
	}
	int GetChecksum()
	{
		return checked(UtilityClass.ShiftAndWrap(Name.GetHashCode(), 2) ^ UtilityClass.ShiftAndWrap(FolderLocation.GetHashCode(), 3) ^ UtilityClass.ShiftAndWrap(17 * MaxGeneratedWorldPopulation, 4) ^ UtilityClass.ShiftAndWrap(17 * MinEnrolledStudentCount, 5) ^ UtilityClass.ShiftAndWrap(17 * MaxEnrolledStudentCount, 6) ^ UtilityClass.ShiftAndWrap(17 * Game.DictOfStats.Count, 7) ^ UtilityClass.ShiftAndWrap(StartLocationName.GetHashCode(), 8) ^ UtilityClass.ShiftAndWrap(MapLocationName.GetHashCode(), 9) ^ UtilityClass.ShiftAndWrap(17 * ListOfLocation.Count, 10));
	}
};

#endif // THEWORLD_H
