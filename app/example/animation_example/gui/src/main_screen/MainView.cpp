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
    /*
     * Setup background image
     */
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);

    /*
     * Setup button with correct bitmaps and label
     * Set the callback used for the button
     */
    btnToggle.setBitmaps(Bitmap(BITMAP_BTN_ID), Bitmap(BITMAP_BTN_PRESSED_ID));
    btnToggle.setXY(175, 198);
    btnToggle.setLabelText(TypedText(T_START));
    btnToggle.setLabelColor(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    btnToggle.setLabelColorPressed(Color::getColorFrom24BitRGB(0xD5, 0x73, 0x00));
    btnToggle.setAction(buttonClickedCallback);

    /*
     * Place animation and callback to catch end of animation
     */
    animation.setXY(161, 18);
    animation.setDoneAction(animationEndedCallback);

    /*
     * Remember to add widgets to container.
     * They must be added from bottom and out, or else upper layer(s)
     * may block view of elements below.
     */
    add(imgBackground);
    add(btnToggle);
    add(animation);
}

/**
 * Determine which button was pressed, and let
 * presenter decide how to react on specific action
 */
void MainView::buttonClicked(const AbstractButton& source)
{
    presenter->togglePressed();
}

/**
 * Start the animation in the reverse direction
 */
void MainView::animationEnded(const AnimatedImage& source)
{
    animation.startAnimation(!animation.isReverse(), false, true);
}

/**
 * Start the animation in the same direction as it was stopped.
 * Change the label text to reflect the state
 */
void MainView::startAnimation()
{
    animation.startAnimation(animation.isReverse(), false, true);
    btnToggle.setLabelText(TypedText(T_STOP));
}

/**
 * Stop, or pause, the animation.
 * Change the label text to reflect the state
 */
void MainView::stopAnimation()
{
    animation.pauseAnimation();
    btnToggle.setLabelText(TypedText(T_START));
}

/**
 * Tells whether the animation is running or not.
 * @return Returns true if the animation is running, otherwise returns false
 */
bool MainView::isAnimationRunning()
{
    return animation.isRunning();
}
