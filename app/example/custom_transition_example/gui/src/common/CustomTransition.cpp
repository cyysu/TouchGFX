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
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/transitions/Transition.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>
#include <gui/common/CustomTransition.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>

CustomTransition::CustomTransition() :
    Transition(),
    snapshot(),
    leftDoorImage(Bitmap(BITMAP_LEFTDOOR_ID)),
    rightDoorImage(Bitmap(BITMAP_RIGHTDOOR_ID)),
    pauseCounter(PAUSE_TICKS),
    doorState(CLOSING)
{
    //Set the position of the snapshot and make it cover the entire screen.
    snapshot.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    //Make a snapshot of the area the snapshot covers.
    snapshot.makeSnapshot();
}

CustomTransition::~CustomTransition()
{
}

void CustomTransition::init()
{
    Transition::init();

    //Set the initial positions of the images used in the transition animation.
    leftDoorImage.setX(-leftDoorImage.getWidth());
    rightDoorImage.setX(HAL::DISPLAY_WIDTH + 18);

    //Add the widgets to the container.
    //The snapshot is placed below the door images to show a snapshot of the screen we are transitioning away from while the doors closes.
    screenContainer->add(snapshot);
    screenContainer->add(leftDoorImage);
    screenContainer->add(rightDoorImage);
}

void CustomTransition::tearDown()
{
    Transition::tearDown();

    //Remove the door images from the container of the new screen.
    screenContainer->remove(leftDoorImage);
    screenContainer->remove(rightDoorImage);
}

void CustomTransition::handleTickEvent()
{
    switch (doorState)
    {
    case CLOSING:
        {
            //Move the door images towards the center of the screen.
            leftDoorImage.moveRelative(DELTA_X, 0);
            rightDoorImage.moveRelative(-DELTA_X, 0);

            //The doors are closed when the left image has x-coordinate 0.
            if (leftDoorImage.getX() == 0)
            {
                //Go to the closed state.
                doorState = CLOSED;
            }
        }
        break;

    case OPENING:
        {
            //Move the door images toward the edges of the screen.
            leftDoorImage.moveRelative(-DELTA_X, 0);
            rightDoorImage.moveRelative(DELTA_X, 0);

            //The Doors are open when the left image is moved out of the screen.
            if (leftDoorImage.getX() == -leftDoorImage.getWidth())
            {
                //When the doors have fully opened, the transition is done.
                //Signal that the transition is done.
                done = true;
            }
        }
        break;

    case CLOSED:
        {
            //Remove the snapshot to reveal the contents of the new screen.
            screenContainer->remove(snapshot);
            //Go to the pause state.
            doorState = PAUSE;
        }
        break;

    case PAUSE:
        {
            //Do nothing in this state until the counter reaches 0.
            if (pauseCounter-- == 0)
            {
                //Go to the opening state.
                doorState = OPENING;
            }
        }
        break;

    default:
        break;
    }
}
