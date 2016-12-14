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
#include <gui/animated_graphics_screen/AnimatedGraphicsView.hpp>
#include "BitmapDatabase.hpp"
#include <gui/animated_graphics_screen/BumpMap.hpp>
#include <touchgfx/EasingEquations.hpp>

AnimatedGraphicsView::AnimatedGraphicsView() :
    DemoView(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    currentBumpMap(0),
    bumpMapImage(BITMAP_LIGHT_EFFECT_IMAGE_ID, _bump_map_touchgfx_logo, _light_source),
    onButtonPressed(this, &AnimatedGraphicsView::buttonPressedhandler)
{
    bumpMapInfo[0].image = BITMAP_LIGHT_EFFECT_IMAGE_ID;
    bumpMapInfo[0].bump_map = _bump_map_touchgfx_logo;
    bumpMapInfo[1].image = BITMAP_LIGHT_EFFECT_IMAGE_TEST_ID;
    bumpMapInfo[1].bump_map = _bump_map_touchgfx_logo_2;
    updateBumpMapImage();
}

AnimatedGraphicsView::~AnimatedGraphicsView()
{
}

void AnimatedGraphicsView::setupScreen()
{
    shade.setColor(0x0);
    shade.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), HAL::DISPLAY_HEIGHT);
    currentState = ANIMATE_SHADE_UP;

    bumpMapImage.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), HAL::DISPLAY_HEIGHT);
    bumpMapImage.setVisible(true);

    nextButton.setBitmaps(Bitmap(BITMAP_NEXT_BUTTON_ID), Bitmap(BITMAP_NEXT_BUTTON_PRESSED_ID));
    nextButton.setXY(HAL::DISPLAY_WIDTH - nextButton.getWidth() - 10, HAL::DISPLAY_HEIGHT - nextButton.getHeight() - 10);
    nextButton.setAction(onButtonPressed);
    nextButton.setTouchable(false);

    add(bumpMapImage);
    add(shade);
    add(nextButton);

    // Because this view takes a long time to render, we must sample touch at every frame to avoid laggy touch input.
    // Remember the original setting so it can be restored when leaving this view.
    originalTouchSampleRate = HAL::getInstance()->getTouchSampleRate();
    HAL::getInstance()->setTouchSampleRate(1);
}

void AnimatedGraphicsView::tearDownScreen()
{
    // Restore original touch sample rate.
    HAL::getInstance()->setTouchSampleRate(originalTouchSampleRate);
}

void AnimatedGraphicsView::handleTickEvent()
{
    if (currentState == ANIMATE_TO_NEXT_IMAGE)
    {
        animateToNextImage();
    }
    else if (currentState == ANIMATE_SHADE_UP)
    {
        animateShadeUp();
    }
}

void AnimatedGraphicsView::handleDragEvent(const DragEvent& evt)
{
    bumpMapImage.setLightPosition(evt.getNewX(), evt.getNewY());
}

void AnimatedGraphicsView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &nextButton)
    {
        currentState = ANIMATE_TO_NEXT_IMAGE;
        animationCounter = 0;
        nextButton.setTouchable(false);
    }
}

void AnimatedGraphicsView::updateBumpMapImage()
{
    bumpMapImage.setImage(Bitmap(bumpMapInfo[currentBumpMap].image));
    bumpMapImage.setBumpMap(bumpMapInfo[currentBumpMap].bump_map);
    bumpMapImage.invalidate();
}

void AnimatedGraphicsView::animateToNextImage()
{
    uint8_t animateShadeDownDuration = 18;
    uint8_t changeImageDuration = 1;


    if (animationCounter <= animateShadeDownDuration)
    {
        int16_t deltaBackground = EasingEquations::quadEaseOut(animationCounter, 0, HAL::DISPLAY_HEIGHT, animateShadeDownDuration);
        shade.moveTo(backButton.getWidth(), -HAL::DISPLAY_HEIGHT + deltaBackground);

    }
    else if (animationCounter == animateShadeDownDuration + changeImageDuration)
    {
        currentBumpMap++;
        if (currentBumpMap == NUMBER_OF_BUMP_MAPS)
        {
            currentBumpMap = 0;
        }
        updateBumpMapImage();
    }
    else
    {
        animationCounter = 0;
        currentState = ANIMATE_SHADE_UP;
    }

    animationCounter++;
}

void AnimatedGraphicsView::animateShadeUp()
{
    uint8_t animateShadeUpDuration = 18;

    if (animationCounter <= animateShadeUpDuration)
    {
        int16_t deltaBackground = EasingEquations::quadEaseIn(animationCounter, 0, HAL::DISPLAY_HEIGHT, animateShadeUpDuration);
        shade.moveTo(backButton.getWidth(), -deltaBackground);
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        nextButton.setTouchable(true);
    }

    animationCounter++;
}
