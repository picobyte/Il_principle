
#include "person.h"
#include "personrelationshipdatabase.h"

void PersonRelationshipDatabase::SetRelationshipValue(Person& owner, Person& target, double value, bool add_to = false)
{
    uint64_t key = owner.UID | (target.UID << 32);
    QHash<uint64_t, double>::iterator it = relationship_table.find(key);
    if (it == relationship_table.end())
        relationship_table.insert(key, value);
    else
        it->value = add_to ? it->value + value : value;
}
void PersonRelationshipDatabase::AddRelationshipValue(Person& owner, Person& target, double value)
{
    SetRelationshipValue(owner, target, value, true);
}
double PersonRelationshipDatabase::GetRelationshipValue(Person& owner, Person& target) const
{
    return relationship_table.value(owner.UID | (target.UID << 32));
}
void PersonRelationshipDatabase::SetRelationshipDataDict(Person& owner, Person& target, QString& tag, int  value, bool add_to = false)
{
    uint64_t key = owner.UID | (target.UID << 32);
    QHash<uint64_t, relationshipdata_entry>::iterator rsdt = relationshipdata_table.find(key);
    if (rsdt == relationship_table.end()) {
        if (relationship_table.find(key) == relationship_table.end())
            relationship_table.insert(it, {.ownerId = owner.UID, .targetId = target.UID, .value = 0.0});
        relationshipdata_table.insert(key, {.dataKey = tag, .dataValue = value});
    } else {
        rsdt->dataValue = add_to ? rsdt->dataValue + value : value;
        rsdt->dataKey = tag;
    }
}
void PersonRelationshipDatabase::AddRelationshipDataDict(Person& owner, Person& target, QString& tag, int value)
{
    SetRelationshipDataDict(owner, target, value, tag, true);
}
int PersonRelationshipDatabase::GetRelationshipDataDict(Person& owner, Person& target, QString& tag)
{
    QHash<uint64_t, relationshipdata_entry>::iterator it = relationshipdata_table.find(owner.UID | (target.UID << 32));
    return it != relationship_table.end() && it->dataKey == tag ? it->dataValue : 0;
}
bool PersonRelationshipDatabase::TagExists(Person owner, Person target, QString tag)
{
    QHash<uint64_t, relationshipdata_entry>::iterator it = relationshipdata_table.find(owner.UID | (target.UID << 32));
    return it != relationship_table.end() && it->dataKey == tag;
}

