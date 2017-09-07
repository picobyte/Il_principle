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
    QDate MinDate() const;
    QDate MaxDate() const;
    int CurrentDay() const
    {
        return intCurrentDay;
    }
    QDate TodayDate() const
    {
        return GetDateForDay(CurrentDay());
    }
    QString DayName() const
    {
        return QDate::longDayName(TodayDate().dayOfWeek());
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
        return TodayDate().dayOfWeek() == Qt::Monday;
    }
    bool IsFirstDayOfMonth() const
    {
        return TodayDate().day() == 1;
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
        return TodayDate().daysInMonth();
    }
    int GetRemainingDaysInMonth() const
    {
        QDate D = TodayDate();
        return D.daysInMonth() - D.day();
    }
    int GetWeekendDaysInMonth()
    {
        int remain = GetRemainingDaysInMonth();
        int WeekendDays = (2 * remain / 7);
        QDate D = TodayDate();
        int today = D.dayOfWeek();
        int endDay = D.addDays(remain % 7).dayOfWeek();
        if (endDay < today)
            return WeekendDays + (today == Qt::Sunday ? 1 : 2);

        return WeekendDays + (endDay < Qt::Saturday ? 0 : endDay - Qt::Friday);
    }
    int GetWorkDaysInMonth()
    {
        return GetRemainingDaysInMonth() - GetWeekendDaysInMonth();
    }
    QDate GetDateForDay(const int SchoolDay) const
    {
        return MinDate().addDays(SchoolDay - 1);
    }
    int GetDayForDate(const QDate& Dt) const
    {
        return MinDate().daysTo(Dt);
    }
    bool DateIsWeekend(const QDate& Dt) const
    {
        return Dt.dayOfWeek() == Qt::Saturday || Dt.dayOfWeek() == Qt::Sunday;
    }
    void AddCalendarNote(CalendarEntry& Note)
    {
        RemoveCalendarNote(Note);
        ListOfCalendarEntries.append(Note);
    }
    void RemoveCalendarNote(CalendarEntry& Note)
    {
        ListOfCalendarEntries.removeOne(Note);
    }
    bool CheckIsHoliday(const QDate& Dt) const
    {
        for (QList<CalendarEntry>::const_iterator ce = ListOfCalendarEntries.begin(); ce != ListOfCalendarEntries.end(); ++ce)
            if (ce->ApplyDate.date() == Dt && ce->Status == CalendarEntryStatus::Holiday)
                return true;
        return false;
    }
    bool CheckDayType(const EventDayTypes& DayType, const QDate& CheckDate) const;
    void NextDay();
    int GetHashCode()
    {
        return 17 * intCurrentDay ^ 23 * ListOfCalendarEntries.count();
    }
};

#endif // GAMECALENDAR_H
