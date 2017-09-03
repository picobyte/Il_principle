
#include "person.h"
#include "ruleeffect.h"


void RuleEffect::ExecuteRuleForPerson(Person *Per)
{
    if (Genders.contains(Per.gender))
        AdjustPerson(&Per);
}
void RuleEffect::AdjustPerson(Person *Per)
{
    if (Per != NULL){
        for (QList<StatChange>::iterator it = StatChanges.begin();
             it != StatChanges.end(); ++it)
            it->AdjustStat(Per);
/*                for (QList<BodySizeChange>::iterator it = BodySizeChanges.begin();
             it != BodySizeChanges.end(); ++it)
            Per->ApplyBodySizeChange(*it);*/
    }
}
