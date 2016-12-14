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
#ifndef ROOM_HPP
#define ROOM_HPP

/**
 * The Room class define the available rooms used by the demo
 */
class Room
{
public:
    enum RoomTypes
    {
        ALL_ROOMS_SELECTED = -3,
        ROOMS_SELECTED = -2,
        NO_ROOM_SELECTED = -1,
        ROOM1 = 0,
        ROOM2,
        LIVINGROOM,
        BEDROOM,
        KITCHEN
    };
    static const int NUMBER_OF_ROOMS = KITCHEN + 1;

    typedef RoomTypes RoomType;

    Room(RoomType room = NO_ROOM_SELECTED) : room(room)
    {
    }

    Room(uint8_t index)
    {
        room = (RoomType)index;
    }

    operator RoomType() const
    {
        return room;
    }
private:
    RoomType room;
};

#endif
