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
#include <gui/tiles/WeatherTile.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

WeatherTile::WeatherTile() :
    BaseTile(),
    currentState(WEATHER_OUT),
    counter(0),
    animationCallback(this, &WeatherTile::handleAnimationEvent)
{
    Application::getInstance()->registerTimerWidget(this);

    background.setXY(0, 0);
    background.setBitmap(Bitmap(BITMAP_WEATHER_BAR_ID));

    add(background);

    for (uint8_t i = 0; i < NUMBER_OF_DAYS; i++)
    {
        daysVisiblePosX[i] = startPosOfIcons + 150 * i;
        daysHiddenPosX[i] = daysVisiblePosX[i] + HAL::DISPLAY_WIDTH;
        days[i].setXY(daysHiddenPosX[i], 10);
        add(days[i]);
    }
    currentDay = 0;
    setupCurrentFiveDays();

    setWidth(background.getWidth());
    setHeight(background.getHeight());

    // animation is complete when the last day has finished its animation
    days[NUMBER_OF_DAYS - 1].setMoveAnimationEndedAction(animationCallback);
}

void WeatherTile::handleTickEvent()
{
    counter++;

    if (currentState == WEATHER_OUT)
    {
        if (counter % 30 == 0)
        {
            setCurrentState(ANIMATE_IN);
        }
    }
    else if (currentState == WEATHER_IN)
    {
        if (counter % 1000 == 0)
        {
            setCurrentState(ANIMATE_OUT);
        }
    }

    if (currentState == ANIMATE_IN)
    {
        uint8_t animationInterval = 12;
        uint8_t dayIndex = counter / animationInterval;
        uint8_t duration;

#ifdef NXP
        duration = 24;
#else
        duration = 18;
#endif

        if (counter % animationInterval == 0 && dayIndex < NUMBER_OF_DAYS)
        {
            // Reset to start position and start animation
            days[dayIndex].moveTo(daysHiddenPosX[dayIndex], days[dayIndex].getY());
            days[dayIndex].startMoveAnimation(daysVisiblePosX[dayIndex], days[dayIndex].getY(), duration, &EasingEquations::cubicEaseOut, &EasingEquations::linearEaseNone);
        }
    }
    else if (currentState == ANIMATE_OUT)
    {
        uint8_t animationInterval = 8;
        uint8_t dayIndex = counter / animationInterval;
        uint8_t duration;

#ifdef NXP
        duration = 22;
#else
        duration = 16;
#endif

        if (counter % animationInterval == 0 && dayIndex < NUMBER_OF_DAYS)
        {
            // Reset to start position and start animation
            days[dayIndex].moveTo(daysVisiblePosX[dayIndex], days[dayIndex].getY());
            days[dayIndex].startMoveAnimation(daysVisiblePosX[dayIndex] - HAL::DISPLAY_WIDTH, days[dayIndex].getY(), duration, &EasingEquations::cubicEaseIn, &EasingEquations::linearEaseNone);
        }
    }
}

void WeatherTile::setupCurrentFiveDays()
{
    // Hardcoded values. No integration with the model
    days[0].setIcon(BITMAP_ICON_LIGHTNING_ID);
    days[0].setDayTemperature(21);
    days[0].setNightTemperature(14);
    days[1].setIcon(BITMAP_ICON_RAIN_ID);
    days[1].setDayTemperature(15);
    days[1].setNightTemperature(9);
    days[2].setIcon(BITMAP_ICON_RAIN_SUN_ID);
    days[2].setDayTemperature(20);
    days[2].setNightTemperature(11);
    days[3].setIcon(BITMAP_ICON_CLOUDY_ID);
    days[3].setDayTemperature(17);
    days[3].setNightTemperature(13);

#ifndef RESOLUTION_640X480
    days[4].setIcon(BITMAP_ICON_SUN_ID);
    days[4].setDayTemperature(24);
    days[4].setNightTemperature(14);
#endif

    for (uint8_t i = 0; i < NUMBER_OF_DAYS; i++)
    {
        days[i].setDayName((TEXTS)(T_WEEKDAY_0 + ((currentDay + i) % 7)));
    }
    showingCurrentWeek = true;
}

void WeatherTile::setupNextFiveDays()
{
    // Hardcoded values. No integration with the model
    days[0].setIcon(BITMAP_ICON_LIGHTNING_ID);
    days[0].setDayTemperature(23);
    days[0].setNightTemperature(16);
    days[1].setIcon(BITMAP_ICON_SUN_ID);
    days[1].setDayTemperature(25);
    days[1].setNightTemperature(15);
    days[2].setIcon(BITMAP_ICON_RAIN_SUN_ID);
    days[2].setDayTemperature(21);
    days[2].setNightTemperature(12);
    days[3].setIcon(BITMAP_ICON_RAIN_SUN_ID);
    days[3].setDayTemperature(22);
    days[3].setNightTemperature(12);

#ifndef RESOLUTION_640X480
    days[4].setIcon(BITMAP_ICON_SUN_ID);
    days[4].setDayTemperature(24);
    days[4].setNightTemperature(17);
#endif

    for (uint8_t i = 0; i < NUMBER_OF_DAYS; i++)
    {
        days[i].setDayName((TEXTS)(T_WEEKDAY_0 + ((currentDay + 5 + i) % 7)));
    }
    showingCurrentWeek = false;
}

void WeatherTile::setCurrentState(States newState)
{
    counter = 0;
    currentState = newState;
}

void WeatherTile::handleAnimationEvent(const MoveAnimator<WeatherTileDayElement>& obj)
{

    if (currentState == ANIMATE_IN)
    {
        setCurrentState(WEATHER_IN);
    }
    else if (currentState == ANIMATE_OUT)
    {
        showingCurrentWeek ? setupNextFiveDays() : setupCurrentFiveDays();
        setCurrentState(WEATHER_OUT);
    }
}
