#ifndef gVISUALEVENT_H
#define gVISUALEVENT_H
#include <QString>
#include <QHash>
#include <QDateTime>
#include "json_macros.h"
#include "game.h"
#include "theworld.h"
#include "seqvariable.h"

class VisualEvent {
    QList<SeqOperation> SeqObjects;
    QList<SeqVariable> SeqVars;
    QList<SeqPeripheral> SeqPeripherals;
    QList<SeqOperation> PendingOperations;
    QHash<QString, QString> TextReplaceDict;
    QHash<QString, SeqVariable> ParamVars;
public:
    bool Accepted;
    SeqActLat_RemoteEvent ReturnRemote;
    QString Author;
    QString jsonFileName;
    QDateTime LastModificationDate;
    unsigned UniqueID;
    int SheduledFor;
    int SheduledForTime;
    bool Virtualize;
    TriggerType triggerType;
    int Priority;
    bool HighPriority;
    QPoint ButtonLocation;
    QString ButtonName;
    QString ChoiceName;
    QString Description;
    //readonly object dictLock;
    const QString ShortjsonFileName() const
    {
        QString ShortjsonFileName;
        if (!jsonFileName.startsWith(Game::GamePath))
            return jsonFileName;

        if (filename.isEmpty() || jsonFileName.Length < Path.Combine(Game::GamePath, TheWorld::FolderLocation, "Events\\").Length)
            return "";
        return jsonFileName.Substring(Path.Combine(Game::GamePath, TheWorld::FolderLocation, "Events\\").Length);
    }
    VisualEvent(QJsonObject *d = NULL)
    {
        if (d) init(d);
        Author = "";
        jsonFileName = "";
        UniqueID = 0u;
        Virtualize = false;
        //TriggerType = TriggerType.Location;
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJLIST_FROM_JSON(it, SeqObjects, SeqOperation)
            else __IF_OBJLIST_FROM_JSON(it, SeqVars, SeqVariable)
            else __IF_OBJLIST_FROM_JSON(it, SeqPeripherals, SeqPeripheral)
            else __IF_OBJLIST_FROM_JSON(it, PendingOperations, SeqOperation)
            else __IF_VAR_FROM_JSON_AS(it, Accepted, toBool)
            else __IF_OBJ_FROM_JSON(it, ReturnRemote)
            else __IF_VAR_FROM_JSON_AS(it, Author, toString)
            else __IF_VAR_FROM_JSON_AS(it, jsonFileName, toString)
            //else __IF_OBJ_FROM_JSON(it, LastModificationDate) //QDateTime
            else __IF_VAR_FROM_JSON_AS(it, UniqueID, toInt)
            else __IF_VAR_FROM_JSON_AS(it, SheduledFor, toInt)
            else __IF_VAR_FROM_JSON_AS(it, SheduledForTime, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Virtualize, toBool)
            else __IF_OBJ_FROM_JSON(it, TriggerType)
            else __IF_VAR_FROM_JSON_AS(it, Priority, toInt)
            else __IF_VAR_FROM_JSON_AS(it, HighPriority, toBool)
            //else __IF_OBJ_FROM_JSON(it, ButtonLocation) //QPoint
            else __IF_VAR_FROM_JSON_AS(it, ButtonName, toString)
            else __IF_VAR_FROM_JSON_AS(it, ChoiceName, toString)
            else __IF_VAR_FROM_JSON_AS(it, Description, toString)
            //else __IF_OBJ_FROM_JSON(it, dictLock)
            // *INDENT-ON*
        }
    }
    bool ShouldSerializejsonFileName()
    {
        return !jsonFileName.isEmpty();
    }
    bool ShouldSerializeLastModificationDate()
    {
        return Game::GameInitialized;
    }
    bool ShouldSerializeVirtualize()
    {
        return Virtualize;
    }
    bool ShouldSerializePriority()
    {
        return Priority != 0;
    }
    bool ShouldSerializeHighPriority()
    {
        return HighPriority;
    }
    bool ShouldSerializeButtonLocation()
    {
        return TriggerType == TriggerType.Button;
    }
    bool ShouldSerializeDescription()
    {
        return !(Description.isNull() || Description.contains(QRegExp("^\\s*$")));
    }
    bool ShouldSerializeTextReplaceDict()
    {
        return TextReplaceDict.count() > 0;
    }
    void PostGameInit()
    {
        foreach (SeqOperation it, SeqObjects)
            it.PostGameInit();

        foreach (SeqVariable it, SeqVars)
            it.PostGameInit();

        foreach (SeqPeripheral it, SeqPeripherals)
            it.PostGameInit();
    }
    void PostGameLoad()
    {
        foreach (SeqOperation it, SeqObjects)
            it.PostGameLoad();

        foreach (SeqVariable it, SeqVars)
            it.PostGameLoad();

        foreach (SeqPeripheral it, SeqPeripherals)
            it.PostGameLoad();
    }
    unsigned GetNextID()
    {
        unsigned Best = 0;
        foreach (SeqOperation Obj, SeqObjects)
            if (Obj.ID > Best)
                Best = Obj.ID;

        foreach (SeqVariable Var, SeqVars)
            if (Var.ID > Best)
                Best = Var.ID;

        foreach (SeqPeripheral Peri, SeqPeripherals)
            if (Peri.ID > Best)
                Best = Peri.ID;

        return checked((unsigned)(unchecked((ulong)Best) + 1uL));
    }
    void AddSeqObject(SeqObject ObjToAdd)
    {
        if (ObjToAdd is SeqOperation)
            SeqObjects.append((SeqOperation)ObjToAdd);
        else if (ObjToAdd is SeqVariable)
            SeqVars.append((SeqVariable)ObjToAdd);
        else if (ObjToAdd is SeqPeripheral)
            SeqPeripherals.append((SeqPeripheral)ObjToAdd);
    }
    void ReplaceSeqObject(SeqObject OldObject, SeqObject NewObject)
    {
        if (OldObject is SeqOperation && NewObject is SeqOperation) {
            int index = SeqObjects.IndexOf((SeqOperation)OldObject);
            SeqObjects.removeAt(index);
            SeqObjects.insert(index, (SeqOperation)NewObject);
            return;
        }
        if (OldObject is SeqVariable && NewObject is SeqVariable) {
            int index = SeqVars.IndexOf((SeqVariable)OldObject);
            SeqVars.removeAt(index);
            SeqVars.insert(index, (SeqVariable)NewObject);
            return;
        }
        if (OldObject is SeqPeripheral && NewObject is SeqPeripheral) {
            int index = SeqPeripherals.IndexOf((SeqPeripheral)OldObject);
            SeqPeripherals.removeAt(index);
            SeqPeripherals.insert(index, (SeqPeripheral)NewObject);
            return;
        }
        Interaction.MsgBox(QString.Format("Unable to replace {0} with {1} because the objects derive from different base types!", OldObject.Name, NewObject.Name), MsgBoxStyle.Exclamation, "Replace SeqObject");
    }
    void RemoveSeqObject(SeqOperation ObjToRemove)
    {
        SeqObjects.removeOne(ObjToRemove);
    }
    void RemoveSeqObject(SeqVariable ObjToRemove)
    {
        SeqVars.removeOne(ObjToRemove);
    }
    void RemoveSeqObject(SeqPeripheral ObjToRemove)
    {
        SeqPeripherals.removeOne(ObjToRemove);
    }
    SeqOperation FindSeqObjectByID(unsigned SearchID)
    {
        int imin = 0;
        int imax = SeqObjects.count() - 1;
        while (imax >= imin) {

            int imid = imin + (imax - imin) / 2;
            if (SeqObjects[imid].ID == SearchID)
                return SeqObjects[imid];

            if (SeqObjects[imid].ID < SearchID)
                imin = imid + 1;
            else
                imax = imid - 1;
        }
        return NULL;
    }
    SeqVariable FindSeqVarByID(unsigned SearchID, bool NoResolve = false)
    {
        SeqVariable Var = NULL;
        int imin = 0;
        // checked {
        int imax = SeqVars.count() - 1;
        while (imax >= imin) {

            int imid = imin + (imax - imin) / 2;
            if (SeqVars[imid].ID == SearchID) {
                Var = SeqVars[imid];
                break;
            }
            if (SeqVars[imid].ID < SearchID)
                imin = imid + 1;
            else
                imax = imid - 1;
        }
        if (Var is SeqVar_Reference && !NoResolve) {
            SeqVariable SeqVar = NULL;
            SeqVar_Reference RefVar = (SeqVar_Reference)Var;
            if (RefVar.TargetVar != NULL)
                SeqVar = RefVar.TargetVar;
            else {
                if (filename.isEmpty())
                    SeqVar = FindSeqVarByID(RefVar.RefID, false);
                else {
                    VisualEvent ev = VisualEventManager.GetEventByFilename(RefVar.RefFileName, VisualEventKind.NONE);
                    if (ev != NULL)
                        SeqVar = ev.FindSeqVarByID(RefVar.RefID, false);
                }
                RefVar.TargetVar = SeqVar;
            }
            return SeqVar;
        }
        return Var;
    }
    bool TryEvent()
    {
        return new EventRunner().TryEvent(this);
    }
    bool TryEvent(object Arg)
    {
        return new EventRunner().TryEvent(this, RuntimeHelpers.GetObjectValue(Arg));
    }
    bool TryEvent(QHash<QString, SeqVariable> Vars)
    {
        return new EventRunner().TryEvent(this, Vars);
    }
    void Execute()
    {
        new EventRunner().Execute(this);
    }
    void Execute(object Arg)
    {
        new EventRunner().Execute(this, RuntimeHelpers.GetObjectValue(Arg));
    }
    void Execute(QHash<QString, SeqVariable> Vars)
    {
        new EventRunner().Execute(this, Vars);
    }
    void Execute(object Arg, QHash<QString, SeqVariable> Vars)
    {
        new EventRunner().Execute(this, RuntimeHelpers.GetObjectValue(Arg), Vars);
    }
    void AddToDictionary(QString key, QString value)
    {
        object obj = dictLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (filename.isEmpty())
            throw new ArgumentNullException("nKey", "Tried to add an empty QString as key to the event dictionary!");

        TextReplaceDict[key] = value;
    }
    QString GetFromDictionary(QString key)
    {
        object obj = dictLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        QString GetFromDictionary;
        // lock (obj) {
        if (filename.isEmpty())
            throw new ArgumentNullException("aKey", "Tried to find an entry for an empty key QString in the event dictionary!");

        if (TextReplaceDict.ContainsKey(key))
            GetFromDictionary = TextReplaceDict[key];
 else {
            GetFromDictionary = "";
        }
        return GetFromDictionary;
    }
    void RemoveFromDictionary(QString key)
    {
        object obj = dictLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (filename.isEmpty())
            throw new ArgumentNullException("aKey", "Tried to remove an empty key QString from the event dictionary!");

        TextReplaceDict.remove(key);
    }
    QString ProcessTextInDictionary(QString T)
    {
        object obj = dictLock;
        ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        QString ProcessTextInDictionary;
        // lock (obj) {
        if (TextReplaceDict.count() > 0) {
            StringBuilder sb = new StringBuilder(T);
            for (QHash<QString, QString>::iterator it = TextReplaceDict.begin();
                    it != TextReplaceDict.end(); ++it)
            {
                KeyValuePair<QString, QString> kvp = enumerator.Current;
                sb.Replace(kvp.Key, kvp.Value);
            }
            ProcessTextInDictionary = sb.ToString();
        } else {
            ProcessTextInDictionary = T;
        }
        return ProcessTextInDictionary;
    }
    void SortSeqObjects()
    {
        SeqObjects.Sort();
        SeqVars.Sort();
        SeqPeripherals.Sort();
    }
    QString ToString()
    {
        return "Visual Event: " + jsonFileName.Substring(checked(jsonFileName.LastIndexOf(Path.DirectorySeparatorChar) + 1));
    }
    void HandleSeqObjectReplacement(SeqObject oldObject, QString replacement)
    {
        // XXX: possibly a target for optimization
        SeqObject newObject = oldObject.ReplaceObject(replacement);
        // checked {
        if (newObject != NULL) {
            if (oldObject is SeqOperation) {
                unsigned[] NewIndices = ((SeqOperation)oldObject).UpdateInputLinksForReplacement(replacement);
                if (NewIndices != NULL) {
                    foreach (SeqOperation op, SeqObjects) {
                        if (op.OutputLinks.count() > 0) {
                            int num = op.OutputLinks.count() - 1;
                            for (int lnkID = 0; lnkID <= num; lnkID++) {
                                OutputLink link = op.OutputLinks[lnkID];
                                if (link.HasOutputs()) {
                                    int num2 = link.OutputIDs.count() - 1;
                                    for (int targetID = 0; targetID <= num2; targetID++)
                                        if (link.OutputIDs[targetID] == oldObject.ID && (int)link.OutputIndices[targetID] < NewIndices.count()<unsigned>())
                                            link.OutputIndices[targetID] = (byte)NewIndices[(int)link.OutputIndices[targetID]];
                                }
                            }
                        }
                    }
                }
            }
            ReplaceSeqObject(oldObject, newObject);
        }
    }
    QString AutoUpdateEvent()
    {
        AutoUpdateDeprecatedObjects();
        StringBuilder sb = new StringBuilder();
        foreach (SeqOperation SeqObj, SeqObjects) {
            QString fixedResult = SeqObj.AutoFixProperties();
            if (!(fixedResult.isNull() || fixedResult.contains(QRegExp("^\\s*$")))) {
                sb.AppendLine(QString.Format("--- {0} (ID: {1}) ---", SeqObj.Name, SeqObj.ID));
                sb.AppendLine(fixedResult);
            }
        }
        for (QList<SeqVariable>::iterator it = SeqVars.begin();
                it != SeqVars.end(); ++it)
        {
            SeqVariable SeqVar = enumerator2.Current;
            QString fixedResult2 = SeqVar.AutoFixProperties();
            if (!(fixedResult2.isNull() || fixedResult2.contains(QRegExp("^\\s*$")))) {
                sb.AppendLine(QString.Format("--- {0} (ID: {1}) ---", SeqVar.Name, SeqVar.ID));
                sb.AppendLine(fixedResult2);
            }
        }
        return sb.ToString();
    }
    QString CheckEventForErrors()
    {
        StringBuilder sb = new StringBuilder();
        QList<SeqObject> unlinkedObjs = new QList<SeqObject>();
        foreach (SeqOperation obj, SeqObjects)
            if (!(obj is SeqEvent) && !(obj is SeqAct_TODO))
                unlinkedObjs.append(obj);
        for (QList<SeqVariable>::iterator it = SeqVars.begin();
                it != SeqVars.end(); ++it)
        {
            SeqVariable obj2 = enumerator2.Current;
            unlinkedObjs.append(obj2);
        }
        // XXX: possibly a target for optimization
        for (QList<SeqOperation>::iterator it = SeqObjects.begin();
                it != SeqObjects.end(); ++it)
        {
            SeqOperation SeqObj = enumerator3.Current;
            QString result = SeqObj.CheckForErrors(this);
            if (!(result.isNull() || result.contains(QRegExp("^\\s*$")))) {
                sb.AppendLine(QString.Format("--- {0} (ID: {1}) ---", SeqObj.Name, SeqObj.ID));
                sb.AppendLine(result);
            }
            if (SeqObj is SeqOperation) {
                SeqOperation SeqOp = SeqObj;
                for (QList<OutputLink>::iterator it = SeqOp.OutputLinks.begin();
                        it != SeqOp.OutputLinks.end(); ++it)
                {
                    OutputLink link = enumerator4.Current;
                    for (QList<unsigned>::iterator it2 = link.OutputIDs.begin();
                            it2 != link.OutputIDs.end(); ++it2)
                    {
                        VisualEvent._ClosureS__122_0 closureS__122_ = new VisualEvent._ClosureS__122_0();
                        closureS__122_.SVBSLocal_id = checked((int)enumerator5.Current);
                        unlinkedObjs.RemoveAll((SeqObject uobj) => (ulong)uobj.ID == (ulong)((long)closureS__122_.SVBSLocal_id));
                    }
                }
                for (QList<VariableLink>::iterator it = SeqOp.VariableLinks.begin();
                        it != SeqOp.VariableLinks.end(); ++it)
                {
                    VariableLink link2 = enumerator6.Current;
                    for (QList<unsigned>::iterator it2 = link2.VariableIDs.begin();
                            it2 != link2.VariableIDs.end(); ++it2)
                    {
                        VisualEvent._ClosureS__122_1 closureS__122_2 = new VisualEvent._ClosureS__122_1();
                        closureS__122_2.SVBSLocal_id = checked((int)enumerator7.Current);
                        unlinkedObjs.RemoveAll((SeqObject uobj) => (ulong)uobj.ID == (ulong)((long)closureS__122_2.SVBSLocal_id));
                    }
                }
            }
        }
        for (QList<SeqVariable>::iterator it = SeqVars.begin(); it != SeqVars.end(); ++it) {
            SeqVariable SeqVar = enumerator8.Current;
            QString result2 = SeqVar.CheckForErrors(this);
            if (!(result2.isNull() || result2.contains(QRegExp("^\\s*$")))) {
                sb.AppendLine(QString.Format("--- {0} (ID: {1}) ---", SeqVar.Name, SeqVar.ID));
                sb.AppendLine(result2);
            }
            if (SeqVar is SeqVar_Reference) {
                VisualEvent._ClosureS__122_2 closureS__122_3 = new VisualEvent._ClosureS__122_2();
                closureS__122_3.SVBSLocal_refVar = (SeqVar_Reference)SeqVar;
                if (filename.isEmpty())
                    unlinkedObjs.RemoveAll((SeqObject uobj) => uobj.ID == closureS__122_3.SVBSLocal_refVar.RefID);

            }
        }
        if (unlinkedObjs.count() > 0) {
            using (UnlinkedObjsWarning msgBox = new UnlinkedObjsWarning(ShortjsonFileName))
            {
                msgBox.DisplayList(unlinkedObjs);
                msgBox.ShowDialog();
            }
        }
        WalkConnectedObjectsForErrors();
        return sb.ToString();
    }
    void AutoUpdateDeprecatedObjects()
    {
        // checked {
        int num = SeqObjects.count() - 1;
        for (int i = 0; i <= num; i++) {
            QString depStr = SeqObjects[i].DeprecatedBy();
            if (!filename.isEmpty() && !depStr.Equals("Obsolete"))
                HandleSeqObjectReplacement(SeqObjects[i], depStr);

        }
        int num2 = SeqVars.count() - 1;
        for (int j = 0; j <= num2; j++) {
            QString depStr2 = SeqVars[j].DeprecatedBy();
            if (!filename.isEmpty() && !depStr2.Equals("Obsolete"))
                HandleSeqObjectReplacement(SeqVars[j], depStr2);

        }
        int num3 = SeqPeripherals.count() - 1;
        for (int k = 0; k <= num3; k++) {
            QString depStr3 = SeqPeripherals[k].DeprecatedBy();
            if (!filename.isEmpty() && !depStr3.Equals("Obsolete"))
                HandleSeqObjectReplacement(SeqPeripherals[k], depStr3);

        }
    }
    void WalkConnectedObjectsForErrors()
    {
        SeqEvent EventStart = (SeqEvent)SeqObjects.Find((VisualEvent._ClosureS__.SI124_0 == NULL) ? (VisualEvent._ClosureS__.SI124_0 = new Predicate<SeqOperation>(VisualEvent._ClosureS__.SI._LambdaS__124_0)) : VisualEvent._ClosureS__.SI124_0);
        // checked {
        if (EventStart != NULL) {
            Queue<SeqOperation> OpQueue = new Queue<SeqOperation>();
            QList<unsigned> SeenEvents = new QList<unsigned>();
            OpQueue.Enqueue(EventStart);
            // XXX: possibly a target for optimization
            while (OpQueue.count() != 0) {
                SeqOperation CurOp = OpQueue.Dequeue();
                if (!SeenEvents.contains(CurOp.ID)) {
                    SeenEvents.append(CurOp.ID);
                    if (CurOp.CheckLinkTypes(this))
                        break;

                    foreach (OutputLink CurOutput, CurOp.OutputLinks) {
                        int i = 0;
                        while (i < CurOutput.OutputIDs.count()) {
                            SeqOperation NextOp = FindSeqObjectByID(CurOutput.OutputIDs[i]);
                            if (NextOp == NULL) {
                                if (Interaction.MsgBox(QString.Format("The operation '{0}' (ID: {1}) was trying to link to a non-existent operation (ID: {2}) on output '{3}'. Removing the faulty link.\\n", new object[]
                                {
                                    CurOp.Name,
                                    CurOp.ID,
                                    CurOutput.OutputIDs[i],
                                    CurOutput.Name
                                }), (MsgBoxStyle)Conversions.ToInteger("Check for Errors"), NULL) == MsgBoxResult.Cancel)
                                {
                                    return;
                                }
                                CurOutput.OutputIDs.removeAt(i);
                                CurOutput.OutputIndices.removeAt(i);
                            } else {
                                i++;
                                OpQueue.Enqueue(NextOp);
                            }
                        }
                    }
                }
            }
        }
    }
    int CompareTo(object obj)
    {
        int CompareTo;
        if (obj is VisualEvent)
            return checked(Priority - ((VisualEvent)obj).Priority);

        return 0;
    }
};

#endif // gVISUALEVENT_H
