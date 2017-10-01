#ifndef INVENTORYCOLLECTION_H
#define INVENTORYCOLLECTION_H

#include "json_macros.h"
#include <item.h>

struct InvItem
{

};

class InventoryCollection {
    QHash<QString, InvItem> inventory;
public:
    bool IsEmpty() const
    {
        return inventory.count() == 0;
    }
    //XmlSchema GetSchema() // obsolete
    void ReadXml(XmlReader reader)
    {
        XmlSerializer keySerializer = new XmlSerializer(typeof(QString));
        XmlSerializer valueListSerializer = new XmlSerializer(typeof(InventoryList));
        if (!reader.IsEmptyElement)
        {
            reader.Read();
            while (reader.NodeType != XmlNodeType.EndElement)
            {
                reader.ReadStartElement("invEntry");
                reader.ReadStartElement("name");
                QString key = (QString)keySerializer.Deserialize(reader);
                reader.ReadEndElement();
                reader.ReadStartElement("entries");
                InventoryList valueList = (InventoryList)valueListSerializer.Deserialize(reader);
                reader.ReadEndElement();
                Add(key, valueList);
                reader.ReadEndElement();
                reader.MoveToContent();
            }
            reader.ReadEndElement();
        }
    }
    void WriteXml(XmlWriter writer)
    {
        XmlSerializer keySerializer = new XmlSerializer(typeof(QString));
        XmlSerializer valueListSerializer = new XmlSerializer(typeof(InventoryList));
        // try {
        SortedDictionary<QString, InventoryList>.Enumerator enumerator = GetEnumerator();
        while (enumerator.MoveNext())
        {
            KeyValuePair<QString, InventoryList> kvp = enumerator.Current;
            writer.WriteStartElement("invEntry");
            writer.WriteStartElement("name");
            keySerializer.Serialize(writer, kvp.Key);
            writer.WriteEndElement();
            writer.WriteStartElement("entries");
            valueListSerializer.Serialize(writer, kvp.Value);
            writer.WriteEndElement();
            writer.WriteEndElement();
        }
        // }
    }
    object Clone()
    {
        InventoryCollection NewInventory = new InventoryCollection();
        // try {
        for (SortedDictionary<QString, InventoryList>::iterator it = Keys.begin();
                it != Keys.end(); ++it)
        {
            QString key = enumerator.Current;
            InventoryList Lst = new InventoryList();
            // try {
            QList<Item>.Enumerator enumerator2 = base[key].GetEnumerator();
            while (enumerator2.MoveNext())
            {
                Item Itm = enumerator2.Current;
                Lst.Add((Item)Itm.Clone());
            }
            // }
            NewInventory.Add(key, Lst);
        }
        // }
        return NewInventory;
    }
    int AddInventory(Item& obj)
    {
        if (ContainsKey(obj.DisplayName))
        {
            base[obj.DisplayName].Add(obj);
            return base[obj.DisplayName].count();
        }
                InventoryList cilist = new InventoryList();
                cilist.Add(obj);
                Add(obj.DisplayName, cilist);
                return cilist.count();
    }
    int CloneIntoInventory(Item obj, int quantity = 1)
    {
        if (obj == NULL) {
            throw new ArgumentNullException("obj");
        }
        QString.IsNullOrEmpty(obj.DisplayName);
        if (quantity < 1) {
            throw new ArgumentException("Adding to inventory must have positive quantity.", Conversions.ToString(quantity));
        }
        InventoryList clonelist = new InventoryList(quantity);
        // checked {
        for (int i = 0; i < quantity; i++)
            clonelist.Add((Item)obj.Clone());

        if (ContainsKey(obj.DisplayName)) {

            base[obj.DisplayName].AddRange(clonelist);
            return base[obj.DisplayName].count();
        }
        Add(obj.DisplayName, clonelist);
        return clonelist.count();
        // }
    }
    bool HasItem(QString displayName)
    {
        return ContainsKey(displayName);
    }
    bool HasKey(QString keyName)
    {
        // try {
        for (SortedDictionary<QString, InventoryList>::iterator it = Keys.begin();
                it != Keys.end(); ++it) {

            QString key = enumerator.Current;
            if (key.StartsWith(keyName) && key.EndsWith("Key"))
                return true;
        }
        // }
        // try {
        for (SortedDictionary<QString, InventoryList>::iterator it = Values.begin();
                it != Values.end(); ++it) {

            QList<Item> itmList = enumerator2.Current;
            // try {
            for (QList<Item>::iterator it2 = itmList.begin();
                    it2 != itmList.end(); ++it2) {

                Item itm = enumerator3.Current;
                if (itm.IsContainer && itm.Inventory.HasKey(keyName))
                    return true;
            }
            // }
        }
        // }
        return false;
    }
    bool HasKey(ILock LockData)
    {
        // try {
        for (SortedDictionary<QString, InventoryList>::iterator it = Keys.begin();
                it != Keys.end(); ++it)
            if (enumerator.Current.Equals(LockData.KeyName))
                return true;

        // }
        // try {
        for (SortedDictionary<QString, InventoryList>::iterator it = Values.begin();
                it != Values.end(); ++it) {

            InventoryList itmList = enumerator2.Current;
            // try {
            for (QList<Item>::iterator it2 = itmList.begin();
                    it2 != itmList.end(); ++it2) {

                Item itm = enumerator3.Current;
                if (itm.IsContainer && itm.Inventory.HasKey(LockData))
                    return true;
            }
            // }
        }
        // }
        return false;
    }
    Item GetItemObject(QString displayName)
    {
        Item GetItemObject;
        if (ContainsKey(displayName))
            return base[displayName][0];

        return NULL;

    }
    int SubtractInventory(QString displayName)
    {
        if (!ContainsKey(displayName))
            return 0;

        InventoryList expr_14 = base[displayName];
        expr_14.RemoveAt(0);
        if (expr_14.count() == 0)
            Remove(displayName);

        return expr_14.count();
    }
    Item TakeInventory(QString displayName)
    {
        if (!ContainsKey(displayName))
            return NULL;

        InventoryList expr_14 = base[displayName];
        Item itm = expr_14[0];
        expr_14.RemoveAt(0);
        if (expr_14.count() == 0)
            Remove(displayName);

        return itm;
    }
    void RemoveSpecific(Item itemRef)
    {
        if (itemRef == NULL) {
            throw new ArgumentNullException("itemRef", "RemoveSpecific got NULL inventory item");
        }
        if (ContainsKey(itemRef.DisplayName)) {

            base[itemRef.DisplayName].Remove(itemRef);
            if (base[itemRef.DisplayName].count() == 0)
                Remove(itemRef.DisplayName);
        }
    }
    void RemoveAll(QString name)
    {
        Remove(name);
    }
    bool Equals(object obj)
    {
        bool Equals;
        if (obj == this)
            return true;

        if (obj is InventoryCollection) {
            InventoryCollection inv = (InventoryCollection)obj;
            if (inv.Keys.count() != Keys.count())
                return false;

            // try {
            for (SortedDictionary<QString, InventoryList>::iterator it = inv.Keys.begin();
                    it != inv.Keys.end(); ++it) {
                QString i = enumerator.Current;
                if (!HasKey(i) || !inv[i].Equals(base[i]))
                    return false;
            }
            // }
            return true;
        }
        return false;
    }

    InventoryCollection(QJsonObject *d = NULL) {}
};

#endif // INVENTORYCOLLECTION_H
