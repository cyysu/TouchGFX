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
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <gui/graph_screen/GraphLine.hpp>
#include <gui/graph_screen/GraphBelow.hpp>
#include <gui/graph_screen/GraphDots.hpp>
#include <gui/graph_screen/PainterVerticalAlpha.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#endif
#include <BitmapDatabase.hpp>

#include <touchgfx/widgets/Box.hpp>

using namespace touchgfx;

class Graph : public Container
{
public:
    static const int NUMBER_OF_POINTS = 17;

    Graph();
    virtual ~Graph() { }

    void setup(int newWidth, int newHeight, colortype lineColor, colortype backgroundColor);

    bool addValue(int x, int y)
    {
        return graphLine.addValue(x, y);
    }

    bool deleteValue(int x)
    {
        return graphLine.deleteValue(x);
    }

    void clear()
    {
        graphLine.clearGraph();
    }

    void setRange(int left, int right, int top, int bottom) ;

    void setLineVisible(bool lineVisible);
    void setDotsVisible(bool dotsVisible);
    void setDotsBackgroundVisible(bool dotsBackgroundVisible);
    void setAreaVisible(bool areaVisible);

    void setDotShape(int startAngle, int angleStep, int lineWidth);
    void setDotBackgroundShape(int startAngle, int angleStep, int lineWidth);

    uint8_t getAlpha()
    {
        return myAlpha;
    }
    void setAlpha(uint8_t alpha)
    {
        myAlpha = alpha;
        graphLine.setAlpha(myAlpha);
        graphArea.setAlpha(myAlpha);
        graphDots.setAlpha(myAlpha);
        graphDotsBackground.setAlpha(myAlpha);
        invalidate();
    }
protected:

    GraphLine graphLine;
    GraphBelow graphArea;
    GraphDots graphDots;
    GraphDots graphDotsBackground;

    GraphLine::GraphPoint graphBuffer[NUMBER_OF_POINTS];

#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 graphLinePainter;
    PainterRGB565 graphDotsPainter;
    PainterRGB565 graphDotsBackgroundPainter;
#elif USE_BPP==24
    PainterRGB888 graphLinePainter;
    PainterRGB888 graphDotsPainter;
    PainterRGB888 graphDotsBackgroundPainter;
#endif
    PainterVerticalAlpha graphAreaPainter;

    uint8_t myAlpha;
};


#endif /* GRAPH_HPP */
