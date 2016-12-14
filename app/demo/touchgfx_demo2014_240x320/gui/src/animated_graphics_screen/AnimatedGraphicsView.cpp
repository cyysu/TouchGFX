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
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/EasingEquations.hpp>

AnimatedGraphicsView::AnimatedGraphicsView() :
    animationCounter(0),
    bumpMapImage(BITMAP_LIGHT_EFFECT_IMAGE_ID, _bump_map_touchgfx_logo, _light_source),
    onButtonPressed(this, &AnimatedGraphicsView::buttonPressedhandler)
{
    bumpMapInfo.image = BITMAP_LIGHT_EFFECT_IMAGE_ID;
    bumpMapInfo.bump_map = _bump_map_touchgfx_logo;
}

AnimatedGraphicsView::~AnimatedGraphicsView()
{
}

void AnimatedGraphicsView::setupScreen()
{
    bumpMapImage.setPosition(0, 0, HAL::DISPLAY_WIDTH, Bitmap(BITMAP_LIGHT_EFFECT_IMAGE_ID).getHeight());
    bumpMapImage.setVisible(true);
    updateBumpMapImage();

    exitButton.setBitmaps(Bitmap(BITMAP_ANIMATED_GRAPHICS_BACK_BUTTON_ID), Bitmap(BITMAP_ANIMATED_GRAPHICS_BACK_BUTTON_PRESSED_ID));
    exitButton.setXY(0, bumpMapImage.getHeight());
    exitButton.setAction(onButtonPressed);

    // ExitButton will be inactive until shade animation has ended
    exitButton.setTouchable(false);

    shade.setColor(0x0);
    shade.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - exitButton.getHeight());
    currentState = ANIMATE_SHADE_UP;

    add(bumpMapImage);
    add(shade);
    add(exitButton);
}

void AnimatedGraphicsView::tearDownScreen()
{

}

void AnimatedGraphicsView::handleTickEvent()
{
    if (currentState == ANIMATE_SHADE_UP)
    {
        animateShadeUp();
    }
}

void AnimatedGraphicsView::handleDragEvent(const DragEvent& evt)
{
    // Drag is disabled due to the capability of the resistive touch on the ST Discovery board
    //bumpMapImage.setLightPosition(evt.getNewX(), evt.getNewY());
}

void AnimatedGraphicsView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &exitButton)
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuScreen();
    }
}

void AnimatedGraphicsView::updateBumpMapImage()
{
    bumpMapImage.setImage(Bitmap(bumpMapInfo.image));
    bumpMapImage.setBumpMap(bumpMapInfo.bump_map);
    bumpMapImage.invalidate();
}

void AnimatedGraphicsView::animateShadeUp()
{
    uint8_t animateShadeUpDuration = 18;

    if (animationCounter <= animateShadeUpDuration)
    {
        int16_t deltaBackground = EasingEquations::quadEaseIn(animationCounter, 0, shade.getHeight(), animateShadeUpDuration);
        shade.moveTo(0, -deltaBackground);
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        exitButton.setTouchable(true);
    }

    animationCounter++;
}
