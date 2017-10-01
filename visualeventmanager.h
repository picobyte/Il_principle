#ifndef VISUALEVENTMANAGER_H
#define VISUALEVENTMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "json_macros.h"
#include "visualevent.h"
#include "theworld.h"
#include "game.h"
#include "location.h"

namespace VisualEventManager {
    QList<VisualEvent*> FunctionEvents;
    QHash<QString, QList<VisualEvent*>* > ExtensionEvents;
    QList<VisualEvent*> InteractionEvents;
    QList<VisualEvent*> StaticEvents;
    QList<VisualEvent*> NativeEvents;
    QList<VisualEvent*> ItemEvents;
    QList<VisualEvent*> PaperDollHandlers;
    QList<VisualEvent*> ScheduleHandlers;
    QList<VisualEvent*> ResponseEvents;
    QList<VisualEvent*> LocationMasterEvents;
    QList<VisualEvent*> LocationEvents;
    QList<VisualEvent*> PersonAttachedEvents;
    QList<VisualEvent*> ClubEvents;

    QString ChoppedFilename(QString& filename)
    {
        return QFileInfo(filename).canonicalFilePath().replace(QRegExp(QString("(?:)")+Game::GamePath.toUtf8()+"/"+TheWorld::FolderLocation.toUtf8()+")?Events/"), "");
    }
    VisualEventKind DetermineEventKind(QString& filename)
    {
        if (filename.isEmpty())
            qFatal("Empty filename not allowed");

        QString s = ChoppedFilename(filename);
        if (s.startsWith("FunctionLibrary"))
            return VisualEventKind::FunctionEvent;

        if (s.startsWith("ExtensionLibrary"))
            return VisualEventKind::ExtensionEvent;

        if (s.startsWith("Interactions"))
            return VisualEventKind::InteractionEvent;

        if (s.startsWith("StaticEvents"))
            return VisualEventKind::StaticEvent;

        if (s.startsWith("Location"))
            return VisualEventKind::LocationEvent;

        if (s.startsWith("ClubEvents"))
            return VisualEventKind::ClubEvent;

        if (s.startsWith("NativeEvents"))
            return VisualEventKind::NativeEvent;

        if (s.startsWith("PaperDollHandlers"))
            return VisualEventKind::PaperDollHandler;

        if (s.startsWith("ScheduleHandlers"))
            return VisualEventKind::ScheduleHandler;

        if (s.startsWith("PersonAttached"))
            return VisualEventKind::PersonAttachedEvent;

        if (s.startsWith("ItemEvents") || s.endsWith("ItemEvent") || s.endsWith("ItemEvent.ve.xml") || s.endsWith("ItemPickedUp") || s.endsWith("ItemPickedUp.ve.xml"))
            return VisualEventKind::ItemEvent;

        return VisualEventKind::NONE;

    }
    VisualEvent* GetEventByFilename(QString& filename, VisualEventKind kind = VisualEventKind::NONE)
    {
        if (kind == VisualEventKind::NONE)
            kind = DetermineEventKind(filename);

        QString chopped = ChoppedFilename(filename);
        QString namePlusExtension = chopped + ".ve.xml";
        QList<VisualEvent*>* ql = &LocationMasterEvents;
        switch (kind)
        {
        case VisualEventKind::FunctionEvent:
            ql = &FunctionEvents;
            break;
        case VisualEventKind::ExtensionEvent:
            foreach (QList<VisualEvent*>* ql, ExtensionEvents.values())
                for (QList<VisualEvent*>::iterator it = ql->begin(); it != ql->end(); ++it)
                    if ((*it)->jsonFileName.endsWith(namePlusExtension) || (*it)->jsonFileName.endsWith(chopped))
                        return *it;
            return NULL;
        case VisualEventKind::InteractionEvent:
            ql = &InteractionEvents;
            break;
        case VisualEventKind::StaticEvent:
            ql = &StaticEvents;
            break;
        case VisualEventKind::NativeEvent:
            ql = &NativeEvents;
            break;
        case VisualEventKind::ItemEvent:
            ql = &ItemEvents;
            break;
        case VisualEventKind::PersonAttachedEvent:
            ql = &PersonAttachedEvents;
            break;
        case VisualEventKind::ClubEvent:
            ql = &ClubEvents;
            break;
        case VisualEventKind::LocationEvent:
            for (QList<VisualEvent*>::iterator it = LocationEvents.begin(); it != LocationEvents.end(); ++it)
                if ((*it)->jsonFileName.endsWith(namePlusExtension) || (*it)->jsonFileName.endsWith(chopped))
                    return *it;
            break;
        case VisualEventKind::ResponseEvent:
            qFatal("Not implemented");
        case VisualEventKind::PaperDollHandler:
            ql = &PaperDollHandlers;
            break;
        case VisualEventKind::ScheduleHandler:
            ql = &ScheduleHandlers;
            break;
        default:
            for (QList<VisualEvent*>::iterator it = ItemEvents.begin(); it != ItemEvents.end(); ++it)
                if ((*it)->jsonFileName.endsWith(namePlusExtension) || (*it)->jsonFileName.endsWith(chopped))
                    return *it;
            for (QList<VisualEvent*>::iterator it = LocationEvents.begin(); it != LocationEvents.end(); ++it)
                if ((*it)->jsonFileName.endsWith(namePlusExtension) || (*it)->jsonFileName.endsWith(chopped))
                    return *it;
        }

        for (QList<VisualEvent*>::iterator it = ql->begin(); it != ql->end(); ++it)
            if ((*it)->jsonFileName.endsWith(namePlusExtension) || (*it)->jsonFileName.endsWith(chopped))
                return *it;

        return NULL;
    }
    Person* GetPersonObjectByEventFilename(QString& filename)
    {
        QString dirname = QFileInfo(filename).canonicalPath();
        for (QHash<QString, Person*>::iterator p = Game::DictOfPersonNames.begin(); p != Game::DictOfPersonNames.end(); ++p)
            if (dirname.contains(p.key().toLower().replace(" ", "").prepend("/") + "/"))
                return p.value();
        return NULL;
    }
    VisualEvent* GetLocationMasterEvent(Location& Loc);
    VisualEvent* AttachPersonEvent(const QString& filename, Person* P);
    VisualEvent* DetachPersonEvent(const QString& filename, Person* P);
    VisualEvent* LoadFunctionEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");

        VisualEvent LoadFunctionEvent;
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            FunctionEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        FunctionEvents.append(ev);
        return ev;
    }
    void LoadEventDependencies(VisualEvent* ev)
    {
        foreach (SeqOperation op, ev->SeqObjects) {
            if (op is SeqActLat_RemoteEvent) {
                SeqActLat_RemoteEvent remoteEvent = (SeqActLat_RemoteEvent)op;
                if (GetEventByFilename(remoteEvent.RemoteFileName, VisualEventKind::NONE) == NULL)
                    LoadEventDependencies(LoadEvent(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "Events", remoteEvent.RemoteFileName + ".ve.xml"), VisualEventKind::NONE));
            }
        }
        // try {
        for (QList<SeqVariable>::iterator it = ev->SeqVars.begin();
                it != ev->SeqVars.end(); ++it)
        {
            SeqVariable var = enumerator2.Current;
            if (var is SeqVar_Reference) {
                SeqVar_Reference refVar = (SeqVar_Reference)var;
                if (!filename.isEmpty() && GetEventByFilename(refVar.RefFileName, VisualEventKind::NONE) == NULL)
                    LoadEventDependencies(LoadEvent(Path.Combine(Game.GamePath, Game.TheSchool.FolderLocation, "Events", refVar.RefFileName + ".ve.xml"), VisualEventKind::NONE));
            }
        }
        // }
    }
    void ClearAllEvents()
    {
        FunctionEvents.clear();
        InteractionEvents.clear();
        StaticEvents.clear();
        NativeEvents.clear();
        ItemEvents.clear();
        PaperDollHandlers.clear();
        ScheduleHandlers.clear();
        ResponseEvents.clear();
        LocationMasterEvents.clear();
        LocationEvents.clear();
        ClubEvents.clear();
        PersonAttachedEvents.clear();
        foreach (QList<VisualEvent*>* lst, ExtensionEvents)
            lst->clear();

        ExtensionEvents.clear();
    }
    VisualEvent* LoadExtensionEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");

        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }

        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        int endIndex = ev->jsonFileName.LastIndexOf(Path.DirectorySeparatorChar);
        if (endIndex < 0)
            qFatal(QString("The filename of the event '").append(filename + "' was invalid. The event needs to be in a subfolder!").toUtf8());

        QString dictKey = ev->jsonFileName.Substring(0, endIndex);
        if (!ExtensionEvents.ContainsKey(dictKey))
            ExtensionEvents.append(dictKey, new QList<VisualEvent>());

        if (replaceExisting) {
            for (int i = 0; i < ExtensionEvents[dictKey].count(); i++) {
                if (ExtensionEvents[dictKey][i].jsonFileName.endsWith(ev->jsonFileName)) {
                    ExtensionEvents[dictKey].RemoveAt(i);
                    break;
                }
            }
        }
        ExtensionEvents[dictKey]->append(ev);
        return ev;
    }
    VisualEvent* LoadInteractionEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");

        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }

        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            InteractionEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        InteractionEvents.append(ev);
        return ev;

    }
    VisualEvent* LoadStaticEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            StaticEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        StaticEvents.append(ev);
        return ev;

    }
    VisualEvent* LoadNativeEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            NativeEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        NativeEvents.append(ev);
        return ev;

    }
    VisualEvent* LoadItemEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            ItemEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        ItemEvents.append(ev);
        return ev;

    }
    VisualEvent* LoadPaperDollHandler(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            PaperDollHandlers.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        PaperDollHandlers.append(ev);
        return ev;

    }
    VisualEvent* LoadScheduleHandler(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting)
            ScheduleHandlers.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(ev->jsonFileName));
        ScheduleHandlers.append(ev);
        return ev;

    }
    VisualEvent* LoadPersonAttachedEvent(QString& filename, bool replaceExisting = true, Person P = NULL)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        // checked {
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        if (replaceExisting) {
            int num = PersonAttachedEvents.count() - 1;
            for (int i = 0; i <= num; i++) {
                if (PersonAttachedEvents[i].jsonFileName.endsWith(ev->jsonFileName)) {
                    PersonAttachedEvents[i] = ev;
                    ev->UniqueID = (unsigned)i;
                    LoadPersonAttachedEvent = ev;
                    return LoadPersonAttachedEvent;
                }
            }
        }
        PersonAttachedEvents.append(ev);
        ev->UniqueID = (unsigned)(PersonAttachedEvents.count() - 1);
        if (P != NULL && !P.AttachedEventIDs.contains(ev->UniqueID))
            P.AttachedEventIDs.append(ev->UniqueID);
        return ev;

        // }
    }
    VisualEvent* LoadLocationEvent(QString& filename, bool replaceExisting = true)
    {
        _ClosureS__75_0 closureS__75_ = new _ClosureS__75_0();
        if (filename.isEmpty())
            qFatal("Filename required");
        // checked {
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        closureS__75_.SVBSLocal_ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        closureS__75_.SVBSLocal_ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        closureS__75_.SVBSLocal_ev->jsonFileName = ChoppedFilename(filename);
        if (closureS__75_.SVBSLocal_ev->TriggerType == TriggerType.LocationMaster) {
            if (replaceExisting)
                LocationMasterEvents.RemoveAll((VisualEvent oldEv) => oldev->jsonFileName.endsWith(closureS__75_.SVBSLocal_ev->jsonFileName));
            LocationMasterEvents.append(closureS__75_.SVBSLocal_ev);
        } else {
            if (replaceExisting) {
                int num = LocationEvents.count() - 1;
                for (int i = 0; i <= num; i++) {
                    if (LocationEvents[i].jsonFileName.endsWith(closureS__75_.SVBSLocal_ev->jsonFileName)) {
                        LocationEvents[i] = closureS__75_.SVBSLocal_ev;
                        closureS__75_.SVBSLocal_ev->UniqueID = (unsigned)i;
                        LoadLocationEvent = closureS__75_.SVBSLocal_ev;
                        return LoadLocationEvent;
                    }
                }
            }
            LocationEvents.append(closureS__75_.SVBSLocal_ev);
            closureS__75_.SVBSLocal_ev->UniqueID = (unsigned)(LocationEvents.count() - 1);
        }
        return closureS__75_.SVBSLocal_ev;

        // }
    }
    VisualEvent* LoadClubEvent(QString& filename, bool replaceExisting = true)
    {
        if (filename.isEmpty())
            qFatal("Filename required");
        // checked {
        if (!QFile(filename).exists()) {
            qWarning(QString("The file '").append(filename).append("' was not found and skipped during startup!").toUtf8());
            return NULL;
        }
        VisualEvent* ev = XMLSerialize<VisualEvent>.ReadFromXML(filename);
        ev->LastModificationDate = File.GetLastWriteTimeUtc(filename);
        ev->jsonFileName = ChoppedFilename(filename);
        if (replaceExisting) {
            int num = ClubEvents.count() - 1;
            for (int i = 0; i <= num; i++) {
                if (ClubEvents[i].jsonFileName.endsWith(ev->jsonFileName)) {
                    ClubEvents[i] = ev;
                    ev->UniqueID = (unsigned)i;
                    LoadClubEvent = ev;
                    return LoadClubEvent;
                }
            }
        }
        ClubEvents.append(ev);
        ev->UniqueID = (unsigned)(ClubEvents.count() - 1);
        return ev;

        // }
    }
    VisualEvent* LoadEvent(QString& filename, VisualEventKind kind = VisualEventKind::NONE)
    {
        if (kind == VisualEventKind::NONE)
            kind = DetermineEventKind(filename);

        switch (kind)
        {
        case VisualEventKind::FunctionEvent:
        {
            return LoadFunctionEvent(filename, true);
        }
        case VisualEventKind::ExtensionEvent:
        {
            return LoadExtensionEvent(filename, true);
        }
        case VisualEventKind::InteractionEvent:
        {
            return LoadInteractionEvent(filename, true);
        }
        case VisualEventKind::StaticEvent:
        {
            return LoadStaticEvent(filename, true);
        }
        case VisualEventKind::NativeEvent:
        {
            return LoadNativeEvent(filename, true);
        }
        case VisualEventKind::ItemEvent:
        {
            return LoadItemEvent(filename, true);
        }
        case VisualEventKind::PersonAttachedEvent:
        {
            return LoadPersonAttachedEvent(filename, true, NULL);
        }
        case VisualEventKind::ClubEvent:
        {
            return LoadClubEvent(filename, true);
        }
        case VisualEventKind::LocationEvent:
        {
            return LoadLocationEvent(filename, true);
        }
        case VisualEventKind::ResponseEvent:
            qFatal("Not implemented");
        case VisualEventKind::PaperDollHandler:
        {
            return LoadPaperDollHandler(filename, true);
        }
        case VisualEventKind::ScheduleHandler:
        {
            return LoadScheduleHandler(filename, true);
        }
        }
        qFatal(QString("Cannot load event based on kind NONE.\r\nFull path: ").append(filename + "\r\nChopped path: " + ChoppedFilename(filename)).toUtf8());
        return NULL;
    }
    bool TryNativeEvent(QString filename)
    {
        if (!filename.endsWith(".ve.xml"))
            filename += ".ve.xml";

        foreach (VisualEvent* ev, NativeEvents)
            if (ev->jsonFileName.endsWith(filename))
                return ev->TryEvent();

        return false;
    }
    bool TryNativeEvent(QString& filename, object argument)
    {
        if (!filename.endsWith(".ve.xml"))
            filename += ".ve.xml";

        foreach (VisualEvent* ev, NativeEvents)
            if (ev->jsonFileName.endsWith(filename))
                return ev->TryEvent(RuntimeHelpers.GetObjectValue(argument));

        return false;
    }
    void ExecuteNativeEvent(QString filename)
    {
        if (!filename.endsWith(".ve.xml"))
            filename += ".ve.xml";
        // try {
        foreach (VisualEvent* ev, NativeEvents) {
            if (ev->jsonFileName.endsWith(filename)) {
                ev->Execute();
                break;
            }
        }
        // }
    }
    void ExecuteNativeEvent(QString& filename, object argument)
    {
        if (!filename.endsWith(".ve.xml"))
            filename += ".ve.xml";
        // try {
        foreach (VisualEvent* ev, NativeEvents) {
            if (ev->jsonFileName.endsWith(filename)) {
                ev->Execute(RuntimeHelpers.GetObjectValue(argument));
                break;
            }
        }
        // }
    }
    Task ExecuteNativeEventAsync(QString filename)
    {
        VB_StateMachine_81_ExecuteNativeEventAsync vB_StateMachine_81_ExecuteNativeEventAsync = default(VB_StateMachine_81_ExecuteNativeEventAsync);
        vB_StateMachine_81_ExecuteNativeEventAsync.SVBSLocal_filename = filename;
        vB_StateMachine_81_ExecuteNativeEventAsync.SState = -1;
        vB_StateMachine_81_ExecuteNativeEventAsync.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_81_ExecuteNativeEventAsync.SBuilder.Start<VB_StateMachine_81_ExecuteNativeEventAsync>(ref vB_StateMachine_81_ExecuteNativeEventAsync);
        return vB_StateMachine_81_ExecuteNativeEventAsync.SBuilder.Task;
    }
    Task ExecuteNativeEventAsync(QString& filename, object argument)
    {
        VB_StateMachine_82_ExecuteNativeEventAsync vB_StateMachine_82_ExecuteNativeEventAsync = default(VB_StateMachine_82_ExecuteNativeEventAsync);
        vB_StateMachine_82_ExecuteNativeEventAsync.SVBSLocal_filename = filename;
        vB_StateMachine_82_ExecuteNativeEventAsync.SVBSLocal_argument = argument;
        vB_StateMachine_82_ExecuteNativeEventAsync.SState = -1;
        vB_StateMachine_82_ExecuteNativeEventAsync.SBuilder = AsyncTaskMethodBuilder.Create();
        vB_StateMachine_82_ExecuteNativeEventAsync.SBuilder.Start<VB_StateMachine_82_ExecuteNativeEventAsync>(ref vB_StateMachine_82_ExecuteNativeEventAsync);
        return vB_StateMachine_82_ExecuteNativeEventAsync.SBuilder.Task;
    }

};

#endif // VISUALEVENTMANAGER_H
