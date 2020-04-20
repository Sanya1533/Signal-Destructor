#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "InterruptsCreator.h"
#include "NoiseCreator.h"
#include "SnapCreator.h"
#include "HumCreator.h"

//==============================================================================
YearprojectAudioProcessorEditor::YearprojectAudioProcessorEditor (YearprojectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	interruptsSliderPanel = new SliderPanel();

	interruptsSliderPanel->setBackgroundColor(Colours::darkslateblue);

	interruptsSliderPanel->setBorderColour(Colours::grey);

	interruptsSliderPanel->setBorderPosition(Point<int>(3, 3));

	interruptsSliderPanel->setBorderWidth(3);

	interruptsSliderPanel->setTitle(L"Interrupts");

	interruptsSliderPanel->addComponent(getParametredSlider(L"Frequency"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Duration", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Gustota Prerivaniy", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));
	

	p.addEffect(new InterruptsCreator(
		interruptsSliderPanel->getChildWithTitle(L"Frequency")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Duration")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Gustota Prerivaniy")->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
	));

	interruptsSliderPanel->addListener(this);
	

	noiseSliderPanel = new SliderPanel();

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(L"Noise");

	noiseSliderPanel->addComponent(getParametredSlider(L"Frequency", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	noiseSliderPanel->addComponent(getParametredSlider(L"Duration", LabeledSlider::LabelAbove, Slider::NoTextBox));
	noiseSliderPanel->addComponent(getParametredSlider(L"Volume", LabeledSlider::LabelBelow, Slider::NoTextBox, 0, 100, 0.01));

	p.addEffect(new NoiseCreator(
		noiseSliderPanel->getChildWithTitle(L"Frequency")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Duration")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Volume")->getSlider()->getValueObject(),
		noiseSliderPanel->getActive()
	));

	noiseSliderPanel->addListener(this);


	snapSliderPanel = new SliderPanel();

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(L"Tresk");

	snapSliderPanel->addComponent(getParametredSlider(L"Frequency", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	snapSliderPanel->addComponent(getParametredSlider(L"Duration"));
	snapSliderPanel->addComponent(getParametredSlider(L"Volume", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	p.addEffect(new SnapCreator(
		snapSliderPanel->getChildWithTitle(L"Frequency")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Duration")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Volume")->getSlider()->getValueObject(),
		snapSliderPanel->getActive()
	));

	snapSliderPanel->addListener(this);


	humSliderPanel = new SliderPanel();

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(L"Gudenie");

	humSliderPanel->addComponent(getParametredSlider(L"Frequency", LabeledSlider::LabelAbove, Slider::NoTextBox));
	humSliderPanel->addComponent(getParametredSlider(L"Duration", LabeledSlider::LabelAbove, Slider::TextBoxBelow));
	humSliderPanel->addComponent(getParametredSlider(L"Volume", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	p.addEffect(new HumCreator(
		humSliderPanel->getChildWithTitle(L"Frequency")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Duration")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Volume")->getSlider()->getValueObject(),
		humSliderPanel->getActive()
	));

	humSliderPanel->addListener(this);


	addAndMakeVisible(interruptsSliderPanel);
	addAndMakeVisible(noiseSliderPanel);
	addAndMakeVisible(snapSliderPanel);
	addAndMakeVisible(humSliderPanel);

	setSize(1000, 600);
}

YearprojectAudioProcessorEditor::~YearprojectAudioProcessorEditor()
{
}

//==============================================================================
void YearprojectAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void YearprojectAudioProcessorEditor::resized()
{
	interruptsSliderPanel->setBounds(0, 0, getWidth(), getHeight() / 4);
	noiseSliderPanel->setBounds(0, getHeight() / 4, getWidth(), getHeight() / 4);
	snapSliderPanel->setBounds(0, getHeight() / 2, getWidth(), getHeight() / 4);
	humSliderPanel->setBounds(0, getHeight() * 3 / 4, getWidth(), getHeight() / 4);
}

void YearprojectAudioProcessorEditor::mouseDoubleClick(SliderPanel* panel, const MouseEvent& event)
{
	if ((bool)panel->getActive().getValue())
	{
		panel->setBackgroundColor(Colours::grey);
		panel->setBorderColour(Colours::lightgrey);
	}
	else
	{
		panel->setBackgroundColor(Colours::darkslateblue);
		panel->setBorderColour(Colours::grey);
	}
	panel->setActive(!(bool)panel->getActive().getValue());
}

LabeledSlider* YearprojectAudioProcessorEditor::getParametredSlider(String text, LabeledSlider::LabelPosition labelPosition, Slider::TextEntryBoxPosition boxPosition, double minValue, double maxValue, double interval, Slider::SliderStyle style, double labelPercentage)
{
	LabeledSlider* labeledSlider = new LabeledSlider(new Slider(style, boxPosition), new Label("", text), labelPosition, labelPercentage);
	labeledSlider->setRange(minValue, maxValue, interval);
	return labeledSlider;
}