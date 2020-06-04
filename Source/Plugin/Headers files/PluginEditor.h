#pragma once
#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "SliderPanel.h"
#include "LabeledSlider.h"

#include "TextValueButton.h"

using namespace juce;

class SignalDestructorAudioProcessorEditor : public AudioProcessorEditor, 
    public ComboBox::Listener, public KeyListener, public TextButton::Listener
{
public:
    SignalDestructorAudioProcessorEditor(SignalDestructorAudioProcessor& p);
    ~SignalDestructorAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

    void comboBoxChanged(ComboBox* changedComboBox) override;

    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;

    void buttonClicked(Button* button) override;
private:
    vector<SliderPanel*> panels;

    SignalDestructorAudioProcessor& processor;

    ComboBox* languages;

    LabeledSlider* getParametredSlider(String text,String* name=nullptr, double minValue = 0, double maxValue = 1, double interval = 0.001, LabeledSlider::LabelPosition labelPosition = LabeledSlider::LabelAbove, Slider::TextEntryBoxPosition boxPosition = Slider::TextBoxBelow, Slider::SliderStyle style = Slider::Rotary, double labelPercentage = 0.15);

    TextValueButton* getParameteredButton(String name, String firstName, String* secondName=nullptr, String* firstText = nullptr, String* secondText=nullptr);
    TextButton* getParameteredButton(String name, String* text=nullptr);

    String modifyText(string text);

    void setListenersToTextEditors();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SignalDestructorAudioProcessorEditor)
};