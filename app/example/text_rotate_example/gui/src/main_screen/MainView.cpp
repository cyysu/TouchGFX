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
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

void MainView::setupScreen()
{
    // Setup background image
    img.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
    img.setXY(0, 0);

    // Setup button with correct bitmaps and label
    antiClockwiseButton.setBitmaps(Bitmap(BITMAP_BTN_ID), Bitmap(BITMAP_BTN_PRESSED_ID));
    antiClockwiseButton.setXY(320, 30);
    antiClockwiseButton.setLabelText(TypedText(T_ROTATE_ANTICLOCKWISE));
    antiClockwiseButton.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    antiClockwiseButton.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    antiClockwiseButton.setAction(antiClockwiseClickedCallback);

    // Setup button with correct bitmaps and label
    clockwiseButton.setBitmaps(Bitmap(BITMAP_BTN2_ID), Bitmap(BITMAP_BTN2_PRESSED_ID));
    clockwiseButton.setXY(394, 116);
    clockwiseButton.setLabelText(TypedText(T_ROTATE_CLOCKWISE));
    clockwiseButton.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    clockwiseButton.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    clockwiseButton.setLabelRotation(TEXT_ROTATE_90);
    clockwiseButton.setAction(clockwiseClickedCallback);

    // Setup main text
    mainTxt.setTypedText(TypedText(T_MAIN_TEXT));
    mainTxt.setPosition(50, 40, 201, 191);
    mainTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    mainTxt.setRotation(rotation);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(img);
    add(antiClockwiseButton);
    add(clockwiseButton);
    add(mainTxt);
}

void MainView::clockwiseClicked(const AbstractButton& source)
{
    switch (rotation)
    {
    case TEXT_ROTATE_0:
        rotation = TEXT_ROTATE_90;
        break;
    case TEXT_ROTATE_90:
        rotation = TEXT_ROTATE_180;
        break;
    case TEXT_ROTATE_180:
        rotation = TEXT_ROTATE_270;
        break;
    case TEXT_ROTATE_270:
        rotation = TEXT_ROTATE_0;
        break;
    }
    mainTxt.setRotation(rotation);
    mainTxt.invalidate();
}

void MainView::antiClockwiseClicked(const AbstractButton& source)
{
    switch (rotation)
    {
    case TEXT_ROTATE_0:
        rotation = TEXT_ROTATE_270;
        break;
    case TEXT_ROTATE_90:
        rotation = TEXT_ROTATE_0;
        break;
    case TEXT_ROTATE_180:
        rotation = TEXT_ROTATE_90;
        break;
    case TEXT_ROTATE_270:
        rotation = TEXT_ROTATE_180;
        break;
    }
    mainTxt.setRotation(rotation);
    mainTxt.invalidate();
}
