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
#include <gui/graph_screen/Graph.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <math.h>

Graph::Graph() :
    myAlpha(255)
{
}

Graph::~Graph()
{
}

void Graph::setup(int newWidth, int newHeight, colortype lineColor, colortype backgroundColor)
{
    setWidth(newWidth);
    setHeight(newHeight);

    graphLinePainter.setColor(lineColor);
    graphAreaPainter.setColor(lineColor, getHeight());
    graphDotsPainter.setColor(lineColor);
    graphDotsBackgroundPainter.setColor(backgroundColor);

    graphLine.setLinkedGraph(graphArea);
    graphLine.setLinkedGraph(graphDots);
    graphLine.setLinkedGraph(graphDotsBackground);

    graphLine.setPosition(0, 0, getWidth(), getHeight());
    graphLine.setPainter(graphLinePainter);
    graphLine.setBuffer(graphBuffer, NUMBER_OF_POINTS);
    graphLine.setLineWidth(1);
    graphLine.setRange(-6, 400, 400, 0);

    graphArea.setPainter(graphAreaPainter);
    graphArea.setLineWidth(0);

    graphDots.setPainter(graphDotsPainter);
    graphDots.setLineWidth(7);
    graphDots.setDotShape(0, 90);

    graphDotsBackground.setPainter(graphDotsBackgroundPainter);
    graphDotsBackground.setLineWidth(9);
    graphDotsBackground.setDotShape(0, 30);

    add(graphArea);
    add(graphLine);
    add(graphDotsBackground);
    add(graphDots);
}

void Graph::setRange(int left, int right, int top, int bottom)
{
    graphLine.setRange(left, right, top, bottom);
}

void Graph::setLineVisible(bool lineVisible)
{
    graphLine.setVisible(lineVisible);
}

void Graph::setDotsVisible(bool dotsVisible)
{
    graphDots.setVisible(dotsVisible);
}

void Graph::setDotsBackgroundVisible(bool dotsBackgroundVisible)
{
    graphDotsBackground.setVisible(dotsBackgroundVisible);
}

void Graph::setAreaVisible(bool areaVisible)
{
    graphArea.setVisible(areaVisible);
}

void Graph::setDotShape(int startAngle, int angleStep, int lineWidth)
{
    graphDots.setDotShape(startAngle, angleStep);
    graphDots.setLineWidth(lineWidth);
    graphDots.invalidate();
}

void Graph::setDotBackgroundShape(int startAngle, int angleStep, int lineWidth)
{
    graphDotsBackground.setDotShape(startAngle, angleStep);
    graphDotsBackground.setLineWidth(lineWidth);
    graphDots.invalidate();
}

void Graph::setAlpha(uint8_t alpha)
{
    myAlpha = alpha;
    graphLine.setAlpha(myAlpha);
    graphArea.setAlpha(myAlpha);
    graphDots.setAlpha(myAlpha);
    graphDotsBackground.setAlpha(myAlpha);
    invalidate();
}

uint8_t Graph::getAlpha()
{
    return myAlpha;
}
