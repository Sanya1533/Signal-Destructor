#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderListener.h"
#include "SliderPanel.h"
#include "LabeledSlider.h"

//==============================================================================
/**
*/
class YearprojectAudioProcessorEditor  : public AudioProcessorEditor, public SliderListener, public SliderPanel::MouseListener
{
public:
    YearprojectAudioProcessorEditor (YearprojectAudioProcessor&);
    ~YearprojectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider, String message) override;

    void mouseDoubleClick(SliderPanel* panel,const MouseEvent& event) override;

private:
    YearprojectAudioProcessor& processor;

    SliderPanel* interruptsSliderPanel;

    SliderPanel* noiseSliderPanel;

    SliderPanel* snapSliderPanel;

    SliderPanel* humSliderPanel;

    LabeledSlider* getParametredSlider(String text,LabeledSlider::LabelPosition labelPosition=LabeledSlider::LabelAbove,Slider::TextEntryBoxPosition boxPosition=Slider::TextBoxBelow,  double minValue=0, double maxValue=1, double interval=0.001, Slider::SliderStyle style = Slider::Rotary, double labelPercentage=0.15);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YearprojectAudioProcessorEditor)
};