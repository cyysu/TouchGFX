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
#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

#include <gui/model/Time.hpp>
#include <gui/model/RoomTemperatureInfo.hpp>

class Model
{
public:
    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    uint8_t getNumberOfRooms();
    RoomTemperatureInfo& getRoomTemperatureInfo(uint8_t roomIndex);
    RoomTemperatureInfo& getRoomTemperatureInfoById(uint8_t roomId);

    void setSelectedRoom(uint8_t roomId);
    uint8_t getSelectedRoom();
    void setRoomTemperature(int16_t temperature);

    bool getMCULoadActive() const
    {
        return mcuLoadActive;
    }
    void setMCULoadActive(bool active)
    {
        mcuLoadActive = active;
    }

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

    bool mcuLoadActive;

    Time currentTime;

    RoomTemperatureInfo roomTemperatureInfo[10];
    uint8_t numberOfRooms;
    uint8_t selectedRoom;
};

#endif /* MODEL_HPP */
