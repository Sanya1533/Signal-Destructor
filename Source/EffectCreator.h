 #pragma once
#include<JuceHeader.h>

class EffectCreator
{
public:
    EffectCreator(Value isActive);

    float virtual createEffect(float signal)=0;

    void virtual moveTime() = 0;

    bool getActive();

    void setActive(Value isActive);

protected:
    static Random randomGenerator;

    Value isActive=Value(true);
};