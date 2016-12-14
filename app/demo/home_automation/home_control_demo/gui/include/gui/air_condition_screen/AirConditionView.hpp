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
#ifndef AIR_CONDITION_VIEW_HPP
#define AIR_CONDITION_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/air_condition_screen/AirConditionPresenter.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/common/JogWheel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/RoomSelector.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

/**
 * AirConditionView - room temperature control
 *
 * Select a room and adjust the temperature by turning clockwise or anticlockwise on the jogwheel.
 * When the jogwheel is released the temperature is updated for the selected room
 */
class AirConditionView : public BaseView<AirConditionPresenter>
{
public:
    AirConditionView();
    virtual ~AirConditionView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void setJogwheelActive(int16_t value);
    void setJogwheelInactive(bool animate = true);

    void setRoomTemperature(Room room, int16_t value);
    void deselectAllRooms();
private:
    ScrollableContainer roomSelectorViewPort;
    RoomSelector roomSelector;

    static const int16_t INITIAL_TEMPERATURE = 0;
    static const int16_t JOGWHEEL_DELTA = 6;

    JogWheel jogWheel;
    FadeAnimator<TextAreaWithOneWildcard> jogWheelOutput;
    Unicode::UnicodeChar jogWheelOutputTextBuffer[5];

    Callback<AirConditionView, Room> onRoomSelected;
    Callback<AirConditionView, int16_t> onJogWheelValueChanged;
    Callback<AirConditionView, int16_t> onJogWheelEndDragEvent;

    void roomSelected(Room room);
    void jogWheelValueChanged(int16_t value);
    void jogWheelEndDragEvent(int16_t value);
};

#endif
