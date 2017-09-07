#include "location.h"
#include "schoolupgrade.h"

size_t SchoolUpgrade::schoolupgradeCounter = 0;

Location* SchoolUpgrade::getLocation() const
{
    return &Game.GetLocation(LocationName);
}

void SchoolUpgrade::setLocation(Location* v)
{
    LocationName = v ? v->Name : "";
}

