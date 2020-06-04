#pragma once

static class Configuration
{
public:
	static double getSampleRate();

	static void setSampleRate(double newRate);
private:
	static double sampleRate;
};