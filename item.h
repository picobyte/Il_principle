#ifndef ITEM_H
#define ITEM_H
#include "json_macros.h"

class Item {
public:
	const QString DisplayName() const
	{
		QString DisplayName;
		if (QString.IsNullOrEmpty(intDisplayName))
		{
			return Name;


	{
		return intDisplayName;

	}
	const QString InventoryName() const
	{
		return DisplayName;
	}
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
		return IsContainer && !Inventory.IsEmpty;
	}
	bool ShouldSerializeEventName()
	{
		return !(EventName.isNull() || EventName.contains(QRegExp("^\\s*$")));
	}
	async Task UsedBy(Person Per)
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
	VisualEvent GetItemEvent()
	{
		VisualEvent VE = NULL;
		if (!(EventName.isNull() || EventName.contains(QRegExp("^\\s*$"))))
		{
			VE = VisualEventManager.GetEventByFilename(EventName, VisualEventKind.ItemEvent);
		}
		if (VE == NULL)
		{
			VE = VisualEventManager.GetEventByFilename(DisplayName + "_ItemEvent", VisualEventKind.ItemEvent);
		}
		if (VE == NULL && Operators.CompareString(DisplayName, Name, false) != 0)
		{
			VE = VisualEventManager.GetEventByFilename(Name + "_ItemEvent", VisualEventKind.ItemEvent);
		}
		return VE;
	}
	bool ShouldBePickedUpBy(Person Per)
	{
		bool ShouldBePickedUpBy;
		if (Per != Game.HeadTeacher && (IsSpecial || HideFromMenu || IsContainer))
		{
			ShouldBePickedUpBy = false;
		}
		else
		{
			VisualEvent VE = VisualEventManager.GetEventByFilename(DisplayName + "_ItemEvent", VisualEventKind.ItemEvent);
			if (VE == NULL && Operators.CompareString(DisplayName, Name, false) != 0)
			{
				VE = VisualEventManager.GetEventByFilename(Name + "_ItemEvent", VisualEventKind.ItemEvent);
			}
			if (VE != NULL)
			{
				ItemProperties.Item = this;
				ItemProperties.User = Per;
				ItemProperties.Mode = 1;
				ShouldBePickedUpBy = VE.TryEvent(ItemProperties);
			}
			else
			{
				ShouldBePickedUpBy = false;
			}
		}
		return ShouldBePickedUpBy;
	}
	void AddToSellLocation(Location loc)
	{
		if (!SellLocationName.Split(new char[]
		{
			','
		}, StringSplitOptions.RemoveEmptyEntries).ToList<QString>().contains(loc.Name))
		{
			SellLocationName = (SellLocationName + "," + loc.Name).TrimStart(new char[]
			{
				','
			});
		}
	}
	void RemoveFromSellLocation(Location loc)
	{
		QList<QString> sellLocations = SellLocationName.Split(new char[]
		{
			','
		}, StringSplitOptions.RemoveEmptyEntries).ToList<QString>();
		if (sellLocations.contains(loc.Name))
		{
			StringBuilder sb = new StringBuilder();
			// try {
			foreach (QString s in sellLocations)
			{
				if (!s.Equals(loc.Name))
				{
					sb.append(s).append(',');
				}
			}
			// }
			SellLocationName = sb.ToString().TrimEnd(new char[]
			{
				','
			});
		}
	}
	void AddToBuyLocation(Location loc)
	{
		if (!BuyLocationName.Split(new char[]
		{
			','
		}, StringSplitOptions.RemoveEmptyEntries).ToList<QString>().contains(loc.Name))
		{
			BuyLocationName = (BuyLocationName + "," + loc.Name).TrimStart(new char[]
			{
				','
			});
		}
	}
	void RemoveFromBuyLocation(Location loc)
	{
		QList<QString> buyLocations = BuyLocationName.Split(new char[]
		{
			','
		}, StringSplitOptions.RemoveEmptyEntries).ToList<QString>();
		if (buyLocations.contains(loc.Name))
		{
			StringBuilder sb = new StringBuilder();
			// try {
			for (QList<QString>::iterator it = buyLocations.begin();
					it != buyLocations.end(); ++it)
			{
				QString s = enumerator.Current;
				if (!s.Equals(loc.Name))
				{
					sb.append(s).append(',');
				}
			}
			// }
			BuyLocationName = sb.ToString().TrimEnd(new char[]
			{
				','
			});
		}
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
