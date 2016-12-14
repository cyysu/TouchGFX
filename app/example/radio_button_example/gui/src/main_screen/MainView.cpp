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
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainView::MainView() :
    radioButtonSelectedCallback(this, &MainView::radioButtonSelectedHandler),
    radioButtonDeselectedCallback(this, &MainView::radioButtonDeselectedHandler)
{
}

void MainView::setupScreen()
{
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);
    add(imgBackground);

    // Setup text
    selectedText.setXY(180, 140);
    selectedText.setTypedText(TypedText(T_SELECTED_TEXT));
    selectedText.setWildcard(selectedTextBuffer);
    selectedText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    deselectedText.setXY(180, 180);
    deselectedText.setTypedText(TypedText(T_DESELECTED_TEXT));
    deselectedText.setWildcard(deselectedTextBuffer);
    deselectedText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    add(selectedText);
    add(deselectedText);

    for (int i = 0; i < NUMBER_OF_RADIO_BUTTONS; i++)
    {
        radioButtonGroup.add(radioButtons[i]);
        radioButtons[i].setBitmaps(Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_PRESSED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_PRESSED_ID));
        radioButtons[i].setXY(90, 26 + 50 * i);
        add(radioButtons[i]);
    }

    // Setup callbacks
    radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);
    radioButtonGroup.setRadioButtonDeselectedHandler(radioButtonDeselectedCallback);

    radioButtonGroup.setSelected(radioButtons[1]);

    // Allow deselecting by clicking on a selected radiobutton
    //radioButtonGroup.setDeselectionEnabled(true);

}

void MainView::tearDownScreen()
{

}

void MainView::radioButtonSelectedHandler(const AbstractButton& radioButton)
{
    Unicode::snprintf(selectedTextBuffer, 4, "%d", getRadioButtonIndex(radioButton));
    selectedText.resizeToCurrentText();
    selectedText.invalidate();
}

void MainView::radioButtonDeselectedHandler(const AbstractButton& radioButton)
{
    Unicode::snprintf(deselectedTextBuffer, 4, "%d", getRadioButtonIndex(radioButton));
    deselectedText.resizeToCurrentText();
    deselectedText.invalidate();
}

int16_t MainView::getRadioButtonIndex(const AbstractButton& radioButton)
{
    int result = -1;
    for (int i = 0; i < NUMBER_OF_RADIO_BUTTONS; i++)
    {
        if (&radioButtons[i] == &radioButton)
        {
            result = i;
            break;
        }
    }
    return result;
}
