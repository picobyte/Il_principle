#include "locationjobdetails.h"
#include "person.h"

bool LocationJobDetails::CanEmploy(Person* Per)
{
    return Per && JobAllowed(Per) && GenderAllowed(Per) && !IsFullyStaffed();
}
bool LocationJobDetails::JobAllowed(Person* Per)
{
    return Per && QString.IsNullOrEmpty(Per->Job) || Per->Job == JobTitle;
}
bool LocationJobDetails::GenderAllowed(Person* Per)
{
    return Per && GenderRestriction.isEmpty() || Per->Gender == GenderRestriction;
}
