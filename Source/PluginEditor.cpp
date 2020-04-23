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
	interruptsSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Случайный коэффициент",0, 100, 1));
	

	p.addEffect(new InterruptsCreator(
		interruptsSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"Случайный коэффициент")->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
	));

	interruptsSliderPanel->addListener(this);
	

	noiseSliderPanel = new SliderPanel();

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(L"Шум");

	noiseSliderPanel->addComponent(getParametredSlider(L"Частота"));
	noiseSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	noiseSliderPanel->addComponent(getParametredSlider(L"Громкость", 0, 100, 0.01));
	noiseSliderPanel->addComponent(getParametredSlider(L"Случайный коэффициент", 0, 100, 1));

	p.addEffect(new NoiseCreator(
		noiseSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"Случайный коэффициент")->getSlider()->getValueObject(),
		noiseSliderPanel->getActive()
	));

	noiseSliderPanel->addListener(this);


	snapSliderPanel = new SliderPanel();

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(L"Треск");

	snapSliderPanel->addComponent(getParametredSlider(L"Частота"));
	snapSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	snapSliderPanel->addComponent(getParametredSlider(L"Громкость", 0, 100, 0.01));
	snapSliderPanel->addComponent(getParametredSlider(L"Случайный коэффициент", 0, 100, 1));
	snapSliderPanel->addComponent(getParametredSlider(L"Густота", 0, 44099, 1));
	snapSliderPanel->addComponent(getParametredSlider(L"Клиппинг сигнала", 0, 300, 0.1));

	p.addEffect(new SnapCreator(
		snapSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Случайный коэффициент")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Густота")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"Клиппинг сигнала")->getSlider()->getValueObject(),
		snapSliderPanel->getActive()
	));

	snapSliderPanel->addListener(this);


	humSliderPanel = new SliderPanel();

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(L"Гудение");

	humSliderPanel->addComponent(getParametredSlider(L"Частота"));
	humSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	humSliderPanel->addComponent(getParametredSlider(L"Громкость",0,100,0.01));
	humSliderPanel->addComponent(getParametredSlider(L"Случайный коэффициент", 0, 100, 1));

	p.addEffect(new HumCreator(
		humSliderPanel->getChildWithTitle(L"Частота")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Длительность")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Громкость")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"Случайный коэффициент")->getSlider()->getValueObject(),
		humSliderPanel->getActive()
	));

	humSliderPanel->addListener(this);


	addAndMakeVisible(interruptsSliderPanel);
	addAndMakeVisible(noiseSliderPanel);
	addAndMakeVisible(snapSliderPanel);
	addAndMakeVisible(humSliderPanel);

	setSize(800, 700);
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

LabeledSlider* YearprojectAudioProcessorEditor::getParametredSlider(String text, double minValue , double maxValue, double interval,LabeledSlider::LabelPosition labelPosition, Slider::TextEntryBoxPosition boxPosition, Slider::SliderStyle style, double labelPercentage)
{
	LabeledSlider* labeledSlider = new LabeledSlider(new Slider(style, boxPosition), new Label("", text), labelPosition, labelPercentage);
	labeledSlider->setRange(minValue, maxValue, interval);
	return labeledSlider;
}