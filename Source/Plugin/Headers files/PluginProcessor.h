#pragma once
#include <JuceHeader.h>
#include "EffectCreator.h"
#include "TextValueButton.h"

class SignalDestructorAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    SignalDestructorAudioProcessor();
    ~SignalDestructorAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    //==============================================================================
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void addEffect(EffectCreator* newEffect);
    Array<EffectCreator*> getEffects();

    void addParameter(String id, Slider* sourceSlider);
    void addParameter(String id, TextValueButton* sourceButton);
private:
    AudioProcessorValueTreeState parameters;

    Array<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>> slidersConnections;
    Array<ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment>> buttonsConnections;

    Array<EffectCreator*> effects;

    void addParameter(String name, float minValue, float maxValue, float interval, float curValue);

    float useEffects(float signal);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SignalDestructorAudioProcessor)
};
