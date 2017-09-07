#ifndef GAMECALENDAR_H
#define GAMECALENDAR_H
#include <QDateTime>
#include "json_macros.h"
#include "theworld.h"
#include "calendarentry.h"

class GameCalendar {
public:
    QList<CalendarEntry> ListOfCalendarEntries;
    int intCurrentDay;
    QDateTime MinDate() const;
    QDateTime MaxDate() const;
    int CurrentDay() const
    {
        return intCurrentDay;
    }
    QDateTime& TodayDate() const
    {
        return GetDateForDay(CurrentDay());
    }
    QString DayName() const
    {
        return QDate::longDayName(TodayDate().date().dayOfWeek());
    }
    bool IsWeekend() const
    {
        return DateIsWeekend(TodayDate());
    }
    bool IsHoliday() const
    {
        return CheckIsHoliday(TodayDate());
    }
    bool IsFirstDayOfWeek() const
    {
        return TodayDate().date().dayOfWeek() == Qt::Monday;
    }
    bool IsFirstDayOfMonth() const
    {
        return TodayDate().date().day() == 1;
    }
    bool IsLastDayOfMonth() const
    {
        return GetRemainingDaysInMonth() == 0;
    }

    GameCalendar(QJsonObject *d = NULL)
    {
        if (d) init(d);
        intCurrentDay = 1;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJLIST_FROM_JSON(it, ListOfCalendarEntries, CalendarEntry)
            else __IF_VAR_FROM_JSON_AS(it, intCurrentDay, toInt)
            // *INDENT-ON*
        }
    }
    int GetDaysInMonth()
    {
        return TodayDate().date().daysInMonth();
    }
    int GetRemainingDaysInMonth() const
    {
        QDate D = TodayDate().date();
        return D.daysInMonth() - D.day();
    }
    int GetWeekendDaysInMonth()
    {
        int remain = GetRemainingDaysInMonth();
        int WeekendDays = (2 * remain / 7);
        QDate D = TodayDate().date();
        int today = D.dayOfWeek();
        int endDay = D.addDays(remain % 7).dayOfWeek();
        if (endDay < today)
            return WeekendDays + (today == Qt::Sunday ? 1 : 2);

        return WeekendDays + (endDay < Qt::Saturday ? 0 : endDay - Qt::Friday);
        // }
    }
    int GetWorkDaysInMonth()
    {
        QDateTime T = TodayDate;
        int M = T.Month;
        // checked {
        QDateTime Start = T.AddDays((double)(0 - (T.Day - 1)));
        int WorkDays = 0;
        while (Start.Month == M)
        {
            if (Start.DayOfWeek != Qt::Saturday && Start.DayOfWeek != Qt::Sunday && !CheckIsHoliday(Start))
                WorkDays++;

            Start = Start.AddDays(1.0);
        }
        return WorkDays;
        // }
    }
    QDateTime& GetDateForDay(const int SchoolDay) const
    {
        return GameCalendar.MinDate.addDays(SchoolDay - 1);
    }
    int GetDayForDate(const QDateTime Dt) const
    {
        return (Dt - GameCalendar.MinDate).Days;
    }
    bool DateIsWeekend(const QDateTime Dt) const
    {
        return Dt.date().dayOfWeek() == Qt::Saturday || Dt.date().dayOfWeek() == Qt::Sunday;
    }
    void AddCalendarNote(CalendarEntry& Note)
    {
        RemoveCalendarNote(Note);
        ListOfCalendarEntries.append(Note);
    }
    void RemoveCalendarNote(CalendarEntry& Note)
    {
        ListOfCalendarEntries.Remove(Note);
    }
    bool CheckIsHoliday(const QDateTime Dt) const
    {
        for (QList<CalendarEntry>::iterator ce = ListOfCalendarEntries.begin(); ce != ListOfCalendarEntries.end(); ++ce)
            if (ce->ApplyDate == Dt && ce->Status == CalendarEntryStatus.Holiday)
                return true;
        return false;
    }
    bool CheckDayType(const EventDayTypes& DayType, const QDateTime& CheckDate) const;
    void NextDay();
    int GetHashCode()
    {
        return 17 * intCurrentDay ^ 23 * ListOfCalendarEntries.count();
    }
};

#endif // GAMECALENDAR_H
