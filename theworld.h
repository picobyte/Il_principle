#ifndef THEWORLD_H
#define THEWORLD_H
#include <QDateTime>
#include "location.h"

class TheWorld {
	double reputation;
	int money;
	QList<QString> GlobalStats;
        //QList<UIProgressBarDefinition> ProgressBarStats;
        //ConcurrentDictionary<QString, Location> DictOfLocation;
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
        void set_Reputation(double& value)
	{
		reputation = value < 0.0 ? 0.0 : (value > 100.0 ? 100.0 : value);
	}
	const int get_Money() const
	{
		return money;
	}
        void set_Money(int& value)
	{
		money = value < -999999999 ? -999999999 : (value > 999999999 ? 999999999 : value);
	}
	TheWorld() : FilePath(""),
		MaxGeneratedWorldPopulation(1200),
		MinEnrolledStudentCount(75),
		MaxEnrolledStudentCount(400),
                MinDate(QDate(2010, 2, 1)),
                MaxDate(QDate(2012, 6, 30))
	{}
	void RecalculateBuildingMaintenance()
	{
		int Total = 0;
                /*IEnumerator<SchoolUpgrade>::iterator it;
                for (it = Game.ListOfSchoolUpgrades.begin(); it != enumerator.end(); ++it)
			Total -= it.Current.MaintenanceCost;

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
                Game.DictOfAccounts["Building Maintenance"].Payment = Total;*/
	}
	void ConvertToDict()
	{
                /*if (DictOfLocation.count() == 0)
		{
			ListOfWorkplaces.Clear();
                        QList<Location>:: iterator it;
                        for (it = ListOfLocation.begin(); it != ListOfLocation.end(); ++it)
			{
                                DictOfLocation.TryAdd(Loc.Name, *it);
                                if (it->AssociatedJobs.Count > 0 && it->Region != Region.School)
				{
                                        ListOfWorkplaces.Add(*it);
				}
                                if (it->AllowedGenders.Count == 0)
				{
                                        it->AllowedGenders.AddRange(new Gender[]
					{
						Gender.Male,
						Gender.Female,
						Gender.Futanari
					});
                                }
			}
			ListOfLocation.Clear();
                }*/
	}
	void ConvertToList()
	{
                /*if (ListOfLocation.Count != DictOfLocation.Values.Count)
		{
			ListOfLocation.Clear();
			ListOfLocation.AddRange(DictOfLocation.Values);
                }*/
	}
        static inline uint32_t ShiftAndWrap (uint32_t n, unsigned int c)
        {
            const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);  // assumes width is a power of 2.
            c &= mask;
            return (n<<c) | (n>>( (-c)&mask ));
        }

	int GetChecksum()
	{
                return ShiftAndWrap(qHash(Name), 2)
                        ^ ShiftAndWrap(qHash(FolderLocation), 3)
                        ^ ShiftAndWrap(17 * MaxGeneratedWorldPopulation, 4)
                        ^ ShiftAndWrap(17 * MinEnrolledStudentCount, 5)
                        ^ ShiftAndWrap(17 * MaxEnrolledStudentCount, 6)
                        /*^ ShiftAndWrap(17 * Game.DictOfStats.count(), 7)*/
                        ^ ShiftAndWrap(qHash(StartLocationName), 8)
                        ^ ShiftAndWrap(qHash(MapLocationName), 9)
                        ^ ShiftAndWrap(17 * ListOfLocation.count(), 10);
	}
};

#endif // THEWORLD_H
