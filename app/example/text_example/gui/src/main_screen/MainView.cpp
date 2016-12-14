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
    switchLanguageButton.setBitmaps(Bitmap(BITMAP_BTN_ID), Bitmap(BITMAP_BTN_PRESSED_ID));
    switchLanguageButton.setXY(311, 110);
    switchLanguageButton.setLabelText(TypedText(T_SWITCH_LANGUAGE));
    switchLanguageButton.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    switchLanguageButton.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    switchLanguageButton.setAction(buttonClickedCallback);

    // Setup headline text
    headlineTxt.setTypedText(TypedText(T_MAIN_HEADLINE));
    headlineTxt.setPosition(50, 45, 250, 100);
    headlineTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Setup main text
    mainTxt.setTypedText(TypedText(T_MAIN_TEXT));
    mainTxt.setPosition(50, 90, 250, 100);
    mainTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Setup TouchGFX animating text
    touchgfxTxt.setWildcard(touchgfxBuf);
    touchgfxTxt.setTypedText(TypedText(T_TOUCHGFX_TEXT));
    touchgfxTxt.setPosition(50, 170, 250, 100);
    touchgfxTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Setup tick counter
    tickCounter = 0;

    // Setup ticktxt with correct initalised buffer
    // for wildcard text
    Unicode::snprintf(tickTxtBuf, 5, "%d", tickCounter);
    tickTxt.setWildcard(tickTxtBuf);
    tickTxt.setTypedText(TypedText(T_TICK_COUNTER));
    tickTxt.setPosition(50, 195, 150, 100);
    tickTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(img);
    add(switchLanguageButton);
    add(headlineTxt);
    add(mainTxt);
    add(touchgfxTxt);
    add(tickTxt);
}

void MainView::updateWildcardTexts(uint16_t tick)
{
    // Update tick text and invalidate text area,
    // which will result in it being redrawn.
    Unicode::snprintf(tickTxtBuf, 5, "%d", tick);
    tickTxt.invalidate();

    // Update the TouchGFX text, let it use tick % 9 characters
    // and remember to zero terminate it
    Unicode::strncpy(touchgfxBuf, "TouchGFX", tick % 9);
    touchgfxBuf[tick % 9] = 0;
    touchgfxTxt.invalidate();
}

void MainView::handleTickEvent()
{
    // Update the wildcard text, but only each 10th time
    if (++tickCounter % 10 == 0)
    {
        updateWildcardTexts(tickCounter / 10);
    }
}

void MainView::buttonClicked(const AbstractButton& source)
{
    /* Determine which button was pressed, and let
       presenter decide how to react on specific action */
    if (&switchLanguageButton == &source)
    {
        presenter->switchLanguage();
    }
}

void MainView::redrawTexts()
{
    // Force a redraw of all widgets containing texts.
    switchLanguageButton.invalidate();
    headlineTxt.invalidate();
    mainTxt.invalidate();
    tickTxt.invalidate();
}
