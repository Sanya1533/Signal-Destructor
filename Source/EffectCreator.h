 #pragma once
#include<JuceHeader.h>

class EffectCreator
{
public:
    EffectCreator(Value isActive);

    double virtual createEffect(double signal)=0;

    void virtual moveTime() = 0;

    bool getActive();

    void setActive(Value isActive);

protected:
    static Random randomGenerator;

    Value isActive=Value(true);
};