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
#ifndef EASING_EQUATION_GRAPH_HPP
#define EASING_EQUATION_GRAPH_HPP

#include <gui/graph_screen/GraphLine.hpp>
#include <touchgfx/containers/Container.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#endif
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class EasingEquationGraph : public Container
{
public:

    EasingEquationGraph();
    virtual ~EasingEquationGraph() { }

    void setup(int newWidth, int newHeight, colortype lineColor, uint16_t lineWidth);

    template <class T>
    bool addValue(T x, T y)
    {
        return graphLine.addValue(x, y);
    }

    template <class T>
    bool deleteValue(T x)
    {
        return graphLine.deleteValue(x);
    }

    void clear()
    {
        graphLine.clearGraph();
    }

    void setRange(int left, int right, int top, int bottom) ;

protected:
    static const int NUMBER_OF_POINTS = 52;

    GraphLine graphLine;

    GraphLine::GraphPoint graphBuffer[NUMBER_OF_POINTS];

#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 graphLinePainter;
#elif USE_BPP==24
    PainterRGB888 graphLinePainter;
#endif
};


#endif /* EASING_EQUATION_GRAPH_HPP */
