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
#include <gui/first_screen/FirstView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
void FirstView::setupScreen()
{
    //Set the bitmap on the background.
    background.setBitmap(Bitmap(BITMAP_FIRST_BG_ID));

    //Set bitmap on the button.
    changeScreenBtn.setBitmaps(Bitmap(BITMAP_BTN_ID), Bitmap(BITMAP_BTN_PRESSED_ID));
    changeScreenBtn.setXY(173, 105);

    //Set the text on the button.
    changeScreenBtn.setLabelText(TypedText(T_CHANGE_TO_SCREEN_2));

    //Set the color of the label.
    changeScreenBtn.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    changeScreenBtn.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));

    //Set the callback to be called when clicked.
    changeScreenBtn.setAction(changeScreenBtnClickedCallback);

    //Make the button inactive - it should first be active when the transition is done.
    changeScreenBtn.setTouchable(false);

    //Add the background and the button to the container.
    add(background);
    add(changeScreenBtn);
}

void FirstView::tearDownScreen()
{

}

void FirstView::changeScreenBtnClicked(const AbstractButton& src)
{
    //Tell the presenter to initiate a screen change.
    presenter->goToSecondScreen();
}

void FirstView::afterTransition()
{
    //Make the button active to allow user-interaction.
    changeScreenBtn.setTouchable(true);
}
