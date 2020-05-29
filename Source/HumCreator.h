#pragma once
#include "EffectCreator.h"
#include "maximilian.h"

class HumCreator : public EffectCreator
{
public:
	HumCreator(double frequency = 0.0, double duration = 0.0, double volume = 0.0, double randomFactor=0.0, bool isActive = true);

	HumCreator(Value frequency = Value(0.0), Value duration = Value(0.0), Value volume = Value(0.0), Value randomFactor = Value(0.0), Value isActive = Value(true));

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

private:
	Value frequency;

	Value duration;

	Value volume;

	Value randomFactor;

	int durationTime = 0;

	int freqTime = 0;

	bool play = false;

	float previous = 0.0f;

	int counter = -1;

	maxiOsc maxiLFO = maxiOsc();
};