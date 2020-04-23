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

	interruptsSliderPanel->setTitle(L"����������");

	interruptsSliderPanel->addComponent(getParametredSlider(L"�������"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"������������"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"��������� �����������",0, 100, 1));
	

	p.addEffect(new InterruptsCreator(
		interruptsSliderPanel->getChildWithTitle(L"�������")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"������������")->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(L"��������� �����������")->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
	));

	interruptsSliderPanel->addListener(this);
	

	noiseSliderPanel = new SliderPanel();

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(L"���");

	noiseSliderPanel->addComponent(getParametredSlider(L"�������"));
	noiseSliderPanel->addComponent(getParametredSlider(L"������������"));
	noiseSliderPanel->addComponent(getParametredSlider(L"���������", 0, 100, 0.01));
	noiseSliderPanel->addComponent(getParametredSlider(L"��������� �����������", 0, 100, 1));

	p.addEffect(new NoiseCreator(
		noiseSliderPanel->getChildWithTitle(L"�������")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"������������")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"���������")->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(L"��������� �����������")->getSlider()->getValueObject(),
		noiseSliderPanel->getActive()
	));

	noiseSliderPanel->addListener(this);


	snapSliderPanel = new SliderPanel();

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(L"�����");

	snapSliderPanel->addComponent(getParametredSlider(L"�������"));
	snapSliderPanel->addComponent(getParametredSlider(L"������������"));
	snapSliderPanel->addComponent(getParametredSlider(L"���������", 0, 100, 0.01));
	snapSliderPanel->addComponent(getParametredSlider(L"��������� �����������", 0, 100, 1));
	snapSliderPanel->addComponent(getParametredSlider(L"�������", 0, 44099, 1));
	snapSliderPanel->addComponent(getParametredSlider(L"�������� �������", 0, 300, 0.1));

	p.addEffect(new SnapCreator(
		snapSliderPanel->getChildWithTitle(L"�������")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"������������")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"���������")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"��������� �����������")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"�������")->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(L"�������� �������")->getSlider()->getValueObject(),
		snapSliderPanel->getActive()
	));

	snapSliderPanel->addListener(this);


	humSliderPanel = new SliderPanel();

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(L"�������");

	humSliderPanel->addComponent(getParametredSlider(L"�������"));
	humSliderPanel->addComponent(getParametredSlider(L"������������"));
	humSliderPanel->addComponent(getParametredSlider(L"���������",0,100,0.01));
	humSliderPanel->addComponent(getParametredSlider(L"��������� �����������", 0, 100, 1));

	p.addEffect(new HumCreator(
		humSliderPanel->getChildWithTitle(L"�������")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"������������")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"���������")->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(L"��������� �����������")->getSlider()->getValueObject(),
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