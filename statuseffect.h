#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include "json_macros.h"
#include "game.h"
#include "statuseffectinstance.h"
#include "modifier.h"

class StatusEffect {
public:
    QString Name;
    QString DisplayName;
    StatusEffectAccumulationType AccumulationType;
    int Duration;
    QList<ModifierBase> Modifiers;
    StatusEffectInstance* GetInstance();
    StatusEffect(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, DisplayName, toString)
            else __IF_OBJ_FROM_JSON(it, AccumulationType)
            else __IF_VAR_FROM_JSON_AS(it, Duration, toInt)
            else __IF_OBJLIST_FROM_JSON(it, Modifiers, ModifierBase)
            // *INDENT-ON*
        }
    }
};
#endif // STATUSEFFECT_H
