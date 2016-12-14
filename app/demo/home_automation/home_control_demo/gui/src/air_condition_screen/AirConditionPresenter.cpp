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
#include <gui/air_condition_screen/AirConditionPresenter.hpp>
#include <gui/air_condition_screen/AirConditionView.hpp>
#include <gui/model/Model.hpp>

AirConditionPresenter::AirConditionPresenter(AirConditionView& v)
    : BasePresenter(v), view(v)
{
}

void AirConditionPresenter::activate()
{
    BasePresenter::activate();
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        view.setRoomTemperature((Room) i, model->getRoomAirConTemp((Room) i));
    }
}

void AirConditionPresenter::deactivate()
{
    BasePresenter::deactivate();
}

void AirConditionPresenter::roomSelected(Room room)
{
    if (room == Room::NO_ROOM_SELECTED)
    {
        view.setJogwheelInactive();
    }
    else
    {
        view.setJogwheelActive(model->getRoomAirConTemp(room));
    }
}

void AirConditionPresenter::roomAirConTempUpdated(Room room, int16_t value)
{
    model->setRoomAirConTemp(room, value);
    view.setRoomTemperature(room, model->getRoomAirConTemp(room));
}
