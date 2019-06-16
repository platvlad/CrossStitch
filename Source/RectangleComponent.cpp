#include "RectangleComponent.h"

RectangleComponent::RectangleComponent(int width, int height, int pixelWidth) : pixelWidth(pixelWidth)
{
    addAndMakeVisible(goButton = new TextButton("Go"));
    addAndMakeVisible(nextButton = new TextButton("Next"));
    addAndMakeVisible(toInvert = new ToggleButton("Invert pattern"));
    setSize(width, height);
    goButton->addListener(this);
    nextButton->addListener(this);
    toInvert->addListener(this);
}

RectangleComponent::~RectangleComponent()
{
}

//==============================================================================
void RectangleComponent::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setFont(Font(16.0f));
    g.setColour(Colours::white);
    for (int y = 5, i = 0; (y <= getHeight() && i <= heightInCells); y += pixelWidth, ++i)
    {
        g.drawLine(5, y, widthInCells * pixelWidth + 5, y, 2);
    }
    for (int x = 5, i = 0; (x <= getWidth() && i <= widthInCells); x += pixelWidth, ++i)
    {
        g.drawLine(x, 5, x, heightInCells * pixelWidth + 5, 2);
    }
    g.setColour(Colours::lightpink);
    for (int i = 0; i < heightInCells; ++i)
    {
        for (int j = 0; j < widthInCells; ++j)
        {
            if (pixels[i][j])
            {
                g.fillRect(j * pixelWidth + 5, i * pixelWidth + 5, pixelWidth, pixelWidth);
            }
        }
    }
    if (startedGraphBuilding)
    {
        g.setColour(Colours::red);
        if (!path.empty())
        {
            int vertexNum = path[path.size() - 1];
            int y = vertexNum / (widthInCells + 1);
            int x = vertexNum % (widthInCells + 1);
            g.fillEllipse(x * pixelWidth + 3, y * pixelWidth + 3, 4, 4);
        }
        int lastElemIndex = path.size() - 1;
        for (int i = 0; i < lastElemIndex; ++i)
        {
            if (abs(path[i] - path[i + 1]) == (widthInCells + 1))
            {
                continue;
            }
            int y1 = path[i] / (widthInCells + 1);
            int x1 = path[i] % (widthInCells + 1);
            int y2 = path[i + 1] / (widthInCells + 1);
            int x2 = path[i + 1] % (widthInCells + 1);
            g.drawLine(x1 * pixelWidth + 5, y1 * pixelWidth + 5, x2 * pixelWidth + 5, y2 * pixelWidth + 5, 1);
        }
    }
}

void RectangleComponent::resized()
{
    goButton->setBounds(0, heightInCells * pixelWidth + 45, 30, 20);
    nextButton->setBounds(50, heightInCells * pixelWidth + 45, 30, 20);
    toInvert->setBounds(0, heightInCells * pixelWidth + 75, 50, 20);
}

void RectangleComponent::setWidthHeightPixelWidth(int width, int height, int newPixelWidth)
{
    pixelWidth = newPixelWidth;
    widthInCells = width;
    heightInCells = height;
    setSize(width * pixelWidth + 105, height * pixelWidth + 105);
    for (int i = 0; i < height; ++i)
    {
        std::vector<bool> pixelRow;
        for (int j = 0; j < width; ++j)
        {
            pixelRow.push_back(false);
        }
        pixels.push_back(pixelRow);
    }
}

void RectangleComponent::buttonClicked(Button* clickedButton)
{
    if (clickedButton == goButton)
    {
        graph = Graph(pixels, widthInCells, heightInCells);
        graph.findPath();
        startedGraphBuilding = true;
        repaint();
    }
    if (clickedButton == nextButton)
    {
        if (graph.hasNext())
        {
            int nextVertex = graph.next();
            path.push_back(nextVertex);
            repaint();
        }
    }
    if (clickedButton == toInvert)
    {
        for (std::vector<bool> pixelRow : pixels)
        {
            for (int i = 0; i < pixelRow.size(); ++i)
            {
                pixelRow[i] = !pixelRow[i];
            }
        }
        repaint();
    }

}

void RectangleComponent::mouseUp(const MouseEvent& event)
{
    Point<int> mousePosition = event.getPosition();
    int x = mousePosition.getX();
    int y = mousePosition.getY();
    int row = y / pixelWidth;
    int column = x / pixelWidth;
    if (row >= 0 && row < heightInCells && column >= 0 && column < widthInCells)
    {
        pixels[row][column] = !pixels[row][column];
    }
    repaint();
}