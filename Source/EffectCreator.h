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

    void setTime(int newTime);

    int getTime();

protected:
    int time=0;

    Value isActive=Value(true);
};