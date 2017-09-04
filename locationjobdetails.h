#ifndef LOCATIONJOBDETAILS_H
#define LOCATIONJOBDETAILS_H
#include "json_macros.h"

class Person;
class LocationJobDetails {
    QList<QString> Staff;
public:
    QString JobTitle;
    int NumberOfJobs;
    QString GenderRestriction;
    bool WeekdayShift;
    bool SchoolShift;
    bool EveningShift;
    bool WeekendShift;
    LocationJobDetails(QJsonObject *d = NULL)
    {
        if (d) init(d);
        JobTitle = "";
        NumberOfJobs = 1;
        GenderRestriction = "";
        WeekdayShift = true;
        SchoolShift = false;
        EveningShift = false;
        WeekendShift = false;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, JobTitle, toString)
            else __IF_VAR_FROM_JSON_AS(it, NumberOfJobs, toInt)
            else __IF_VAR_FROM_JSON_AS(it, GenderRestriction, toString)
            else __IF_VAR_FROM_JSON_AS(it, WeekdayShift, toBool)
            else __IF_VAR_FROM_JSON_AS(it, SchoolShift, toBool)
            else __IF_VAR_FROM_JSON_AS(it, EveningShift, toBool)
            else __IF_VAR_FROM_JSON_AS(it, WeekendShift, toBool)
            else __IF_LIST_FROM_JSON_TYPED(it, Staff, toString)
            // *INDENT-ON*
        }
    }
    bool ShouldSerializeNumberOfJobs()
    {
        return NumberOfJobs != 1;
    }
    bool ShouldSerializeGenderRestriction()
    {
        return !GenderRestriction.isEmpty();
    }
    bool ShouldSerializeWeekdayShift()
    {
        return !WeekdayShift;
    }
    bool ShouldSerializeSchoolShift()
    {
        return SchoolShift;
    }
    bool ShouldSerializeEveningShift()
    {
        return EveningShift;
    }
    bool ShouldSerializeWeekendShift()
    {
        return WeekendShift;
    }
    bool ShouldSerializeStaff()
    {
        return Staff.count() > 0;
    }
    LocationJobDetails(const LocationJobDetails& rhs) {
        JobTitle = rhs.JobTitle;
        NumberOfJobs = rhs.NumberOfJobs;
        GenderRestriction = rhs.GenderRestriction;
        WeekdayShift = rhs.WeekdayShift;
        EveningShift = rhs.EveningShift;
        WeekendShift = rhs.WeekendShift;
        SchoolShift = rhs.SchoolShift;
    }
    LocationJobDetails& operator=(LocationJobDetails& rhs) {
        rhs.JobTitle = JobTitle;
        rhs.NumberOfJobs = NumberOfJobs;
        rhs.GenderRestriction = GenderRestriction;
        rhs.WeekdayShift = WeekdayShift;
        rhs.EveningShift = EveningShift;
        rhs.WeekendShift = WeekendShift;
        rhs.SchoolShift = SchoolShift;
    }
    QString ToString()
    {
        return "LocationJobDetails: " + JobTitle;
    }
    bool CanEmploy(Person& Per);
    bool JobAllowed(Person& Per);
    bool GenderAllowed(Person& Per);
    bool IsFullyStaffed()
    {
        return NumberOfJobs > 0 && Staff.count() >= NumberOfJobs;
    }
};

#endif // LOCATIONJOBDETAILS_H
