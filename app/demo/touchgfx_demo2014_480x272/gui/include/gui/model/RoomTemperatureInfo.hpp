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
#ifndef ROOM_TEMPERATURE_INFO_HPP_
#define ROOM_TEMPERATURE_INFO_HPP_

#include <stdint.h>
#include <touchgfx/Texts.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class RoomTemperatureInfo
{
public:
    enum weekday
    {
        MONDAY = 0,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY,
        NUMBER_OF_DAYS
    };

    RoomTemperatureInfo() {}
    ~RoomTemperatureInfo() {};

    void setRoomId(uint8_t id)
    {
        roomId = id;
    }
    uint8_t getRoomId()
    {
        return roomId;
    }

    void setRoomName(TEXTS name)
    {
        roomName = name;
    }
    TEXTS getRoomName()
    {
        return roomName;
    }

    void setRoomNameHeadline(TEXTS name)
    {
        roomNameHeadline = name;
    }
    TEXTS getRoomNameHeadline()
    {
        return roomNameHeadline;
    }

    void setRoomScheduleHeadline(TEXTS name)
    {
        roomScheduleHeadline = name;
    }
    TEXTS getRoomScheduleHeadline()
    {
        return roomScheduleHeadline;
    }

    void setCurrentTemperature(int16_t temp)
    {
        currentTemperature = temp;
    }
    int16_t getCurrentTemperature()
    {
        return currentTemperature;
    }

    void setScheduleDayTemp(weekday day, int16_t temp)
    {
        scheduleDayTemp[day] = temp;
    }
    int16_t getScheduleDayTemp(weekday day)
    {
        return scheduleDayTemp[day];
    }

    void setScheduleNightTemp(weekday day, int16_t temp)
    {
        scheduleNightTemp[day] = temp;
    }
    int16_t getScheduleNightTemp(weekday day)
    {
        return scheduleNightTemp[day];
    }

private:
    uint8_t roomId;

    TEXTS roomName;
    TEXTS roomNameHeadline;
    TEXTS roomScheduleHeadline;
    int16_t currentTemperature;
    int16_t scheduleDayTemp[NUMBER_OF_DAYS];
    int16_t scheduleNightTemp[NUMBER_OF_DAYS];
};


#endif /* ROOM_TEMPERATURE_INFO_HPP_ */
