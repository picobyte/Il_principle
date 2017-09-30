#ifndef EVENTSTRUCTMANAGER_H
#define EVENTSTRUCTMANAGER_H
#include <QDir>
#include "theworld.h"
#include "json_macros.h"
#include "eventstructdefinition.h"

class EventStructManager {
    QHash<QString, QHash<QString, VarType>* > StructDefinitions;
public:

    EventStructManager()
    {
        LoadStructDefinitions();
    }
    QHash<QString, VarType>* GetStructDefinition(QString& structName)
    {
        return StructDefinitions.value(structName);
    }
    void LoadStructDefinitions()
    {
        QDir dir;
        dir.setCurrent(QCoreApplication::applicationDirPath()+"/../Il_principle/Schools/"+TheWorld::FolderLocation+"/StructTemplates");
        QDirIterator it(dir.path(), QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QString fname = it.next();
            QFile f(fname);
            if (!f.open(QIODevice::ReadOnly)) {
                qWarning(QString("Couldn't open file ").append(fname).toUtf8());
                continue;
            }
            QJsonObject d = QJsonDocument::fromJson(f.readAll()).object().value("EventStructDefinition").toObject();
            QHash<QString, VarType>* defs = new QHash<QString, VarType>();

            foreach(QJsonValue val, d.value("Item").toArray()) {
                QJsonObject el = val.toObject();
                QString value = el.value("@Value").toString();
                QString key = el.value("@Key").toString();

                if (value == "VT_Any")
                    defs->insert(key, VarType::Any);
                else if (value == "VT_Int")
                    defs->insert(key, VarType::Int);
                else if (value == "VT_Dbl")
                    defs->insert(key, VarType::Dbl);
                else if (value == "VT_Bool")
                    defs->insert(key, VarType::Bool);
                else if (value == "VT_Str")
                    defs->insert(key, VarType::Str);
                else if (value == "VT_StrList")
                    defs->insert(key, VarType::StrList);
                else if (value == "VT_Date")
                    defs->insert(key, VarType::Date);
                else if (value == "VT_Obj")
                    defs->insert(key, VarType::Obj);
                else if (value == "VT_ObjList")
                    defs->insert(key, VarType::ObjList);
                else if (value == "VT_DblDictionary")
                    defs->insert(key, VarType::DblDictionary);
                else if (value == "VT_StrDictionary")
                    defs->insert(key, VarType::StrDictionary);
                else if (value == "VT_StructDictionary")
                    defs->insert(key, VarType::StructDictionary);
            }
            StructDefinitions.insert(d.value("Name").toString(), defs);
        }
    }
    bool IsValidEventStruct(QString& structName)
    {
        QHash<QString, QHash<QString, VarType>* >::iterator f = StructDefinitions.find(structName);
        if (f == StructDefinitions.end())
            return false;

        foreach (VarType type, f.value()->values())
            if (type == VarType::Any)
                return false;

        return true;
    }
};

#endif // EVENTSTRUCTMANAGER_H
