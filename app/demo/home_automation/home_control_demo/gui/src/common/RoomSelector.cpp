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
#include <gui/common/RoomSelector.hpp>
#include <gui/common/Constants.hpp>
#include <math.h>
#include <gui/model/Room.hpp>

using namespace touchgfx;


RoomSelector::RoomSelector(const touchgfx::TypedText& roomIndicatorText, bool multiSelectEnabled) :
    roomSelectedCallback(),
    multiSelectEnabled(multiSelectEnabled)
{
    setTouchable(true);

    roomLayout.setBitmap(Bitmap(BITMAP_ROOM_LAYOUT_ID));
    roomLayout.setXY(0, 0);

    rooms[Room::ROOM1].setBitmap(Bitmap(BITMAP_ROOM1_SELECTED_ID));
    rooms[Room::ROOM1].setXY(0, 0);

    rooms[Room::ROOM2].setBitmap(Bitmap(BITMAP_ROOM2_SELECTED_ID));
    rooms[Room::ROOM2].setXY(0, 190);

    rooms[Room::LIVINGROOM].setBitmap(Bitmap(BITMAP_LIVING_ROOM_SELECTED_ID));
    rooms[Room::LIVINGROOM].setXY(0, 0);

    rooms[Room::BEDROOM].setBitmap(Bitmap(BITMAP_BED_ROOM_SELECTED_ID));
    rooms[Room::BEDROOM].setXY(138, 190);

    rooms[Room::KITCHEN].setBitmap(Bitmap(BITMAP_KITCHEN_SELECTED_ID));
    rooms[Room::KITCHEN].setXY(318, 191);

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        roomText[i].setTypedText(roomIndicatorText);
        roomText[i].setColor(Colors_TEXT_DARK);
        setRoomText((Room) i, 20);
        roomText[i].setWildcard(roomTextBuffer[i]);
    }
    // Note that y-position is the font baseline
    roomText[Room::ROOM1].setPosition(13, 100, 124);
    roomText[Room::ROOM2].setPosition(13, 280, 124);
    roomText[Room::LIVINGROOM].setPosition(243, 130, 124);
    roomText[Room::BEDROOM].setPosition(171, 280, 124);
    roomText[Room::KITCHEN].setPosition(335, 280, 124);

    deselectAllRooms();

    setWidth(roomLayout.getWidth());
    setHeight(roomLayout.getHeight());

    add(roomLayout);
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        add(rooms[Room::NUMBER_OF_ROOMS - i - 1]);
    }
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        add(roomText[Room::NUMBER_OF_ROOMS - i - 1]);
    }
}

RoomSelector::~RoomSelector()
{
}

void RoomSelector::initializeRoom(Room room, bool selected)
{
    rooms[room].setVisible(selected);
    rooms[room].invalidate();

    roomText[room].setColor(selected ? Colors_TEXT_LIGHT : Colors_TEXT_DARK);
    roomText[room].invalidate();
}

void RoomSelector::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        xValueWhenPressed = this->getAbsoluteRect().x;
        return;
    }

    bool movedSincePressed = ((xValueWhenPressed < this->getAbsoluteRect().x) ? this->getAbsoluteRect().x - xValueWhenPressed : xValueWhenPressed - this->getAbsoluteRect().x) > 10;

    if (evt.getType() == ClickEvent::RELEASED && !movedSincePressed)
    {

        int pressedXAbs = evt.getX() + this->getAbsoluteRect().x;
        int pressedYAbs = evt.getY() + this->getAbsoluteRect().y;

        for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
        {
            if (rooms[i].getAbsoluteRect().intersect(pressedXAbs, pressedYAbs))
            {
                rooms[i].isVisible() ? deselectRoom((Room)i) : selectRoom((Room) i);
                break;
            }
        }
    }
}

void RoomSelector::setRoomText(Room room, int value)
{
    Unicode::snprintf(roomTextBuffer[room], BUFFER_LENGTH, "%d", value);
    roomText[room].invalidate();
}

void RoomSelector::selectRoom(Room room)
{
    if (!multiSelectEnabled)
    {
        deselectAllRooms(false);
    }
    rooms[room].setVisible(true);
    rooms[room].invalidate();
    roomText[room].setColor(Colors_TEXT_LIGHT);
    roomText[room].invalidate();
    notifyChanges();
}

void RoomSelector::deselectRoom(Room room)
{
    if (!multiSelectEnabled)
    {
        deselectAllRooms(false);
    }
    else
    {
        rooms[room].setVisible(false);
        rooms[room].invalidate();

        roomText[room].setColor(Colors_TEXT_DARK);
        roomText[room].invalidate();
    }
    notifyChanges();
}

Room RoomSelector::getCurrentSelectedRoom()
{
    Room room = Room(Room::NO_ROOM_SELECTED);
    uint8_t countSelectedRooms = 0;

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        if (rooms[i].isVisible())
        {
            countSelectedRooms++;
            room = Room((Room::RoomType)i);
        }
    }
    switch (countSelectedRooms)
    {
    case 0:
    case 1:
        // roomId allready ok
        break;
    case Room::NUMBER_OF_ROOMS:
        room = Room::ALL_ROOMS_SELECTED;
        break;
    default:
        room = Room::ROOMS_SELECTED;
    }
    return room;
}

void RoomSelector::selectAllRooms(bool notify)
{
    if (multiSelectEnabled)
    {
        for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
        {
            rooms[i].setVisible(true);
            rooms[i].invalidate();

            roomText[i].setColor(Colors_TEXT_LIGHT);
            roomText[i].invalidate();
        }
    }
    if (notify)
    {
        notifyChanges();
    }
}

void RoomSelector::deselectAllRooms(bool notify)
{
    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        rooms[i].setVisible(false);
        rooms[i].invalidate();

        roomText[i].setColor(Colors_TEXT_DARK);
        roomText[i].invalidate();
    }
    if (notify)
    {
        notifyChanges();
    }
}

bool RoomSelector::isSelected(Room room)
{
    return rooms[room].isVisible();
}

void RoomSelector::notifyChanges()
{
    if (roomSelectedCallback && roomSelectedCallback->isValid())
    {
        roomSelectedCallback->execute(getCurrentSelectedRoom());
    }
}
