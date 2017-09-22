#include "game.h"
#include "statuseffect.h"

StatusEffectInstance* StatusEffect::GetInstance()
{
    return new StatusEffectInstance(Name, Game::GameTime.CurrentTimestamp, Duration);
}
