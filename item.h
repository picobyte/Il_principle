#ifndef ITEM_H
#define ITEM_H
#include "json_macros.h"

class Item {
public:
    int Uses, MaxUses, Counter;
    bool IsSpecial, HideFromMenu, CanTrade, IsActive, IsAutomatic, IsContainer;
    QString Name, Description, ImageLocation, BuyLocationName, SellLocationName, Data, KeyName, EventName;

    //Inventory
    //ItemProperties
    Item(QJsonObject *d = NULL):
        Uses(0),
        MaxUses(0),
        Counter(0),
        IsSpecial(false),
        HideFromMenu(false),
        CanTrade(true),
        IsActive(false),
        IsAutomatic(false),
        IsContainer(false),
        Name(""),
        Description(""),
        ImageLocation(""),
        BuyLocationName(""),
        SellLocationName(""),
        Data(""),
        KeyName(""),
        //Inventory(new InventoryCollection()),
        //ItemProperties(new EP_ItemEvent()),
        EventName("")
    {
            if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            else __IF_VAR_FROM_JSON_AS(it, ImageLocation, toString)
            else __IF_VAR_FROM_JSON_AS(it, BuyLocationName, toString)
            else __IF_VAR_FROM_JSON_AS(it, SellLocationName, toString)
            else __IF_VAR_FROM_JSON_AS(it, Data, toString)
            else __IF_VAR_FROM_JSON_AS(it, KeyName, toString)
            else __IF_VAR_FROM_JSON_AS(it, EventName, toString)
            else __IF_VAR_FROM_JSON_AS(it, IsSpecial, toBool)
            else __IF_VAR_FROM_JSON_AS(it, HideFromMenu, toBool)
            else __IF_VAR_FROM_JSON_AS(it, IsActive, toBool)
            else __IF_VAR_FROM_JSON_AS(it, IsAutomatic, toBool)
            else __IF_VAR_FROM_JSON_AS(it, IsContainer, toBool)
            else __IF_VAR_FROM_JSON_AS(it, Uses, toInt)
            else __IF_VAR_FROM_JSON_AS(it, MaxUses, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Counter, toInt)
        }
    }
};

#endif // ITEM_H
