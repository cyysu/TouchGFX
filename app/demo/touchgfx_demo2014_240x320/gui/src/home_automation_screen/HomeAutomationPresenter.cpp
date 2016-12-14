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
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/home_automation_screen/HomeAutomationView.hpp>
#include <gui/common/FrontendApplication.hpp>

HomeAutomationPresenter::HomeAutomationPresenter(HomeAutomationView& v) :
    view(v)
{
}

HomeAutomationPresenter::~HomeAutomationPresenter()
{
}

void HomeAutomationPresenter::activate()
{
    for (uint8_t i = 0; i < model->getNumberOfRooms(); i++)
    {
        view.insertRoom(model->getRoomTemperatureInfo(i));
    }
    roomSelected(model->getSelectedRoom());
}

void HomeAutomationPresenter::deactivate()
{

}

void HomeAutomationPresenter::roomUpdated(RoomTemperatureInfo& room)
{
    view.updateRoom(room);
}

void HomeAutomationPresenter::roomSelected(uint8_t roomId)
{
    model->setSelectedRoom(roomId);
    view.setSelectedMenuItem(model->getRoomTemperatureInfoById(roomId));
}

void HomeAutomationPresenter::newRoomTemperature(int16_t temperature)
{
    model->setRoomTemperature(temperature);
}

void HomeAutomationPresenter::newScheduleAccepted()
{
    view.saveScheduleInfo(model->getRoomTemperatureInfoById(model->getSelectedRoom()));
}

RoomTemperatureInfo& HomeAutomationPresenter::getSelectedRoom()
{
    return model->getRoomTemperatureInfo(model->getSelectedRoom());
}

void HomeAutomationPresenter::exitScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuScreen();
}



