#include "game.h"
#include "gtime.h"

const TimeFrame gTime::SchoolTime = TimeFrame(7, 50, 16, 0);
const TimeFrame gTime::FirstPeriod = TimeFrame(7, 50, 9, 20);
const TimeFrame gTime::SecondPeriod = TimeFrame(9, 40, 11, 10);
const TimeFrame gTime::ThirdPeriod = TimeFrame(11, 30, 13, 0);
const TimeFrame gTime::FourthPeriod = TimeFrame(14, 30, 16, 0);
const TimeFrame gTime::DetentionTime = TimeFrame(16, 0, 18, 0);
const TimeFrame gTime::StandardWorkHours = TimeFrame(8, 0, 16, 0);
const TimeFrame gTime::EveningWorkHours = TimeFrame(16, 0, 20, 0);
const TimeFrame gTime::WeekendWorkHours = TimeFrame(9, 0, 17, 0);
const TimeFrame gTime::Lunch = TimeFrame(13, 5, 14, 25);
const TimeFrame gTime::Sleep = TimeFrame(23, 0, 6, 30);
const TimeData gTime::SunriseTime = TimeData(6, 0);
const TimeData gTime::DaylightTime = TimeData(8, 0);
const TimeData gTime::SundownTime = TimeData(20, 0);
const TimeData gTime::NightTime = TimeData(22, 0);

const int gTime::MinutesInHour = 60;
const int gTime::HoursInDay = 24;


int gTime::Hour() const
{
    return round(floor(Game::TickCount / 60.0));
}
int gTime::Minute() const
{
    return Game::TickCount % 60;
}

const int gTime::CurrentTimestamp() const
{
    if (Game::SchoolCalendar != NULL)
        return checked(Game::SchoolCalendar.CurrentDay * 1440 + Game::TickCount);

    return Game::TickCount;
}

const bool gTime::IsSchoolDay() const
{
    return !Game::SchoolCalendar.IsHoliday && !Game::SchoolCalendar.IsWeekend;
}

bool gTime::IsWeekendWorkTime() const
{
    return !Game::SchoolCalendar.IsHoliday() && Game::SchoolCalendar.IsWeekend() && WeekendWorkHours.contains(CurrentTime());
}

void gTime::CheckGameEnd()
{
    if (Game::TheSchool.Reputation <= 0.0 || DateTime.Compare(Game::SchoolCalendar.TodayDate, GameCalendar.MaxDate) > 0)
    {
        GameplayManager.EndGame();
    }
}

void gTime::UpdatePrincipalStats(int Ticks, double EnergyMod)
{
    if (EnergyMod > 0.0)
        Game::HeadTeacher.AddStat("Energy", (double)Ticks * EnergyMod * ((100.0 + Game::HeadTeacher.GetStat("Stamina")) * 0.005));
    else
        Game::HeadTeacher.AddStat("Energy", ((double)Ticks - (double)Ticks * (Game::HeadTeacher.GetStat("Stamina") * 0.002)) * EnergyMod);

    Game::HeadTeacher.AddStat("Arousal", (double)(checked(0 - Ticks)) / 10000.0);
    FormManager.GameForm.RefreshSchoolInfo(true);
}

void gTime::UpdateRandomWorkspaceAssignments()
{
    if (Game::TheSchool.ListOfWorkplaces.count() > 0)
    {
        Location wp = Game::TheSchool.ListOfWorkplaces[Game::RNG.Next(Game::TheSchool.ListOfWorkplaces.count())];
        if (!wp.Name.Equals("General Job"))
        {
            // try {
            IEnumerator<LocationJobDetails> enumerator = wp.AssociatedJobs.Where((_ClosureS__.SI72_0 == NULL) ? (_ClosureS__.SI72_0 = new Func<LocationJobDetails, bool>(_ClosureS__.SI._LambdaS__72_0)) : _ClosureS__.SI72_0).GetEnumerator();
            while (enumerator.MoveNext())
            {
                _ClosureS__72_0 closureS__72_ = new _ClosureS__72_0();
                closureS__72_.SVBSLocal_job = enumerator.Current;
                QList<Person> matchingEmployees = (from per in Game::UnemployedPersons.Values
                                                  where QString.Equals(per.Job, closureS__72_.SVBSLocal_job.JobTitle)
                                                  select per).ToList<Person>();
                while (!closureS__72_.SVBSLocal_job.IsFullyStaffed())
                {
                    if (matchingEmployees.count() == 0)
                    {
                        break;
                    }
                    Person per2 = matchingEmployees[Game::RNG.Next(matchingEmployees.count())];
                    per2.AssignWork(wp, closureS__72_.SVBSLocal_job);
                    matchingEmployees.Remove(per2);
                }
                while (!closureS__72_.SVBSLocal_job.IsFullyStaffed() && Game::UnemployedPersons.count() != 0)
                {
                    Game::UnemployedPersons.Values.ElementAtOrDefault(Game::RNG.Next(Game::UnemployedPersons.count())).AssignWork(wp, closureS__72_.SVBSLocal_job);
                }
            }
            // }
        }
    }
}
void gTime::UpdateOutfitsForTime()
{
    TimeData curTime = CurrentTime;
    if (Sleep.StartTime.Equals(curTime))
    {
        // try {
        IEnumerator<Person> enumerator = Game::DictOfPersonNames.Values.Where((_ClosureS__.SI73_0 == NULL) ? (_ClosureS__.SI73_0 = new Func<Person, bool>(_ClosureS__.SI._LambdaS__73_0)) : _ClosureS__.SI73_0).GetEnumerator();
        while (enumerator.MoveNext())
        {
            enumerator.Current.UpdateOutfitLevel();
        }
        return;
        // }
    }
    if (Sleep.EndTime.Equals(curTime))
    {
        // try {
        IEnumerator<Person> enumerator2 = Game::DictOfPersonNames.Values.Where((_ClosureS__.SI73_1 == NULL) ? (_ClosureS__.SI73_1 = new Func<Person, bool>(_ClosureS__.SI._LambdaS__73_1)) : _ClosureS__.SI73_1).GetEnumerator();
        while (enumerator2.MoveNext())
        {
            enumerator2.Current.UpdateOutfitLevel();
        }
        // }
    }
}

void CheckEventExecution_ST(QMap<int, QList<VisualEvent>> eventExecuteDict)
{
    // checked {
    // try {
    for (QList<unsigned>::iterator it = Game::HeadTeacher.AttachedEventIDs.begin();
            it != Game::HeadTeacher.AttachedEventIDs.end(); ++it)
    {
        unsigned EvID = enumerator.Current;
        VisualEvent VE = VisualEventManager.PersonAttachedEvents[(int)EvID];
        if (VE.TriggerType == TriggerType.Location && VE.TryEvent(Game::HeadTeacher))
        {
            AddToExecuteDict(VE, eventExecuteDict);
        }
    }
    // }
    // try {
    for (QHash<QString, Person>::iterator it = Game::PlayerLocation.Occupants.Values.begin();
            it != Game::PlayerLocation.Occupants.Values.end(); ++it)
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
    for (IEnumerator<Clubs>::iterator it = Game::ListOfClubs.Values.begin();
            it != Game::ListOfClubs.Values.end(); ++it)
    {
        Clubs cl = enumerator4.Current;
        if (cl != NULL && cl.CurrentClubLevel() != NULL && cl.ClubRoom == Game::HeadTeacher.CurrentLocation && Game::GameTime.IsTimeForClub(cl))
        {
            // try {
            for (QList<unsigned>::iterator it2 = cl.CurrentClubLevel().ClubEventIDs.begin();
                    it2 != cl.CurrentClubLevel().ClubEventIDs.end(); ++it2)
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
    if (Game::PlayerLocation.EventIDs.count() > 0)
    {
        int num = Game::PlayerLocation.EventIDs.count() - 1;
        for (int i = 0; i <= num; i++)
        {
            VisualEvent VE4 = VisualEventManager.LocationEvents[(int)Game::PlayerLocation.EventIDs[i]];
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

void PositionSchedule_ST(int SchedulingFrequency)
{
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
            // try {
            int Best = -2147483648;
            PersonScheduleHandler BestHandler = NULL;
            // try {
            for (QList<PersonScheduleHandler>::iterator it = Game::ListOfScheduleHandlers.begin();
                    it != Game::ListOfScheduleHandlers.end(); ++it)
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

bool IsTime(int Hour, int Minute)
{
    return Game::GameTime.Hour == Hour && Game::GameTime.Minute == Minute;
}
bool IsTime(TimeData& TD) const
{
    return Game::GameTime.Hour == TD.Hour && Game::GameTime.Minute == TD.Minute;
}
bool IsTimeBetween(int Hour1, int Minute1, int Hour2, int Minute2) const
{
    // checked {
    int TickStart = Hour1 * 60 + Minute1;
    int TickStop = Hour2 * 60 + Minute2;

    if (TickStart <= TickStop)
        return (Game::TickCount >= TickStart && Game::TickCount <= TickStop);

    return (Game::TickCount >= TickStart || Game::TickCount <= TickStop);
    // }
}
bool IsTimeBetween(TimeData& TD1, TimeData& TD2) const
{
    // checked {
    int TickStart = TD1.Hour * 60 + TD1.Minute;
    int TickStop = TD2.Hour * 60 + TD2.Minute;

    if (TickStart <= TickStop)
        return (Game::TickCount >= TickStart && Game::TickCount <= TickStop);

    return (Game::TickCount >= TickStart || Game::TickCount <= TickStop);
    // }
}
