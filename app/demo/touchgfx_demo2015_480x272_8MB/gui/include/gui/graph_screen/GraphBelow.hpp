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
#ifndef GRAPHBELOW_HPP
#define GRAPHBELOW_HPP

#include <gui/graph_screen/GraphLine.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/widgets/canvas/Canvas.hpp>
#include <touchgfx/widgets/canvas/CanvasWidget.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

/**
* @class GraphBelow GraphBelow.hpp gui/common/GraphBelow.hpp
*
* @brief Simple widget capable of drawing a graph line. The graph line consists of a number of
*        points with different x values. Points on the graph can be added and removed and the
*        coordinate system of the graph can easily be setup.
*
* @see CanvasWidget
*/
class GraphBelow : public GraphLine
{
public:
    /**
    * @fn virtual GraphBelow::~GraphBelow()
    *
    * @brief Virtual Destructor. Not used.
    *
    *        Virtual Destructor. Not used.
    */
    virtual ~GraphBelow();

    /**
    * @fn virtual bool GraphBelow::drawCanvasWidget(const Rect& invalidatedArea) const
    *
    * @brief Draw the graph line.
    *
    *        Draw the graph line. Care is taken not to spend time drawing graphs lines
    *        that are outside the invalidated area.
    *
    * @param invalidatedArea The rectangle to draw, with coordinates relative to this drawable.
    *
    * @return true if it succeeds, false if there was insufficient memory to draw the line.
    */
    virtual bool drawCanvasWidget(const Rect& invalidatedArea) const;

protected:
    virtual Rect getMinimalRectContainingIndices(int firstIndex, int lastIndex) const;

};

#endif
