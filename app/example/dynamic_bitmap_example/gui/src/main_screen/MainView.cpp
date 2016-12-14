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
#include <touchgfx/Color.hpp>
#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

/**
 * Setup all widgets.
 */
void MainView::setupScreen()
{
    background.setPosition(0, 0, 480, 272);
    background.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

    // Setup headline text
    headlineTxt.setTypedText(TypedText(T_INSERT));
    headlineTxt.setPosition(50, 10, 430, 100);
    headlineTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    // Full screen touch area to catch clicks on image (pause)
    touchArea.setPosition(0, 0, 480, 272);
    touchArea.setAction(clickCallback);

    // Play button
    playButton.setBitmaps(Bitmap(BITMAP_PLAY_ID), Bitmap(BITMAP_PLAY_ID));
    playButton.setXY(390, 182);
    playButton.setAction(clickCallback);
    playButton.setVisible(false);

    // Dynamic bitmap positioned, but invisible
    image.setPosition(0, 0, 300, 200);
    image.setVisible(false);

    // Add widgets to Screen
    add(background);
    add(headlineTxt);
    add(image);
    add(touchArea);
    add(playButton);
}

void MainView::tearDownScreen()
{
}

/**
 * Show an error code in the head line
 */
void MainView::showError(uint16_t e)
{
    headlineTxt.setTypedText(TypedText(T_ERROR));
    Unicode::snprintf(errBuf, 9, "%x", e);
    headlineTxt.setWildcard(errBuf);
    headlineTxt.invalidate();
}

/**
 * Show the play button is SD card is mounted
 */
void MainView::sdMounted(bool mounted)
{
    if (mounted)
    {
        //show play button
        playButton.setVisible(true);
        playButton.invalidate();
        //hide "insert SD.." text
        headlineTxt.invalidate();
        headlineTxt.setVisible(false);
    }
    else
    {
        //hide play button
        playButton.invalidate();
        playButton.setVisible(false);
        //show "insert SD.." text
        headlineTxt.setVisible(true);
#ifdef SIMULATOR
        headlineTxt.setTypedText(TypedText(T_ONLYTARGET));
#else
        headlineTxt.setTypedText(TypedText(T_INSERT));
#endif
        headlineTxt.invalidate();

        //move Image down
        image.moveTo(0, 50);
    }
}

/**
 * Callback for clicks on Play button or background.
 * Play button shall only be visible when paused.
 */
void MainView::clicked(const AbstractButton& source)
{
    if (&source == &playButton)
    {
        playButton.invalidate();
        playButton.setVisible(false);
        presenter->playPressed();
    }
    if (&source == &touchArea)
    {
        playButton.setVisible(true);
        playButton.invalidate();
        presenter->backgroundClicked();
    }
}

/**
 * Scale the bitmap to full screen while maintaining aspect ratio
 * Show it centered.
 */
void MainView::showBitmap(BitmapId id)
{
    Bitmap bitmap(id);
    //invalidate bitmap before changing to ensure background is painted
    image.invalidate();
    image.setBitmap(Bitmap(id));

    const float scale_horiz = 480.0f / bitmap.getWidth();
    const float scale_vert  = 272.0f / bitmap.getHeight();
    const float scale = MIN(scale_horiz, scale_vert);

    image.setWidth(static_cast<uint16_t>(bitmap.getWidth() * scale));
    image.setHeight(static_cast<uint16_t>(bitmap.getHeight() * scale));

    //center horizontally
    image.setXY((480 - image.getWidth()) / 2, (272 - image.getHeight()) / 2);

    //make visible (image is invisible first time)
    image.setVisible(true);
    //invalidate bitmap to ensure new picture is drawn
    image.invalidate();
}
