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
#ifndef INTERACTIVEGRAPH_HPP_
#define INTERACTIVEGRAPH_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/data_visualization_screen/Graph.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class InteractiveGraph : public Container
{
public:
    InteractiveGraph();
    virtual ~InteractiveGraph();

    void startGraph();
    void stopGraph();
    void initialize();
    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);

    virtual void getLastChild(int16_t x, int16_t y, Drawable** last)
    {
        *last = this;
    }
    virtual void getLastDraggableChild(int16_t x, int16_t y, Drawable** last)
    {
        *last = this;
    }

private:
    Image background;
    Container topContainer;
    Container graphContainer;
    Box hideTextBox;
    Graph graph;
    Image top;
    Image slider;
    Image dot;
    TextAreaWithOneWildcard graphValue;
    Unicode::UnicodeChar graphValueTextBuffer[5];
    bool scrollStickAndValue;
    bool waitingToScrollStick;

    void showSliderAndValue(int16_t xCoordinate);
    void moveSliderAndValue(int16_t xDelta);
    void graphValueChanged(int16_t value, bool valid = true);

    int16_t getCenterX(Drawable* draw) const
    {
        return draw->getX() + (draw->getWidth() / 2);
    }

    void centerX(Drawable& draw, int16_t x)
    {
        draw.setX(x - (draw.getWidth() / 2));
    }

    void centerY(Drawable& draw, int16_t y)
    {
        draw.setY(y - (draw.getHeight() / 2));
    }
};

#endif /* INTERACTIVEGRAPH_HPP_ */
