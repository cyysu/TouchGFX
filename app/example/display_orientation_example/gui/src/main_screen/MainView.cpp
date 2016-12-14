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
#include <touchgfx/hal/HAL.hpp>
#include <gui/common/FrontendApplication.hpp>

void MainView::setupScreen()
{
    if (HAL::getInstance()->getDisplayOrientation() == ORIENTATION_LANDSCAPE)
    {
        // Setup the screen for landscape mode
        imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
        imgBackground.setXY(0, 0);

        button.setBitmaps(Bitmap(BITMAP_CHANGE_BTN_ID), Bitmap(BITMAP_CHANGE_BTN_PRESSED_ID));
        button.setXY(268, 150);

        text.setPosition(68, 90, 152, 154);
    }
    else
    {
        // Setup the screen for portrait mode
        imgBackground.setBitmap(Bitmap(BITMAP_BG_90_ID));
        imgBackground.setXY(0, 0);

        button.setBitmaps(Bitmap(BITMAP_CHANGE_BTN_90_ID), Bitmap(BITMAP_CHANGE_BTN_PRESSED_90_ID));
        button.setXY(70, 140);

        text.setPosition(60, 320, 152, 154);
    }

    button.setAction(buttonClickedCallback);

    text.setTypedText(TypedText(T_TEXT));
    text.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    add(imgBackground);
    add(button);
    add(text);
}

void MainView::tearDownScreen()
{

}

void MainView::buttonClicked(const AbstractButton& source)
{
    if (&button == &source)
    {
        if (HAL::getInstance()->getDisplayOrientation() == ORIENTATION_LANDSCAPE)
        {
            HAL::getInstance()->setDisplayOrientation(ORIENTATION_PORTRAIT);
        }
        else
        {
            HAL::getInstance()->setDisplayOrientation(ORIENTATION_LANDSCAPE);
        }
        // Recreate the current screen to change orientation
        static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoMainScreen();
    }
}
