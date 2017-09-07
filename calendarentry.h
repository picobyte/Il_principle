#ifndef CALENDARENTRY_H
#define CALENDARENTRY_H
#include <QDateTime>
#include "json_macros.h"

class CalendarEntry {
public:
    QString Name;
    QDateTime ApplyDate;
    QString Text;
    CalendarEntryStatus Status;
    const QString DisplayDate() const
    {
        return ApplyDate.toString(Qt::DefaultLocaleShortDate);
    }

    CalendarEntry(QJsonObject *d = NULL)
    {
        if (d) init(d);
        Name = "";
        Text = "";
        Status = CalendarEntryStatus::Standard;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_OBJ_FROM_JSON(it, ApplyDate)
            else __IF_VAR_FROM_JSON_AS(it, Text, toString)
            else __IF_OBJ_FROM_JSON(it, Status)
            // *INDENT-ON*
        }
    }
    QString ToString()
    {
        return "CalenderEntry: " + Name;
    }
    int GetHashCode()
    {
        return qHash(Name) ^ qHash(ApplyDate) ^ qHash(Text) ^ qHash(static_cast<int>(Status));
    }
    bool Equals(CalendarEntry* other)
    {
        return other && (this == other ||
                (Name == other->Name && ApplyDate == other->ApplyDate && Text == other->Text && Status == other->Status));
    }
};

#endif // CALENDARENTRY_H
