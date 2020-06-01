#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LanguagesManager.h"

//==============================================================================
YearprojectAudioProcessor::YearprojectAudioProcessor()
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

YearprojectAudioProcessor::~YearprojectAudioProcessor()
{
}

//==============================================================================
const String YearprojectAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool YearprojectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool YearprojectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool YearprojectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double YearprojectAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int YearprojectAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int YearprojectAudioProcessor::getCurrentProgram()
{
	return 0;
}

void YearprojectAudioProcessor::setCurrentProgram(int index)
{
}

const String YearprojectAudioProcessor::getProgramName(int index)
{
	return {};
}

void YearprojectAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void YearprojectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void YearprojectAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool YearprojectAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
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

void YearprojectAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
bool YearprojectAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* YearprojectAudioProcessor::createEditor()
{
	return new YearprojectAudioProcessorEditor(*this);
}

//==============================================================================
void YearprojectAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.

	ScopedPointer<XmlElement> xml(parameters.state.createXml().release());
	copyXmlToBinary(*xml, destData);
}

void YearprojectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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

void YearprojectAudioProcessor::addEffect(EffectCreator* newEffect)
{
	effects.add(newEffect);
}

Array<EffectCreator*> YearprojectAudioProcessor::getEffects()
{
	return effects;
}

void YearprojectAudioProcessor::addParameter(String id, Slider* sourceSlider)
{
	slidersConnections.add(new AudioProcessorValueTreeState::SliderAttachment(parameters,id,*sourceSlider));
}

void YearprojectAudioProcessor::addParameter(String id, TextValueButton* sourceButton)
{
	buttonsConnections.add(new AudioProcessorValueTreeState::ButtonAttachment(parameters, id, *sourceButton));
}

void YearprojectAudioProcessor::addParameter(String name, float minValue, float maxValue, float interval, float curValue)
{
	parameters.createAndAddParameter(name, name, name, NormalisableRange<float>(minValue,maxValue,interval),curValue, nullptr, nullptr);
}

float YearprojectAudioProcessor::useEffects(float signal)
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
	return new YearprojectAudioProcessor();;
}