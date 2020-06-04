#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LanguagesManager.h"
#include "Configuration.h"

//==============================================================================
SignalDestructorAudioProcessor::SignalDestructorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
	, parameters(*this, nullptr)
{ 
	using Prop= LanguagesManager::Properties;
	addParameter(Prop::INTERRUPTS + "->" + Prop::FREQUENCY, 0, 1, 0.001, -1);
	addParameter(Prop::INTERRUPTS + "->" + Prop::DURATION, 0, 1, 0.001, 0);
	addParameter(Prop::INTERRUPTS + "->" + Prop::RANDOM_FACTOR, 0, 100, 1, 0);
	addParameter(Prop::NOISE + "->" + Prop::FREQUENCY, 0, 1, 0.001, 0);
	addParameter(Prop::NOISE+ "->" + Prop::DURATION, 0, 1, 0.001, 0);
	addParameter(Prop::NOISE + "->" + Prop::VOLUME, 0, 100, 0.01, 0);
	addParameter(Prop::NOISE + "->" + Prop::RANDOM_FACTOR, 0, 100, 1, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::FREQUENCY, 0, 1, 0.001, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::DURATION, 0, 1, 0.001, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::VOLUME, 0, 100, 0.01, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::RANDOM_FACTOR, 0, 100, 1, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::DENSITY, 0, 44099, 1, 0);
	addParameter(Prop::CRACKLING + "->" + Prop::CLIPPING_FACTOR, 0, 300, 0.1, 0);
	addParameter(Prop::BUZZING + "->" + Prop::FREQUENCY, 0, 1, 0.001, 0);
	addParameter(Prop::BUZZING + "->" + Prop::DURATION, 0, 1, 0.001, 0);
	addParameter(Prop::BUZZING + "->" + Prop::VOLUME, 0, 100, 0.01, 0);
	addParameter(Prop::BUZZING + "->" + Prop::RANDOM_FACTOR, 0, 100, 1, 0);
	addParameter(Prop::INTERRUPTS + "->" + Prop::ACTIVE, 0, 1, 1, 1);
	addParameter(Prop::NOISE + "->" + Prop::ACTIVE, 0, 1, 1, 1);
	addParameter(Prop::CRACKLING + "->" + Prop::ACTIVE, 0, 1, 1, 1);
	addParameter(Prop::BUZZING + "->" + Prop::ACTIVE, 0, 1, 1, 1);
	parameters.state = ValueTree("savedParams");
}

SignalDestructorAudioProcessor::~SignalDestructorAudioProcessor()
{
}

//==============================================================================
const String SignalDestructorAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SignalDestructorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool SignalDestructorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool SignalDestructorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double SignalDestructorAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SignalDestructorAudioProcessor::getNumPrograms()
{
	return 1;
}

int SignalDestructorAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SignalDestructorAudioProcessor::setCurrentProgram(int index)
{
}

const String SignalDestructorAudioProcessor::getProgramName(int index)
{
	return {};
}

void SignalDestructorAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void SignalDestructorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	Configuration::setSampleRate(sampleRate);
}

void SignalDestructorAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SignalDestructorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void SignalDestructorAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	int totalNumInputChannels = getTotalNumInputChannels();
	int totalNumOutputChannels = getTotalNumOutputChannels();
	int totalNumSamples = buffer.getNumSamples();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++)
		buffer.clear(i, 0, buffer.getNumSamples());


	for (int sample = 0; sample < totalNumSamples; sample++)
	{
		for (int channel = 0; channel < totalNumInputChannels; channel++)
		{
			buffer.setSample(channel, sample, useEffects(buffer.getSample(channel, sample)));
		}
		for (EffectCreator* effect:effects)
		{
			effect->moveTime();
		}
	}
}

//==============================================================================
bool SignalDestructorAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SignalDestructorAudioProcessor::createEditor()
{
	return new SignalDestructorAudioProcessorEditor(*this);
}

//==============================================================================
void SignalDestructorAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.

	ScopedPointer<XmlElement> xml(parameters.state.createXml().release());
	copyXmlToBinary(*xml, destData);
}

void SignalDestructorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	ScopedPointer<XmlElement> theParams(getXmlFromBinary(data, sizeInBytes).release());

	if (theParams != nullptr)
	{
		if (theParams->hasTagName(parameters.state.getType()))
		{
			parameters.state = ValueTree::fromXml(*theParams);
		}
	}
}

void SignalDestructorAudioProcessor::addEffect(EffectCreator* newEffect)
{
	effects.add(newEffect);
}

Array<EffectCreator*> SignalDestructorAudioProcessor::getEffects()
{
	return effects;
}

void SignalDestructorAudioProcessor::addParameter(String id, Slider* sourceSlider)
{
	slidersConnections.add(new AudioProcessorValueTreeState::SliderAttachment(parameters,id,*sourceSlider));
}

void SignalDestructorAudioProcessor::addParameter(String id, TextValueButton* sourceButton)
{
	buttonsConnections.add(new AudioProcessorValueTreeState::ButtonAttachment(parameters, id, *sourceButton));
}

void SignalDestructorAudioProcessor::addParameter(String name, float minValue, float maxValue, float interval, float curValue)
{
	parameters.createAndAddParameter(name, name, name, NormalisableRange<float>(minValue,maxValue,interval),curValue, nullptr, nullptr);
}

float SignalDestructorAudioProcessor::useEffects(float signal)
{
	for (EffectCreator *effect:effects)
	{
		signal = effect->createEffect(signal);
	}
	return signal;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SignalDestructorAudioProcessor();;
}