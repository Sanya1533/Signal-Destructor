#include <JuceHeader.h>
#include <map>

#include "PluginProcessor.h"

#include "SliderPanel.h"
#include "LabeledSlider.h"

using namespace juce;

class YearprojectAudioProcessorEditor : public AudioProcessorEditor, public SliderPanel::MouseListener,public ComboBox::Listener
{
public:
    YearprojectAudioProcessorEditor(YearprojectAudioProcessor& p);
    ~YearprojectAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

    void mouseDoubleClick(SliderPanel* panel, const MouseEvent& event) override;

    void comboBoxChanged(ComboBox* changedComboBox) override;

private:
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sld;

    YearprojectAudioProcessor& processor;

    ComboBox* languages;

    vector<SliderPanel*> panels;

    map<wstring, wstring> langMap;

    LabeledSlider* getParametredSlider(String text,String* name=nullptr, double minValue = 0, double maxValue = 1, double interval = 0.001, LabeledSlider::LabelPosition labelPosition = LabeledSlider::LabelAbove, Slider::TextEntryBoxPosition boxPosition = Slider::TextBoxBelow, Slider::SliderStyle style = Slider::Rotary, double labelPercentage = 0.15);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YearprojectAudioProcessorEditor)
};