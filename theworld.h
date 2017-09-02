#ifndef THEWORLD_H
#define THEWORLD_H
#include <QDateTime>
#include "json_macros.h"

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
};

#endif // THEWORLD_H
