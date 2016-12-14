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
#include <gui/blinds_screen/BlindsView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Constants.hpp>

using namespace touchgfx;

BlindsView::BlindsView() :
    jogWheel(INITIAL_TEMPERATURE, JOGWHEEL_DELTA),
    onBlindsSelected(this, &BlindsView::blindsSelected),
    onJogWheelValueChanged(this, &BlindsView::jogWheelValueChanged),
    onJogWheelEndDragEvent(this, &BlindsView::jogWheelEndDragEvent)
{
    menu.set(Menu::Blinds);
}

void BlindsView::setupScreen()
{
    baseview::setupScreen();

    headline.setBitmap(Bitmap(BITMAP_BLINDS_HEADLINE_ID));

    blindsSelector.setXY(0, 0);
    blindsSelector.setBlindsSelectedCallback(onBlindsSelected);
    blindsSelectorViewPort.setPosition(260, 0, HAL::DISPLAY_WIDTH - 260, blindsSelector.getHeight());
    blindsSelectorViewPort.add(blindsSelector);

    jogWheel.setBitmaps(Bitmap(BITMAP_JOGWHEEL_NORMAL_ID), Bitmap(BITMAP_JOGWHEEL_PRESSED_ID));
    jogWheel.setXY(26, 120);
    jogWheel.setMinValue(0);
    jogWheel.setMaxValue(100);
    jogWheel.setStepInterval(5);
    jogWheel.setValueUpdatedCallback(onJogWheelValueChanged);
    jogWheel.setEndDragEventCallback(onJogWheelEndDragEvent);

    jogWheelOutput.setPosition(jogWheel.getX() + 78, jogWheel.getY() + 84, 78, 52);
    jogWheelOutput.setTypedText(TypedText(T_JOGWHEEL_INDICATOR_PERCENTAGE));
    jogWheelOutput.setColor(Colors_TEXT_LIGHT);
    jogWheelOutput.setWildcard(jogWheelOutputTextBuffer);
    jogWheelValueChanged(INITIAL_TEMPERATURE);

    setJogwheelInactive(false);
    jogWheelOutput.setAlpha(0);

    jogWheelPercentage.setBitmap(Bitmap(BITMAP_JOGWHEEL_PERCENTAGE_ID));
    jogWheelPercentage.setXY(jogWheelOutput.getX() + jogWheelOutput.getWidth() / 2 - jogWheelPercentage.getWidth() / 2 - 2, jogWheelOutput.getY() + 46);
    jogWheelPercentage.setAlpha(0);

    content.add(blindsSelectorViewPort);
    content.add(jogWheel);
    content.add(jogWheelOutput);
    content.add(jogWheelPercentage);
}

void BlindsView::tearDownScreen()
{
}

void BlindsView::setJogwheelActive(int16_t value)
{
    jogWheelValueChanged(value);
    jogWheel.setValue(value);
    jogWheel.setTouchable(true);

    if (jogWheelOutput.getAlpha() == 0)
    {
        jogWheelOutput.startFadeAnimation(255, 10, &EasingEquations::linearEaseInOut);
        jogWheelPercentage.startFadeAnimation(255, 10, &EasingEquations::linearEaseInOut);
    }
}

void BlindsView::setJogwheelInactive(bool animate)
{
    jogWheel.setTouchable(false);

    if (animate)
    {
        jogWheelOutput.startFadeAnimation(0, 10, &EasingEquations::linearEaseInOut);
        jogWheelPercentage.startFadeAnimation(0, 10, &EasingEquations::linearEaseInOut);
    }
}

void BlindsView::jogWheelValueChanged(int16_t value)
{
    Unicode::snprintf(jogWheelOutputTextBuffer, JOG_WHEEL_OUTPUT_BUFFER_LENGTH, "%d", value);
    jogWheelOutput.invalidate();
}

void BlindsView::jogWheelEndDragEvent(int16_t value)
{
    for (int8_t i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        if (blindsSelector.isSelected(Room(i)))
        {
            presenter->roomBlindsPercentageUpdated(Room(i), value);
        }
    }
}

void BlindsView::blindsSelected(int16_t selectedBlind, uint16_t numberOfSelectedBlinds)
{
    presenter->blindsSelected(selectedBlind, numberOfSelectedBlinds);
}

Room BlindsView::getRoomFromBlindId(int16_t selectedBlind)
{
    return blindsSelector.getRoomFromBlindId(selectedBlind);
}

void BlindsView::setBlindPercentage(Room room, int16_t value)
{
    blindsSelector.setRoomText(room, value);
}
