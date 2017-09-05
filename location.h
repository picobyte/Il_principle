#ifndef LOCATION_H
#define LOCATION_H

#include <QPoint>
#include "json_macros.h"
#include "item.h"
#include "person.h"
#include "locationpropertychange.h"
#include "locationjobdetails.h"
#include "visualevent.h"
#include "locationmodifiercollection.h"
#include "inventorycollection.h"
#include "locationaddress.h"
#include "schoolsubject.h"
#include "rule.h"

class Location {
    QList<Item> ItemsForSale;
    QList<unsigned> EventIDs;
    QList<unsigned> ButtonEventIDs;
    QList<LocationAddress> LstLocationAddress;
    QList<Gender> AllowedGenders;
    QHash<QString, Person> Occupants;
    int lastSelectorTimestamp;
    //readonly object occupantLock;
    //readonly object pickupLock;
    QHash<Gender, WeightedRandomizer<Location> > locationSelector;
    //object updateLocSelectorLock;
    QList<LocationJobDetails> AssociatedJobs;
public:
    enum class RoomPopWeight
    {
        VerySparse = 1,
        Sparse,
        Normal = 5,
        Crowded = 10,
        VeryCrowded = 25
    };
    QString Name;
    QString DisplayName;
    QString Description;
    Region region;
    QPoint worldEditorCoords;
    bool IsIndoors;
    bool IsClassroom;
    OutfitType SpecialOutfit;
    int TimeToCrossRoom;
    QString Imagelocation;
    bool Built;
    VisualEvent LocationMasterEvent;
    QString RoomEventsLocation;
    QString RoomSharedEventsLocation;
    bool CanExitToWorldMap;
    int SecurityLevel;
    QString KeyName;
    bool Known;
    InventoryCollection Inventory;
    PeopleAmount VisitFrequency;
    LocationModifierCollection LocationModifiers;
    LocationPropertyChange PropertyChange;

    const QString get_InventoryName() const
    {
        return DisplayName.isEmpty() ? Name : DisplayName;
    }
    const SchoolSubject CurrentSubject() const
    {
        int classindex = 0;
        // try {
        for (QHash<int, QString>::iterator it = Game.ClassAssignments.AssignedClassrooms.Keys.begin();
                it != Game.ClassAssignments.AssignedClassrooms.Keys.end(); ++it) {

            if (Game.ClassAssignments.AssignedClassrooms[it.key()].Equals(Name))
                classindex = it.key();
        }
        // }
        SchoolSubject CurrentSubject;
        if (classindex > 0)
            return Game.GetSubject(Game.ClassAssignments.AssignedSubjects[classindex]);

        return NULL;
    }

    Location(QJsonObject *d = NULL)
    {
        if (d) init(d);
        Name = "";
        DisplayName = "";
        Description = "";
        region = Region::City;
        IsIndoors = true;
        TimeToCrossRoom = 1;
        Imagelocation = "";
        Built = true;
        RoomEventsLocation = "";
        RoomSharedEventsLocation = "";
        CanExitToWorldMap = false;
        SecurityLevel = 0;
        KeyName = "";
        Known = false;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, DisplayName, toString)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_OBJ_FROM_JSON(it, Region)
            else __IF_VAR_FROM_JSON_AS(it, IsIndoors, toBool)
            else __IF_VAR_FROM_JSON_AS(it, IsClassroom, toBool)
            else __IF_ENUM_FROM_JSON_AS(it, SpecialOutfit, OutfitType)
            else __IF_VAR_FROM_JSON_AS(it, TimeToCrossRoom, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Imagelocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, Built, toBool)
            else __IF_OBJLIST_FROM_JSON(it, AssociatedJobs, LocationJobDetails)
            else __IF_OBJ_FROM_JSON(it, LocationMasterEvent)
            else __IF_VAR_FROM_JSON_AS(it, RoomEventsLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, RoomSharedEventsLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, CanExitToWorldMap, toBool)
            else __IF_VAR_FROM_JSON_AS(it, SecurityLevel, toInt)
            else __IF_VAR_FROM_JSON_AS(it, KeyName, toString)
            else __IF_VAR_FROM_JSON_AS(it, Known, toBool)
            else __IF_OBJLIST_FROM_JSON(it, ItemsForSale, Item)
            else __IF_OBJ_FROM_JSON(it, Inventory)
            else __IF_LIST_FROM_JSON_TYPED(it, EventIDs, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, ButtonEventIDs, toInt)
            else __IF_OBJLIST_FROM_JSON(it, LstLocationAddress, LocationAddress)
            else __IF_OBJ_FROM_JSON(it, VisitFrequency)
            else __IF_LIST_FROM_JSON_ENUM(it, AllowedGenders, Gender)
            else __IF_OBJ_FROM_JSON(it, LocationModifiers)
            else __IF_OBJ_FROM_JSON(it, PropertyChange)
            //else __IF_OBJ_FROM_JSON(it, worldEditorCoords) //QPoint
            //else __IF_OBJ_FROM_JSON(it, occupantLock)
            //else __IF_OBJ_FROM_JSON(it, pickupLock)
            else __IF_VAR_FROM_JSON_AS(it, lastSelectorTimestamp, toInt)
            //else __IF_OBJ_FROM_JSON(it, updateLocSelectorLock)
            // *INDENT-ON*
        }
    }
    bool ShouldSerializeDisplayName()
    {
        return !DisplayName.isEmpty();
    }
    bool ShouldSerializeDescription()
    {
        return !Description.isEmpty();
    }
    bool ShouldSerializeRegion()
    {
        return region > Region::City;
    }
    bool ShouldSerializeIsIndoors()
    {
        return !IsIndoors;
    }
    bool ShouldSerializeIsClassroom()
    {
        return IsClassroom && region == Region::School;
    }
    bool ShouldSerializeSpecialOutfit()
    {
        return SpecialOutfit > OutfitType::DefaultOutfit;
    }
    OutfitType GetActualSpecialOutfit()
    {
        LocMod_SpecialOutfit modifier = LocationModifiers.EnumerateHighestPriorityApplicableModifiers<LocMod_SpecialOutfit>().FirstOrDefault<LocMod_SpecialOutfit>();
        OutfitType GetActualSpecialOutfit;
        if (modifier != NULL)
            return modifier.OutfitType;

        return SpecialOutfit;
    }
    bool ShouldSerializeImagelocation()
    {
        return !Imagelocation.isEmpty();
    }
    bool ShouldSerializeBuilt()
    {
        return !Built;
    }
    bool ShouldSerializeAssociatedJobs()
    {
        return AssociatedJobs.count() > 0;
    }
    bool ShouldSerializeRoomEventsLocation()
    {
        return !RoomEventsLocation.isEmpty();
    }
    bool ShouldSerializeRoomSharedEventsLocation()
    {
        return !RoomSharedEventsLocation.isEmpty();
    }
    bool ShouldSerializeCanExitToWorldMap()
    {
        return CanExitToWorldMap;
    }
    bool ShouldSerializeSecurityLevel()
    {
        return SecurityLevel != 0;
    }
    bool ShouldSerializeKeyName()
    {
        return !(KeyName.isNull() || KeyName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeKnown()
    {
        return Known;
    }
    bool ShouldSerializeItemsForSale()
    {
        return ItemsForSale.count() > 0;
    }
    bool ShouldSerializeInventory()
    {
        return !Inventory.IsEmpty;
    }
    bool ShouldSerializeEventIDs()
    {
        return EventIDs.count() > 0;
    }
    bool ShouldSerializeButtonEventIDs()
    {
        return ButtonEventIDs.count() > 0;
    }
    bool ShouldSerializeLstLocationAddress()
    {
        return LstLocationAddress.count() > 0;
    }
    bool ShouldSerializeVisitFrequency()
    {
        return VisitFrequency > PeopleAmount::Empty;
    }
    PeopleAmount GetActualVisitFrequency()
    {
        LocMod_VisitFrequency modifier = LocationModifiers.EnumerateHighestPriorityApplicableModifiers<LocMod_VisitFrequency>().FirstOrDefault<LocMod_VisitFrequency>();
        PeopleAmount GetActualVisitFrequency;
        if (modifier != NULL)
            return modifier.VisitFrequency;

        return VisitFrequency;
    }
    bool ShouldSerializeAllowedGenders()
    {
        return AllowedGenders.count() > 0;
    }
    bool ShouldSerializeLocationModifiers()
    {
        return LocationModifiers.count() > 0;
    }
    void OccupantEnter(Person P)
    {
        //object obj = occupantLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (P != Game.HeadTeacher && !Occupants.contains(P.Name))
            Occupants.Add(P.Name, P);
        // }
    }
    void OccupantLeave(Person P)
    {
        //object obj = occupantLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        Occupants.remove(P.Name);
        // }
    }
    void LocationInteractions(Person Per)
    {
        if (PropertyChange != NULL && Built)
            PropertyChange.AffectPerson(Per);

        //object obj = pickupLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        QList<Item> ActiveItems = Inventory.GetSingleActiveItems();
        if (ActiveItems.count() > 0 && Game.RNG.Next(5) == 0) {

            Item Itm = ActiveItems[Game.RNG.Next(ActiveItems.count() - 1)];
            if (Itm.ShouldBePickedUpBy(Per)) {
                Per.Inventory.AddInventory(Itm);
                Inventory.RemoveSpecific(Itm);
            }
        }
        // }
    }
    QString GetUILocationName()
    {
        QString GetUILocationName;
        if (!DisplayName.isEmpty())
            return ((SecurityLevel > 0 && !Game.HeadTeacher.Inventory.HasKey(this)) ? (DisplayName + " (\ud83d\udd12)") : DisplayName);

        return ((SecurityLevel > 0 && !Game.HeadTeacher.Inventory.HasKey(this)) ? (Name + " (\ud83d\udd12)") : Name);
    }
    QString ToString()
    {
        return "Location: " + Name;
    }
    Location(const Location& rhs) {
        ItemsForSale = rhs.ItemsForSale;
        ItemsForSale = rhs.ItemsForSale;
        EventIDs = rhs.EventIDs;
        ButtonEventIDs = rhs.ButtonEventIDs;
        LstLocationAddress = rhs.LstLocationAddress;
        AllowedGenders = rhs.AllowedGenders;
        Occupants = rhs.Occupants;
        lastSelectorTimestamp = rhs.lastSelectorTimestamp;
        AssociatedJobs = rhs.AssociatedJobs;
        Name = rhs.Name;
        DisplayName = rhs.DisplayName;
        Description = rhs.Description;
        region = rhs.region;
        worldEditorCoords = rhs.worldEditorCoords;
        IsIndoors = rhs.IsIndoors;
        IsClassroom = rhs.IsClassroom;
        SpecialOutfit = rhs.SpecialOutfit;
        TimeToCrossRoom = rhs.TimeToCrossRoom;
        Imagelocation = rhs.Imagelocation;
        Built = rhs.Built;
        LocationMasterEvent = rhs.LocationMasterEvent;
        RoomEventsLocation = rhs.RoomEventsLocation;
        RoomSharedEventsLocation = rhs.RoomSharedEventsLocation;
        CanExitToWorldMap = rhs.CanExitToWorldMap;
        SecurityLevel = rhs.SecurityLevel;
        KeyName = rhs.KeyName;
        Known = rhs.Known;
        Inventory = rhs.Inventory;
        VisitFrequency = rhs.VisitFrequency;
        LocationModifiers = rhs.LocationModifiers;
        PropertyChange = rhs.PropertyChange;
    }
    Location& operator=(Location& rhs) {
        rhs.ItemsForSale = ItemsForSale;
        rhs.ItemsForSale = ItemsForSale;
        rhs.EventIDs = EventIDs;
        rhs.ButtonEventIDs = ButtonEventIDs;
        rhs.LstLocationAddress = LstLocationAddress;
        rhs.AllowedGenders = AllowedGenders;
        rhs.Occupants = Occupants;
        rhs.lastSelectorTimestamp = lastSelectorTimestamp;
        rhs.AssociatedJobs = AssociatedJobs;
        rhs.Name = Name;
        rhs.DisplayName = DisplayName;
        rhs.Description = Description;
        rhs.region = region;
        rhs.worldEditorCoords = worldEditorCoords;
        rhs.IsIndoors = IsIndoors;
        rhs.IsClassroom = IsClassroom;
        rhs.SpecialOutfit = SpecialOutfit;
        rhs.TimeToCrossRoom = TimeToCrossRoom;
        rhs.Imagelocation = Imagelocation;
        rhs.Built = Built;
        rhs.LocationMasterEvent = LocationMasterEvent;
        rhs.RoomEventsLocation = RoomEventsLocation;
        rhs.RoomSharedEventsLocation = RoomSharedEventsLocation;
        rhs.CanExitToWorldMap = CanExitToWorldMap;
        rhs.SecurityLevel = SecurityLevel;
        rhs.KeyName = KeyName;
        rhs.Known = Known;
        rhs.Inventory = Inventory;
        rhs.VisitFrequency = VisitFrequency;
        rhs.LocationModifiers = LocationModifiers;
        rhs.PropertyChange = PropertyChange;
        return rhs;
    };
    QString GetLocationImagePath(Location *room)
    {
        if (room == NULL)
            return QString.Empty;

        if (room->Occupants.count() > 5) {
            bool nudity = false;
            if (room->region == Region::School) {
                // try {
                for (IEnumerator<Rule>::iterator rule = Game.ListOfRules.Values.begin();
                        rule != Game.ListOfRules.Values.end(); ++rule) {
                    if (rule->ActiveRuleChoice != NULL) {
                        if (room->GetActualSpecialOutfit() == OutfitType::Swimsuit) {
                            if (rule->ActiveRuleChoice.NudeSwimsuit) {
                                nudity = true;
                                break;
                            }
                        }
                        else if (rule->ActiveRuleChoice.NudeOutfit) {
                            nudity = true;
                            break;
                        }
                    }
                }
                // }
            } else if (room->Occupants.Values.Average((Location._ClosureS__.SI154_0 == NULL) ? (Location._ClosureS__.SI154_0 = new Func<Person, double>(Location._ClosureS__.SI._LambdaS__154_0)) : Location._ClosureS__.SI154_0) < 30.0) {
                nudity = true;
            }
            if (nudity && Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednudenight.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednudenight.jpg");

            if (nudity && (Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednudesunset.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednudesunset.jpg");

            if (nudity && Game.GameTime.CheckDaylightTime == Daylight.Day && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednude.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednude.jpg");

            if (Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednight.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdednight.jpg");

            if ((Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdedsunset.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowdedsunset.jpg");

            if (Game.GameTime.CheckDaylightTime == Daylight.Day && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowded.jpg")))
                return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "crowded.jpg");
        }

        if (Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "emptynight.jpg")))
            return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "emptynight.jpg");

        if ((Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "emptysunset.jpg")))
            return Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "emptysunset.jpg");

        QString imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room->Imagelocation, "empty.jpg");
        return File.Exists(imgpath) ? imgpath : "";

    }
    Location GetRandomLocationWeighted(Gender ForGender)
    {
        //object obj = Location.updateLocSelectorLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (Location.lastSelectorTimestamp != Game.GameTime.CurrentTimestamp) {

            // try {
            for (QHash<Gender, WeightedRandomizer<Location> >::iterator it = locationSelector.Values.begin();
                 it != locationSelector.Values.end(); ++it)
                it.clear();

            // }
            // try {
            for (IEnumerator<Location>::iterator room = Game.TheSchool.DictOfLocation.Values.begin();
                    room != Game.TheSchool.DictOfLocation.Values.end(); ++room) {

                PeopleAmount visitFrequency = room->GetActualVisitFrequency();
                // try {
                for (QList<Gender>::iterator g = room->AllowedGenders.begin(); g != room->AllowedGenders.end(); ++g) {
                    switch (visitFrequency)
                    {
                    case PeopleAmount::VerySparse:
                        locationSelector[*g].AddItem(1, &(*room));
                        break;
                    case PeopleAmount::Sparse:
                        locationSelector[*g].AddItem(2, &(*room));
                        break;
                    case PeopleAmount::Normal:
                        locationSelector[*g].AddItem(5, &(*room));
                        break;
                    case PeopleAmount::Crowded:
                        locationSelector[*g].AddItem(10, &(*room));
                        break;
                    case PeopleAmount::VeryCrowded:
                        locationSelector[*g].AddItem(25, &(*room));
                        break;
                    }
                }
                // }
            }
            // }
            lastSelectorTimestamp = Game.GameTime.CurrentTimestamp;
        }
        // }
        return locationSelector[ForGender].GetRandomItem();
    }
};

#endif // LOCATION_H
