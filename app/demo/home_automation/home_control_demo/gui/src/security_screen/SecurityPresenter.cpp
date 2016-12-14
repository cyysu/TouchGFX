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
#include <gui/security_screen/SecurityPresenter.hpp>
#include <gui/security_screen/SecurityView.hpp>
#include <gui/model/Model.hpp>

SecurityPresenter::SecurityPresenter(SecurityView& v)
    : BasePresenter(v), view(v)
{
}

void SecurityPresenter::activate()
{
    BasePresenter::activate();
    securityChanged(); // trigger an view update
}

void SecurityPresenter::deactivate()
{
    BasePresenter::deactivate();
}

void SecurityPresenter::roomChanged()
{
    // save security selections in model
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        model->setRoomSecurity(Room(i), view.getRoomSecurity(Room(i)));
    }
}

void SecurityPresenter::setSecurityForAllRooms(bool active)
{
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        model->setRoomSecurity(Room(i), active);
        view.setRoomSecurity(Room(i), model->getRoomSecurity(Room(i)));
    }
}

void SecurityPresenter::securityChanged()
{
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        view.setRoomSecurity(Room(i), model->getRoomSecurity(Room(i)));
    }
    // update all button state
    Room room = view.getCurrentSelectedRoom();
    if (room == Room::ALL_ROOMS_SELECTED)
    {
        view.setAllRoomButton(true);
    }
    else if (room == Room::NO_ROOM_SELECTED)
    {
        view.setAllRoomButton(false);
    }
}

