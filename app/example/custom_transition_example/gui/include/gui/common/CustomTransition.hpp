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
#ifndef CUSTOMTRANSITION_HPP_
#define CUSTOMTRANSITION_HPP_
#include <touchgfx/transitions/Transition.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>
#include <touchgfx/widgets/Image.hpp>

using namespace touchgfx;

/**
 * The visual effect of the transition implemented in this example, resembles two doors being closed and opened from both sides of the screen.
 * Both doors closes to hide the screen the transition is coming from. The doors then open again to reveal the screen the transition is going to.
 */
class CustomTransition : public Transition
{
public:
    CustomTransition();
    virtual ~CustomTransition();
    virtual void init();
    virtual void tearDown();
    virtual void handleTickEvent();

private:

    /**
     * An enum defining the different states the transition can have.
     */
    typedef enum
    {
        OPENING,
        CLOSING,
        CLOSED,
        PAUSE
    } DoorState;

    /**
     * The snapshot widget is used to take a snapshot of the screen transitioning from.
     */
    SnapshotWidget snapshot;

    /**
     * Image for the left door.
     */
    Image leftDoorImage;

    /**
     * Image for the right door.
     */
    Image rightDoorImage;

    /**
     * The counter defining the number of ticks to wait before opening the doors.
     */
    uint8_t pauseCounter;

    /**
     * The current state of the transition.
     */
    DoorState doorState;

    /**
     * The number of pixels to move the doors on the x-axis at each tick.
     */
    static const uint8_t DELTA_X = 6;

    static const uint8_t PAUSE_TICKS = 30;
};

#endif /* CUSTOMTRANSITION_HPP_ */
