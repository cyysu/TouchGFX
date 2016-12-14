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
#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

void MainView::setupScreen()
{
    imgBackground.setBitmap(Bitmap(BITMAP_SCROLL_BG_ID));
    imgBackground.setXY(0, 0);

    scrollCnt.setPosition(42, 42, 396, 188);

    longTxt.setTypedText(TypedText(T_LOREM_IPSUM));
    // White text
    longTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    // Make text area larger than scrollable container, and set x,y
    // relative to scroll container.
    longTxt.setPosition(0, 0, 450, 720);
    scrollCnt.add(longTxt);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(imgBackground);
    add(scrollCnt);
}
