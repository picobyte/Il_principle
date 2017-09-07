#ifndef EVENTSTRUCTMANAGER_H
#define EVENTSTRUCTMANAGER_H
#include <QDir>
#include "json_macros.h"

class EventStructManager {
    QHash<QString, EventStructDefinition> StructDefinitions;
public:

    EventStructManager(QJsonObject *d = NULL)
    {
        StructDefinitions[""] = EventStructDefinition("");
        LoadStructDefinitions();
    }
    void init(QJsonObject *d) {}
    void AddStructDefinition(EventStructDefinition sd)
    {
        if (!StructDefinitions.contains(sd.Name) && EventStructManager.IsValidEventStruct(sd))
            StructDefinitions.Add(sd.Name, sd);
    }
    EventStructDefinition GetStructDefinition(QString structName)
    {
        EventStructDefinition GetStructDefinition;
        if (StructDefinitions.ContainsKey(structName))
            return StructDefinitions[structName];

        return NULL;
    }
    void LoadStructDefinitions()
    {
        // checked {
        if (Directory.Exists(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "StructTemplates"))) {

            QString[] files = Directory.GetFiles(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "StructTemplates"), "*.xml");
            for (int i = 0; i < files.Length; i++) {

                EventStructDefinition sd = XMLSerialize<EventStructDefinition>.ReadFromXML(files[i]);
                if (!StructDefinitions.ContainsKey(sd.Name))
                    StructDefinitions.Add(sd.Name, sd);
            }
        }
        // }
    }
    bool IsValidEventStruct(EventStructDefinition sd)
    {
        // try {
        for (QHash<QString, VarType>::iterator it = sd.MemberDefinitions.Keys.begin();
                it != sd.MemberDefinitions.Keys.end(); ++it) {

            QString memberDef = enumerator.Current;
            if (sd.MemberDefinitions[memberDef] == VarType.VT_Any)
                return false;
        }
        // }
        return true;
    }
};

#endif // EVENTSTRUCTMANAGER_H
