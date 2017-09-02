#ifndef ITEM_H
#define ITEM_H
#include "json_macros.h"

class Item {
public:
    QStrign Name, Description, ImageLocation, BuyLocationName, SellLocationName, Data, KeyName, EventName;
    bool IsSpecial, HideFromMenu, CanTrade, IsActive, IsAutomatic, IsContainer;
    int Uses, MaxUses, Counter;
    //Inventory
    //ItemProperties
    Item(QJsonObject *d = NULL):
        Name(""),
        IsSpecial(false),
        Description(""),
        HideFromMenu(false),
        ImageLocation(""),
        BuyLocationName(""),
        SellLocationName(""),
        CanTrade(true),
        Uses(0),
        MaxUses(0),
        IsActive(false),
        IsAutomatic(false),
        Counter(0),
        Data(""),
        IsContainer(false),
        KeyName(""),
        //Inventory(new InventoryCollection()),
        //ItemProperties(new EP_ItemEvent()),
        EventName("")
    {
            if (d) init(d);
    }
    void init(QJsonObject *d)
    {
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
};

#endif // ITEM_H
