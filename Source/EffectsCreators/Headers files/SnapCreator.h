#pragma once
#include "EffectCreator.h"

class SnapCreator : public EffectCreator
{
public:
	SnapCreator(double frequency = 0.0, double duration = 0.0, double volume = 0.0,int randomFactor=0, double snapDensity=0.0,double signalClipping=1.0,bool isActive = true);

	SnapCreator(Value frequency = Value(0.0), Value duration = Value(0.0), Value volume = Value(0.0),Value randomFactor = Value(var(0)), Value snapDensity=Value(0.0),Value signalClipping=Value(1.0),Value isActive = Value(true));

	float createEffect(float signal) override;

	void moveTime() override;

	void setFrequency(Value frequency);
	Value getFrequency();

	void setDuration(Value duration);
	Value getDuration();

	void setVolume(Value volume);
	Value getVolume();

	void setRandomFactor(Value randomFactor);
	Value getRandomFactor();

	void setDensity(Value snapDensity);
	Value getDensity();

	void setSignalClipping(Value signalClipping);
	Value getSignalClipping();

private:
	Value frequency;

	Value duration;

	Value volume;

	Value randomFactor;

	Value snapDensity;

	Value signalClipping;

	int durationTime = 0;

	int freqTime = 0;

   	int played = 0; 

	bool play = false;

	bool direction = false;
};