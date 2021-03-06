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
#include <gui/live_data_display_screen/LiveDataDisplayView.hpp>
#include <touchgfx/EasingEquations.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <stdlib.h>


LiveDataDisplayView::LiveDataDisplayView() :
    DemoView(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    tickCounter(0),
    dragX(0),
    infoScreens(EAST)
{
}

LiveDataDisplayView::~LiveDataDisplayView()
{
}

void LiveDataDisplayView::setupScreen()
{
    backButtonShadow.setBitmap(Bitmap(BITMAP_BACK_MENU_SHADOW_ID));
    backButtonShadow.setXY(backButton.getWidth(), 0);

    backgroundSwipeAreaLeft.setBitmap(Bitmap(BITMAP_WEATHER_BACKGROUND_ENDING_1_ID));
    backgroundSwipeAreaLeft.setXY(backButton.getWidth(), 0);

    backgroundSwipeAreaRight.setBitmap(Bitmap(BITMAP_WEATHER_BACKGROUND_ENDING_4_ID));
    backgroundSwipeAreaRight.setXY(HAL::DISPLAY_WIDTH - backgroundSwipeAreaRight.getWidth(), 0);

    infoScreensViewPort.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), HAL::DISPLAY_HEIGHT);

    infoScreen[0].setBitmap(BITMAP_WEATHER_BACKGROUND_1_ID);
    infoScreen[0].setCity(CityInfo::COPENHAGEN);
    infoScreen[0].setTextColor(Color::getColorFrom24BitRGB(0xFA, 0xF0, 0xB4));
    infoScreen[1].setBitmap(BITMAP_WEATHER_BACKGROUND_2_ID);
    infoScreen[1].setCity(CityInfo::HONG_KONG);
    infoScreen[1].setTextColor(Color::getColorFrom24BitRGB(0x0A, 0x45, 0x064));
    infoScreen[2].setBitmap(BITMAP_WEATHER_BACKGROUND_3_ID);
    infoScreen[2].setCity(CityInfo::MUMBAI);
    infoScreen[2].setTextColor(Color::getColorFrom24BitRGB(0x27, 0x5F, 0x7D));
    infoScreen[3].setBitmap(BITMAP_WEATHER_BACKGROUND_4_ID);
    infoScreen[3].setCity(CityInfo::NEW_YORK);
    infoScreen[3].setTextColor(Color::getColorFrom24BitRGB(0xBA, 0xD2, 0xDA));

    infoScreens.setXY(0, 0);
    infoScreens.add(infoScreen[0]);
    infoScreens.add(infoScreen[1]);
    infoScreens.add(infoScreen[2]);
    infoScreens.add(infoScreen[3]);
    infoScreensViewPort.add(infoScreens);

    currentScreen = 0;
    weekInfoBar.setPosition(backButton.getWidth(), 185, HAL::DISPLAY_WIDTH - backButton.getWidth(), 60);
    weekInfoBar.setTextColor(infoScreen[currentScreen].getTextColor());
    weekInfoBar.setInfo(infoScreen[currentScreen].getCity());

    dotIndicator.setNumberOfDots(NUMBER_OF_SCREENS);
    dotIndicator.setBitmaps(Bitmap(BITMAP_WEATHER_DOT_NORMAL_ID), Bitmap(BITMAP_WEATHER_DOT_SELECTED_ID));
    dotIndicator.setXY(backButton.getWidth() + ((HAL::DISPLAY_WIDTH - backButton.getWidth() - dotIndicator.getWidth()) / 2), 252);


    add(backgroundSwipeAreaLeft);
    add(backgroundSwipeAreaRight);
    add(infoScreensViewPort);
    add(weekInfoBar);
    add(dotIndicator);

    add(backButtonShadow);
}

void LiveDataDisplayView::tearDownScreen()
{

}

void LiveDataDisplayView::handleTickEvent()
{
    tickCounter++;

    if (currentState == ANIMATE_SWIPE_CANCELLED_LEFT)
    {
        animateSwipeCancelledLeft();
    }
    else if (currentState == ANIMATE_SWIPE_CANCELLED_RIGHT)
    {
        animateSwipeCancelledRight();
    }
    else if (currentState == ANIMATE_LEFT)
    {
        animateLeft();
    }
    else if (currentState == ANIMATE_RIGHT)
    {
        animateRight();
    }

    // Sometimes change current temperature to make
    // demo screen look alive
    if (tickCounter % 100 == 0)
    {
        for (int16_t i = 0; i < NUMBER_OF_SCREENS; i++)
        {
            if ((rand() % 4) == 0)
            {
                infoScreen[i].adjustTemperature();
            }
        }
    }

}

void LiveDataDisplayView::handleClickEvent(const ClickEvent& evt)
{
    // If an animation is already in progress do not
    // react to clicks
    if (currentState != NO_ANIMATION)
    {
        if (evt.getX() < backButton.getWidth())
        {
            DemoView<LiveDataDisplayPresenter>::handleClickEvent(evt);
        }
        return;
    }

    if (evt.getType() == ClickEvent::RELEASED)
    {
        // Save current position for use during animation
        animateDistance = dragX;
        startX = infoScreens.getX();

        if (dragX < 0)
        {
            if (currentScreen == NUMBER_OF_SCREENS - 1 || dragX > -120)
            {
                currentState = ANIMATE_SWIPE_CANCELLED_LEFT;
            }
            else
            {
                currentState = ANIMATE_LEFT;
            }
        }
        else if (dragX > 0)
        {
            if (currentScreen == 0 || dragX < 120)
            {
                currentState = ANIMATE_SWIPE_CANCELLED_RIGHT;
            }
            else
            {
                currentState = ANIMATE_RIGHT;
            }
        }

        //adjustInfoScreens();
    }

    if (evt.getX() < backButton.getWidth())
    {
        DemoView<LiveDataDisplayPresenter>::handleClickEvent(evt);
        return;
    }
}

void LiveDataDisplayView::handleDragEvent(const DragEvent& evt)
{
    // If an animation is already in progress do not
    // react to drags
    if (currentState != NO_ANIMATION)
    {
        return;
    }

    dragX += evt.getDeltaX();

    // Do not show too much background next to end screens
    if (currentScreen == 0 && dragX > backgroundSwipeAreaLeft.getWidth())
    {
        dragX = backgroundSwipeAreaLeft.getWidth();
    }
    else if (currentScreen == NUMBER_OF_SCREENS - 1 && dragX < -backgroundSwipeAreaRight.getWidth())
    {
        dragX = -backgroundSwipeAreaRight.getWidth();
    }

    adjustInfoScreens();
}

void LiveDataDisplayView::handleGestureEvent(const GestureEvent& evt)
{
    // Do not accept gestures while animating
    if (currentState != NO_ANIMATION)
    {
        return;
    }

    if (evt.getType() == evt.SWIPE_HORIZONTAL)
    {
        // Save current position for use during animation
        animateDistance = dragX;
        startX = infoScreens.getX();

        if (evt.getVelocity() < 0  && currentScreen < NUMBER_OF_SCREENS - 1)
        {
            currentState = ANIMATE_LEFT;
        }
        else if (evt.getVelocity() > 0  && currentScreen > 0)
        {
            currentState = ANIMATE_RIGHT;
        }
    }
}

void LiveDataDisplayView::adjustInfoScreens()
{
    infoScreens.moveTo(-(currentScreen * (HAL::DISPLAY_WIDTH - backButton.getWidth())) + dragX, 0);

    int alphaAdjustment = (dragX < 0) ? -dragX : dragX;
    weekInfoBar.setAlpha(255 - alphaAdjustment);
}

void LiveDataDisplayView::animateSwipeCancelledLeft()
{
    uint8_t duration = 14;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, -animateDistance, duration);
        dragX = animateDistance + delta;

        adjustInfoScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        dragX = 0;
        adjustInfoScreens();
    }
    animationCounter++;
}

void LiveDataDisplayView::animateSwipeCancelledRight()
{
    uint8_t duration = 14;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, animateDistance, duration);
        dragX = animateDistance - delta;

        adjustInfoScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        dragX = 0;
        adjustInfoScreens();
    }
    animationCounter++;
}

void LiveDataDisplayView::animateLeft()
{
    uint8_t duration = 10;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, infoScreensViewPort.getWidth() + animateDistance, duration);
        dragX = animateDistance - delta;

        adjustInfoScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        currentScreen++;
        dragX = 0;
        weekInfoBar.setTextColor(infoScreen[currentScreen].getTextColor());
        weekInfoBar.setInfo(infoScreen[currentScreen].getCity());
        adjustInfoScreens();
        dotIndicator.goRight();
    }
    animationCounter++;
}

void LiveDataDisplayView::animateRight()
{
    uint8_t duration = 10;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, infoScreensViewPort.getWidth() - animateDistance, duration);
        dragX = animateDistance + delta;

        adjustInfoScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        currentScreen--;
        dragX = 0;
        weekInfoBar.setTextColor(infoScreen[currentScreen].getTextColor());
        weekInfoBar.setInfo(infoScreen[currentScreen].getCity());
        adjustInfoScreens();
        dotIndicator.goLeft();
    }
    animationCounter++;
}
