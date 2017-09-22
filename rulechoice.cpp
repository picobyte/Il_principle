#include "game.h"
#include "rulechoice.h"

void RuleChoice::ExecuteRule()
{
    if (Game::HiredTeacher.count() > 0)
    {
        for (QList<RuleEffect>::iterator it = RuleEffects.begin();
                it != RuleEffects.end(); ++it)
            it->ExecuteRuleForGroup();

        TheWorld::Reputation(TheWorld::Reputation() + RuleReputation / 5.0);
    }
}
