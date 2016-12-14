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
#include <gui/air_condition_screen/AirConditionView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;


AirConditionView::AirConditionView() :
    roomSelector(TypedText(T_ROOM_INDICATOR_DEGREE)),
    jogWheel(INITIAL_TEMPERATURE, JOGWHEEL_DELTA),
    onRoomSelected(this, &AirConditionView::roomSelected),
    onJogWheelValueChanged(this, &AirConditionView::jogWheelValueChanged),
    onJogWheelEndDragEvent(this, &AirConditionView::jogWheelEndDragEvent)
{
    menu.set(Menu::AirCondition);
}

void AirConditionView::setupScreen()
{
    baseview::setupScreen();

    headline.setBitmap(Bitmap(BITMAP_AIR_CON_HEADLINE_ID));

    roomSelector.setXY(0, 0);
    roomSelector.setWidth(roomSelector.getWidth() + 20);
    roomSelector.setRoomSelectedCallback(onRoomSelected);
    roomSelectorViewPort.setPosition(280, 40, HAL::DISPLAY_WIDTH - 280, roomSelector.getHeight());
    roomSelectorViewPort.add(roomSelector);

    jogWheel.setBitmaps(Bitmap(BITMAP_JOGWHEEL_NORMAL_ID), Bitmap(BITMAP_JOGWHEEL_PRESSED_ID));
    jogWheel.setXY(26, 120);
    jogWheel.setMinValue(10);
    jogWheel.setMaxValue(35);
    jogWheel.setStepInterval(1);
    jogWheel.setValueUpdatedCallback(onJogWheelValueChanged);
    jogWheel.setEndDragEventCallback(onJogWheelEndDragEvent);

    jogWheelOutput.setPosition(jogWheel.getX() + 78, jogWheel.getY() + 84, 78, 52);
    jogWheelOutput.setTypedText(TypedText(T_JOGWHEEL_INDICATOR_DEGREE));
    jogWheelOutput.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    jogWheelOutput.setWildcard(jogWheelOutputTextBuffer);
    jogWheelValueChanged(INITIAL_TEMPERATURE);

    setJogwheelInactive(false);
    jogWheelOutput.setAlpha(0);

    content.add(roomSelectorViewPort);
    content.add(jogWheel);
    content.add(jogWheelOutput);
}

void AirConditionView::tearDownScreen()
{
}

void AirConditionView::setJogwheelActive(int16_t value)
{
    jogWheelValueChanged(value);
    jogWheel.setValue(value);
    jogWheel.setTouchable(true);

    if (jogWheelOutput.getAlpha() == 0)
    {
        jogWheelOutput.startFadeAnimation(255, 10,  &EasingEquations::linearEaseInOut);
    }
}

void AirConditionView::setJogwheelInactive(bool animate)
{
    jogWheel.setTouchable(false);

    if (animate)
    {
        jogWheelOutput.startFadeAnimation(0, 10, &EasingEquations::linearEaseInOut);
    }
}

void AirConditionView::setRoomTemperature(Room room, int16_t value)
{
    roomSelector.setRoomText(room, value);
}

void AirConditionView::roomSelected(Room room)
{
    presenter->roomSelected(room);
}

void AirConditionView::jogWheelValueChanged(int16_t value)
{
    Unicode::snprintf(jogWheelOutputTextBuffer, 5, "%d", value);
    jogWheelOutput.invalidate();
}

void AirConditionView::jogWheelEndDragEvent(int16_t value)
{
    presenter->roomAirConTempUpdated(roomSelector.getCurrentSelectedRoom(), value);
}

void AirConditionView::deselectAllRooms()
{
    roomSelector.deselectAllRooms();
}
