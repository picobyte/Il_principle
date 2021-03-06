#include "game.h"

#define __init_dict_if_key(it, _key, _as) \
    if (it.key() == #_key) {\
        QJsonObject v = it.value().toObject();\
        _as[v["Name"].toString()] = _key(&v);\
    }

bool Game::jsonLoad(QString f)
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

bool Game::jsonSave(QString f) const
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

Game::Game(const char * school):
    GameCulture("en-GB"),
    EventLogflag(false),
    DesiredNumSchoolClasses(2),
    TickCount(0),
    LastWorldLocationPath(""),
    GameInitialized(false),
    GameLoading(false),
    LastAutosaveDay(1),
    CheatsUsed(false)
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
