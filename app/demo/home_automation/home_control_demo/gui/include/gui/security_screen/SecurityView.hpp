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
#ifndef SECURITY_VIEW_HPP
#define SECURITY_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/security_screen/SecurityPresenter.hpp>
#include <gui/security_screen/SecurityRoomSelector.hpp>
#include <gui/common/SelectionButton.hpp>
#include <touchgfx/mixins/ClickListener.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>

using namespace touchgfx;

/**
 * SecurityView - control of a security system
 *
 * Select a room to turn the alarm monitoring ON and OFF.
 * It is possible to enable/disable alarm monitoring for all the rooms by pressing the large on/off button.
 */
class SecurityView : public BaseView<SecurityPresenter>
{
public:
    SecurityView();
    virtual ~SecurityView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    /**
     * The following functions are used by the presenter
     */
    void setRoomSecurity(Room room, bool active);
    bool getRoomSecurity(Room room)
    {
        return roomSelector.isSelected(room);
    }
    Room getCurrentSelectedRoom()
    {
        return roomSelector.getCurrentSelectedRoom();
    }
    void setAllRoomButton(bool buttonOff);
private:
    touchgfx::ScrollableContainer roomSelectorViewPort;
    SecurityRoomSelector roomSelector;
    SelectionButton allRoomButton;

    touchgfx::Callback<SecurityView> onAllButtonClicked;
    void allRoomButtonClicked();

    touchgfx::Callback<SecurityView, Room> onRoomClicked;
    void roomSelected(Room room);
};

#endif
