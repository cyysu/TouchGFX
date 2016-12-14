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
#include <gui/common/McuLoadSlider.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>


McuLoadSlider::McuLoadSlider() :
    animationCounter(0)
{
    background.setBitmap(Bitmap(BITMAP_DEMO_MCU_LOAD_BACKGROUND_ID));
    setWidth(background.getWidth());
    setHeight(background.getHeight());

    // set background outside container
    background.setXY(background.getWidth(), 0);
    background.setAlpha(168);

    mcuLoadHeadline.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_TEXT));
    mcuLoadHeadline.setPosition(background.getX(), 0, background.getWidth(), 15);
    mcuLoadHeadline.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));


    // Setup mcuLoadTxt with correct initialized buffer
    // for wildcard text
    Unicode::snprintf(mcuLoadTxtbuf, 5, "%d", 0);
    mcuLoadTxt.setWildcard(mcuLoadTxtbuf);
    mcuLoadTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_VALUE));
    mcuLoadTxt.setPosition(background.getX(), 15, background.getWidth(), 15);
    mcuLoadTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    add(background);
    add(mcuLoadHeadline);
    add(mcuLoadTxt);
}

void McuLoadSlider::setValue(uint8_t load)
{
    Unicode::snprintf(mcuLoadTxtbuf, 5, "%d", load);
    mcuLoadTxt.invalidate();
}

void McuLoadSlider::show()
{
    Application::getInstance()->registerTimerWidget(this);
    state = LEFT_ANIMATION;
    startPositionX = background.getWidth();
}

void McuLoadSlider::hide()
{
    Application::getInstance()->registerTimerWidget(this);
    state = RIGHT_ANIMATION;
    startPositionX = background.getX();
}

void McuLoadSlider::handleTickEvent()
{

    uint8_t duration = 7;

    if (animationCounter > duration)
    {
        // End of animation
        state = NO_ANIMATION;
        animationCounter = 0;
        Application::getInstance()->unregisterTimerWidget(this);
    }
    else
    {
        int8_t animationDirection = (state == LEFT_ANIMATION) ? -1 : 1;
        background.moveTo(startPositionX + animationDirection * EasingEquations::linearEaseNone(animationCounter, 0, getWidth(), duration), 0);
        mcuLoadHeadline.setPosition(background.getX(), 0, background.getWidth(), 15);
        mcuLoadTxt.setPosition(background.getX(), 15, background.getWidth(), 15);
        mcuLoadHeadline.invalidate();
        mcuLoadTxt.invalidate();
        animationCounter++;
    }
}
