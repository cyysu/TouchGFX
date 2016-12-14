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
#include <gui/data_visualization_screen/BarContainer.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <assert.h>
#include <stdlib.h>

BarContainer::BarContainer() :
    ListLayout(EAST),
    animate(false)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 2 == 0)
        {
            bars[i].image.setBitmap(Bitmap(BITMAP_GRAPH_6HOURS_PINK_BAR_ID));
            add(bars[i].image);
            // Adjustment for placing bar correctly on background grid image
            bars[i].image.setX(bars[i].image.getX() + i);
        }
        else
        {
            bars[i].image.setBitmap(Bitmap(BITMAP_GRAPH_6HOURS_GREEN_BAR_ID));
            add(bars[i].image);
            // Adjustment for placing bar correctly on background grid image
            bars[i].image.setX(bars[i - 1].image.getX() + bars[i - 1].image.getWidth());
        }
        // Force ListLayout to show all of rightmost bar
        setWidth(getWidth() + 10);
    }

    Application::getInstance()->registerTimerWidget(this);
}

BarContainer::~BarContainer()
{
}

void BarContainer::startAnimation()
{
    animate = true;
    animationCounter = 0;

    for (int i = 0; i < SIZE; i++)
    {
        bars[i].targetValue = (int16_t)(getHeight() * (rand() / (float)(RAND_MAX)));
        bars[i].image.setY(getBarHeight());
    }
}

int16_t BarContainer::getBarHeight() const
{
    assert(SIZE > 0 && "Number of bars is zero");
    return bars[0].image.getHeight();
}

void BarContainer::handleTickEvent()
{
    if (animate)
    {
        if (animationCounter <= ANIMATION_STEPS)
        {
            for (int i = 0; i < SIZE; i++)
            {
                int16_t delta = EasingEquations::circEaseOut(animationCounter, 0, bars[i].targetValue, ANIMATION_STEPS);
                bars[i].image.moveTo(bars[i].image.getX(), getBarHeight() - delta);
            }
        }
        else
        {
            // Final step: stop the animation
            animate = false;
            animationCounter = 0;
        }
        animationCounter++;
    }
}
