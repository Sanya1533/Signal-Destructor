#pragma once
#include <JuceHeader.h>
#include <vector>
#include "SliderListener.h"

using namespace std;

class LabeledSlider :
    public Component,
    public Slider::Listener
{
public:
    enum LabelPosition
    {
        NoLabel = 0,
        LabelLeft = 1,
        LabelRight = 2,
        LabelAbove = 3,
        LabelBelow = 4
    };

    //==============================================================================
    LabeledSlider();
    LabeledSlider(Slider* slider, Label* label, LabelPosition labelPosition, float labelPercentage = 0.15);
    ~LabeledSlider();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

    void setLabelPosition(LabelPosition position);

    void setLabelPercentage(float percantage);

    void setLabel(Label* label);

    void setSlider(Slider* slider);

    Slider* getSlider();

    void setLabelText(String text);

    void setLabelFont(Font font);

    void setSliderStyle(Slider::SliderStyle sliderStyle);

    void addListener(SliderListener* listener);

    Label* getLabel();

    void setMaxValue(double newMaxValue, NotificationType notification = dontSendNotification, bool allowNudgingOfOtherValues = true);

    void setMinValue(double newMinValue, NotificationType notification = dontSendNotification, bool allowNudgingOfOtherValues = true);

private:
    Label* label;

    Slider* slider;

    float labelPercentage = 0.15;

    LabelPosition labelPosition = LabelPosition::NoLabel;

    vector<SliderListener*> listeners = vector<SliderListener*>(0);

    bool isSliderRotary();
};