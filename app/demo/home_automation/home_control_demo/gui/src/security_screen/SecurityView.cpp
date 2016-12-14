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
#include <gui/security_screen/SecurityView.hpp>
#include <BitmapDatabase.hpp>


SecurityView::SecurityView() :
    onAllButtonClicked(this, &SecurityView::allRoomButtonClicked),
    onRoomClicked(this, &SecurityView::roomSelected)
{
    menu.set(Menu::Security);
}

void SecurityView::setupScreen()
{
    baseview::setupScreen();

    headline.setBitmap(touchgfx::Bitmap(BITMAP_SECURITY_HEADLINE_ID));

    roomSelector.setXY(0, 0);
    roomSelector.setWidth(roomSelector.getWidth() + 20);
    roomSelector.setRoomSelectedCallback(onRoomClicked);
    roomSelectorViewPort.setPosition(280, 40, touchgfx::HAL::DISPLAY_WIDTH - 280, roomSelector.getHeight());
    roomSelectorViewPort.add(roomSelector);

    allRoomButton.setPressedAction(onAllButtonClicked);
    allRoomButton.setBitmaps(touchgfx::Bitmap(BITMAP_SECURITY_ALL_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_SECURITY_ALL_OFF_BUTTON_ID));
    allRoomButton.setXY(25, 88);

    content.add(roomSelectorViewPort);
    content.add(allRoomButton);
}

void SecurityView::tearDownScreen()
{
}

void SecurityView::allRoomButtonClicked()
{
    presenter->setSecurityForAllRooms(allRoomButton.isSelected() ? true : false);
}

void SecurityView::roomSelected(Room room)
{
    presenter->roomChanged();
}

void SecurityView::setRoomSecurity(Room room, bool active)
{
    // avoid callback from RoomSelector
    roomSelector.initializeRoom(room, active);
}

void SecurityView::setAllRoomButton(bool buttonOff)
{
    allRoomButton.forceState(buttonOff);
    allRoomButton.invalidate();
}
