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
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);

    imgCounter.setBitmap(Bitmap(BITMAP_COUNTER_BOX_ID));
    imgCounter.setXY(258, 61);

    // Initial button bitmaps is set by MainPresenter by calling MainView::setCount(...)
    btnUp.setXY(67, 60);
    btnDown.setXY(67, 158);

    // The same callback is used for both buttons
    btnUp.setAction(buttonClickedCallback);
    btnDown.setAction(buttonClickedCallback);

    // Initial value is set by MainPresenter by calling MainView::setCount(...)
    countTxt.setWildcard(countTxtbuf);
    countTxt.setTypedText(TypedText(T_COUNT));
    // White text
    countTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    // Same position and size as imgCounter
    countTxt.setPosition(258, 61, 152, 154);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(imgBackground);
    add(imgCounter);
    add(btnUp);
    add(btnDown);
    add(countTxt);
}

void MainView::tearDownScreen()
{

}

void MainView::buttonClicked(const AbstractButton& source)
{
    /* Determine which button was pressed, and let
       presenter decide how to react on specific action */
    if (&btnUp == &source)
    {
        presenter->upPressed();
    }
    else if (&btnDown == &source)
    {
        presenter->downPressed();
    }
}

void MainView::setCount(uint8_t countValue)
{
    Unicode::snprintf(countTxtbuf, 3, "%d", countValue);
    // Invalidate text area, which will result in it being redrawn in next tick.
    countTxt.invalidate();
}

void MainView::setLimitEffects(bool belowUpper, bool aboveLower)
{
    btnUp.setTouchable(belowUpper);
    btnDown.setTouchable(aboveLower);

    if (belowUpper)
    {
        btnUp.setBitmaps(Bitmap(BITMAP_UP_BTN_ID), Bitmap(BITMAP_UP_BTN_PRESSED_ID));
    }
    else
    {
        btnUp.setBitmaps(Bitmap(BITMAP_UP_BTN_DISABLED_ID), Bitmap(BITMAP_UP_BTN_DISABLED_ID));
    }

    if (aboveLower)
    {
        btnDown.setBitmaps(Bitmap(BITMAP_DOWN_BTN_ID), Bitmap(BITMAP_DOWN_BTN_PRESSED_ID));
    }
    else
    {
        btnDown.setBitmaps(Bitmap(BITMAP_DOWN_BTN_DISABLED_ID), Bitmap(BITMAP_DOWN_BTN_DISABLED_ID));
    }

    btnUp.invalidate();
    btnDown.invalidate();
}

