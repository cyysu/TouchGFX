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
#include <gui/security_screen/SecurityRoomSelector.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;


SecurityRoomSelector::SecurityRoomSelector() :
    RoomSelector(touchgfx::TypedText(T_ROOM_INDICATOR_DEGREE), true)
{
    roomLayout.setBitmap(Bitmap(BITMAP_SECURITY_ROOM_LAYOUT_ID));
    // replace selected bitmaps
    rooms[Room::ROOM1].setBitmap(Bitmap(BITMAP_SECURITY_ROOM1_SELECTED_ID));
    rooms[Room::ROOM2].setBitmap(Bitmap(BITMAP_SECURITY_ROOM2_SELECTED_ID));
    rooms[Room::LIVINGROOM].setBitmap(Bitmap(BITMAP_SECURITY_LIVING_ROOM_SELECTED_ID));
    rooms[Room::BEDROOM].setBitmap(Bitmap(BITMAP_SECURITY_BED_ROOM_SELECTED_ID));
    rooms[Room::KITCHEN].setBitmap(Bitmap(BITMAP_SECURITY_KITCHEN_SELECTED_ID));

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        roomText[i].setVisible(false);
    }
}

SecurityRoomSelector::~SecurityRoomSelector()
{

}
