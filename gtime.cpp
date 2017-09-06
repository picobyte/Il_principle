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
