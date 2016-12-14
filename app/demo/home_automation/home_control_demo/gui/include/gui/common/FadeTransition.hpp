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
#ifndef FADE_TRANSITION_HPP_
#define FADE_TRANSITION_HPP_

#include <touchgfx/transitions/Transition.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

template <class T>
class FadeAnimatorSpecial : public FadeAnimator<T>
{
public:
    /**
    * It is not possible to register a timer widget from inside a transition class. Therefore the handleTickEvent function must be called manual.
    */
    void doManualTickEvent()
    {
        this->handleTickEvent();
    }
};

/**
* The visual effect of the transition implemented in this demo, is fading out the old screen and the new screen is fading in.
*/
class FadeTransition : public Transition
{
public:
    FadeTransition();
    virtual ~FadeTransition();
    virtual void init();
    virtual void tearDown();
    virtual void handleTickEvent();

private:

    /**
    * An enum defining the different states the transition can have.
    */
    enum  FadeState
    {
        FADING_IN_START,
        FADING_OUT_START,
        FADING_IN,
        FADING_OUT,
        CLOSED,
        PAUSE
    };

    Callback<FadeTransition, const FadeAnimator<Image>&> animationCallback;
    void handleAnimationEvent(const FadeAnimator<Image>& drawable);

    /**
    * The snapshot widget is used to take a snapshot of the screen transitioning from.
    */
    SnapshotWidget snapshot;
    FadeAnimatorSpecial<Image> fadeImage;

    FadeState fadeState;
};

#endif
