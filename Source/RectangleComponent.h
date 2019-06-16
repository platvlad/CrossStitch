#pragma once
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PixelComponent.h"
#include "Graph.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class RectangleComponent : public Component, public Button::Listener
{
public:
    RectangleComponent(int width = 0, int height = 0, int pixelWidth = 0);
    ~RectangleComponent();

    void paint(Graphics&) override;
    void resized() override;
    void mouseUp(const MouseEvent& event) override;
    void buttonClicked(Button* clickedButton) override;

    void setWidthHeightPixelWidth(int width, int height, int pixelWidth);

private:
    ScopedPointer<TextButton> goButton;
    ScopedPointer<TextButton> nextButton;
    ScopedPointer<ToggleButton> toInvert;
    Graph graph;
    bool startedGraphBuilding = false;
    std::vector<std::vector<bool>> pixels;
    std::vector<int> path;

    int widthInCells;
    int heightInCells;
    int pixelWidth;
    //bool pixels[100][100] = { false };
    //PixelComponent** pixelComponents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RectangleComponent)
};
