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

	interruptsSliderPanel->setTitle(L"Прерывания");

	interruptsSliderPanel->addComponent(getParametredSlider(L"Частота"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Густота прерываний", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));
	

	p.addEffect(new InterruptsCreator(
		interruptsSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Густота прерываний")->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
	));

	interruptsSliderPanel->addListener(this);
	

	noiseSliderPanel = new SliderPanel();

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(L"Шум");

	noiseSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	noiseSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelAbove, Slider::NoTextBox));
	noiseSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelBelow, Slider::NoTextBox, 0, 100, 0.01));

	p.addEffect(new NoiseCreator(
		noiseSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		noiseSliderPanel->getActive()
	));

	noiseSliderPanel->addListener(this);


	snapSliderPanel = new SliderPanel();

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(L"Треск");

	snapSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	snapSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	snapSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	p.addEffect(new SnapCreator(
		snapSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		snapSliderPanel->getActive()
	));

	snapSliderPanel->addListener(this);


	humSliderPanel = new SliderPanel();

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(L"Гудение");

	humSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelAbove, Slider::NoTextBox));
	humSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelAbove, Slider::TextBoxBelow));
	humSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	p.addEffect(new NoiseCreator(
		humSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
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