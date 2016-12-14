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
    background.setPosition(0, 0, 320, 240);
    background.setColor(0);

    forward.setBitmaps(Bitmap(BITMAP_ARROW_FORWARD_ID), Bitmap(BITMAP_ARROW_FORWARD_PRESSED_ID));
    forward.setXY(200, 170);
    forward.setAction(action);

    back.setBitmaps(Bitmap(BITMAP_ARROW_BACK_ID), Bitmap(BITMAP_ARROW_BACK_PRESSED_ID));
    back.setXY(25, 170);
    back.setAction(action);
    back.setVisible(false);

    desc.setTypedText(TypedText(T_DESCRIPTION_1));
    desc.setPosition(5, 30, 315, 150);
    desc.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    add(background);
    add(forward);
    add(back);
    add(desc);
}

void MainView::tearDownScreen()
{

}

void MainView::buttonClicked(const AbstractButton& btn)
{
    if (&btn == &forward)
    {
        position++;
    }
    else
    {
        position--;
    }

    forward.setVisible(position < 2);
    forward.invalidate();
    back.setVisible(position > 0);
    back.invalidate();

    desc.setTypedText(TypedText((TypedTextId)(T_DESCRIPTION_1 + position)));
    desc.invalidate();
}
