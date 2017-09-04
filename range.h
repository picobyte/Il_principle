#ifndef RANGE_H
#define RANGE_H
#include "json_macros.h"

class Range {
public:
    double Min;
    double Max;
    double AddValueWithinRange(double BaseValue, double AddValue)
    {
        double NewValue = BaseValue + AddValue;
        if (AddValue == 0.0)
            return BaseValue;

        if (WithinRange(NewValue))
            return NewValue;

        if (WithinRange(BaseValue))
            return AddValue > 0.0 ? Max : Min;

        if (AddValue > 0.0)
            return BaseValue < Min ? NewValue : BaseValue;

        return BaseValue > Max ? NewValue : BaseValue;
    }
    bool WithinRange(double Value)
    {
        return Value >= Min && Value <= Max;
    }

    Range(const Range& rhs)
    {
        Min = rhs.Min;
        Max = rhs.Max;
    }
    Range& operator=(Range& rhs)
    {
        rhs.Min = Min;
        rhs.Max = Max;
        return rhs;
    }

    Range(QJsonObject *d = NULL)
    {
        if (d) init(d);

    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, Min, toDouble)
            else __IF_VAR_FROM_JSON_AS(it, Max, toDouble)
            // *INDENT-ON*
        }
    }
};
#endif // RANGE_H
