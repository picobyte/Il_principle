#include "game.h"

namespace Game {
Location* PlayerLocation() const
{
    if (HeadTeacher == NULL)
        return NULL;

    return &HeadTeacher->CurrentLocation;
}

QString GetPersonDisplayName(QString& PerName)
{
    Person* per = GetPerson(PerName);
    if (per != NULL)
        return per->DisplayName;

    return PerName;
}

void RecalculateStaffSalary()
{

    int Total = 0;
    for (QMap<QString, Person*>::iterator Per = HiredStaff.begin(); Per != HiredStaff.end(); ++Per) {
        Total -= (*Per)->Salary;
    }
    if (!DictOfAccounts.contains("Staff Salary"))
        DictOfAccounts.insert("Staff Salary", Account("Staff Salary", 0, Payperiode::Monthly, false, true));

    DictOfAccounts["Staff Salary"].Payment = Total;
}

#define __init_dict_if_key(it, _key, _as) \
    if (it.key() == #_key) {\
    QJsonObject v = it.value().toObject();\
    _as[v["Name"].toString()] = _key(&v);\
}


bool jsonLoad(QString f)
{
    QFile loadFile(f);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();


    QJsonDocument loadDoc(f.endsWith("json") ? QJsonDocument::fromJson(saveData)
                                             : QJsonDocument::fromBinaryData(saveData));
    QJsonObject d = loadDoc.object();
    QJsonObject::iterator it;
    for (it = d.begin(); it != d.end(); ++it) {
        observed_keys.insert(it.key());
        if(it.key() != "SchoolUpgrade") {
            return true;
        }
        __init_dict_if_key(it, Account, DictOfAccounts)
                else __init_dict_if_key(it, Clubs, ListOfClubs)
                else __init_dict_if_key(it, Stat, DictOfStats)
                else __init_dict_if_key(it, Skill, DictOfSkills)
                else __init_dict_if_key(it, Rule, ListOfRules)
                else __init_dict_if_key(it, SchoolSubject, DictOfSubjects)
                else __init_dict_if_key(it, Item, ListOfBaseItems)
                else __init_dict_if_key(it, StatusEffect, DictOfStatusEffects)
                else if (it.key() == "SchoolUpgrade") {
            QJsonObject v = it.value().toObject();
            SchoolUpgrade su(&v);
            ListOfSchoolUpgrades.insert(su);
        }
    }

    if (data.contains(f))
        qFatal(f.append(" already exists in object").toUtf8());
    data[f] = loadDoc.object();
    return true;
}
#undef __init_if_key

bool jsonSave(QString f) const
{
    QFile saveFile(f);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    //For testing:
    QJsonDocument saveDoc(data);
    saveFile.write(f.endsWith("json") ? saveDoc.toJson() : saveDoc.toBinaryData());

    return true;
}

Game(const char * school)
{
    QDir dir;
    dir.setCurrent(QCoreApplication::applicationDirPath()+"/../Il_principle/Schools/"+school);
    QDirIterator it(dir.path(), QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        jsonLoad(it.next());
    qWarning(QString("observed keys: ").append(observed_keys.toList().join(", ")).toUtf8());
    //qInfo(QString::asprintf("loaded %d Accounts", DictOfAccounts.count()).toUtf8());

    qInfo(QString::asprintf("%d files remaining", data.count()).toUtf8());
    dir.setCurrent(QCoreApplication::applicationDirPath()+"/../Il_principle/save");
    jsonSave("test.json");
    //QStringList imagesList = directory.entryList(QStringList("*.json"));

}
Location* GetWorkForJob(QString& JobName)
{
    QHash<const QString&, Location>::iterator it;
    for (it = TheWorld::DictOfLocation.begin(); it != TheWorld::DictOfLocation.end(); ++it)
        if (it->JobTitle == JobName && !it->IsFullyStaffed())
            return &(*it);
}
}
