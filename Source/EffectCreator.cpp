#include "EffectCreator.h"

EffectCreator::EffectCreator(Value isActive)
{
    this->isActive.referTo(isActive);
}

bool EffectCreator::getActive()
{
    return (bool)this->isActive.getValue();
}

void EffectCreator::setActive(Value isActive)
{
    this->isActive.referTo(isActive);
}

void EffectCreator::setTime(int newTime)
{
    time = newTime%(44100*5);
}

int EffectCreator::getTime()
{
    return time;
}