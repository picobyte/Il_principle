#ifndef LOCATION_H
#define LOCATION_H

#include <QPoint>
#include "json_macros.h"
#include "item.h"
#include "person.h"

class Location {
    QList<Item> ItemsForSale;
    QList<unsigned> EventIDs;
    QList<unsigned> ButtonEventIDs;
    //QList<LocationAddress> LstLocationAddress;
    QList<Gender> AllowedGenders;
    QHash<QString, Person> Occupants;
    int lastSelectorTimestamp;
    //readonly object occupantLock;
    //readonly object pickupLock;
    //QHash<Gender, WeightedRandomizer<Location>> locationSelector;
    //object updateLocSelectorLock;
    //QList<LocationJobDetails> AssociatedJobs;
public:
	enum RoomPopWeight
	{
		VerySparse = 1,
		Sparse,
		Normal = 5,
		Crowded = 10,
		VeryCrowded = 25
	}
	QString _Name;
	QString _DisplayName;
	QString _Description;
	Region _Region;
	bool _IsIndoors;
	bool _IsClassroom;
	OutfitType _SpecialOutfit;
	int _TimeToCrossRoom;
	QString _Imagelocation;
	bool _Built;
	QList<LocationJobDetails> _AssociatedJobs;
	VisualEvent _LocationMasterEvent;
	QString _RoomEventsLocation;
	QString _RoomSharedEventsLocation;
	bool _CanExitToWorldMap;
	int _SecurityLevel;
	QString _KeyName;
	bool _Known;
	QList<Item> _ItemsForSale;
	InventoryCollection _Inventory;
	QList<unsigned> _EventIDs;
	QList<unsigned> _ButtonEventIDs;
	QList<LocationAddress> _LstLocationAddress;
	PeopleAmount _VisitFrequency;
	QList<Gender> _AllowedGenders;
	LocationModifierCollection _LocationModifiers;
	LocationPropertyChange _PropertyChange;
	Point _worldEditorCoords;
	QHash<QString, Person> _Occupants;
	readonly object occupantLock;
	readonly object pickupLock;
	QHash<Gender, WeightedRandomizer<Location>> locationSelector;
	int lastSelectorTimestamp;
	object updateLocSelectorLock;
	const QString Name() const {return Name;}
	void Name(QString& v) {Name = v;}
	const QString DisplayName() const {return DisplayName;}
	void DisplayName(QString& v) {DisplayName = v;}
	const QString Description() const {return Description;}
	void Description(QString& v) {Description = v;}
	const Region Region() const {return Region;}
	void Region(Region& v) {Region = v;}
	const bool IsIndoors() const {return IsIndoors;}
	void IsIndoors(bool& v) {IsIndoors = v;}
	const bool IsClassroom() const {return IsClassroom;}
	void IsClassroom(bool& v) {IsClassroom = v;}
	const OutfitType SpecialOutfit() const {return SpecialOutfit;}
	void SpecialOutfit(OutfitType& v) {SpecialOutfit = v;}
	const int TimeToCrossRoom() const {return TimeToCrossRoom;}
	void TimeToCrossRoom(int& v) {TimeToCrossRoom = v;}
	const QString Imagelocation() const {return Imagelocation;}
	void Imagelocation(QString& v) {Imagelocation = v;}
	const bool Built() const {return Built;}
	void Built(bool& v) {Built = v;}
	const VisualEvent LocationMasterEvent() const {return LocationMasterEvent;}
	void LocationMasterEvent(VisualEvent& v) {LocationMasterEvent = v;}
	const QString RoomEventsLocation() const {return RoomEventsLocation;}
	void RoomEventsLocation(QString& v) {RoomEventsLocation = v;}
	const QString RoomSharedEventsLocation() const {return RoomSharedEventsLocation;}
	void RoomSharedEventsLocation(QString& v) {RoomSharedEventsLocation = v;}
	const bool CanExitToWorldMap() const {return CanExitToWorldMap;}
	void CanExitToWorldMap(bool& v) {CanExitToWorldMap = v;}
	const int SecurityLevel() const {return SecurityLevel;}
	void SecurityLevel(int& v) {SecurityLevel = v;}
	const QString KeyName() const {return KeyName;}
	void KeyName(QString& v) {KeyName = v;}
	const bool Known() const {return Known;}
	void Known(bool& v) {Known = v;}
	const InventoryCollection Inventory() const {return Inventory;}
	void Inventory(InventoryCollection& v) {Inventory = v;}
	const QString InventoryName() const
	{
		if (QString.IsNullOrEmpty(DisplayName))
		{
			return Name;
		}
		return DisplayName;
	}
	const PeopleAmount VisitFrequency() const {return VisitFrequency;}
	void VisitFrequency(PeopleAmount& v) {VisitFrequency = v;}
	const LocationModifierCollection LocationModifiers() const {return LocationModifiers;}
	void LocationModifiers(LocationModifierCollection& v) {LocationModifiers = v;}
	const LocationPropertyChange PropertyChange() const {return PropertyChange;}
	void PropertyChange(LocationPropertyChange& v) {PropertyChange = v;}
	const Point WorldEditorCoords() const
	{
		return _worldEditorCoords;
	}
	void WorldEditorCoords(Point& v)
	{
		_worldEditorCoords = new Point(Conversion.Int(value.X), Conversion.Int(value.Y));
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
		{
			return Game.GetSubject(Game.ClassAssignments.AssignedSubjects[classindex]);


	{
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
		SpecialOutfit = OutfitType.DefaultOutfit;
		TimeToCrossRoom = 1;
		Imagelocation = "";
		Built = true;
		AssociatedJobs = new QList<LocationJobDetails>();
		RoomEventsLocation = "";
		RoomSharedEventsLocation = "";
		CanExitToWorldMap = false;
		SecurityLevel = 0;
		KeyName = "";
		Known = false;
		ItemsForSale = new QList<Item>();
		Inventory = new InventoryCollection();
		EventIDs = new QList<unsigned>();
		ButtonEventIDs = new QList<unsigned>();
		LstLocationAddress = new QList<LocationAddress>();
		VisitFrequency = PeopleAmount.Empty;
		AllowedGenders = new QList<Gender>();
		LocationModifiers = new LocationModifierCollection();
		Occupants = new QHash<QString, Person>();
		occupantLock = RuntimeHelpers.GetObjectValue(new object());
		pickupLock = RuntimeHelpers.GetObjectValue(new object());
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_VAR_FROM_JSON_AS(it, _Name, toString)
			else __IF_VAR_FROM_JSON_AS(it, _DisplayName, toString)
			else __IF_VAR_FROM_JSON_AS(it, _Description, toString)
			else __IF_OBJ_FROM_JSON_AS(it, _Region)
			else __IF_VAR_FROM_JSON_AS(it, _IsIndoors, toBool)
			else __IF_VAR_FROM_JSON_AS(it, _IsClassroom, toBool)
			else __IF_ENUM_FROM_JSON_AS(it, _SpecialOutfit, OutfitType)
			else __IF_VAR_FROM_JSON_AS(it, _TimeToCrossRoom, toInt)
			else __IF_VAR_FROM_JSON_AS(it, _Imagelocation, toString)
			else __IF_VAR_FROM_JSON_AS(it, _Built, toBool)
			else __IF_OBJLIST_FROM_JSON(it, _AssociatedJobs, LocationJobDetails)
			else __IF_OBJ_FROM_JSON_AS(it, _LocationMasterEvent)
			else __IF_VAR_FROM_JSON_AS(it, _RoomEventsLocation, toString)
			else __IF_VAR_FROM_JSON_AS(it, _RoomSharedEventsLocation, toString)
			else __IF_VAR_FROM_JSON_AS(it, _CanExitToWorldMap, toBool)
			else __IF_VAR_FROM_JSON_AS(it, _SecurityLevel, toInt)
			else __IF_VAR_FROM_JSON_AS(it, _KeyName, toString)
			else __IF_VAR_FROM_JSON_AS(it, _Known, toBool)
			else __IF_OBJLIST_FROM_JSON(it, _ItemsForSale, Item)
			else __IF_OBJ_FROM_JSON_AS(it, _Inventory)
			else __IF_LIST_FROM_JSON_TYPED(it, _EventIDs, toInt)
			else __IF_LIST_FROM_JSON_TYPED(it, _ButtonEventIDs, toInt)
			else __IF_OBJLIST_FROM_JSON(it, _LstLocationAddress, LocationAddress)
			else __IF_OBJ_FROM_JSON_AS(it, _VisitFrequency)
			else __IF_LIST_FROM_JSON_ENUM(it, _AllowedGenders, Gender)
			else __IF_OBJ_FROM_JSON_AS(it, _LocationModifiers)
			else __IF_OBJ_FROM_JSON_AS(it, _PropertyChange)
			else __IF_OBJ_FROM_JSON_AS(it, _worldEditorCoords)

			else __IF_OBJ_FROM_JSON_AS(it, occupantLock)
			else __IF_OBJ_FROM_JSON_AS(it, pickupLock)

			else __IF_VAR_FROM_JSON_AS(it, lastSelectorTimestamp, toInt)
			else __IF_OBJ_FROM_JSON_AS(it, updateLocSelectorLock)
			// *INDENT-ON*
		}
	}
	bool ShouldSerializeDisplayName()
	{
		return !QString.IsNullOrEmpty(DisplayName);
	}
	bool ShouldSerializeDescription()
	{
		return !QString.IsNullOrEmpty(Description);
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
		return SpecialOutfit > OutfitType.DefaultOutfit;
	}
	OutfitType GetActualSpecialOutfit()
	{
		LocMod_SpecialOutfit modifier = LocationModifiers.EnumerateHighestPriorityApplicableModifiers<LocMod_SpecialOutfit>().FirstOrDefault<LocMod_SpecialOutfit>();
		OutfitType GetActualSpecialOutfit;
		if (modifier != NULL)
		{
			return modifier.OutfitType;


	{
		return SpecialOutfit;

	}
	bool ShouldSerializeImagelocation()
	{
		return !QString.IsNullOrEmpty(Imagelocation);
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
		return !QString.IsNullOrEmpty(RoomEventsLocation);
	}
	bool ShouldSerializeRoomSharedEventsLocation()
	{
		return !QString.IsNullOrEmpty(RoomSharedEventsLocation);
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
		{
			return modifier.VisitFrequency;


	{
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
		if (!QString.IsNullOrEmpty(DisplayName))
		{
			return ((SecurityLevel > 0 && !Game.HeadTeacher.Inventory.HasKey(this)) ? (DisplayName + " (\ud83d\udd12)") : DisplayName);


	{
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
							if (room.GetActualSpecialOutfit() == OutfitType.Swimsuit)
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
    //Region region;
    QPoint worldEditorCoords;
    bool IsIndoors;
    bool IsClassroom;
    OutfitType SpecialOutfit;
    int TimeToCrossRoom;
    QString Imagelocation;
    bool Built;
    //VisualEvent LocationMasterEvent;
    QString RoomEventsLocation;
    QString RoomSharedEventsLocation;
    bool CanExitToWorldMap;
    int SecurityLevel;
    QString KeyName;
    bool Known;
    //InventoryCollection Inventory;
    //PeopleAmount VisitFrequency;
    //LocationModifierCollection LocationModifiers;
    //LocationPropertyChange PropertyChange;

    const QString get_InventoryName() const
    {
        return DisplayName.isEmpty() ? Name : DisplayName;
    }
    /*const SchoolSubject get_CurrentSubject() const
        {
                QHash<int, QString>::iterator it;
                for (it = Game.ClassAssignments.AssignedClassrooms.begin();
                            it != Game.ClassAssignments.AssignedClassrooms.end(); ++it) {
                        subj = Game.ClassAssignments.AssignedClassrooms[it.Current];
                        if (subj.equals(Name))
                            return subj;
                }
                return NULL;
        }*/
    Location(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
                    else __IF_VAR_FROM_JSON_AS(it, DisplayName, toString)
                    else __IF_VAR_FROM_JSON_AS(it, Description, toString)
                    //else __IF_OBJ_FROM_JSON_AS(it, Region)
                    else __IF_VAR_FROM_JSON_AS(it, IsIndoors, toBool)
                    else __IF_VAR_FROM_JSON_AS(it, IsClassroom, toBool)
                    else __IF_ENUM_FROM_JSON_AS(it, SpecialOutfit, OutfitType)
                    else __IF_VAR_FROM_JSON_AS(it, TimeToCrossRoom, toInt)
                    else __IF_VAR_FROM_JSON_AS(it, Imagelocation, toString)
                    else __IF_VAR_FROM_JSON_AS(it, Built, toBool)
                    //else __IF_OBJLIST_FROM_JSON(it, AssociatedJobs, LocationJobDetails)
                    //else __IF_OBJ_FROM_JSON_AS(it, LocationMasterEvent)
                    else __IF_VAR_FROM_JSON_AS(it, RoomEventsLocation, toString)
                    else __IF_VAR_FROM_JSON_AS(it, RoomSharedEventsLocation, toString)
                    else __IF_VAR_FROM_JSON_AS(it, CanExitToWorldMap, toBool)
                    else __IF_VAR_FROM_JSON_AS(it, SecurityLevel, toInt)
                    else __IF_VAR_FROM_JSON_AS(it, KeyName, toString)
                    else __IF_VAR_FROM_JSON_AS(it, Known, toBool)
                    else __IF_OBJLIST_FROM_JSON(it, ItemsForSale, Item)
                    //else __IF_OBJ_FROM_JSON_AS(it, Inventory)
                    else __IF_LIST_FROM_JSON_TYPED(it, EventIDs, toInt)
                    else __IF_LIST_FROM_JSON_TYPED(it, ButtonEventIDs, toInt)
                    //else __IF_OBJLIST_FROM_JSON(it, LstLocationAddress, LocationAddress)
                    //else __IF_OBJ_FROM_JSON_AS(it, VisitFrequency)
                    else __IF_LIST_FROM_JSON_ENUM(it, AllowedGenders, Gender)
                    //else __IF_OBJ_FROM_JSON_AS(it, LocationModifiers)
                    //else __IF_OBJ_FROM_JSON_AS(it, PropertyChange)
                    //else __IF_OBJ_FROM_JSON_AS(it, worldEditorCoords)
                    //QHash<QString, Person> Occupants
                    //else __IF_OBJ_FROM_JSON_AS(it, occupantLock)
                    //else __IF_OBJ_FROM_JSON_AS(it, pickupLock)
                    // QHash<Gender, WeightedRandomizer<Location>> locationSelector
                    else __IF_VAR_FROM_JSON_AS(it, lastSelectorTimestamp, toInt)
                    //else __IF_OBJ_FROM_JSON_AS(it, updateLocSelectorLock)
        }
    }
};

#endif // LOCATION_H
