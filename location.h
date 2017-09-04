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

class Location {
    QList<Item> ItemsForSale;
    QList<unsigned> EventIDs;
    QList<unsigned> ButtonEventIDs;
    QList<LocationAddress> _LstLocationAddress;
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
                it != Game.ClassAssignments.AssignedClassrooms.Keys.end(); ++it)
        {
            int ci = enumerator.Current;
            if (Game.ClassAssignments.AssignedClassrooms[ci].Equals(Name))
            {
                classindex = ci;
            }
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
        Region = Region.City;
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
            __IF_VAR_FROM_JSON_AS(it, _Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, _DisplayName, toString)
            else __IF_VAR_FROM_JSON_AS(it, _Description, toString)
            else __IF_OBJ_FROM_JSON(it, _Region)
            else __IF_VAR_FROM_JSON_AS(it, _IsIndoors, toBool)
            else __IF_VAR_FROM_JSON_AS(it, _IsClassroom, toBool)
            else __IF_ENUM_FROM_JSON_AS(it, _SpecialOutfit, OutfitType)
            else __IF_VAR_FROM_JSON_AS(it, _TimeToCrossRoom, toInt)
            else __IF_VAR_FROM_JSON_AS(it, _Imagelocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, _Built, toBool)
            else __IF_OBJLIST_FROM_JSON(it, _AssociatedJobs, LocationJobDetails)
            else __IF_OBJ_FROM_JSON(it, _LocationMasterEvent)
            else __IF_VAR_FROM_JSON_AS(it, _RoomEventsLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, _RoomSharedEventsLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, _CanExitToWorldMap, toBool)
            else __IF_VAR_FROM_JSON_AS(it, _SecurityLevel, toInt)
            else __IF_VAR_FROM_JSON_AS(it, _KeyName, toString)
            else __IF_VAR_FROM_JSON_AS(it, _Known, toBool)
            else __IF_OBJLIST_FROM_JSON(it, _ItemsForSale, Item)
            else __IF_OBJ_FROM_JSON(it, _Inventory)
            else __IF_LIST_FROM_JSON_TYPED(it, _EventIDs, toInt)
            else __IF_LIST_FROM_JSON_TYPED(it, _ButtonEventIDs, toInt)
            else __IF_OBJLIST_FROM_JSON(it, _LstLocationAddress, LocationAddress)
            else __IF_OBJ_FROM_JSON(it, _VisitFrequency)
            else __IF_LIST_FROM_JSON_ENUM(it, _AllowedGenders, Gender)
            else __IF_OBJ_FROM_JSON(it, _LocationModifiers)
            else __IF_OBJ_FROM_JSON(it, _PropertyChange)
            else __IF_OBJ_FROM_JSON(it, _worldEditorCoords)
            else __IF_OBJ_FROM_JSON(it, occupantLock)
            else __IF_OBJ_FROM_JSON(it, pickupLock)
            else __IF_VAR_FROM_JSON_AS(it, lastSelectorTimestamp, toInt)
            else __IF_OBJ_FROM_JSON(it, updateLocSelectorLock)
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
        return Region > Region.City;
    }
    bool ShouldSerializeIsIndoors()
    {
        return !IsIndoors;
    }
    bool ShouldSerializeIsClassroom()
    {
        return IsClassroom && Region == Region.School;
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
        return VisitFrequency > PeopleAmount.Empty;
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
        object obj = occupantLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (P != Game.HeadTeacher && !Occupants.ContainsKey(P.Name))
        {
            Occupants.Add(P.Name, P);
        }
        // }
    }
    void OccupantLeave(Person P)
    {
        object obj = occupantLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        Occupants.Remove(P.Name);
        // }
    }
    void LocationInteractions(Person Per)
    {
        if (PropertyChange != NULL && Built)
        {
            PropertyChange.AffectPerson(Per);
        }
        object obj = pickupLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        QList<Item> ActiveItems = Inventory.GetSingleActiveItems();
        if (ActiveItems.count() > 0 && Game.RNG.Next(5) == 0)
        {
            Item Itm = ActiveItems[Game.RNG.Next(checked(ActiveItems.count() - 1))];
            if (Itm.ShouldBePickedUpBy(Per))
            {
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
    object Clone()
    {
        Location expr_0B = (Location)MemberwiseClone();
        expr_0B.AssociatedJobs = AssociatedJobs.Select((Location._ClosureS__.SI153_0 == NULL) ? (Location._ClosureS__.SI153_0 = new Func<LocationJobDetails, LocationJobDetails>(Location._ClosureS__.SI._LambdaS__153_0)) : Location._ClosureS__.SI153_0).ToList<LocationJobDetails>();
        expr_0B.ItemsForSale = ItemsForSale.Select((Location._ClosureS__.SI153_1 == NULL) ? (Location._ClosureS__.SI153_1 = new Func<Item, Item>(Location._ClosureS__.SI._LambdaS__153_1)) : Location._ClosureS__.SI153_1).ToList<Item>();
        expr_0B.Inventory = (InventoryCollection)Inventory.Clone();
        expr_0B.EventIDs.AddRange(EventIDs);
        expr_0B.ButtonEventIDs.AddRange(ButtonEventIDs);
        expr_0B.LstLocationAddress.AddRange(LstLocationAddress);
        return expr_0B;
    }
    QString GetLocationImagePath(Location room)
    {
        QString GetLocationImagePath;
        if (room == NULL)
        {
            GetLocationImagePath = QString.Empty;
        }
        else
        {
            bool crowded = false;
            bool nudity = false;
            if (room.Occupants.count() > 5)
            {
                crowded = true;
                if (room.Region == Region.School)
                {
                    // try {
                    for (IEnumerator<Rule>::iterator it = Game.ListOfRules.Values.begin();
                            it != Game.ListOfRules.Values.end(); ++it)
                    {
                        Rule Rule = enumerator.Current;
                        if (Rule.ActiveRuleChoice != NULL)
                        {
                            if (room.GetActualSpecialOutfit() == OutfitType::Swimsuit)
                            {
                                if (Rule.ActiveRuleChoice.NudeSwimsuit)
                                {
                                    nudity = true;
                                    break;
                                }
                            }
                            else if (Rule.ActiveRuleChoice.NudeOutfit)
                            {
                                nudity = true;
                                break;
                            }
                        }
                    }
                    goto IL_D5;
                    // }
                }
                if (room.Occupants.Values.Average((Location._ClosureS__.SI154_0 == NULL) ? (Location._ClosureS__.SI154_0 = new Func<Person, double>(Location._ClosureS__.SI._LambdaS__154_0)) : Location._ClosureS__.SI154_0) < 30.0)
                {
                    nudity = true;
                }
            }
            IL_D5:
            QString imgpath;
            if (nudity && Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednudenight.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednudenight.jpg");
            }
            else if (nudity && (Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednudesunset.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednudesunset.jpg");
            }
            else if (nudity && Game.GameTime.CheckDaylightTime == Daylight.Day && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednude.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednude.jpg");
            }
            else if (crowded && Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednight.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdednight.jpg");
            }
            else if (crowded && (Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdedsunset.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowdedsunset.jpg");
            }
            else if (crowded && Game.GameTime.CheckDaylightTime == Daylight.Day && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowded.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "crowded.jpg");
            }
            else if (Game.GameTime.CheckDaylightTime == Daylight.Night && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "emptynight.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "emptynight.jpg");
            }
            else if ((Game.GameTime.CheckDaylightTime == Daylight.Sunrise || Game.GameTime.CheckDaylightTime == Daylight.Sunset) && File.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "emptysunset.jpg")))
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "emptysunset.jpg");
            }
            else
            {
                imgpath = Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, room.Imagelocation, "empty.jpg");
                if (!File.Exists(imgpath))
                {
                    imgpath = "";
                }
            }
            GetLocationImagePath = imgpath;
        }
        return GetLocationImagePath;
    }
    Location GetRandomLocationWeighted(Gender ForGender)
    {
        object obj = Location.updateLocSelectorLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (Location.lastSelectorTimestamp != Game.GameTime.CurrentTimestamp)
        {
            // try {
            QHash<Gender, WeightedRandomizer<Location>>.ValueCollection.Enumerator enumerator = Location.locationSelector.Values.GetEnumerator();
            while (enumerator.MoveNext())
            {
                enumerator.Current.Clear();
            }
            // }
            // try {
            for (IEnumerator<Location>::iterator it = Game.TheSchool.DictOfLocation.Values.begin();
                    it != Game.TheSchool.DictOfLocation.Values.end(); ++it)
            {
                Location room = enumerator2.Current;
                PeopleAmount visitFrequency = room.GetActualVisitFrequency();
                // try {
                for (QList<Gender>::iterator it2 = room.AllowedGenders.begin();
                        it2 != room.AllowedGenders.end(); ++it2)
                {
                    Gender g = enumerator3.Current;
                    switch (visitFrequency)
                    {
                    case PeopleAmount.VerySparse:
                        Location.locationSelector[g].AddItem(1, ref room);
                        break;
                    case PeopleAmount.Sparse:
                        Location.locationSelector[g].AddItem(2, ref room);
                        break;
                    case PeopleAmount.Normal:
                        Location.locationSelector[g].AddItem(5, ref room);
                        break;
                    case PeopleAmount.Crowded:
                        Location.locationSelector[g].AddItem(10, ref room);
                        break;
                    case PeopleAmount.VeryCrowded:
                        Location.locationSelector[g].AddItem(25, ref room);
                        break;
                    }
                }
                // }
            }
            // }
            Location.lastSelectorTimestamp = Game.GameTime.CurrentTimestamp;
        }
        // }
        return Location.locationSelector[ForGender].GetRandomItem();
        }
};

#endif // LOCATION_H
