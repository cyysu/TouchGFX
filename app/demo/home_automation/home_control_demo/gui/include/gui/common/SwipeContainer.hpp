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
#ifndef SWIPE_CONTAINER_HPP
#define SWIPE_CONTAINER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/common/DotIndicator.hpp>


class SwipeContainer : public touchgfx::Container
{
public:
    SwipeContainer(uint16_t width, uint16_t height);
    virtual ~SwipeContainer();

    virtual void handleTickEvent();
    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);
    virtual void handleDragEvent(const touchgfx::DragEvent& evt);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& evt);

    virtual void add(touchgfx::Drawable& screen);

    uint8_t getNumberOfScreens()
    {
        return numberOfScreens;
    }

private:

    enum States
    {
        ANIMATE_SWIPE_CANCELLED_LEFT,
        ANIMATE_SWIPE_CANCELLED_RIGHT,
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    } currentState;

    uint8_t numberOfScreens;

    uint8_t animationCounter;

    // Indicates how far you should drag a screen before it results in a screen change
    uint16_t swipeCutoff;

    int16_t dragX;
    int16_t animateDistance;
    int16_t startX;
    uint8_t currentScreen;

    // Background that becomes visible when trying to swipe
    // beyond the number of screens.
    touchgfx::Image backgroundSwipeAreaLeft;
    touchgfx::Image backgroundSwipeAreaRight;

    DotIndicator dotIndicator;

    touchgfx::ListLayout screens;

    void adjustScreens();

    void animateSwipeCancelledLeft();
    void animateSwipeCancelledRight();
    void animateLeft();
    void animateRight();
};


#endif
