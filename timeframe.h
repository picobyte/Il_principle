#ifndef TIMEFRAME_H
#define TIMEFRAME_H
#include "json_macros.h"
#include "timedata.h"

class TimeFrame {
public:
    TimeData StartTime;
    TimeData EndTime;

    TimeFrame(TimeData start, TimeData end): TimeFrame(start.Hour, start.Minute, end.Hour, end.Minute) {}
    TimeFrame(int StartHour, int StartMinute, int EndHour, int EndMinute):
        StartTime(StartHour, StartMinute), EndTime(EndHour, EndMinute) {}
    bool contains(const TimeData time) const
    {
        int timeTicks = time.Ticks();
        int startTicks = StartTime.Ticks();
        int endTicks = EndTime.Ticks();
        bool Contains;
        if (startTicks > endTicks)
            return (timeTicks >= startTicks || timeTicks < endTicks);

        return (timeTicks >= startTicks && timeTicks < endTicks);
    }
    bool Contains(int hr, int mn) const
    {
        return contains(TimeData(hr, mn));
    }
    QString& ToString();
};

#endif // TIMEFRAME_H
