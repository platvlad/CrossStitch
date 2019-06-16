#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class PixelComponent : public Component
{
public:
    //==============================================================================
    PixelComponent(int pixelWidth = 0, bool chosen = false);

    ~PixelComponent();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;
    void invert();
    void setPixelWidth(int newPixelWidth);
    bool getChosen();


private:
    //==============================================================================
    // Your private member variables go here...


    int pixelWidth;
    bool chosen = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PixelComponent)
};
