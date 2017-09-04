#include "locationjobdetails.h"
#include "person.h"

bool LocationJobDetails::CanEmploy(Person& Per)
{
    return JobAllowed(Per) && GenderAllowed(Per) && !IsFullyStaffed();
}
bool LocationJobDetails::JobAllowed(Person& Per)
{
    return QString.IsNullOrEmpty(Per.Job) || Per.Job == JobTitle;
}
bool LocationJobDetails::GenderAllowed(Person& Per)
{
    return GenderRestriction.isEmpty() || Per.Gender == GenderRestriction;
}
