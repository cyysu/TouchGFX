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
#include <gui/common/FadeTransition.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/transitions/Transition.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/Layout.hpp>
#include <gui/common/Constants.hpp>

using namespace touchgfx;

FadeTransition::FadeTransition() :
    Transition(),
    animationCallback(this, &FadeTransition::handleAnimationEvent),
    snapshot()
{
    //Set the position of the snapshot and make it cover the entire screen.
    snapshot.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - Layout::menu().height);
    //Make a snapshot of the area the snapshot covers.
    snapshot.makeSnapshot();

    fadeImage.setAlpha(0);
    fadeImage.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
    fadeImage.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - Layout::menu().height);

    fadeState = FADING_OUT_START;
    fadeImage.setFadeAnimationEndedAction(animationCallback);
}


FadeTransition::~FadeTransition()
{
}

void FadeTransition::init()
{
    Transition::init();

    //Add the widgets to the container.
    screenContainer->add(snapshot);
    screenContainer->add(fadeImage);
}

void FadeTransition::tearDown()
{
    Transition::tearDown();
}

void FadeTransition::handleTickEvent()
{
    switch (fadeState)
    {
    case FADING_OUT_START:
        fadeImage.startFadeAnimation(255, 2, &EasingEquations::linearEaseInOut);
        fadeState = FADING_OUT;
        break;

    case FADING_IN_START:
        screenContainer->remove(snapshot);
        fadeImage.startFadeAnimation(0, 2, &EasingEquations::linearEaseInOut);
        fadeState = FADING_IN;
        break;

    case FADING_OUT:
    case FADING_IN:
        // just wait until animation is finish
        fadeImage.doManualTickEvent();
        break;

    case CLOSED:
        done = true;
        screenContainer->remove(fadeImage);
        fadeState = PAUSE;
        break;

    case PAUSE:
    // do nothing
    default:
        ;
    }
    fadeImage.invalidate();
}

void FadeTransition::handleAnimationEvent(const FadeAnimator<Image>& drawable)
{
    if (fadeState == FADING_OUT)
    {
        fadeState = FADING_IN_START;
    }
    else if (fadeState == FADING_IN)
    {
        fadeState = CLOSED;
    }

}
