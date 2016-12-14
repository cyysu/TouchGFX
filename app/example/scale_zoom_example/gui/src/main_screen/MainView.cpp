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
#include <touchgfx/EasingEquations.hpp>

MainView::MainView() :
    currentAnimation(0),
    animationEndedCallback(this, &MainView::animationEndedHandler)
{
}

void MainView::setupScreen()
{
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);

    // Show ScalableImage at 76x76 pixels. Original bitmap 200x200 pixels.
    // Uses Bilinear Interpolation rendering algorithm
    scalableImage0.setBitmap(Bitmap(BITMAP_IMAGE00_ID));
    scalableImage0.setPosition(10, 40, 76, 76);
    scalableImage0.setScalingAlgorithm(ScalableImage::BILINEAR_INTERPOLATION);

    // Show ScalableImage at 76x76 pixels. Original bitmap 200x200 pixels.
    // Uses Nearest Neighbor rendering algorithm
    scalableImage1.setBitmap(Bitmap(BITMAP_IMAGE00_ID));
    scalableImage1.setPosition(10, 140, 76, 76);
    scalableImage1.setScalingAlgorithm(ScalableImage::NEAREST_NEIGHBOR);

    // Setup ZoomAnimationImage
    zoomAnimationImage.setBitmaps(Bitmap(BITMAP_IMAGE01_SMALL_ID), Bitmap(BITMAP_IMAGE01_LARGE_ID));
    zoomAnimationImage.setPosition(100, 10, 100, 100);

    // Attach method callback for the animation. This callback is called
    // when an animation ends
    zoomAnimationImage.setAnimationEndedCallback(animationEndedCallback);

    // Start animation
    zoomAnimationImage.startZoomAndMoveAnimation(240, 40, 200, 200, 30);

    add(imgBackground);
    add(scalableImage0);
    add(scalableImage1);
    add(zoomAnimationImage);

}

void MainView::tearDownScreen()
{

}

// Handle one animation end by starting another.
void MainView::animationEndedHandler(const ZoomAnimationImage& image)
{
    currentAnimation = (currentAnimation + 1) % 4;

    if (currentAnimation == 0)
    {
        zoomAnimationImage.startZoomAndMoveAnimation(240, 40, 200, 200, 30);
    }
    else if (currentAnimation == 1)
    {
        zoomAnimationImage.startZoomAnimation(100, 100, 30, ZoomAnimationImage::FIXED_CENTER);
    }
    else if (currentAnimation == 2)
    {
        zoomAnimationImage.startZoomAndMoveAnimation(100, 60, 200, 200, 40, ZoomAnimationImage::FIXED_LEFT_AND_TOP, EasingEquations::quadEaseInOut, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
    }
    else if (currentAnimation == 3)
    {
        zoomAnimationImage.startZoomAndMoveAnimation(110, 10, 100, 100, 40, ZoomAnimationImage::FIXED_LEFT_AND_TOP, EasingEquations::quadEaseInOut, EasingEquations::bounceEaseOut, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
    }
}
