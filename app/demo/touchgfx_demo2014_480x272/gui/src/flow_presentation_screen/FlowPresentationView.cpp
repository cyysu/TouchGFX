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
#include <gui/flow_presentation_screen/FlowPresentationView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/EasingEquations.hpp>


FlowPresentationView::FlowPresentationView() :
    DemoView(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    numberOfForegroundImages(4),
    onButtonPressed(this, &FlowPresentationView::buttonPressedhandler)
{
}

FlowPresentationView::~FlowPresentationView()
{
}

void FlowPresentationView::setupScreen()
{
    portViewWidth = HAL::DISPLAY_WIDTH - backButton.getWidth();
    portViewHeight = HAL::DISPLAY_HEIGHT;

    background.setBitmap(Bitmap(BITMAP_PARALLAX_BACKGROUND_ID));
    background.setXY(0, 0);
    backgroundExtension.setBitmap(Bitmap(BITMAP_PARALLAX_BACKGROUND_ID));
    backgroundExtension.setXY(background.getWidth(), 0);

    foregroundImage0.setBitmap(Bitmap(BITMAP_PARALLAX_FOREGROUND_0_ID));
    foregroundImage0.setXY(((portViewWidth - foregroundImage0.getWidth()) / 2), 56);

    foregroundImage1.setBitmap(Bitmap(BITMAP_PARALLAX_FOREGROUND_1_ID));
    foregroundImage1.setXY(((portViewWidth - foregroundImage1.getWidth()) / 2) + 1 * portViewWidth, 0);

    foregroundImage2.setBitmap(Bitmap(BITMAP_PARALLAX_FOREGROUND_2_ID));
    foregroundImage2.setXY(((portViewWidth - foregroundImage2.getWidth()) / 2) + 2 * portViewWidth + 16, 0);

    foregroundImage3.setBitmap(Bitmap(BITMAP_PARALLAX_FOREGROUND_3_ID));
    foregroundImage3.setXY(((portViewWidth - foregroundImage3.getWidth()) / 2) + 3 * portViewWidth + 18, 8);

    foreground.add(foregroundImage0);
    foreground.add(foregroundImage1);
    foreground.add(foregroundImage2);
    foreground.add(foregroundImage3);
    foreground.setPosition(0, 10, numberOfForegroundImages * portViewWidth, HAL::DISPLAY_HEIGHT - 10);
    foregroundIndex = 0;

    leftButton.setBitmaps(Bitmap(BITMAP_PREVIOUS_BUTTON_ID), Bitmap(BITMAP_PREVIOUS_BUTTON_PRESSED_ID));
    leftButton.setXY(10, HAL::DISPLAY_HEIGHT - leftButton.getHeight() - 8);
    leftButton.setAction(onButtonPressed);
    leftButton.setAlpha(0);

    rightButton.setBitmaps(Bitmap(BITMAP_NEXT_BUTTON_ID), Bitmap(BITMAP_NEXT_BUTTON_PRESSED_ID));
    rightButton.setXY(portViewWidth - rightButton.getWidth() - 8, HAL::DISPLAY_HEIGHT - rightButton.getHeight() - 8);
    rightButton.setAction(onButtonPressed);

    setButtonActiveState();

    dotIndicator.setNumberOfDots(numberOfForegroundImages);
    dotIndicator.setBitmaps(Bitmap(BITMAP_WEATHER_DOT_SELECTED_ID), Bitmap(BITMAP_WEATHER_DOT_NORMAL_ID));
    dotIndicator.setXY((portViewWidth - dotIndicator.getWidth()) / 2, HAL::DISPLAY_HEIGHT - 18);

    flowPresentationViewPort.add(background);
    flowPresentationViewPort.add(backgroundExtension);
    flowPresentationViewPort.add(foreground);
    flowPresentationViewPort.add(leftButton);
    flowPresentationViewPort.add(rightButton);
    flowPresentationViewPort.add(dotIndicator);
    flowPresentationViewPort.setPosition(backButton.getWidth(), 0, portViewWidth, portViewHeight);

    add(flowPresentationViewPort);
}

void FlowPresentationView::tearDownScreen()
{

}

void FlowPresentationView::handleTickEvent()
{
    if (currentState == ANIMATE_LEFT)
    {
        animateLeft();
    }
    else if (currentState == ANIMATE_RIGHT)
    {
        animateRight();
    }
}

void FlowPresentationView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &leftButton)
    {
        setState(ANIMATE_RIGHT);
        dotIndicator.goLeft();
    }
    else if (&button == &rightButton)
    {
        setState(ANIMATE_LEFT);
        dotIndicator.goRight();
    }
    setButtonActiveState();
}

void FlowPresentationView::setState(States newState)
{
    animationCounter = 1;
    currentState = newState;
}

void FlowPresentationView::animateLeft()
{
    uint8_t duration = 18;

    if (animationCounter <= duration)
    {
        int16_t deltaBackground = EasingEquations::quadEaseInOut(animationCounter, 0, 120, duration);
        background.moveTo(-foregroundIndex * 120 - deltaBackground, background.getY());
        backgroundExtension.moveTo(-foregroundIndex * 120 - deltaBackground + background.getWidth(), background.getY());

        int16_t deltaForeground = EasingEquations::quadEaseInOut(animationCounter, 0, portViewWidth, duration);
        foreground.moveTo(-foregroundIndex * portViewWidth - deltaForeground, foreground.getY());

        if ((foregroundIndex + 1) >= (numberOfForegroundImages - 1))
        {
            int16_t deltaAlpha = EasingEquations::quadEaseInOut(animationCounter, 0, 255, duration);
            rightButton.setAlpha((uint8_t) 255 - deltaAlpha);
        }
        else if (foregroundIndex <= 0)
        {
            int16_t deltaAlpha = EasingEquations::quadEaseInOut(animationCounter, 0, 255, duration);
            leftButton.setAlpha((uint8_t) deltaAlpha);
        }
    }
    else
    {
        // Final step: stop the animation
        setState(NO_ANIMATION);
        animationCounter = 0;
        foregroundIndex++;
        setButtonActiveState();
    }
    animationCounter++;
}

void FlowPresentationView::animateRight()
{
    uint8_t duration = 18;

    if (animationCounter <= duration)
    {
        int16_t deltaBackground = EasingEquations::quadEaseInOut(animationCounter, 0, 120, duration);
        background.moveTo(-foregroundIndex * 120 + deltaBackground, background.getY());
        backgroundExtension.moveTo(-foregroundIndex * 120 + deltaBackground + background.getWidth(), background.getY());

        int16_t deltaForeground = EasingEquations::quadEaseInOut(animationCounter, 0, portViewWidth, duration);
        foreground.moveTo(-foregroundIndex * portViewWidth + deltaForeground, foreground.getY());

        if ((foregroundIndex) >= (numberOfForegroundImages - 1))
        {
            int16_t deltaAlpha = EasingEquations::quadEaseInOut(animationCounter, 0, 255, duration);
            rightButton.setAlpha((uint8_t) deltaAlpha);
        }
        else if ((foregroundIndex - 1) <= 0)
        {
            int16_t deltaAlpha = EasingEquations::quadEaseInOut(animationCounter, 0, 255, duration);
            leftButton.setAlpha((uint8_t) 255 - deltaAlpha);
        }
    }
    else
    {
        // Final step: stop the animation
        setState(NO_ANIMATION);
        animationCounter = 0;
        foregroundIndex--;
        setButtonActiveState();
    }
    animationCounter++;
}

void FlowPresentationView::setButtonActiveState()
{
    if (currentState == NO_ANIMATION)
    {
        if (foregroundIndex >= (numberOfForegroundImages - 1))
        {
            leftButton.setTouchable(true);
            rightButton.setTouchable(false);
        }
        else if (foregroundIndex <= 0)
        {
            leftButton.setTouchable(false);
            rightButton.setTouchable(true);
        }
        else
        {
            leftButton.setTouchable(true);
            rightButton.setTouchable(true);
        }
    }
    else
    {
        leftButton.setTouchable(false);
        rightButton.setTouchable(false);
    }
}
