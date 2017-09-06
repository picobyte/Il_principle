#include "timedata.h"

QString& TimeData::ToString() {
    return QString::asprintf("d:%02d", Hour, Minute);
}
