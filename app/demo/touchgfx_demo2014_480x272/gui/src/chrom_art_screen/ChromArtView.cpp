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
#include <gui/chrom_art_screen/ChromArtView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/FrontendApplication.hpp>

ChromArtView::ChromArtView() :
    DemoView(),
    currentState(ANIMATE_STARTUP),
    animationCounter(0),
    tickCounter(0),
    onButtonPressed(this, &ChromArtView::buttonPressedhandler)
{
}

ChromArtView::~ChromArtView()
{
}

void ChromArtView::setupScreen()
{
    viewPort.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), HAL::DISPLAY_HEIGHT);

    //background.setColor(Color::getColorFrom24BitRGB(0x3D, 0x87, 0xC4));
    //background.setPosition(0, 0, viewPort.getWidth(), viewPort.getHeight());

    background.setXY(0, 0);
    background.setBitmap(Bitmap(BITMAP_CHROM_ART_SUN_ID));

    clouds0.setBitmap(Bitmap(BITMAP_CHROM_ART_CLOUDS_ID));
    clouds0.setXY(0, 20);
    clouds0.setAlpha(0);

    clouds1.setBitmap(Bitmap(BITMAP_CHROM_ART_CLOUDS_ID));
    clouds1.setXY(clouds0.getWidth() + CLOUD_SPACING, 20);
    clouds1.setAlpha(0);

    treeLeft.setBitmap(Bitmap(BITMAP_CHROM_ART_BACKGROUND_LEFT_ID));
    treeRight.setBitmap(Bitmap(BITMAP_CHROM_ART_BACKGROUND_RIGHT_ID));
    treeLeft.setXY(viewPort.getWidth() - treeLeft.getWidth() - treeRight.getWidth(), HAL::DISPLAY_HEIGHT - treeLeft.getHeight());
    treeRight.setXY(treeLeft.getX() + treeLeft.getWidth(), HAL::DISPLAY_HEIGHT - treeRight.getHeight());
    treeLeft.setAlpha(0);
    treeRight.setAlpha(0);

    chromArtOnOffButton.setBitmaps(Bitmap(BITMAP_CHROM_ART_ON_BUTTON_ID), Bitmap(BITMAP_CHROM_ART_OFF_BUTTON_ID));
    chromArtOnOffButton.setXY(16, HAL::DISPLAY_HEIGHT - chromArtOnOffButton.getHeight() - 10);
    chromArtOnOffButton.setAction(onButtonPressed);

    stLogo.setBitmap(Bitmap(BITMAP_ST_LOGO_ID));
    stLogo.setXY(150, 40);
    stLogo.setAlpha(0);

    touchGFXLogo.setBitmap(Bitmap(BITMAP_TOUCHGFX_LOGO_ID));
    touchGFXLogo.setXY(30, 80);
    touchGFXLogo.setAlpha(0);

    nextButton.setBitmaps(Bitmap(BITMAP_LAYER_BUTTON_ID), Bitmap(BITMAP_LAYER_BUTTON_PRESSED_ID));
    nextButton.setXY(viewPort.getWidth() - nextButton.getWidth() - 16, HAL::DISPLAY_HEIGHT - nextButton.getHeight() - 10);
    nextButton.setAction(onButtonPressed);

    nextInsertElement = &treeRight;

    viewPort.add(background);
    viewPort.add(clouds0);
    viewPort.add(clouds1);
    viewPort.add(stLogo);
    viewPort.add(touchGFXLogo);
    viewPort.add(treeLeft);
    viewPort.add(treeRight);
    viewPort.add(chromArtOnOffButton);
    viewPort.add(nextButton);

    add(viewPort);
}

#if defined(ST) && !defined(SIMULATOR)
extern volatile bool disableChromArt;
#endif

void ChromArtView::tearDownScreen()
{
#if defined(ST) && !defined(SIMULATOR)
    disableChromArt = false;
#endif
}

void ChromArtView::handleTickEvent()
{
    tickCounter++;

    // Do not enter screen saver from this screen
    static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();

    if (currentState == ANIMATE_TO_NEXT_SETUP)
    {
        animateToNextSetup();
    }
    else if (currentState == ANIMATE_STARTUP)
    {
        animateStartUp();
    }

    //   if (tickCounter % 2 == 0)
    {
        animateClouds();
    }
}

void ChromArtView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &nextButton)
    {
        nextButton.setTouchable(false);

        currentState = ANIMATE_TO_NEXT_SETUP;
        animationCounter = 0;
    }
    else if (&button == &chromArtOnOffButton)
    {
#if defined(ST) && !defined(SIMULATOR)
        disableChromArt = !disableChromArt;
#endif
    }
}


void ChromArtView::animateToNextSetup()
{
    uint8_t fadeDuration = 18;

    if (animationCounter < fadeDuration)
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter, 0, 255, fadeDuration - 1);
        stLogo.setAlpha((uint8_t)(255 - alpha));
        touchGFXLogo.setAlpha((uint8_t)(255 - alpha));
        stLogo.invalidate();
        touchGFXLogo.invalidate();
    }
    else if (animationCounter == fadeDuration)
    {
        viewPort.remove(stLogo);
        viewPort.insert(nextInsertElement, stLogo);

        viewPort.remove(touchGFXLogo);
        viewPort.insert(&stLogo, touchGFXLogo);
        viewPort.invalidate();

        // Prepare the next insertion
        if (nextInsertElement == &treeRight)
        {
            nextInsertElement = &background;
        }
        else if (nextInsertElement == &background)
        {
            nextInsertElement = &clouds1;
        }
        else
        {
            nextInsertElement = &treeRight;
        }
    }
    else if (animationCounter < (uint8_t)(fadeDuration * 2))
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter - fadeDuration, 0, 255, fadeDuration - 1);
        stLogo.setAlpha((uint8_t) alpha);
        touchGFXLogo.setAlpha((uint8_t) alpha);
        stLogo.invalidate();
        touchGFXLogo.invalidate();
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

void ChromArtView::animateStartUp()
{
    uint8_t fadeDuration = 34;

    if (animationCounter < fadeDuration)
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter, 0, 255, fadeDuration - 1);
        clouds0.setAlpha((uint8_t) alpha);
        clouds1.setAlpha((uint8_t) alpha);
        clouds0.invalidate();
        clouds1.invalidate();
    }
    else if (animationCounter < (uint8_t)(fadeDuration * 2))
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter - fadeDuration, 0, 255, fadeDuration - 1);
        stLogo.setAlpha((uint8_t) alpha);
        stLogo.invalidate();
    }
    else if (animationCounter < (uint8_t)(fadeDuration * 3))
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter - (fadeDuration * 2), 0, 255, fadeDuration - 1);
        touchGFXLogo.setAlpha((uint8_t) alpha);
        touchGFXLogo.invalidate();
    }
    else if (animationCounter < (uint8_t)(fadeDuration * 4))
    {
        int16_t alpha = EasingEquations::quadEaseIn(animationCounter - (fadeDuration * 3), 0, 255, fadeDuration - 1);
        treeLeft.setAlpha((uint8_t) alpha);
        treeRight.setAlpha((uint8_t) alpha);
        treeLeft.invalidate();
        treeRight.invalidate();
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

void ChromArtView::animateClouds()
{
    clouds0.moveTo(clouds0.getX() - 1, clouds0.getY());
    clouds1.moveTo(clouds1.getX() - 1, clouds1.getY());

    if (clouds0.getX() + clouds0.getWidth() < 0)
    {
        clouds0.moveTo(clouds1.getX() + clouds1.getWidth() + CLOUD_SPACING, clouds0.getY());
    }
    else if (clouds1.getX() + clouds1.getWidth() < 0)
    {
        clouds1.moveTo(clouds0.getX() + clouds0.getWidth() + CLOUD_SPACING, clouds1.getY());
    }
}
