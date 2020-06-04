#include "EffectCreator.h"

Random EffectCreator::randomGenerator = Random();

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