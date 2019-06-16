#include "PixelComponent.h"

PixelComponent::PixelComponent(int pixelWidth, bool chosen) : pixelWidth(pixelWidth), chosen(chosen)
{
    setSize(pixelWidth, pixelWidth);
}

PixelComponent::~PixelComponent()
{
}

//==============================================================================
void PixelComponent::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    if (!chosen)
    {
        g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    }
    else
    {
        g.fillAll(Colours::lightpink);
    }
}

void PixelComponent::resized()
{

}

void PixelComponent::invert()
{
    chosen = !chosen;
    repaint();
}

void PixelComponent::setPixelWidth(int newPixelWidth)
{
    pixelWidth = newPixelWidth;
    setSize(pixelWidth, pixelWidth);
    repaint();
}

bool PixelComponent::getChosen()
{
    return chosen;
}