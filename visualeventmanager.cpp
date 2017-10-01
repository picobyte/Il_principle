
#include "person.h"
#include "visualeventmanager.h"

namespace VisualEventManager {
VisualEvent* GetLocationMasterEvent(Location& Loc)
{
    VisualEvent GetLocationMasterEvent;
    if (Loc.LocationMasterEvent != NULL)
        return Loc.LocationMasterEvent;

    for (QList<VisualEvent>::iterator ev = LocationMasterEvents.begin();ev != LocationMasterEvents.end(); ++ev)
        if (ev->jsonFileName.endsWith("LOC_" + Loc.Name + ".ve.xml"))
            return Loc.LocationMasterEvent = &*ev;

    for (QList<VisualEvent>::iterator ev = LocationMasterEvents.begin();ev != LocationMasterEvents.end(); ++ev)
        if (ev->jsonFileName.endsWith("LOC_Dummy.ve.xml"))
            return Loc.LocationMasterEvent = &*ev;

    return NULL;
}
VisualEvent* AttachPersonEvent(const QString& filename, Person* P)
{
    if (P == NULL) return NULL;

    VisualEvent* ev = GetEventByFilename(filename, VisualEventKind::PersonAttachedEvent);
    if (ev && !P->AttachedEventIDs.contains(ev->UniqueID))
        P->AttachedEventIDs.append(ev->UniqueID);
    return ev;
}
VisualEvent* DetachPersonEvent(const QString& filename, Person* P)
{
    if (P == NULL) return NULL;

    VisualEvent* ev = GetEventByFilename(filename, VisualEventKind::PersonAttachedEvent);
    if (ev && !P->AttachedEventIDs.contains(ev->UniqueID))
        P->AttachedEventIDs.removeOne(ev->UniqueID);
    return ev;
}
}
