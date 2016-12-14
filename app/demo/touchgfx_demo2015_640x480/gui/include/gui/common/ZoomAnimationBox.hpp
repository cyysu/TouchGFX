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
#ifndef ZOOM_ANIMATION_BOX_HPP_
#define ZOOM_ANIMATION_BOX_HPP_

#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/EasingEquations.hpp>

using namespace touchgfx;

class ZoomAnimationBox : public Box
{
public:
    ZoomAnimationBox();
    virtual ~ZoomAnimationBox();

    void startZoomAnimation(int16_t endWidth, int16_t endHeight, uint16_t duration, touchgfx::EasingEquation widthProgressionEquation = &touchgfx::EasingEquations::linearEaseNone, EasingEquation heightProgressionEquation = &touchgfx::EasingEquations::linearEaseNone);

    virtual void handleTickEvent();

    /**
     * Associates an action to be performed when the animation ends.
     *
     * @param callback The callback to be executed. The callback will be given a
     * reference to the ZoomAnimationBox.
     *
     * @see GenericCallback
     */
    void setAnimationEndedCallback(touchgfx::GenericCallback<const ZoomAnimationBox&>& callback)
    {
        animationEndedAction = &callback;
    }


protected:

    /**
     * Animation states.
     *
     * ANIMATE_ZOOM: Zoom animation state
     */
    enum States
    {
        ANIMATE_ZOOM,
        NO_ANIMATION
    };

    /**
     * The current animation state
     */
    States currentState;

    /**
     * The progress counter for the animation
     */
    uint32_t animationCounter;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationStartWidth;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationStartHeight;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationEndWidth;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationEndHeight;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationStartX;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationStartY;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationDeltaX;

    /**
     * Member variable for the current animation
     */
    int16_t zoomAnimationDeltaY;


    /**
     * Member variable for the current animation
     */
    uint16_t animationDuration;

    /**
     * Member variable for the current animation
     */
    EasingEquation zoomAnimationWidthEquation;

    /**
     * Member variable for the current animation
     */
    EasingEquation zoomAnimationHeightEquation;

    /**
     * Animation ended Callback
     */
    touchgfx::GenericCallback<const ZoomAnimationBox&>* animationEndedAction;

    /**
     * Sets the current animation state.
     *
     * @param state The new state.
     */
    virtual void setCurrentState(States state);
};

#endif /* ZOOM_ANIMATION_BOX_HPP_ */
