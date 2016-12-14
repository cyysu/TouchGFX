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
#ifndef ROOM_SELECTOR_HPP
#define ROOM_SELECTOR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/FontPosition.hpp>
#include <gui/model/Room.hpp>

/**
 *
 */
class RoomSelector : public touchgfx::Container
{
public:
    RoomSelector(const touchgfx::TypedText& roomIndicatorText = touchgfx::TypedText(), bool multiSelectEnabled = false);
    virtual ~RoomSelector();

    void initializeRoom(Room room, bool selected);
    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);

    void setRoomSelectedCallback(touchgfx::GenericCallback< Room >& callback)
    {
        roomSelectedCallback = &callback;
    }
    void setRoomText(Room room, int value);
    Room getCurrentSelectedRoom();
    bool isSelected(Room room);

    void selectRoom(Room room);
    void selectAllRooms(bool notify = true);
    void deselectRoom(Room room);
    void deselectAllRooms(bool notify = true);
protected:
    void notifyChanges();

    touchgfx::Image roomLayout;

    touchgfx::Image rooms[Room::NUMBER_OF_ROOMS];
    FontPosition<touchgfx::TextAreaWithOneWildcard> roomText[Room::NUMBER_OF_ROOMS];
    static const uint8_t BUFFER_LENGTH = 5;
    touchgfx::Unicode::UnicodeChar roomTextBuffer[Room::NUMBER_OF_ROOMS][BUFFER_LENGTH];

    touchgfx::GenericCallback< Room >* roomSelectedCallback;
    bool multiSelectEnabled;

    int16_t xValueWhenPressed;
};


#endif
