#include "timeframe.h"

QString& TimeFrame::ToString()
{
    return StartTime.ToString() + " - " + EndTime.ToString();
}
