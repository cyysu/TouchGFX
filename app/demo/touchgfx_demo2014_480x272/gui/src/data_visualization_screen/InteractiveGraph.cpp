/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.5.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include <gui/data_visualization_screen/InteractiveGraph.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

InteractiveGraph::InteractiveGraph() :
    scrollStickAndValue(false),
    waitingToScrollStick(false)
{
    // Do not redelegate touch events to contained child drawables.
    //hijackTouchEvents(true);

    background.setBitmap(Bitmap(BITMAP_GRAPH_12HOURS_BACK_ID));
    add(background);

    topContainer.setPosition(29, 30, 429, 26);
    hideTextBox.setPosition(0, 0, 400, 26);
    hideTextBox.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    hideTextBox.setVisible(false);
    topContainer.add(hideTextBox);

    top.setBitmap(Bitmap(BITMAP_GRAPH_SLIDER_TOP_ID));
    top.setY(5);
    top.setVisible(false);
    topContainer.add(top);

    graphValue.setY(7);
    graphValue.setWidth(60);
    graphValue.setHeight(40);
    graphValue.setTypedText(TypedText(T_GRAPHVALUE));
    graphValue.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    graphValue.setWildcard(graphValueTextBuffer);
    graphValue.setVisible(false);
    topContainer.add(graphValue);
    add(topContainer);

    graphContainer.setPosition(58, 0, 370, 200);
    graphContainer.add(graph);

    slider.setBitmap(Bitmap(BITMAP_GRAPH_SLIDER_LINE_ID));
    slider.setY(56);
    slider.setVisible(false);
    graphContainer.add(slider);

    dot.setBitmap(Bitmap(BITMAP_GRAPH_SLIDER_DOT_ID));
    dot.setVisible(false);
    graphContainer.add(dot);

    add(graphContainer);

    Application::getInstance()->registerTimerWidget(this);
}

InteractiveGraph::~InteractiveGraph()
{
}

void InteractiveGraph::initialize()
{
    graph.setPosition(0, 0, getWidth(), getHeight());
    startGraph();
}

void InteractiveGraph::startGraph()
{
    Application::getInstance()->registerTimerWidget(&graph);
    Application::getInstance()->registerTimerWidget(this);
}

void InteractiveGraph::stopGraph()
{
    Application::getInstance()->unregisterTimerWidget(&graph);
    Application::getInstance()->unregisterTimerWidget(this);
}

void InteractiveGraph::showSliderAndValue(int16_t xCoordinate)
{
    // Ignore out-of-bounds
    if ((xCoordinate > graphContainer.getX()) && (xCoordinate < (graphContainer.getWidth() + graphContainer.getX())))
    {
        centerX(slider, xCoordinate - graphContainer.getX());
        centerX(top, xCoordinate - topContainer.getX());
        centerX(graphValue, xCoordinate - topContainer.getX());
        slider.setVisible(true);
        // Hide text
        hideTextBox.setAlpha(255);
        hideTextBox.setVisible(true);
        top.setVisible(true);
        graphValue.setVisible(true);

        graphValueChanged(graph.getYValue(xCoordinate - graphContainer.getX()), graph.withinCurrentCurve(xCoordinate - graphContainer.getX()));

        // Only draw dot when within current graph curve
        if (graph.withinCurrentCurve(xCoordinate - graphContainer.getX()))
        {
            centerX(dot, xCoordinate - graphContainer.getX());
            centerY(dot, graph.getYCoordinate(xCoordinate - graphContainer.getX()) + 2);
            dot.setVisible(true);
        }
        else
        {
            dot.setVisible(false);
        }
    }
}

void InteractiveGraph::moveSliderAndValue(int16_t xDelta)
{
    int16_t newXCoordinate = (slider.getX() + (slider.getWidth() / 2) + xDelta);

    // Ignore out-of-bounds
    if ((newXCoordinate >= 1) && (newXCoordinate < graphContainer.getWidth()))
    {
        graphValueChanged(graph.getYValue(newXCoordinate), graph.withinCurrentCurve(newXCoordinate));
        slider.moveRelative(xDelta, 0);
        top.moveRelative(xDelta, 0);
        graphValue.moveRelative(xDelta, 0);

        if (graph.isScrolling())
        {
            // Graph is scrolling, let dot follow other drawables
            dot.moveRelative(xDelta, 0);
            centerY(dot, graph.getYCoordinate(newXCoordinate) + 2);
        }
        else if (graph.withinCurrentCurve(newXCoordinate))
        {
            // Graph is not scrolling, but dot has reached curve
            if (! dot.isVisible())
            {
                // Within curve, dot must be show at correct position
                centerX(dot, newXCoordinate);
                dot.setVisible(true);
            }
            else
            {
                // Within curve and already visible, follow other drawables.
                dot.moveRelative(xDelta, 0);
            }
            centerY(dot, graph.getYCoordinate(newXCoordinate) + 2);
        }
        else // Not within current graph curve
        {
            dot.setVisible(false);
            dot.invalidate();
        }
    }
}

void InteractiveGraph::graphValueChanged(int16_t value, bool valid)
{
    if (valid)
    {
        // Make written values somewhat alike values on Y axis
        Unicode::snprintf(graphValueTextBuffer, 5, "%d%%", static_cast<int16_t>((value - 100) * 3.0f));
    }
    else
    {
        Unicode::snprintf(graphValueTextBuffer, 2, "-");
    }
}

void InteractiveGraph::handleTickEvent()
{
    // If graph curve has catched up with stick,
    // then set dot and value visible in the correct position
    if (slider.isVisible() && (! dot.isVisible()) &&
            graph.withinCurrentCurve(getCenterX(&slider)))
    {
        centerX(dot, getCenterX(&slider));
        centerY(dot, graph.getYCoordinate(getCenterX(&slider)) + 2);
        dot.setVisible(true);

        graphValueChanged(graph.getYValue(getCenterX(&slider)));

        waitingToScrollStick = true;
    }

    if (waitingToScrollStick && graph.isScrolling())
    {
        // The entire graph curve is moving, let drawables follow along
        waitingToScrollStick = false;
        scrollStickAndValue = true;
    }

    if (scrollStickAndValue)
    {
        // Graph generates two pixels per tick
        int8_t graphMovement = -2;
        slider.moveRelative(graphMovement, 0);
        top.moveRelative(graphMovement, 0);
        graphValue.moveRelative(graphMovement, 0);
        dot.moveRelative(graphMovement, 0);
    }

    if ((top.getX() < 0) && (hideTextBox.getAlpha() > 0))
    {
        hideTextBox.setAlpha(hideTextBox.getAlpha() - MIN(hideTextBox.getAlpha(), 6));
    }
}

void InteractiveGraph::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        stopGraph();
        showSliderAndValue(evt.getX());
        scrollStickAndValue = false;
        topContainer.invalidate();
    }
    else
    {
        startGraph();
        waitingToScrollStick = true;
    }
}

void InteractiveGraph::handleDragEvent(const DragEvent& evt)
{
    moveSliderAndValue(evt.getDeltaX());
}
