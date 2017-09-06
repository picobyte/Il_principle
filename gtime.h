#ifndef gTIME_H
#define gTIME_H
#include <math.h>
#include <QList>
#include "json_macros.h"
#include "timedata.h"
#include "timeframe.h"
#include "visualevent.h"

class gTime {
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
public:
    static const int MinutesInHour;
    static const int HoursInDay;
    QList<VisualEvent> eventexecutelistHigh;
    QList<VisualEvent> eventexecutelistLow;
    int StudentCount;
    int Teachercount;
    int CurriculumStart;
    int CurClass;
    int CurMod;
    const int Hour() const
    {
        return round(floor(Game.TickCount / 60.0));
    }
    const int Minute() const
    {
        return Game.TickCount % 60;
    }
    const TimeData CurrentTime() const
    {
        return new TimeData(Hour, Minute);
    }
    const int CurrentTimestamp() const
    {
        int CurrentTimestamp;
        if (Game.SchoolCalendar != NULL)
            return checked(Game.SchoolCalendar.CurrentDay * 1440 + Game.TickCount);

        return Game.TickCount;
    }
    const Daylight CheckDaylightTime() const
    {
        TimeData time = CurrentTime;
        Daylight CheckDaylightTime;
        if (time.CompareTo(gTime.SunriseTime) >= 0 && time.CompareTo(gTime.DaylightTime) < 0)
            return Daylight.Sunrise;

        if (time.CompareTo(gTime.DaylightTime) >= 0 && time.CompareTo(gTime.SundownTime) < 0)
            return Daylight.Day;

        if (time.CompareTo(gTime.SundownTime) >= 0 && time.CompareTo(gTime.NightTime) < 0)
            return Daylight.Sunset;

        return Daylight.Night;
    }
    const bool IsSchoolDay() const
    {
        return !Game.SchoolCalendar.IsHoliday && !Game.SchoolCalendar.IsWeekend;
    }
    const bool IsSchoolBreakTime() const
    {
        TimeData time = CurrentTime;
        return IsSchoolTime && !gTime.FirstPeriod.contains(time) && !gTime.SecondPeriod.contains(time) && !gTime.ThirdPeriod.contains(time) && !gTime.FourthPeriod.contains(time);
    }
    const bool IsSchoolTime() const
    {
        return IsSchoolDay && gTime.SchoolTime.contains(CurrentTime);
    }
    const bool IsLunchBreak() const
    {
        return gTime.Lunch.contains(CurrentTime);
    }
    const bool IsFirstPeriod() const
    {
        return IsSchoolDay && gTime.FirstPeriod.contains(CurrentTime);
    }
    const bool IsSecondPeriod() const
    {
        return IsSchoolDay && gTime.SecondPeriod.contains(CurrentTime);
    }
    const bool IsThirdPeriod() const
    {
        return IsSchoolDay && gTime.ThirdPeriod.contains(CurrentTime);
    }
    const bool IsFourthPeriod() const
    {
        return IsSchoolDay && gTime.FourthPeriod.contains(CurrentTime);
    }
    const bool IsDetentionTime() const
    {
        return IsSchoolDay && gTime.DetentionTime.contains(CurrentTime);
    }
    const int ClassPeriod() const
    {
        int ClassPeriod;
        if (!IsSchoolDay)
            return -1;

        if (gTime.FirstPeriod.contains(CurrentTime))
            return 0;

        if (gTime.SecondPeriod.contains(CurrentTime))
            return 1;

        if (gTime.ThirdPeriod.contains(CurrentTime))
            return 2;

        if (gTime.FourthPeriod.contains(CurrentTime))
            return 3;

        return -1;
    }
    const bool IsStandardWorkTime() const
    {
        return IsSchoolDay && gTime.StandardWorkHours.contains(CurrentTime);
    }
    const bool IsEveningWorkTime() const
    {
        return IsSchoolDay && gTime.EveningWorkHours.contains(CurrentTime);
    }
    const bool IsWeekendWorkTime() const
    {
        return !Game.SchoolCalendar.IsHoliday && Game.SchoolCalendar.IsWeekend && gTime.WeekendWorkHours.contains(CurrentTime);
    }
    const bool IsSleepTime() const
    {
        return gTime.Sleep.contains(CurrentTime);
    }

    gTime(QJsonObject *d = NULL)
    {
        if (d) init(d);
        eventexecutelistHigh = new QList<VisualEvent>();
        eventexecutelistLow = new QList<VisualEvent>();
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
    bool IsTimeForClub(Clubs C)
    {
        return IsSchoolDay && C != NULL && C.Active && C.CurrentClubLevel != NULL && gTime.IsTimeBetween(C.CurrentClubLevel.StartTime, C.CurrentClubLevel.EndTime);
    }
    void CheckGameEnd()
    {
        if (Game.TheSchool.Reputation <= 0.0 || DateTime.Compare(Game.SchoolCalendar.TodayDate, GameCalendar.MaxDate) > 0)
        {
            GameplayManager.EndGame();
        }
    }
    void UpdatePrincipalStats(int Ticks, double EnergyMod = -1.0)
    {
        if (EnergyMod > 0.0)
        {
            Game.HeadTeacher.AddStat("Energy", (double)Ticks * EnergyMod * ((100.0 + Game.HeadTeacher.GetStat("Stamina")) * 0.005));
        }
        else
        {
            Game.HeadTeacher.AddStat("Energy", ((double)Ticks - (double)Ticks * (Game.HeadTeacher.GetStat("Stamina") * 0.002)) * EnergyMod);
        }
        Game.HeadTeacher.AddStat("Arousal", (double)(checked(0 - Ticks)) / 10000.0);
        FormManager.GameForm.RefreshSchoolInfo(true);
    }
    /*Task Timerefresh(int Ticks, bool NoEventUpdate = false, double EnergyMod = -1.0)
    {
        gTime.VB_StateMachine_70_Timerefresh vB_StateMachine_70_Timerefresh = default(gTime.VB_StateMachine_70_Timerefresh);
        vB_StateMachine_70_Timerefresh.SVBSMe = this;
        vB_StateMachine_70_Timerefresh.SVBSLocal_Ticks = Ticks;
        vB_StateMachine_70_Timerefresh.SVBSLocal_NoEventUpdate = NoEventUpdate;
        vB_StateMachine_70_Timerefresh.SVBSLocal_EnergyMod = EnergyMod;
        vB_StateMachine_70_Timerefresh.SState = -1;
        vB_StateMachine_70_Timerefresh.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_70_Timerefresh.SBuilder.Start<gTime.VB_StateMachine_70_Timerefresh>(ref vB_StateMachine_70_Timerefresh);
        return vB_StateMachine_70_Timerefresh.SBuilder.Task;
    }
    Task TimerefreshFromEvent(int Ticks, double EnergyMod = -1.0)
    {
        gTime.VB_StateMachine_71_TimerefreshFromEvent vB_StateMachine_71_TimerefreshFromEvent = default(gTime.VB_StateMachine_71_TimerefreshFromEvent);
        vB_StateMachine_71_TimerefreshFromEvent.SVBSMe = this;
        vB_StateMachine_71_TimerefreshFromEvent.SVBSLocal_Ticks = Ticks;
        vB_StateMachine_71_TimerefreshFromEvent.SVBSLocal_EnergyMod = EnergyMod;
        vB_StateMachine_71_TimerefreshFromEvent.SState = -1;
        vB_StateMachine_71_TimerefreshFromEvent.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_71_TimerefreshFromEvent.SBuilder.Start<gTime.VB_StateMachine_71_TimerefreshFromEvent>(ref vB_StateMachine_71_TimerefreshFromEvent);
        return vB_StateMachine_71_TimerefreshFromEvent.SBuilder.Task;
    }*/
    void UpdateRandomWorkspaceAssignments()
    {
        if (Game.TheSchool.ListOfWorkplaces.count() > 0)
        {
            Location wp = Game.TheSchool.ListOfWorkplaces[Game.RNG.Next(Game.TheSchool.ListOfWorkplaces.count())];
            if (!wp.Name.Equals("General Job"))
            {
                // try {
                IEnumerator<LocationJobDetails> enumerator = wp.AssociatedJobs.Where((gTime._ClosureS__.SI72_0 == NULL) ? (gTime._ClosureS__.SI72_0 = new Func<LocationJobDetails, bool>(gTime._ClosureS__.SI._LambdaS__72_0)) : gTime._ClosureS__.SI72_0).GetEnumerator();
                while (enumerator.MoveNext())
                {
                    gTime._ClosureS__72_0 closureS__72_ = new gTime._ClosureS__72_0();
                    closureS__72_.SVBSLocal_job = enumerator.Current;
                    QList<Person> matchingEmployees = (from per in Game.UnemployedPersons.Values
                                                      where QString.Equals(per.Job, closureS__72_.SVBSLocal_job.JobTitle)
                                                      select per).ToList<Person>();
                    while (!closureS__72_.SVBSLocal_job.IsFullyStaffed())
                    {
                        if (matchingEmployees.count() == 0)
                        {
                            break;
                        }
                        Person per2 = matchingEmployees[Game.RNG.Next(matchingEmployees.count())];
                        per2.AssignWork(wp, closureS__72_.SVBSLocal_job);
                        matchingEmployees.Remove(per2);
                    }
                    while (!closureS__72_.SVBSLocal_job.IsFullyStaffed() && Game.UnemployedPersons.count() != 0)
                    {
                        Game.UnemployedPersons.Values.ElementAtOrDefault(Game.RNG.Next(Game.UnemployedPersons.count())).AssignWork(wp, closureS__72_.SVBSLocal_job);
                    }
                }
                // }
            }
        }
    }
    void UpdateOutfitsForTime()
    {
        TimeData curTime = CurrentTime;
        if (gTime.Sleep.StartTime.Equals(curTime))
        {
            // try {
            IEnumerator<Person> enumerator = Game.DictOfPersonNames.Values.Where((gTime._ClosureS__.SI73_0 == NULL) ? (gTime._ClosureS__.SI73_0 = new Func<Person, bool>(gTime._ClosureS__.SI._LambdaS__73_0)) : gTime._ClosureS__.SI73_0).GetEnumerator();
            while (enumerator.MoveNext())
            {
                enumerator.Current.UpdateOutfitLevel();
            }
            return;
            // }
        }
        if (gTime.Sleep.EndTime.Equals(curTime))
        {
            // try {
            IEnumerator<Person> enumerator2 = Game.DictOfPersonNames.Values.Where((gTime._ClosureS__.SI73_1 == NULL) ? (gTime._ClosureS__.SI73_1 = new Func<Person, bool>(gTime._ClosureS__.SI._LambdaS__73_1)) : gTime._ClosureS__.SI73_1).GetEnumerator();
            while (enumerator2.MoveNext())
            {
                enumerator2.Current.UpdateOutfitLevel();
            }
            // }
        }
    }
    /*Task CheckEventExecution()
    {
        gTime.VB_StateMachine_74_CheckEventExecution vB_StateMachine_74_CheckEventExecution = default(gTime.VB_StateMachine_74_CheckEventExecution);
        vB_StateMachine_74_CheckEventExecution.SVBSMe = this;
        vB_StateMachine_74_CheckEventExecution.SState = -1;
        vB_StateMachine_74_CheckEventExecution.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_74_CheckEventExecution.SBuilder.Start<gTime.VB_StateMachine_74_CheckEventExecution>(ref vB_StateMachine_74_CheckEventExecution);
        return vB_StateMachine_74_CheckEventExecution.SBuilder.Task;
    }*/
    /*void CheckEventExecution_MT(SortedDictionary<int, QList<VisualEvent>> eventExecuteDict)
    {
        QList<Task<bool>> eventTryTasks = new QList<Task<bool>>();
        // checked {
        // try {
        for (QList<unsigned>::iterator it = Game.HeadTeacher.AttachedEventIDs.begin();
                it != Game.HeadTeacher.AttachedEventIDs.end(); ++it)
        {
            unsigned EvID = enumerator.Current;
            VisualEvent VE = VisualEventManager.PersonAttachedEvents[(int)EvID];
            if (VE.TriggerType == TriggerType.Location)
            {
                eventTryTasks.Add(Task<bool>.Factory.StartNew((gTime._ClosureS__.SI75_0 == NULL) ? (gTime._ClosureS__.SI75_0 = new Func<object, bool>(gTime._ClosureS__.SI._LambdaS__75_0)) : gTime._ClosureS__.SI75_0, VE));
            }
        }
        // }
        // try {
        for (QHash<QString, Person>::iterator it = Game.PlayerLocation.Occupants.Values.begin();
                it != Game.PlayerLocation.Occupants.Values.end(); ++it)
        {
            gTime._ClosureS__75_0 closureS__75_ = new gTime._ClosureS__75_0();
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
        for (IEnumerator<Clubs>::iterator it = Game.ListOfClubs.Values.begin();
                it != Game.ListOfClubs.Values.end(); ++it)
        {
            Clubs cl = enumerator4.Current;
            if (cl.Active && cl.CurrentClubLevel != NULL && cl.ClubRoom == Game.HeadTeacher.CurrentLocation && Game.GameTime.IsTimeForClub(cl))
            {
                // try {
                for (QList<unsigned>::iterator it2 = cl.CurrentClubLevel.ClubEventIDs.begin();
                        it2 != cl.CurrentClubLevel.ClubEventIDs.end(); ++it2)
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
        if (Game.PlayerLocation.EventIDs.count() > 0)
        {
            int num = Game.PlayerLocation.EventIDs.count() - 1;
            for (int i = 0; i <= num; i++)
            {
                VisualEvent VE4 = VisualEventManager.LocationEvents[(int)Game.PlayerLocation.EventIDs[i]];
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
    void CheckEventExecution_ST(SortedDictionary<int, QList<VisualEvent>> eventExecuteDict)
    {
        // checked {
        // try {
        for (QList<unsigned>::iterator it = Game.HeadTeacher.AttachedEventIDs.begin();
                it != Game.HeadTeacher.AttachedEventIDs.end(); ++it)
        {
            unsigned EvID = enumerator.Current;
            VisualEvent VE = VisualEventManager.PersonAttachedEvents[(int)EvID];
            if (VE.TriggerType == TriggerType.Location && VE.TryEvent(Game.HeadTeacher))
            {
                AddToExecuteDict(VE, eventExecuteDict);
            }
        }
        // }
        // try {
        for (QHash<QString, Person>::iterator it = Game.PlayerLocation.Occupants.Values.begin();
                it != Game.PlayerLocation.Occupants.Values.end(); ++it)
        {
            Person Person = enumerator2.Current;
            // try {
            for (QList<unsigned>::iterator it2 = Person.AttachedEventIDs.begin();
                    it2 != Person.AttachedEventIDs.end(); ++it2)
            {
                unsigned EvID2 = enumerator3.Current;
                VisualEvent VE2 = VisualEventManager.PersonAttachedEvents[(int)EvID2];
                if (VE2.TriggerType == TriggerType.Location && VE2.TryEvent(Person))
                {
                    AddToExecuteDict(VE2, eventExecuteDict);
                }
            }
            // }
        }
        // }
        // try {
        for (IEnumerator<Clubs>::iterator it = Game.ListOfClubs.Values.begin();
                it != Game.ListOfClubs.Values.end(); ++it)
        {
            Clubs cl = enumerator4.Current;
            if (cl != NULL && cl.CurrentClubLevel != NULL && cl.ClubRoom == Game.HeadTeacher.CurrentLocation && Game.GameTime.IsTimeForClub(cl))
            {
                // try {
                for (QList<unsigned>::iterator it2 = cl.CurrentClubLevel.ClubEventIDs.begin();
                        it2 != cl.CurrentClubLevel.ClubEventIDs.end(); ++it2)
                {
                    unsigned EvID3 = enumerator5.Current;
                    VisualEvent VE3 = VisualEventManager.ClubEvents[(int)EvID3];
                    if (VE3.TriggerType == TriggerType.Location && VE3.TryEvent())
                    {
                        AddToExecuteDict(VE3, eventExecuteDict);
                    }
                }
                // }
            }
        }
        // }
        if (Game.PlayerLocation.EventIDs.count() > 0)
        {
            int num = Game.PlayerLocation.EventIDs.count() - 1;
            for (int i = 0; i <= num; i++)
            {
                VisualEvent VE4 = VisualEventManager.LocationEvents[(int)Game.PlayerLocation.EventIDs[i]];
                if (VE4.TriggerType == TriggerType.Location && VE4.TryEvent())
                {
                    AddToExecuteDict(VE4, eventExecuteDict);
                }
            }
        }
        // try {
        for (QList<VisualEvent>::iterator it = VisualEventManager.StaticEvents.begin();
                it != VisualEventManager.StaticEvents.end(); ++it)
        {
            VisualEvent VE5 = enumerator6.Current;
            if (VE5.TriggerType == TriggerType.Location && VE5.TryEvent())
            {
                AddToExecuteDict(VE5, eventExecuteDict);
            }
        }
        // }
        // }
    }
    bool TryEventTask(object obj)
    {
        return ((VisualEvent)obj).TryEvent();
    }
    void AddToExecuteDict(VisualEvent VE, SortedDictionary<int, QList<VisualEvent>> eventExecuteDict)
    {
        if (!eventExecuteDict.ContainsKey(VE.Priority))
        {
            eventExecuteDict.Add(VE.Priority, new QList<VisualEvent>());
        }
        eventExecuteDict[VE.Priority].Insert(Game.RNG.Next(eventExecuteDict[VE.Priority].count()), VE);
    }
    void PositionSchedule()
    {
        int SchedulingFrequency = MySettingsProperty.Settings.SchedulingFrequency < 1 ? 1 : (MySettingsProperty.Settings.SchedulingFrequency > 5 ? 5 : MySettingsProperty.Settings.SchedulingFrequency);
        if (MySettingsProperty.Settings.dbg_DisableMultithreading)
        {
            PositionSchedule_ST(SchedulingFrequency);
        }
        else
        {
            PositionSchedule_MT(SchedulingFrequency);
        }
        CurMod = checked(CurMod + 1) % SchedulingFrequency;
    }
    /*void PositionSchedule_MT(int SchedulingFrequency)
    {
        QList<Task> schedulerTasks = new QList<Task>();
        int i = CurMod;
        // checked {
        while (i < Game.DictOfPersonIDs.Values.count())
        {
            if (Game.DictOfPersonIDs.Values.ElementAtOrDefault(i) == Game.HeadTeacher)
            {
                i += SchedulingFrequency;
            }
            else
            {
                Person per = Game.DictOfPersonIDs.Values.ElementAtOrDefault(i);
                schedulerTasks.Add(Task.Factory.StartNew((gTime._ClosureS__.SI81_0 == NULL) ? (gTime._ClosureS__.SI81_0 = new Action<object>(gTime._ClosureS__.SI._LambdaS__81_0)) : gTime._ClosureS__.SI81_0, per));
                i += SchedulingFrequency;
            }
        }
        Task.WaitAll(schedulerTasks.ToArray(), 30000);
        // }
    }*/
    void PositionSchedule_ST(int SchedulingFrequency)
    {
        int i = CurMod;
        // checked {
        while (i < Game.DictOfPersonIDs.Values.count())
        {
            if (Game.DictOfPersonIDs.Values.ElementAtOrDefault(i) == Game.HeadTeacher)
            {
                i += SchedulingFrequency;
            }
            else
            {
                Person per = Game.DictOfPersonIDs.Values.ElementAtOrDefault(i);
                // try {
                int Best = -2147483648;
                PersonScheduleHandler BestHandler = NULL;
                // try {
                for (QList<PersonScheduleHandler>::iterator it = Game.ListOfScheduleHandlers.begin();
                        it != Game.ListOfScheduleHandlers.end(); ++it)
                {
                    PersonScheduleHandler Handler = enumerator.Current;
                    if (Handler.Priority > Best && Handler.IsApplicableFor(per))
                    {
                        BestHandler = Handler;
                        Best = Handler.Priority;
                    }
                }
                // }
                if (BestHandler != NULL)
                {
                    BestHandler.UpdateLocationFor(per);
                }
                // }
                catch (Exception expr_A0)
                {
                    ProjectData.SetProjectError(expr_A0);
                    Exception ex = expr_A0;
                    ExceptionHandler.HandleException(ex);
                    ProjectData.ClearProjectError();
                }
                i += SchedulingFrequency;
            }
        }
        // }
    }
    /*Task StartNextDay()
    {
        gTime.VB_StateMachine_83_StartNextDay vB_StateMachine_83_StartNextDay = default(gTime.VB_StateMachine_83_StartNextDay);
        vB_StateMachine_83_StartNextDay.SVBSMe = this;
        vB_StateMachine_83_StartNextDay.SState = -1;
        vB_StateMachine_83_StartNextDay.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_83_StartNextDay.SBuilder.Start<gTime.VB_StateMachine_83_StartNextDay>(ref vB_StateMachine_83_StartNextDay);
        return vB_StateMachine_83_StartNextDay.SBuilder.Task;
    }
    Task AdjustPersons()
    {
        gTime.VB_StateMachine_84_AdjustPersons vB_StateMachine_84_AdjustPersons = default(gTime.VB_StateMachine_84_AdjustPersons);
        vB_StateMachine_84_AdjustPersons.SVBSMe = this;
        vB_StateMachine_84_AdjustPersons.SState = -1;
        vB_StateMachine_84_AdjustPersons.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_84_AdjustPersons.SBuilder.Start<gTime.VB_StateMachine_84_AdjustPersons>(ref vB_StateMachine_84_AdjustPersons);
        return vB_StateMachine_84_AdjustPersons.SBuilder.Task;
    }
    Task AdjustPersonStats_MT()
    {
        gTime.VB_StateMachine_85_AdjustPersonStats_MT vB_StateMachine_85_AdjustPersonStats_MT = default(gTime.VB_StateMachine_85_AdjustPersonStats_MT);
        vB_StateMachine_85_AdjustPersonStats_MT.SState = -1;
        vB_StateMachine_85_AdjustPersonStats_MT.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_85_AdjustPersonStats_MT.SBuilder.Start<gTime.VB_StateMachine_85_AdjustPersonStats_MT>(ref vB_StateMachine_85_AdjustPersonStats_MT);
        return vB_StateMachine_85_AdjustPersonStats_MT.SBuilder.Task;
    }
    Task AdjustPersonStats_ST()
    {
        gTime.VB_StateMachine_86_AdjustPersonStats_ST vB_StateMachine_86_AdjustPersonStats_ST = default(gTime.VB_StateMachine_86_AdjustPersonStats_ST);
        vB_StateMachine_86_AdjustPersonStats_ST.SState = -1;
        vB_StateMachine_86_AdjustPersonStats_ST.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_86_AdjustPersonStats_ST.SBuilder.Start<gTime.VB_StateMachine_86_AdjustPersonStats_ST>(ref vB_StateMachine_86_AdjustPersonStats_ST);
        return vB_StateMachine_86_AdjustPersonStats_ST.SBuilder.Task;
    }*/
    bool IsTime(int Hour, int Minute)
    {
        return Game.GameTime.Hour == Hour && Game.GameTime.Minute == Minute;
    }
    bool IsTime(TimeData TD)
    {
        return Game.GameTime.Hour == TD.Hour && Game.GameTime.Minute == TD.Minute;
    }
    bool IsTimeBetween(int Hour1, int Minute1, int Hour2, int Minute2)
    {
        // checked {
        int TickStart = Hour1 * 60 + Minute1;
        int TickStop = Hour2 * 60 + Minute2;
        bool IsTimeBetween;
        if (TickStart <= TickStop)
            return (Game.TickCount >= TickStart && Game.TickCount <= TickStop);

        return (Game.TickCount >= TickStart || Game.TickCount <= TickStop);
        // }
    }
    bool IsTimeBetween(TimeData TD1, TimeData TD2)
    {
        // checked {
        int TickStart = TD1.Hour * 60 + TD1.Minute;
        int TickStop = TD2.Hour * 60 + TD2.Minute;
        bool IsTimeBetween;
        if (TickStart <= TickStop)
            return (Game.TickCount >= TickStart && Game.TickCount <= TickStop);

        return (Game.TickCount >= TickStart || Game.TickCount <= TickStop);
        // }
    }
    /*Task JumpToTime(TimeData TD, ETimePassType Type)
    {
        gTime.VB_StateMachine_91_JumpToTime vB_StateMachine_91_JumpToTime = default(gTime.VB_StateMachine_91_JumpToTime);
        vB_StateMachine_91_JumpToTime.SVBSLocal_TD = TD;
        vB_StateMachine_91_JumpToTime.SVBSLocal_Type = Type;
        vB_StateMachine_91_JumpToTime.SState = -1;
        vB_StateMachine_91_JumpToTime.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_91_JumpToTime.SBuilder.Start<gTime.VB_StateMachine_91_JumpToTime>(ref vB_StateMachine_91_JumpToTime);
        return vB_StateMachine_91_JumpToTime.SBuilder.Task;
    }
    Task PassTime(int Hours, int Minutes, ETimePassType Type)
    {
        gTime.VB_StateMachine_92_PassTime vB_StateMachine_92_PassTime = default(gTime.VB_StateMachine_92_PassTime);
        vB_StateMachine_92_PassTime.SVBSLocal_Hours = Hours;
        vB_StateMachine_92_PassTime.SVBSLocal_Minutes = Minutes;
        vB_StateMachine_92_PassTime.SVBSLocal_Type = Type;
        vB_StateMachine_92_PassTime.SState = -1;
        vB_StateMachine_92_PassTime.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_92_PassTime.SBuilder.Start<gTime.VB_StateMachine_92_PassTime>(ref vB_StateMachine_92_PassTime);
        return vB_StateMachine_92_PassTime.SBuilder.Task;
    }
    bool _LambdaS__70_1(Clubs cl)
    {
        return cl.Active && cl.CurrentClubLevel != NULL && Hour == cl.CurrentClubLevel.EndTime.Hour && Minute == cl.CurrentClubLevel.EndTime.Minute;
    }
    bool _LambdaS__71_0(Clubs cl)
    {
        return cl.Active && cl.CurrentClubLevel != NULL && Hour == cl.CurrentClubLevel.EndTime.Hour && Minute == cl.CurrentClubLevel.EndTime.Minute;
    }*/
};

#endif // gTIME_H
