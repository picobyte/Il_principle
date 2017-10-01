#ifndef ITEM_H
#define ITEM_H
#include <location.h>
#include <person.h>

#include "json_macros.h"
#include "visualevent.h"
#include "visualeventmanager.h"

class Item {
public:
    int Uses, MaxUses, Counter, BuyPrice, SellPrice, BreakInLevel, SecurityLevel;
    bool IsSpecial, HideFromMenu, CanTrade, IsActive, IsAutomatic, IsContainer;
    QString Name, Description, ImageLocation, BuyLocationName, SellLocationName,
        Data, KeyName, EventName, DisplayName;
    QList<Item> Inventory;

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
    bool ShouldSerializeIsSpecial()
    {
        return IsSpecial;
    }
    bool ShouldSerializeDescription()
    {
        return !(Description.isNull() || Description.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeHideFromMenu()
    {
        return HideFromMenu;
    }
    bool ShouldSerializeImageLocation()
    {
        return !(ImageLocation.isNull() || ImageLocation.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeBuyPrice()
    {
        return BuyPrice != 0;
    }
    bool ShouldSerializeBuyLocationName()
    {
        return !(BuyLocationName.isNull() || BuyLocationName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeSellPrice()
    {
        return SellPrice != 0;
    }
    bool ShouldSerializeSellLocationName()
    {
        return !(SellLocationName.isNull() || SellLocationName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeCanTrade()
    {
        return !CanTrade;
    }
    bool ShouldSerializeUses()
    {
        return Uses != 0;
    }
    bool ShouldSerializeMaxUses()
    {
        return MaxUses != 0;
    }
    bool ShouldSerializeIsActive()
    {
        return IsActive && !IsContainer;
    }
    bool ShouldSerializeIsAutomatic()
    {
        return IsAutomatic;
    }
    bool ShouldSerializeCounter()
    {
        return Counter != 0;
    }
    bool ShouldSerializeData()
    {
        return !(Data.isNull() || Data.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeBreakInLevel()
    {
        return BreakInLevel != 0;
    }
    bool ShouldSerializeIsContainer()
    {
        return IsContainer;
    }
    bool ShouldSerializeSecurityLevel()
    {
        return IsContainer && SecurityLevel != 0;
    }
    bool ShouldSerializeKeyName()
    {
        return IsContainer && SecurityLevel != 0 && !(KeyName.isNull() || KeyName.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeInventory()
    {
        return IsContainer && !Inventory.isEmpty();
    }
    bool ShouldSerializeEventName()
    {
        return !(EventName.isNull() || EventName.contains(QRegExp("^\\s*$")));
    }
    async Task UsedBy(Person& Per)
    {
        // checked {
        if (Per == Game.HeadTeacher || IsActive)
        {
            VisualEvent VE = GetItemEvent();
            if (VE != NULL)
            {
                ItemProperties.Item = this;
                ItemProperties.User = Per;
                ItemProperties.Mode = 0;
                EventRunner runner = new EventRunner();
                if (Per == Game.HeadTeacher)
                {
                    if (await runner.TryEventAsync(VE, ItemProperties))
                    {
                        await runner.ExecuteAsync(VE, ItemProperties, false);
                        if (MaxUses != 0)
                        {
                            Uses++;
                            if (Uses >= MaxUses)
                            {
                                Per.Inventory.RemoveSpecific(this);
                            }
                        }
                    }
                }
                else if (runner.TryEvent(VE, ItemProperties))
                {
                    await runner.ExecuteAsync(VE, ItemProperties, false);
                    if (MaxUses != 0)
                    {
                        Uses++;
                        if (Uses >= MaxUses)
                        {
                            Per.Inventory.RemoveSpecific(this);
                        }
                    }
                }
            }
        }
        // }
    }
    VisualEvent* GetItemEvent()
    {
        VisualEvent* VE = NULL;
        if (!(EventName.isNull() || EventName.contains(QRegExp("^\\s*$"))))
            VE = VisualEventManager.GetEventByFilename(EventName, VisualEventKind.ItemEvent);

        if (VE) return VE;

        VE = VisualEventManager.GetEventByFilename(DisplayName + "_ItemEvent", VisualEventKind.ItemEvent);
        if (VE) return VE;

        if (DisplayName != Name)
            return VisualEventManager.GetEventByFilename(Name + "_ItemEvent", VisualEventKind.ItemEvent);
        return VE;
    }
    bool ShouldBePickedUpBy(Person& Per)
    {
        if (Per != Game.HeadTeacher && (IsSpecial || HideFromMenu || IsContainer))
            return false;

        VisualEvent* VE = VisualEventManager.GetEventByFilename(DisplayName + "_ItemEvent", VisualEventKind.ItemEvent);
        if (VE == NULL && DisplayName != Name)
        {
            VE = VisualEventManager.GetEventByFilename(Name + "_ItemEvent", VisualEventKind.ItemEvent);
            if (VE == NULL)
                return false;
        }
        ItemProperties.Item = this;
        ItemProperties.User = Per;
        ItemProperties.Mode = 1;

        return true;
    }
    void AddToSellLocation(Location& loc)
    {
        if (!SellLocationName.contains(QRegExp(loc.Name.prepend("(^|,)")+"(,|$)")))
            SellLocationName += "," + loc.Name;
    }
    void RemoveFromSellLocation(Location loc)
    {
        SellLocationName.replace("(?|(^)%s(?:,|$)|(^|,)%s,)", "\\1");
    }
    void AddToBuyLocation(Location loc)
    {
        if (!BuyLocationName.contains(QRegExp(loc.Name.prepend("(^|,)")+"(,|$)")))
            BuyLocationName += "," + loc.Name;
    }
    void RemoveFromBuyLocation(Location loc)
    {
        BuyLocationName.replace("(?|(^)%s(?:,|$)|(^|,)%s,)", "\\1");
    }
    object Clone()
    {
        return MemberwiseClone();
    }
    bool Equals(object obj)
    {
        bool Equals;
        if (obj == this)
        {
            Equals = true;
        }
        else if (obj is Item)
        {
            Item itm = (Item)obj;
            Equals = (itm.DisplayName.Equals(DisplayName) && itm.Description.Equals(Description) && itm.ItemGroup.Equals(ItemGroup) && itm.IsSpecial == IsSpecial && itm.IsContainer == IsContainer && itm.IsActive == IsActive && itm.IsAutomatic == IsAutomatic && itm.CanTrade == CanTrade && itm.BreakInLevel == BreakInLevel && itm.SecurityLevel == SecurityLevel && itm.KeyName.Equals(KeyName) && itm.BuyLocationName.Equals(BuyLocationName) && itm.SellLocationName.Equals(SellLocationName) && itm.BuyPrice == BuyPrice && itm.SellPrice == SellPrice && itm.Counter == Counter && itm.Data.Equals(Data) && itm.Uses == Uses && itm.MaxUses == MaxUses && itm.ImageLocation.Equals(ImageLocation) && itm.HideFromMenu.Equals(HideFromMenu) && itm.Inventory.Equals(Inventory));
        }
        else
        {
            Equals = false;
        }
        return Equals;
    }
    QString ToString()
    {
        return "Item: " + Name;
    }
};

#endif // ITEM_H
