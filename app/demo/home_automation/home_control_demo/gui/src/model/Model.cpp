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
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>



Model::Model() :
    modelListener(0),
    currentDateTime(System::DateTime::beginning()),
    inactivationNeeded(false)
{
    // Hardcoded start values - for demo purpose
    assert(Room::NUMBER_OF_ROOMS == 5);
    airConTemp[Room::ROOM1] = 20;
    airConTemp[Room::ROOM2] = 18;
    airConTemp[Room::LIVINGROOM] = 20;
    airConTemp[Room::BEDROOM] = 19;
    airConTemp[Room::KITCHEN] = 21;

    blindsPercentage[Room::ROOM1] = 20;
    blindsPercentage[Room::ROOM2] = 55;
    blindsPercentage[Room::LIVINGROOM] = 30;
    blindsPercentage[Room::BEDROOM] = 75;
    blindsPercentage[Room::KITCHEN] = 55;

    lightingPercentage[Room::ROOM1] = 75;
    lightingPercentage[Room::ROOM2] = 85;
    lightingPercentage[Room::LIVINGROOM] = 100;
    lightingPercentage[Room::BEDROOM] = 25;
    lightingPercentage[Room::KITCHEN] = 15;

    sliderValues[0] = 50;
    sliderValues[1] = 180;
    sliderValues[2] = 80;
    sliderValues[3] = 150;

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        securityActivation[i] = false;
    }

    menuPositionX = 0;
}

void Model::setCurrentDateTime(const System::DateTime& dateTime)
{
    // only notify modelListener once per sec
    if ((dateTime - currentDateTime) >= 1)
    {
        currentDateTime = dateTime;
        if (modelListener)
        {
            modelListener->timeChanged();
        }
    }
}

void Model::setWashingMachineState(const WashingMachine::Program program, uint16_t remainingTime)
{
    washingMachine.setState(program, remainingTime);
    if (modelListener)
    {
        modelListener->washingMachineChanged();
    }
}

void Model::setRoomSecurity(Room room, bool active)
{
    if (securityActivation[room] != active)
    {
        securityActivation[room] = active;
        if (modelListener)
        {
            modelListener->securityChanged();
        }
    }
}

void Model::setMenuPosition(int16_t x)
{
    menuPositionX = x;
}

