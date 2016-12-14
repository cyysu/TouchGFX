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

    //Setup button with correct bitmaps and label
    switchLanguageButton.setBitmaps(Bitmap(BITMAP_BTN_ID), Bitmap(BITMAP_BTN_PRESSED_ID));
    switchLanguageButton.setXY(311, 110);
    switchLanguageButton.setLabelText(TypedText(T_SWITCH_LANGUAGE));
    switchLanguageButton.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    switchLanguageButton.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    switchLanguageButton.setAction(buttonClickedCallback);

    // Setup main text
    mainTxt.setTypedText(TypedText(T_MAIN_TEXT));
    mainTxt.setPosition(50, 0, 200, 300);
    mainTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Setup tick counter
    tickCounter = 0;

    // Setup ticktxt with correct initalized buffer
    // for wildcard text
    Unicode::snprintf(tickTxtbuf, 5, "%d", tickCounter);
    tickTxt.setWildcard(tickTxtbuf);
    tickTxt.setTypedText(TypedText(T_TICK_COUNTER));
    tickTxt.setPosition(50, 0, 200, 30);
    tickTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    setLanguage(GB);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(img);
    add(switchLanguageButton);
    add(mainTxt);
    add(tickTxt);
}

void MainView::setWildcardText(uint16_t tick)
{
    // Update wildcard text and Invalidate text area,
    // which will result in it being redrawn.
    Unicode::snprintf(tickTxtbuf, 7, "%d", tick);
    tickTxt.invalidate();
}

void MainView::handleTickEvent()
{
    // Update the wildcard text, but only each 10th time
    if (++tickCounter % 10 == 0)
    {
        setWildcardText(tickCounter / 10);
    }
}

void MainView::buttonClicked(const AbstractButton& source)
{
    if (&switchLanguageButton == &source)
    {
        if (Texts::getLanguage() == GB)
        {
            setLanguage(AR);
        }
        else if (Texts::getLanguage() == AR)
        {
            setLanguage(GB);
        }
    }
}

void MainView::setLanguage(LANGUAGES language)
{
    Texts::setLanguage(language);

    // Force a redraw of all widgets containing texts.
    // Invalidate done both before and after the update of
    // the texts. This to make sure that both the area that
    // the text covered before and after the update is redrawn.
    switchLanguageButton.invalidate();
    mainTxt.invalidate();
    tickTxt.invalidate();

    // Place the main text and tick text. Using setBaseline ensures
    // that the text will stay at the same spot even when changing
    // language and font to a different size
    mainTxt.setBaselineY(60);
    tickTxt.setY(mainTxt.getY() + mainTxt.getTextHeight());

    // Make sure the button text is centered horizontally
    // e.g. if the language setting has changed
    switchLanguageButton.updateTextPosition();

    switchLanguageButton.invalidate();
    mainTxt.invalidate();
    tickTxt.invalidate();
}
