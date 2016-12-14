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

MainView::MainView() :
    newValueCallback(this, &MainView::newValueHandler),
    stopValueCallback(this, &MainView::stopValueHandler)
{
}

void MainView::setupScreen()
{
    // Setup background image
    background.setBitmap(Bitmap(BITMAP_BG_ID));
    background.setXY(0, 0);
    add(background);

    // Setup image0
    image0.setBitmap(Bitmap(BITMAP_IMAGE00_ID));
    image0.setXY(100, 80);
    add(image0);

    // Setup image1
    image1.setBitmap(Bitmap(BITMAP_IMAGE01_ID));
    image1.setXY(280, 80);
    add(image1);

    // Setup horizontalSlider
    horizontalSlider.setXY(210, 200);
    horizontalSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_BACKGROUND_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_CIRCLE_ID));
    horizontalSlider.setNewValueCallback(newValueCallback);

    // Setup slider background and indicator positions. The background does not take up
    // all the slider widget since the indicator needs to extend beyond the background in
    // the min and max positions. This is handled by placing the background at position (18, 15)
    horizontalSlider.setupHorizontalSlider(18, 15, 0, 8, 192);

    // Set the value range of the slider. Since the value us used for setting the 8bit alpha
    // value of the images, the range is set to 0-255.
    // Note that the slider indicator position range is only 192-8 = 184 pixels. This is, however, not a
    // problem just remember that in this case not all values can be set by the slider (since there is not a
    // pixel for each value)
    horizontalSlider.setValueRange(0, 255);
    horizontalSlider.setValue(100);
    add(horizontalSlider);

    // Setup verticalSlider
    verticalSlider.setXY(30, 40);
    verticalSlider.setBitmaps(BITMAP_SLIDER_BACKGROUND_VERTICAL_ID, BITMAP_SLIDER_BACKGROUND_VERTICAL_FILLED_ID, BITMAP_SLIDER_KNOB_SHAPE_ID);
    verticalSlider.setupVerticalSlider(15, 17, 0, 8, 156);
    verticalSlider.setStopValueCallback(stopValueCallback);
    verticalSlider.setValueRange(0, 255, 180);
    add(verticalSlider);
}

void MainView::newValueHandler(const Slider& slider, int value)
{
    if (&slider == &horizontalSlider)
    {
        image1.setAlpha(value);
        image1.invalidate();
    }
}

void MainView::stopValueHandler(const Slider& slider, int value)
{
    if (&slider == &verticalSlider)
    {
        image0.setAlpha(value);
        image0.invalidate();
    }
}
