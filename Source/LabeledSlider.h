#pragma once
#include <JuceHeader.h>
#include <vector>

using namespace std;

class LabeledSlider :
    public Component
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

    void setLabelPosition(LabelPosition position);

    void setLabelPercentage(float percantage);

    void setLabel(Label* label);

    void setSlider(Slider* slider);

    Slider* getSlider();

    void setText(String text);

    void setFont(Font font);

    void setSliderStyle(Slider::SliderStyle sliderStyle);

    Label* getLabel();

    void setMaxValue(double newMaxValue);

    void setMinValue(double newMinValue);

    void setInterval(double newInterval);

    void setRange(double newMinValue=NULL, double newMaxValue=NULL, double newInterval=NULL);

private:
    Label* label;

    Slider* slider;

    float labelPercentage = 0.15;

    LabelPosition labelPosition;// = LabelPosition::NoLabel;

    bool isSliderRotary();
};