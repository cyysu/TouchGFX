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
#include <gui/common/BlindsSelector.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Constants.hpp>
#include <math.h>

using namespace touchgfx;

BlindsSelector::BlindsSelector()
{
    setTouchable(true);

    background.setBitmap(Bitmap(BITMAP_ROOM_LAYOUT_BLINDS_ID));
    background.setXY(0, 0);

    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        selectedDots[i].setBitmap(Bitmap(BITMAP_BLIND_SELECTOR_PRESSED_ID));
    }

    selectedDots[0].setXY(10, 80);
    selectedDots[1].setXY(198, 29);
    selectedDots[2].setXY(278, 29);
    selectedDots[3].setXY(401, 29);
    selectedDots[4].setXY(480, 79);
    selectedDots[5].setXY(480, 167);
    selectedDots[6].setXY(63, 340);
    selectedDots[7].setXY(196, 340);
    selectedDots[8].setXY(269, 340);
    selectedDots[9].setXY(365, 340);
    selectedDots[10].setXY(436, 340);

    blindsToRoom[0] = Room(Room::ROOM1);
    blindsToRoom[1] = Room(Room::LIVINGROOM);
    blindsToRoom[2] = Room(Room::LIVINGROOM);
    blindsToRoom[3] = Room(Room::LIVINGROOM);
    blindsToRoom[4] = Room(Room::LIVINGROOM);
    blindsToRoom[5] = Room(Room::LIVINGROOM);
    blindsToRoom[6] = Room(Room::ROOM2);
    blindsToRoom[7] = Room(Room::BEDROOM);
    blindsToRoom[8] = Room(Room::BEDROOM);
    blindsToRoom[9] = Room(Room::KITCHEN);
    blindsToRoom[10] = Room(Room::KITCHEN);


    deselectAllBlinds();


    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        roomText[i].setTypedText(TypedText(T_ROOM_INDICATOR_PERCENTAGE));
        roomText[i].setColor(Colors_TEXT_DARK);
        setRoomText((Room) i, 20);
        roomText[i].setWildcard(roomTextBuffer[i]);
    }
    roomText[0].setPosition(34, 140 - TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getFontHeight(), 124, TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getMinimumTextHeight());
    roomText[1].setPosition(34, 320 - TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getFontHeight(), 124, TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getMinimumTextHeight());
    roomText[2].setPosition(268, 168 - TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getFontHeight(), 124, TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getMinimumTextHeight());
    roomText[3].setPosition(186, 320 - TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getFontHeight(), 124, TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getMinimumTextHeight());
    roomText[4].setPosition(360, 320 - TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getFontHeight(), 124, TypedText(T_ROOM_INDICATOR_DEGREE).getFont()->getMinimumTextHeight());

    setWidth(background.getWidth());
    setHeight(background.getHeight());

    add(background);

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        add(roomText[i]);
    }
    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        add(selectedDots[i]);
    }
}

BlindsSelector::~BlindsSelector()
{
}

void BlindsSelector::deselectAllBlinds()
{
    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        selectedBlinds[i] = false;
    }
    updateDots();
}

void BlindsSelector::setRoomText(Room room, int value)
{
    Unicode::snprintf(roomTextBuffer[room], 5, "%d", value);
    roomText[room].invalidate();
}

void BlindsSelector::handleClickEvent(const ClickEvent& evt)
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

        for (int i = 0; i < NUMBER_OF_BLINDS; i++)
        {
            if (selectedDots[i].getAbsoluteRect().intersect(pressedXAbs, pressedYAbs))
            {
                selectDot(i, !selectedBlinds[i]);
                break;
            }
        }
    }
}


void BlindsSelector::updateDots()
{
    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        selectedDots[i].setVisible(selectedBlinds[i]);
        selectedDots[i].invalidate();
    }
}

void BlindsSelector::selectDot(int16_t blindId, bool select)
{
    assert(blindId < NUMBER_OF_BLINDS);
    selectedBlinds[blindId] = select;
    updateDots();

    if (blindsSelectedCallback)
    {
        blindsSelectedCallback->execute(blindId, getNumberOfSelectedBlinds());
    }
}

bool BlindsSelector::isSelected(int16_t blindId)
{
    assert(blindId < NUMBER_OF_BLINDS);
    return selectedBlinds[blindId];
}

uint16_t BlindsSelector::getNumberOfSelectedBlinds()
{
    uint16_t result = 0;
    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        result += selectedBlinds[i];
    }
    return result;
}

Room BlindsSelector::getRoomFromBlindId(int16_t blindId)
{
    assert(blindId < NUMBER_OF_BLINDS);
    return blindsToRoom[blindId];
}

bool BlindsSelector::isSelected(Room room)
{
    for (int16_t i = 0; i < NUMBER_OF_BLINDS; i++)
    {
        if (selectedBlinds[i] && getRoomFromBlindId(i) == room)
        {
            return true;
        }
    }
    return false;
}
