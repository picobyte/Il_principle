#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H
#include "json_macros.h"

class StatisticsManager {
public:
	const QString MONEY_KEY = "Cash";
	const QString MONTHLY_ACC_TOTAL_KEY = "Monthly Balance";
	const QString REPUTATION_KEY = "Reputation";
	const QString STUDENTS_KEY = "Students";
	QHash<QString, QList<DataPoint>> _GlobalStatHistory;
	QHash<QString, QList<DataPoint>> _SubjectExperienceHistory;
	QHash<QString, QList<DataPoint>> _AccountingHistory;

	StatisticsManager(QJsonObject *d = NULL)
	{
		GlobalStatHistory.Add("Reputation", new QList<DataPoint>());
		GlobalStatHistory.Add("Students", new QList<DataPoint>());
		AccountingHistory.Add("Cash", new QList<DataPoint>());
		AccountingHistory.Add("Monthly Balance", new QList<DataPoint>());
	}
	void init(QJsonObject *d) { }
	void SaveStatisticsForCurrentDay()
	{
		DateTime nowDate = Game.SchoolCalendar.TodayDate;
		// try {
		for (QList<QString>::iterator it = Game.TheSchool.GlobalStats.begin();
				it != Game.TheSchool.GlobalStats.end(); ++it)
		{
			QString stat = enumerator.Current;
			if (!GlobalStatHistory.ContainsKey(stat))
			{
				GlobalStatHistory.Add(stat, new QList<DataPoint>());
			}
			double statToSave = 0.0;
			// try {
			for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values.begin();
					it != Game.OwnStudents.Values.end(); ++it)
			{
				Person stud = enumerator2.Current;
				statToSave += stud.GetStat(stat);
			}
			// }
			if (Game.OwnStudents.count() > 0)
			{
				statToSave /= (double)Game.OwnStudents.count();
			}
			GlobalStatHistory[stat].Add(DateTimeAxis.CreateDataPoint(nowDate, statToSave));
		}
		// }
		GlobalStatHistory["Reputation"].Add(DateTimeAxis.CreateDataPoint(nowDate, Game.TheSchool.Reputation));
		GlobalStatHistory["Students"].Add(DateTimeAxis.CreateDataPoint(nowDate, (double)Game.OwnStudents.count()));
		// try {
		for (QHash<QString, SchoolSubject>::iterator it = Game.DictOfSubjects.Values.begin();
				it != Game.DictOfSubjects.Values.end(); ++it)
		{
			SchoolSubject subj = *it;
			if (subj.CanBeTaught)
			{
				if (!SubjectExperienceHistory.ContainsKey(subj.Name))
				{
					SubjectExperienceHistory.Add(subj.Name, new QList<DataPoint>());
				}
				double statToSave2 = 0.0;
				// try {
				for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values.begin();
						it != Game.OwnStudents.Values.end(); ++it)
				{
					Person stud2 = enumerator4.Current;
					statToSave2 += stud2.GetSubjectExp(subj.Name);
				}
				// }
				if (Game.OwnStudents.count() > 0)
				{
					statToSave2 /= (double)Game.OwnStudents.count();
				}
				SubjectExperienceHistory[subj.Name].Add(DateTimeAxis.CreateDataPoint(nowDate, statToSave2));
			}
		}
		// }
		// try {
		for (IEnumerator<Account>::iterator it = Game.DictOfAccounts.Values.begin();
				it != Game.DictOfAccounts.Values.end(); ++it)
		{
			Account acc = enumerator5.Current;
			if (acc.Active)
			{
				if (!AccountingHistory.ContainsKey(acc.Name))
				{
					AccountingHistory.Add(acc.Name, new QList<DataPoint>());
				}
				AccountingHistory[acc.Name].Add(DateTimeAxis.CreateDataPoint(nowDate, (double)acc.Payment));
			}
		}
		// }
		AccountingHistory["Cash"].Add(DateTimeAxis.CreateDataPoint(nowDate, (double)Game.TheSchool.Money));
		AccountingHistory["Monthly Balance"].Add(DateTimeAxis.CreateDataPoint(nowDate, Account.GetMonthlyBalance()));
	}
};

#endif // STATISTICSMANAGER_H
