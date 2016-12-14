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
#include <gui/clock_screen/ClockView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

ClockView::ClockView() :
    DemoView(),
    currentSecondCounter(0),
    currentMinuteCounter(0),
    currentHourCounter(0),
    transitionDone(false),
    firstPresenterCall(true)
{
}

ClockView::~ClockView()
{
}

void ClockView::setupScreen()
{
    clockBackground.setBitmap(Bitmap(BITMAP_CLOCK_BACKGROUND_ID));
    clockBackground.setXY(backButton.getWidth(), 0);

    centerDot.setBitmap(Bitmap(BITMAP_CENTER_DOT_ID));
    centerDot.setXY(247, 125);

    handColorRed.setColor(Color::getColorFrom24BitRGB(0xFF, 0x0, 0x0));
    handColorWhite.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    secondHand.setPosition(160, 38, 190, 190);
    secondHand.setOrigin(95, 95);
    secondHand.setPainter(handColorRed);

    minuteHand.setPosition(160, 38, 190, 190);
    minuteHand.setOrigin(95, 95);
    minuteHand.setPainter(handColorWhite);

    hourHand.setPosition(160, 38, 190, 190);
    hourHand.setOrigin(95, 95);
    hourHand.setPainter(handColorWhite);

    add(clockBackground);
    add(hourHand);
    add(minuteHand);
    add(secondHand);
    add(centerDot);
}

void ClockView::tearDownScreen()
{
}

void ClockView::afterTransition()
{
    DemoView<ClockPresenter>::afterTransition();
    transitionDone = true;
}

void ClockView::handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    currentSecondCounter = seconds;
    currentMinuteCounter = minutes;
    //currentHourCounter counts from 0-59 due to the number of images of the hour hand
    currentHourCounter = ((hours % 12) * 5) + (minutes / 12);

    updateClock(currentHourCounter, currentMinuteCounter, currentSecondCounter);
}

void ClockView::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter)
{
    // Updating the clock before transition to the page is done will cause the hands to move unintended.
    // We do allow the first call from the presenter in that case where we do not animate from start.
    if (transitionDone || firstPresenterCall)
    {
        if (firstPresenterCall)
        {
            // To avoid jump in seconds when opening the view
            secondCounter++;
            firstPresenterCall = false;
        }

        secondHand.updateAngle(secondCounter * 6);

        minuteHand.updateAngle(minuteCounter * 6 + secondCounter / 10);

        hourHand.updateAngle(hourCounter * 6 + minuteCounter / 10);
    }
}
