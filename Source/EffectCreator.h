 #pragma once
#include<JuceHeader.h>
#include "SliderToValueConnector.h"

class EffectCreator
{
public:
    EffectCreator(Value isActive);

    double virtual createEffect(double signal)=0;

    bool getActive();

    void setActive(Value isActive);

protected:
    Value isActive=Value(true);
};