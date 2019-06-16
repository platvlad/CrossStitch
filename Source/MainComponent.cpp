#include "MainComponent.h"


MainComponent::MainComponent()
{
    addAndMakeVisible(setHeightLabel = new Label(String(), "Set height:"));
    addAndMakeVisible(setWidthLabel = new Label(String(), "Set width:"));
    addAndMakeVisible(heightEditor = new TextEditor(String()));
    addAndMakeVisible(widthEditor = new TextEditor(String()));
    addAndMakeVisible(okButton = new TextButton("Ok"));
    okButton->addListener(this);
    setSize (1400, 700);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    setHeightLabel->setBounds(20, 20, 80, 20);
    heightEditor->setBounds(110, 20, 50, 20);
    setWidthLabel->setBounds(20, 50, 80, 20);
    widthEditor->setBounds(110, 50, 50, 20);
    okButton->setBounds(30, 80, 30, 20);
    if (generatedRectangle)
    {
        rectangle.setBounds(initialRectangleX - 5, initialRectangleY - 5, width * pixelWidth + 100, height * pixelWidth + 100);
    }
}

void MainComponent::buttonClicked(Button* clickedButton)
{
    if (clickedButton == okButton)
    {
        if (!generatedRectangle)
        {
            String heightString = heightEditor->getText();
            height = heightString.getIntValue();
            String widthString = widthEditor->getText();
            width = widthString.getIntValue();
            if (height > 0 && width > 0) {
                generatedRectangle = true;
                rectangle.setWidthHeightPixelWidth(width, height, pixelWidth);
                addAndMakeVisible(rectangle);
                rectangle.setBounds(initialRectangleX - 5, initialRectangleY - 5, width * pixelWidth + 75, height * pixelWidth + 75);
            }
        }
    }
}
