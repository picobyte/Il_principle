#ifndef gTIME_H
#define gTIME_H
#include <math.h>
#include <QList>
#include "json_macros.h"
#include "timedata.h"
#include "timeframe.h"
#include "visualevent.h"
#include "game.h"

class gTime {
public:
    static const TimeFrame SchoolTime;
    static const TimeFrame FirstPeriod;
    static const TimeFrame SecondPeriod;
    static const TimeFrame ThirdPeriod;
    static const TimeFrame FourthPeriod;
    static const TimeFrame DetentionTime;
    static const TimeFrame StandardWorkHours;
    static const TimeFrame EveningWorkHours;
    static const TimeFrame WeekendWorkHours;
    static const TimeFrame Lunch;
    static const TimeFrame Sleep;
    static const TimeData SunriseTime;
    static const TimeData DaylightTime;
    static const TimeData SundownTime;
    static const TimeData NightTime;
    static const int MinutesInHour;
    static const int HoursInDay;

    QList<VisualEvent> eventexecutelistHigh;
    QList<VisualEvent> eventexecutelistLow;
    int StudentCount;
    int Teachercount;
    int CurriculumStart;
    int CurClass;
    int CurMod;
    int Hour() const;
    int Minute() const;
    const TimeData CurrentTime() const
    {
        return TimeData(Hour(), Minute());
    }
    int CurrentTimestamp() const;
    Daylight CheckDaylightTime() const
    {
        TimeData time = CurrentTime();
        if (time.CompareTo(SunriseTime) >= 0 && time.CompareTo(DaylightTime) < 0)
            return Daylight::Sunrise;

        if (time.CompareTo(DaylightTime) >= 0 && time.CompareTo(SundownTime) < 0)
            return Daylight::Day;

        if (time.CompareTo(SundownTime) >= 0 && time.CompareTo(NightTime) < 0)
            return Daylight::Sunset;

        return Daylight::Night;
    }
    bool IsSchoolDay() const;
    bool IsSchoolBreakTime() const
    {
        const TimeData time = CurrentTime();
        return IsSchoolTime() && !FirstPeriod.contains(time) && !SecondPeriod.contains(time) &&
                !ThirdPeriod.contains(time) && !FourthPeriod.contains(time);
    }
    bool IsSchoolTime() const
    {
        return IsSchoolDay() && SchoolTime.contains(CurrentTime());
    }
    bool IsLunchBreak() const
    {
        return Lunch.contains(CurrentTime());
    }
    bool IsFirstPeriod() const
    {
        return IsSchoolDay() && FirstPeriod.contains(CurrentTime());
    }
    bool IsSecondPeriod() const
    {
        return IsSchoolDay() && SecondPeriod.contains(CurrentTime());
    }
    bool IsThirdPeriod() const
    {
        return IsSchoolDay() && ThirdPeriod.contains(CurrentTime());
    }
    bool IsFourthPeriod() const
    {
        return IsSchoolDay() && FourthPeriod.contains(CurrentTime());
    }
    bool IsDetentionTime() const
    {
        return IsSchoolDay() && DetentionTime.contains(CurrentTime());
    }
    int ClassPeriod() const
    {
        if (!IsSchoolDay())
            return -1;

        if (FirstPeriod.contains(CurrentTime()))
            return 0;

        if (SecondPeriod.contains(CurrentTime()))
            return 1;

        if (ThirdPeriod.contains(CurrentTime()))
            return 2;

        if (FourthPeriod.contains(CurrentTime()))
            return 3;

        return -1;
    }
    bool IsStandardWorkTime() const
    {
        return IsSchoolDay() && StandardWorkHours.contains(CurrentTime());
    }
    bool IsEveningWorkTime() const
    {
        return IsSchoolDay() && EveningWorkHours.contains(CurrentTime());
    }
    bool IsWeekendWorkTime() const;
    bool IsSleepTime() const
    {
        return Sleep.contains(CurrentTime());
    }

    gTime(QJsonObject *d = NULL)
    {
        if (d) init(d);
        StudentCount = 1;
        Teachercount = 0;
        CurriculumStart = 0;
        CurMod = 0;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            /*__IF_OBJLIST_FROM_JSON(it, eventexecutelistHigh, VisualEvent)
            else __IF_OBJLIST_FROM_JSON(it, eventexecutelistLow, VisualEvent)
            else*/ __IF_VAR_FROM_JSON_AS(it, StudentCount, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Teachercount, toInt)
            else __IF_VAR_FROM_JSON_AS(it, CurriculumStart, toInt)
            else __IF_VAR_FROM_JSON_AS(it, CurClass, toInt)
            else __IF_VAR_FROM_JSON_AS(it, CurMod, toInt)
            // *INDENT-ON*
        }
    }
    bool IsTimeForClub(Clubs* C)
    {
        if (C && IsSchoolDay() && C->Active) {

            ClubLevel* ccl = C->CurrentClubLevel();
            return ccl && IsTimeBetween(ccl->StartTime, ccl->EndTime);
        }
        return false;
    }
    void CheckGameEnd();
    void UpdatePrincipalStats(int Ticks, double EnergyMod = -1.0);
    /*Task Timerefresh(int Ticks, bool NoEventUpdate = false, double EnergyMod = -1.0)
    {
        VB_StateMachine_70_Timerefresh vB_StateMachine_70_Timerefresh = default(VB_StateMachine_70_Timerefresh);
        vB_StateMachine_70_Timerefresh.SVBSMe = this;
        vB_StateMachine_70_Timerefresh.SVBSLocal_Ticks = Ticks;
        vB_StateMachine_70_Timerefresh.SVBSLocal_NoEventUpdate = NoEventUpdate;
        vB_StateMachine_70_Timerefresh.SVBSLocal_EnergyMod = EnergyMod;
        vB_StateMachine_70_Timerefresh.SState = -1;
        vB_StateMachine_70_Timerefresh.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_70_Timerefresh.SBuilder.Start<VB_StateMachine_70_Timerefresh>(ref vB_StateMachine_70_Timerefresh);
        return vB_StateMachine_70_Timerefresh.SBuilder.Task;
    }
    Task TimerefreshFromEvent(int Ticks, double EnergyMod = -1.0)
    {
        VB_StateMachine_71_TimerefreshFromEvent vB_StateMachine_71_TimerefreshFromEvent = default(VB_StateMachine_71_TimerefreshFromEvent);
        vB_StateMachine_71_TimerefreshFromEvent.SVBSMe = this;
        vB_StateMachine_71_TimerefreshFromEvent.SVBSLocal_Ticks = Ticks;
        vB_StateMachine_71_TimerefreshFromEvent.SVBSLocal_EnergyMod = EnergyMod;
        vB_StateMachine_71_TimerefreshFromEvent.SState = -1;
        vB_StateMachine_71_TimerefreshFromEvent.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_71_TimerefreshFromEvent.SBuilder.Start<VB_StateMachine_71_TimerefreshFromEvent>(ref vB_StateMachine_71_TimerefreshFromEvent);
        return vB_StateMachine_71_TimerefreshFromEvent.SBuilder.Task;
    }*/
    void UpdateRandomWorkspaceAssignments();
    void UpdateOutfitsForTime();
    /*Task CheckEventExecution()
    {
        VB_StateMachine_74_CheckEventExecution vB_StateMachine_74_CheckEventExecution = default(VB_StateMachine_74_CheckEventExecution);
        vB_StateMachine_74_CheckEventExecution.SVBSMe = this;
        vB_StateMachine_74_CheckEventExecution.SState = -1;
        vB_StateMachine_74_CheckEventExecution.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_74_CheckEventExecution.SBuilder.Start<VB_StateMachine_74_CheckEventExecution>(ref vB_StateMachine_74_CheckEventExecution);
        return vB_StateMachine_74_CheckEventExecution.SBuilder.Task;
    }*/
    /*void CheckEventExecution_MT(SortedDictionary<int, QList<VisualEvent>> eventExecuteDict)
    {
        QList<Task<bool>> eventTryTasks = new QList<Task<bool>>();
        // checked {
        // try {
        for (QList<unsigned>::iterator it = Game::HeadTeacher.AttachedEventIDs.begin();
                it != Game::HeadTeacher.AttachedEventIDs.end(); ++it)
        {
            unsigned EvID = enumerator.Current;
            VisualEvent VE = VisualEventManager.PersonAttachedEvents[(int)EvID];
            if (VE.TriggerType == TriggerType.Location)
            {
                eventTryTasks.Add(Task<bool>.Factory.StartNew((_ClosureS__.SI75_0 == NULL) ? (_ClosureS__.SI75_0 = new Func<object, bool>(_ClosureS__.SI._LambdaS__75_0)) : _ClosureS__.SI75_0, VE));
            }
        }
        // }
        // try {
        for (QHash<QString, Person>::iterator it = Game::PlayerLocation.Occupants.Values.begin();
                it != Game::PlayerLocation.Occupants.Values.end(); ++it)
        {
            _ClosureS__75_0 closureS__75_ = new _ClosureS__75_0();
            closureS__75_.SVBSLocal_Person = enumerator2.Current;
            // try {
            for (QList<unsigned>::iterator it2 = closureS__75_.SVBSLocal_Person.AttachedEventIDs.begin();
                    it2 != closureS__75_.SVBSLocal_Person.AttachedEventIDs.end(); ++it2)
            {
                unsigned EvID2 = enumerator3.Current;
                VisualEvent VE2 = VisualEventManager.PersonAttachedEvents[(int)EvID2];
                if (VE2.TriggerType == TriggerType.Location)
                {
                    eventTryTasks.Add(Task<bool>.Factory.StartNew((closureS__75_.SI1 == NULL) ? (closureS__75_.SI1 = ((object obj) => ((VisualEvent)obj).TryEvent(closureS__75_.SVBSLocal_Person))) : closureS__75_.SI1, VE2));
                }
            }
            // }
        }
        // }
        // try {
        for (IEnumerator<Clubs>::iterator it = Game::ListOfClubs.Values.begin();
                it != Game::ListOfClubs.Values.end(); ++it)
        {
            Clubs cl = enumerator4.Current;
            if (cl.Active && cl.CurrentClubLevel() != NULL && cl.ClubRoom == Game::HeadTeacher.CurrentLocation && Game::GameTime.IsTimeForClub(cl))
            {
                // try {
                for (QList<unsigned>::iterator it2 = cl.CurrentClubLevel().ClubEventIDs.begin();
                        it2 != cl.CurrentClubLevel().ClubEventIDs.end(); ++it2)
                {
                    unsigned EvID3 = enumerator5.Current;
                    VisualEvent VE3 = VisualEventManager.ClubEvents[(int)EvID3];
                    if (VE3.TriggerType == TriggerType.Location)
                    {
                        eventTryTasks.Add(Task<bool>.Factory.StartNew(new Func<object, bool>(TryEventTask), VE3));
                    }
                }
                // }
            }
        }
        // }
        if (Game::PlayerLocation.EventIDs.count() > 0)
        {
            int num = Game::PlayerLocation.EventIDs.count() - 1;
            for (int i = 0; i <= num; i++)
            {
                VisualEvent VE4 = VisualEventManager.LocationEvents[(int)Game::PlayerLocation.EventIDs[i]];
                if (VE4.TriggerType == TriggerType.Location)
                {
                    eventTryTasks.Add(Task<bool>.Factory.StartNew(new Func<object, bool>(TryEventTask), VE4));
                }
            }
        }
        // try {
        for (QList<VisualEvent>::iterator it = VisualEventManager.StaticEvents.begin();
                it != VisualEventManager.StaticEvents.end(); ++it)
        {
            VisualEvent VE5 = enumerator6.Current;
            if (VE5.TriggerType == TriggerType.Location)
            {
                eventTryTasks.Add(Task<bool>.Factory.StartNew(new Func<object, bool>(TryEventTask), VE5));
            }
        }
        // }
        Task.WaitAll(eventTryTasks.ToArray(), 30000);
        // try {
        QList<Task<bool>>.Enumerator enumerator7 = eventTryTasks.GetEnumerator();
        while (enumerator7.MoveNext())
        {
            Task<bool> VE6 = enumerator7.Current;
            if (VE6.Result)
            {
                AddToExecuteDict((VisualEvent)VE6.AsyncState, eventExecuteDict);
            }
        }
        // }
        // }
    }*/
    void CheckEventExecution_ST(QMap<int, QList<VisualEvent>> eventExecuteDict);
    /*bool TryEventTask(object obj)
    {
        return ((VisualEvent)obj).TryEvent();
    }
    void AddToExecuteDict(VisualEvent VE, SortedDictionary<int, QList<VisualEvent>> eventExecuteDict)
    {
        if (!eventExecuteDict.ContainsKey(VE.Priority))
        {
            eventExecuteDict.Add(VE.Priority, new QList<VisualEvent>());
        }
        eventExecuteDict[VE.Priority].Insert(Game::RNG.Next(eventExecuteDict[VE.Priority].count()), VE);
    }*/
    /*void PositionSchedule()
    {
        int SchedulingFrequency = MySettingsProperty.Settings.SchedulingFrequency < 1 ? 1 :
                (MySettingsProperty.Settings.SchedulingFrequency > 5 ? 5 : MySettingsProperty.Settings.SchedulingFrequency);

        if (MySettingsProperty.Settings.dbg_DisableMultithreading)
            PositionSchedule_ST(SchedulingFrequency);
        else
            PositionSchedule_MT(SchedulingFrequency);

        CurMod = checked(CurMod + 1) % SchedulingFrequency;
    }*/
    /*void PositionSchedule_MT(int SchedulingFrequency)
    {
        QList<Task> schedulerTasks = new QList<Task>();
        int i = CurMod;
        // checked {
        while (i < Game::DictOfPersonIDs.Values.count())
        {
            if (Game::DictOfPersonIDs.Values.ElementAtOrDefault(i) == Game::HeadTeacher)
            {
                i += SchedulingFrequency;
            }
            else
            {
                Person per = Game::DictOfPersonIDs.Values.ElementAtOrDefault(i);
                schedulerTasks.Add(Task.Factory.StartNew((_ClosureS__.SI81_0 == NULL) ? (_ClosureS__.SI81_0 = new Action<object>(_ClosureS__.SI._LambdaS__81_0)) : _ClosureS__.SI81_0, per));
                i += SchedulingFrequency;
            }
        }
        Task.WaitAll(schedulerTasks.ToArray(), 30000);
        // }
    }*/
    void PositionSchedule_ST(int SchedulingFrequency);
    /*Task StartNextDay()
    {
        VB_StateMachine_83_StartNextDay vB_StateMachine_83_StartNextDay = default(VB_StateMachine_83_StartNextDay);
        vB_StateMachine_83_StartNextDay.SVBSMe = this;
        vB_StateMachine_83_StartNextDay.SState = -1;
        vB_StateMachine_83_StartNextDay.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_83_StartNextDay.SBuilder.Start<VB_StateMachine_83_StartNextDay>(ref vB_StateMachine_83_StartNextDay);
        return vB_StateMachine_83_StartNextDay.SBuilder.Task;
    }
    Task AdjustPersons()
    {
        VB_StateMachine_84_AdjustPersons vB_StateMachine_84_AdjustPersons = default(VB_StateMachine_84_AdjustPersons);
        vB_StateMachine_84_AdjustPersons.SVBSMe = this;
        vB_StateMachine_84_AdjustPersons.SState = -1;
        vB_StateMachine_84_AdjustPersons.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_84_AdjustPersons.SBuilder.Start<VB_StateMachine_84_AdjustPersons>(ref vB_StateMachine_84_AdjustPersons);
        return vB_StateMachine_84_AdjustPersons.SBuilder.Task;
    }
    Task AdjustPersonStats_MT()
    {
        VB_StateMachine_85_AdjustPersonStats_MT vB_StateMachine_85_AdjustPersonStats_MT = default(VB_StateMachine_85_AdjustPersonStats_MT);
        vB_StateMachine_85_AdjustPersonStats_MT.SState = -1;
        vB_StateMachine_85_AdjustPersonStats_MT.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_85_AdjustPersonStats_MT.SBuilder.Start<VB_StateMachine_85_AdjustPersonStats_MT>(ref vB_StateMachine_85_AdjustPersonStats_MT);
        return vB_StateMachine_85_AdjustPersonStats_MT.SBuilder.Task;
    }
    Task AdjustPersonStats_ST()
    {
        VB_StateMachine_86_AdjustPersonStats_ST vB_StateMachine_86_AdjustPersonStats_ST = default(VB_StateMachine_86_AdjustPersonStats_ST);
        vB_StateMachine_86_AdjustPersonStats_ST.SState = -1;
        vB_StateMachine_86_AdjustPersonStats_ST.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_86_AdjustPersonStats_ST.SBuilder.Start<VB_StateMachine_86_AdjustPersonStats_ST>(ref vB_StateMachine_86_AdjustPersonStats_ST);
        return vB_StateMachine_86_AdjustPersonStats_ST.SBuilder.Task;
    }*/
    bool IsTime(int Hour, int Minute) const;
    bool IsTime(TimeData& TD) const;
    bool IsTimeBetween(int Hour1, int Minute1, int Hour2, int Minute2) const;
    bool IsTimeBetween(TimeData& TD1, TimeData& TD2) const;
    /*Task JumpToTime(TimeData TD, ETimePassType Type)
    {
        VB_StateMachine_91_JumpToTime vB_StateMachine_91_JumpToTime = default(VB_StateMachine_91_JumpToTime);
        vB_StateMachine_91_JumpToTime.SVBSLocal_TD = TD;
        vB_StateMachine_91_JumpToTime.SVBSLocal_Type = Type;
        vB_StateMachine_91_JumpToTime.SState = -1;
        vB_StateMachine_91_JumpToTime.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_91_JumpToTime.SBuilder.Start<VB_StateMachine_91_JumpToTime>(ref vB_StateMachine_91_JumpToTime);
        return vB_StateMachine_91_JumpToTime.SBuilder.Task;
    }
    Task PassTime(int Hours, int Minutes, ETimePassType Type)
    {
        VB_StateMachine_92_PassTime vB_StateMachine_92_PassTime = default(VB_StateMachine_92_PassTime);
        vB_StateMachine_92_PassTime.SVBSLocal_Hours = Hours;
        vB_StateMachine_92_PassTime.SVBSLocal_Minutes = Minutes;
        vB_StateMachine_92_PassTime.SVBSLocal_Type = Type;
        vB_StateMachine_92_PassTime.SState = -1;
        vB_StateMachine_92_PassTime.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_92_PassTime.SBuilder.Start<VB_StateMachine_92_PassTime>(ref vB_StateMachine_92_PassTime);
        return vB_StateMachine_92_PassTime.SBuilder.Task;
    }
    bool _LambdaS__70_1(Clubs cl)
    {
        return cl.Active && cl.CurrentClubLevel() != NULL && Hour == cl.CurrentClubLevel().EndTime.Hour && Minute == cl.CurrentClubLevel().EndTime.Minute;
    }
    bool _LambdaS__71_0(Clubs cl)
    {
        return cl.Active && cl.CurrentClubLevel() != NULL && Hour == cl.CurrentClubLevel().EndTime.Hour && Minute == cl.CurrentClubLevel().EndTime.Minute;
    }*/
};

#endif // gTIME_H
