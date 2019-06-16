#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "RectangleComponent.h"


class MainComponent   : public Component, public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* clickedButton) override;

private:
    //==============================================================================
    // Your private member variables go here...
    ScopedPointer<Label> setHeightLabel;
    ScopedPointer<TextEditor> heightEditor;
    ScopedPointer<Label> setWidthLabel;
    ScopedPointer<TextEditor> widthEditor;
    ScopedPointer<TextButton> okButton;
    RectangleComponent rectangle;

    bool generatedRectangle = false;
    int height = 0;
    int width = 0;
    int initialRectangleX = 160;
    int initialRectangleY = 80;
    const int pixelWidth = 20;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
