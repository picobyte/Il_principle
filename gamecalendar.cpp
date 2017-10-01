#include "game.h"
#include "gamecalendar.h"


QDateTime GameCalendar::MinDate() const
{
    if (Game::TheSchool == NULL)
    {
        return new QDateTime(2010, 2, 1);
    }
    return Game::TheSchool.MinDate;
}
QDateTime GameCalendar::MaxDate() const
{
    if (Game::TheSchool == NULL)
        return new QDateTime(2012, 6, 30);

    return Game::TheSchool.MaxDate;
}

bool GameCalendar::CheckDayType(const EventDayTypes& DayType, const QDateTime& CheckDate) const
{
    return (DayType == EventDayTypes::Weekday && !DateIsWeekend(CheckDate)) || (DayType == EventDayTypes::Weekend && Game::SchoolCalendar.DateIsWeekend(CheckDate)) || (DayType == EventDayTypes::Schoolday && !Game::SchoolCalendar.DateIsWeekend(CheckDate) && !Game::SchoolCalendar.CheckIsHoliday(CheckDate)) || DayType.ToString().Equals(CheckDate.DayOfWeek.ToString()) || DayType == EventDayTypes::All;
}

void GameCalendar::NextDay()
{
    // checked {
    intCurrentDay++;
    // try {
    for (QList<VisualEvent>::iterator it = VisualEventManager.FunctionEvents.begin();
            it != VisualEventManager.FunctionEvents.end(); ++it)
    {
        VisualEvent Ev = *it;
        if (Ev.jsonFileName.EndsWith("Daily_UpdateAccounts.ve.xml"))
        {
            Ev.Execute();
        }
    }
    // }
    // try {
    for (IEnumerator<Account>::iterator it = Game::DictOfAccounts.Values.begin();
            it != Game::DictOfAccounts.Values.end(); ++it)
    {
        Account ac = *it;
        if (ac.Active)
        {
            switch (ac.PayPeriode)
            {
            case Payperiode::Daily:
                if ((!IsWeekend() && !IsHoliday()) || !ac.NoWeekend)
                {
                    TheWorld theSchool;
                    (theSchool = Game::TheSchool).Money = theSchool.Money + ac.Payment;
                }
                break;
            case Payperiode::Weekly:
                if (IsFirstDayOfWeek())
                {
                    TheWorld theSchool;
                    (theSchool = Game::TheSchool).Money = theSchool.Money + ac.Payment;
                }
                break;
            case Payperiode::Monthly:
                if (IsLastDayOfMonth())
                {
                    TheWorld theSchool;
                    (theSchool = Game::TheSchool).Money = theSchool.Money + ac.Payment;
                }
                break;
            }
        }
    }
    // }
    if (!IsWeekend())
    {
        Clubs.AdjustAllClubSizes();
    }
    // try {
    for (QList<VisualEvent>::iterator it = VisualEventManager.NativeEvents.begin();
            it != VisualEventManager.NativeEvents.end(); ++it)
    {
        VisualEvent Ev2 = enumerator3.Current;
        if (Ev2.jsonFileName.EndsWith("Daily.ve.xml"))
        {
            Ev2.Execute();
        }
    }
    // }
    Game::StatisticsManager.SaveStatisticsForCurrentDay();
    FormManager.GameForm.SetNumberOfCalendarNotes(GetCalendarNotesForDay(TodayDate()).Where((GameCalendar._ClosureS__.SI41_0 == NULL) ? (GameCalendar._ClosureS__.SI41_0 = new Func<CalendarEntry, bool>(GameCalendar._ClosureS__.SI._LambdaS__41_0)) : GameCalendar._ClosureS__.SI41_0).count()<CalendarEntry>());
    // }
}
