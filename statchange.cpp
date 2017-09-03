
#include "person.h"
#include "statchange.h"

void StatChange::AdjustStat(Person& Per)
{
    if (WithinRange(Per.GetStat(Stat)))
    {
        Per.AddStat(Stat, Change);
        if (Minimum != 0.0 && Per.GetStat(Stat) < Minimum)
        {
            Per.SetStat(Stat, Minimum);
            return;
        }
        if (Maximum != 0.0 && Per.GetStat(Stat) > Maximum)
        {
            Per.SetStat(Stat, Maximum);
        }
    }
}
