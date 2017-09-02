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
