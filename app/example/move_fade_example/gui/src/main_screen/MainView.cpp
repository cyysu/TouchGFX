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
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>

MainView::MainView() :
    object0AnimationEndedCallback(this, &MainView::object0AnimationEndedHandler),
    object1AnimationEndedCallback(this, &MainView::object1AnimationEndedHandler),
    object2FadeAnimationEndedCallback(this, &MainView::object2FadeAnimationEndedHandler),
    object2MoveAnimationEndedCallback(this, &MainView::object2MoveAnimationEndedHandler)
{
}

void MainView::setupScreen()
{
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);

    object0.setBitmap(Bitmap(BITMAP_IMAGE00_ID));
    object0.setXY(70, 90);
    object0.setMoveAnimationEndedAction(object0AnimationEndedCallback);

    object1.setColor(Color::getColorFrom24BitRGB(0x12, 0xA2, 0xBA));
    object1.setPosition(210, 90, 74, 74);
    object1.setFadeAnimationEndedAction(object1AnimationEndedCallback);

    object2.setBitmap(Bitmap(BITMAP_IMAGE01_ID));
    object2.setXY(330, 90);
    object2.setFadeAnimationEndedAction(object2FadeAnimationEndedCallback);
    object2.setMoveAnimationEndedAction(object2MoveAnimationEndedCallback);

    // Switch between moving back and forth in the animations
    object0AnimationSwitch = false;
    object1AnimationSwitch = false;
    object2FadeAnimationSwitch = false;
    object2MoveAnimationSwitch = false;

    // Start the animations
    object0.startMoveAnimation(76, 130, 10);
    object1.startFadeAnimation(16, 18);
    object2.startMoveAnimation(320, 40, 26);
    object2.startFadeAnimation(128, 32);

    add(imgBackground);
    add(object0);
    add(object1);
    add(object2);
}

void MainView::tearDownScreen()
{

}

/**
 * Callback method for animation-end for object0
 */
void MainView::object0AnimationEndedHandler(const MoveAnimator<Image>& image)
{
    if (object0AnimationSwitch)
    {
        object0.startMoveAnimation(76, 130, 10);
    }
    else
    {
        object0.startMoveAnimation(70, 90, 20, EasingEquations::linearEaseNone, EasingEquations::circEaseOut);
    }
    object0AnimationSwitch = !object0AnimationSwitch;
}

/**
 * Callback method for animation-end for object1
 */
void MainView::object1AnimationEndedHandler(const FadeAnimator<Box>& box)
{
    if (object1AnimationSwitch)
    {
        object1.startFadeAnimation(16, 18);
    }
    else
    {
        object1.startFadeAnimation(255, 30, EasingEquations::quintEaseOut);
    }
    object1AnimationSwitch = !object1AnimationSwitch;
}

/**
 * Callback method for fade animation-end for object2
 */
void MainView::object2FadeAnimationEndedHandler(const FadeAnimator<MoveAnimator<Image> >& image)
{
    if (object2FadeAnimationSwitch)
    {
        object2.startMoveAnimation(320, 40, 26);
    }
    else
    {
        object2.startMoveAnimation(340, 130, 46);
    }
    object2FadeAnimationSwitch = !object2FadeAnimationSwitch;
}

/**
 * Callback method for move animation-end for object2
 */
void MainView::object2MoveAnimationEndedHandler(const MoveAnimator<Image>& image)
{
    if (object2MoveAnimationSwitch)
    {
        object2.startFadeAnimation(128, 32);
    }
    else
    {
        object2.startFadeAnimation(255, 10);
    }
    object2MoveAnimationSwitch = !object2MoveAnimationSwitch;
}
