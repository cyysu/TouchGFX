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
#include <gui/custom_controls_screen/ThreeWayProgressBarCircle.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <assert.h>


ThreeWayProgressBarCircle::ThreeWayProgressBarCircle()
{
    background.setBitmap(Bitmap(BITMAP_CONTROLS_THREE_WAY_SMALL_CIRCLE_ID));
    background.setXY(0, 0);
    add(background);

    add(icon);

    text.setTypedText(TypedText(T_THREE_WAY_PROGRESS_BAR_PERCENTAGE));
    text.setWildcard(textBuffer);
    text.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    text.setPosition(30, 50, 40, 18);
    add(text);
    setPercentage(0);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

ThreeWayProgressBarCircle::~ThreeWayProgressBarCircle()
{
}

void ThreeWayProgressBarCircle::setIcon(BitmapId newIconBmp, BitmapId newIconActiveBmp)
{
    iconBmp = newIconBmp;
    iconActiveBmp = newIconActiveBmp;

    setActive(false);
    icon.setXY((background.getWidth() - icon.getWidth()) / 2, 15);
}

void ThreeWayProgressBarCircle::setActive(bool active)
{
    active ? icon.setBitmap(Bitmap(iconActiveBmp)) : icon.setBitmap(Bitmap(iconBmp));
    icon.invalidate();
}

void ThreeWayProgressBarCircle::setPercentage(int percentage)
{
    Unicode::snprintf(textBuffer, 5, "%d", percentage);
    text.invalidate();
}


