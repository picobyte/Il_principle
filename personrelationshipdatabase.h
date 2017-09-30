#ifndef PERSONRELATIONSHIPDATABASE_H
#define PERSONRELATIONSHIPDATABASE_H
#include "json_macros.h"


struct relationshipdata_entry {
    QString dataKey;
    int dataValue;
};

class person;
class PersonRelationshipDatabase {
    QHash<uint64_t, double> relationship_table;
    QHash<uint64_t, relationshipdata_entry> relationshipdata_table;
public:

    PersonRelationshipDatabase(QJsonObject *d = NULL) {}
    //void InitializeTables() {} // obsolete
    void DeleteTables()
    {
        relationship_table.clear();
        relationshipdata_table.clear();
    }
    void SetRelationshipValue(Person& owner, Person& target, double value, bool add_to = false);
    void AddRelationshipValue(Person& owner, Person& target, double value);
    double GetRelationshipValue(Person& owner, Person& target) const;
    void SetRelationshipDataDict(Person& owner, Person& target, QString& tag, int  value, bool add_to = false);
    void AddRelationshipDataDict(Person& owner, Person& target, QString& tag, int value);
    int GetRelationshipDataDict(Person& owner, Person& target, QString& tag);
    bool TagExists(Person owner, Person target, QString tag);
    //QString ExecuteCommand(QString sql)// no longer supported (only used in debugwindow)
    XmlSchema GetSchema()
    {
        return NULL;
    }
    void WriteXml(XmlWriter writer)
    {
            writer.WriteStartElement("Tables");
            SerializeTable(writer, "relationships");
            SerializeTable(writer, "relationshipdata");
            writer.WriteEndElement();

    }
    void ReadXml(XmlReader reader)
    {
        DeleteTables();
        bool arg_38_0 = reader.IsEmptyElement;
        reader.Read();
        if (!arg_38_0)
        {
            reader.ReadStartElement("Tables");
            DeserializeTables(reader);
            reader.ReadEndElement();
        }
    }
};

#endif // PERSONRELATIONSHIPDATABASE_H
