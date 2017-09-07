#ifndef TIMEDATA_H
#define TIMEDATA_H
#include "json_macros.h"
#include <QString>

class TimeData {
public:
    unsigned Hour;
    unsigned Minute;
    const unsigned Ticks() const
    {
        return Hour * 60 + Minute;
    }
    void init(QJsonObject *d)
    {
        Hour = d->value("Hour").toInt();
        Minute = d->value("Minute").toInt();
    }
    TimeData(unsigned Hour = 0, unsigned Minute = 0)
    {
        unsigned tick = Hour * 60 + Minute;
        Hour = tick / 60 > 23 ? 23 : tick / 60;
        Minute = tick % 60 > 59 ? 59 : tick % 60;
    }
    inline bool operator==(const TimeData& other){
        return Ticks() == other.Ticks();
    }
    int CompareTo(const TimeData& other) const
    {
        return Ticks() - other.Ticks();
    }
    QString& ToString();
};

#endif // TIMEDATA_H
