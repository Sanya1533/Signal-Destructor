#pragma once
#include "EffectCreator.h"

class InterruptsCreator : public EffectCreator
{
public:
	InterruptsCreator(double frequency = 0.0, double duration = 0.0, double density = 0.0, bool isActive = true);

	InterruptsCreator(Value frequency = Value(0.0), Value duration = Value(0.0), Value density = Value(0.0), Value isActive = Value(true));

	virtual double createEffect(double signal) override;

	void setFrequency(Value frequency);
	Value getFrequency();

	void setDuration(Value duration);
	Value getDuration();

	void setDensity(Value density);
	Value getDensity();

private:
	Value frequency;

	Value duration;

	Value density;
};