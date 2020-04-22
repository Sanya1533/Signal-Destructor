#pragma once
#include "EffectCreator.h"

class InterruptsCreator : public EffectCreator
{
public:
	InterruptsCreator(double frequency = 0.0, double duration = 0.0, int randomFactor = 0, bool isActive = true);

	InterruptsCreator(Value frequency = Value(0.0), Value duration = Value(0.0), Value randomFactor = Value(0.0), Value isActive = Value(true));

	double createEffect(double signal) override;

	void moveTime() override;

	void setFrequency(Value frequency);
	Value getFrequency();

	void setDuration(Value duration);
	Value getDuration();

	void setRandomFactor(Value randomFactor);
	Value getRandomFactor();

private:
	Value frequency;

	Value duration;

	Value randomFactor;

	int durationTime=0;

	int freqTime=0;

	bool play = false;
};