#ifndef RULEEFFECT_H
#define RULEEFFECT_H
#include "json_macros.h"
#include "game.h"

class RuleEffect {
public:
    QString ApplyTo;
    QList<Gender> Genders;
    QList<StatChange> StatChanges;
    QList<BodySizeChange> BodySizeChanges;

    RuleEffect(QJsonObject *d = NULL) : ApplyTo("")
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, ApplyTo, toString)
            else __IF_LIST_FROM_JSON_ENUM(it, Genders, Gender)
            else __IF_OBJLIST_FROM_JSON(it, StatChanges, StatChange)
            else __IF_OBJLIST_FROM_JSON(it, BodySizeChanges, BodySizeChange)
        }
    }
    bool ShouldSerializeGenders()
    {
                return Genders.count() > 0;
    }
    bool ShouldSerializeStatChanges()
    {
                return StatChanges.count() != 0;
    }
    bool ShouldSerializeBodySizeChanges()
    {
                return BodySizeChanges.count() != 0;
    }
        void ExecuteRuleForGroup()
        {
            /*if (ApplyTo.contains("Student")) {
                for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values->begin();
                     it != Game.OwnStudents.Values->end(); ++it)
                    if (!it->IsRogue)
                        ExecuteRuleForPerson(*it);
            }
            if (ApplyTo.contains("Detention") && !ApplyTo.contains("Student")) {
                for (QHash<QString, Person>::iterator it = Game.OwnStudents.Values->begin();
                     it != Game.OwnStudents.Values->end(); ++it)
                    if (it->HasDetention)
                        ExecuteRuleForPerson(*it);
            }
            if (ApplyTo.contains("Parent")) {
                for (QHash<QString, Person>::iterator it = Game.DictOfPersonNames.Values->begin();
                     it != Game.DictOfPersonNames.Values->end(); ++it)
                    if (it->IsParent)
                        ExecuteRuleForPerson(*it);
            }
            if (ApplyTo.contains("Staff")) {
                if (ApplyTo.contains("Parent")) {
                    for (QMap<Person>::iterator it = Game.HiredStaff.Values->begin();
                         it != Game.HiredStaff.Values->end(); ++it)
                        if (!it->IsParent)
                            ExecuteRuleForPerson(*it);
                } else {
                    for (IEnumerator<Person>::iterator it = Game.HiredStaff.Values->begin();
                         it != Game.HiredStaff.Values->end(); ++it)
                        ExecuteRuleForPerson(*it);
                }
            }
            if (ApplyTo.contains("Teacher") && !ApplyTo.contains("Staff")) {
                if (ApplyTo.contains("Parent")) {
                    for (IEnumerator<Person>::iterator it = Game.HiredTeacher.Values->begin();
                         it != Game.HiredTeacher.Values->end(); ++it)
                        if (!it->IsParent)
                            ExecuteRuleForPerson(*it);
                } else {
                    for (IEnumerator<Person>::iterator it = Game.HiredTeacher.Values->begin();
                         it != Game.HiredTeacher.Values->end(); ++it)
                        ExecuteRuleForPerson(*it);
                }
            }
            if (ApplyTo.contains("Principal"))
                ExecuteRuleForPerson(Game.HeadTeacher);*/
        }
        void ExecuteRuleForPerson(Person *Per);
        void AdjustPerson(Person *Per);

        /*RuleEffect(RuleEffect& rhs)
        {
            rhs.ApplyTo = ApplyTo;
            rhs.Genders  = Genders;
            rhs.StatChanges = StatChanges;
            rhs.BodySizeChanges = BodySizeChanges;
        }*/
        RuleEffect& operator=(const RuleEffect& rhs) {
            ApplyTo = rhs.ApplyTo;
            Genders  = rhs.Genders;
            StatChanges = rhs.StatChanges;
            BodySizeChanges = rhs.BodySizeChanges;
        };
};

#endif // RULEEFFECT_H
