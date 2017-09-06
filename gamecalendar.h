#ifndef GAMECALENDAR_H
#define GAMECALENDAR_H
#include "json_macros.h"

class GameCalendar {
public:
	QList<CalendarEntry> _ListOfCalendarEntries;
	int _intCurrentDay;
	const DateTime MinDate() const
	{
		if (Game.TheSchool == NULL)
		{
			return new DateTime(2010, 2, 1);
		}
		return Game.TheSchool.MinDate;
	}
	const DateTime MaxDate() const
	{
		if (Game.TheSchool == NULL)
		{
			return new DateTime(2012, 6, 30);
		}
		return Game.TheSchool.MaxDate;
	}
	const int intCurrentDay() const {return intCurrentDay;}
	void intCurrentDay(int& v) {intCurrentDay = v;}
	const int CurrentDay() const
	{
		return intCurrentDay;
	}
	const DateTime TodayDate() const
	{
		return GetDateForDay(CurrentDay);
	}
	const QString DayName() const
	{
		return TodayDate.DayOfWeek.ToString();
	}
	const bool IsWeekend() const
	{
		return DateIsWeekend(TodayDate);
	}
	const bool IsHoliday() const
	{
		return CheckIsHoliday(TodayDate);
	}
	const bool IsFirstDayOfWeek() const
	{
		return TodayDate.DayOfWeek == DayOfWeek.Monday;
	}
	const bool IsFirstDayOfMonth() const
	{
		return TodayDate.Day == 1;
	}
	const bool IsLastDayOfMonth() const
	{
		return GetRemainingDaysInMonth() == 0;
	}

	GameCalendar(QJsonObject *d = NULL)
	{
		if (d) init(d);
		ListOfCalendarEntries = new QList<CalendarEntry>();
		intCurrentDay = 1;
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_OBJLIST_FROM_JSON(it, _ListOfCalendarEntries, CalendarEntry)
			else __IF_VAR_FROM_JSON_AS(it, _intCurrentDay, toInt)
			// *INDENT-ON*
		}
	}
	int GetDaysInMonth()
	{
		DateTime T = TodayDate;
		return DateTime.DaysInMonth(T.Year, T.Month);
	}
	int GetRemainingDaysInMonth()
	{
		DateTime T = TodayDate;
		return checked(DateTime.DaysInMonth(T.Year, T.Month) - T.Day);
	}
	int GetWeekendDaysInMonth()
	{
		DateTime T = TodayDate;
		int M = T.Month;
		// checked {
		DateTime Start = T.AddDays((double)(0 - (T.Day - 1)));
		int WeekendDays = 0;
		while (Start.Month == M)
		{
			if (Start.DayOfWeek == DayOfWeek.Saturday || Start.DayOfWeek == DayOfWeek.Sunday)
			{
				WeekendDays++;
			}
			Start = Start.AddDays(1.0);
		}
		return WeekendDays;
		// }
	}
	int GetWorkDaysInMonth()
	{
		DateTime T = TodayDate;
		int M = T.Month;
		// checked {
		DateTime Start = T.AddDays((double)(0 - (T.Day - 1)));
		int WorkDays = 0;
		while (Start.Month == M)
		{
			if (Start.DayOfWeek != DayOfWeek.Saturday && Start.DayOfWeek != DayOfWeek.Sunday && !CheckIsHoliday(Start))
			{
				WorkDays++;
			}
			Start = Start.AddDays(1.0);
		}
		return WorkDays;
		// }
	}
	DateTime GetDateForDay(int SchoolDay)
	{
		return GameCalendar.MinDate.AddDays((double)(checked(SchoolDay - 1)));
	}
	int GetDayForDate(DateTime Dt)
	{
		return (Dt - GameCalendar.MinDate).Days;
	}
	bool DateIsWeekend(DateTime Dt)
	{
		return Dt.DayOfWeek == DayOfWeek.Saturday || Dt.DayOfWeek == DayOfWeek.Sunday;
	}
	void AddCalendarNote(CalendarEntry Note)
	{
		RemoveCalendarNote(Note);
		ListOfCalendarEntries.Add(Note);
	}
	void RemoveCalendarNote(CalendarEntry Note)
	{
		ListOfCalendarEntries.Remove(Note);
	}
	bool CheckIsHoliday(DateTime Dt)
	{
		return ListOfCalendarEntries.Exists((CalendarEntry ce) => DateTime.Compare(ce.ApplyDate, Dt) == 0 && ce.Status == CalendarEntryStatus.Holiday);
	}
	bool CheckDayType(EventDayTypes DayType, DateTime CheckDate)
	{
		return (DayType == EventDayTypes.Weekday && !DateIsWeekend(CheckDate)) || (DayType == EventDayTypes.Weekend && Game.SchoolCalendar.DateIsWeekend(CheckDate)) || (DayType == EventDayTypes.Schoolday && !Game.SchoolCalendar.DateIsWeekend(CheckDate) && !Game.SchoolCalendar.CheckIsHoliday(CheckDate)) || DayType.ToString().Equals(CheckDate.DayOfWeek.ToString()) || DayType == EventDayTypes.All;
	}
	void NextDay()
	{
		// checked {
		intCurrentDay++;
		// try {
		for (QList<VisualEvent>::iterator it = VisualEventManager.FunctionEvents.begin();
				it != VisualEventManager.FunctionEvents.end(); ++it)
		{
			VisualEvent Ev = enumerator.Current;
			if (Ev.XMLFileName.EndsWith("Daily_UpdateAccounts.ve.xml"))
			{
				Ev.Execute();
			}
		}
		// }
		// try {
		for (IEnumerator<Account>::iterator it = Game.DictOfAccounts.Values.begin();
				it != Game.DictOfAccounts.Values.end(); ++it)
		{
			Account ac = enumerator2.Current;
			if (ac.Active)
			{
				switch (ac.PayPeriode)
				{
				case Payperiode.Daily:
					if ((!IsWeekend && !IsHoliday) || !ac.NoWeekend)
					{
						TheWorld theSchool;
						(theSchool = Game.TheSchool).Money = theSchool.Money + ac.Payment;
					}
					break;
				case Payperiode.Weekly:
					if (IsFirstDayOfWeek)
					{
						TheWorld theSchool;
						(theSchool = Game.TheSchool).Money = theSchool.Money + ac.Payment;
					}
					break;
				case Payperiode.Monthly:
					if (IsLastDayOfMonth)
					{
						TheWorld theSchool;
						(theSchool = Game.TheSchool).Money = theSchool.Money + ac.Payment;
					}
					break;
				}
			}
		}
		// }
		if (!IsWeekend)
		{
			Clubs.AdjustAllClubSizes();
		}
		// try {
		for (QList<VisualEvent>::iterator it = VisualEventManager.NativeEvents.begin();
				it != VisualEventManager.NativeEvents.end(); ++it)
		{
			VisualEvent Ev2 = enumerator3.Current;
			if (Ev2.XMLFileName.EndsWith("Daily.ve.xml"))
			{
				Ev2.Execute();
			}
		}
		// }
		Game.StatisticsManager.SaveStatisticsForCurrentDay();
		FormManager.GameForm.SetNumberOfCalendarNotes(GetCalendarNotesForDay(TodayDate).Where((GameCalendar._ClosureS__.SI41_0 == NULL) ? (GameCalendar._ClosureS__.SI41_0 = new Func<CalendarEntry, bool>(GameCalendar._ClosureS__.SI._LambdaS__41_0)) : GameCalendar._ClosureS__.SI41_0).count()<CalendarEntry>());
		// }
	}
	int GetHashCode()
	{
		return checked(17 * intCurrentDay ^ 23 * ListOfCalendarEntries.count());
	}
};

#endif // GAMECALENDAR_H
