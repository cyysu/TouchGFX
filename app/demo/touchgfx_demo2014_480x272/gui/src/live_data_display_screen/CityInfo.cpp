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
#include <gui/live_data_display_screen/CityInfo.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <stdlib.h>

CityInfo::CityInfo()
{
    textColor = 0x0;
    background.setXY(0, 0);

    cityName.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    cityName.setTypedText(TypedText(T_WEATHER_CITY_0));
    cityName.setPosition(16, 10, 130, 24);

    cityNameDropShadow.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));
    cityNameDropShadow.setTypedText(TypedText(T_WEATHER_CITY_0));
    cityNameDropShadow.setPosition(cityName.getX() + 1, cityName.getY() + 1, cityName.getWidth(), cityName.getHeight());
    cityNameDropShadow.setAlpha(128);

    timeAndDate.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    timeAndDate.setTypedText(TypedText(T_WEATHER_TIME_INFO_0));
    timeAndDate.setPosition(cityName.getX() + cityName.getWidth(), 14, 150, 20);

    timeAndDateDropShadow.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));
    timeAndDateDropShadow.setTypedText(TypedText(T_WEATHER_TIME_INFO_0));
    timeAndDateDropShadow.setPosition(timeAndDate.getX() + 1, timeAndDate.getY() + 1, timeAndDate.getWidth(), timeAndDate.getHeight());
    timeAndDateDropShadow.setAlpha(128);

    largeIcon.setBitmap(Bitmap(BITMAP_WEATHER_BIG_ICON_CLOUDS_ID));
    largeIcon.setXY(232, 48);

    largeTemperature.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    largeTemperature.setTypedText(TypedText(T_WEATHER_LARGE_TEMPERATURE));
    largeTemperature.setPosition(86, 46, 150, 110);
    Unicode::snprintf(largeTemperatureBuffer, 4, "%d", 0);
    largeTemperature.setWildcard(largeTemperatureBuffer);

    largeTemperatureDropShadow.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    largeTemperatureDropShadow.setTypedText(TypedText(T_WEATHER_LARGE_TEMPERATURE));
    largeTemperatureDropShadow.setPosition(largeTemperature.getX() + 1, largeTemperature.getY() + 2, largeTemperature.getWidth(), largeTemperature.getHeight());
    largeTemperatureDropShadow.setWildcard(largeTemperatureBuffer);
    largeTemperatureDropShadow.setAlpha(128);

    add(background);
    add(cityNameDropShadow);
    add(cityName);
    add(timeAndDateDropShadow);
    add(timeAndDate);
    add(largeIcon);
    add(largeTemperatureDropShadow);
    add(largeTemperature);
}

void CityInfo::setBitmap(BitmapId bg)
{
    background.setBitmap(Bitmap(bg));

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}


/* Setup the CityInfo with some static city information
 * In a real world example this data would be live updated
 * and come from the model, but in this demo it is just hard coded.
 */
void CityInfo::setCity(Cities c)
{
    city = c;

    switch (city)
    {
    case COPENHAGEN:
        cityName.setTypedText(TypedText(T_WEATHER_CITY_0));
        cityNameDropShadow.setTypedText(TypedText(T_WEATHER_CITY_0));
        timeAndDate.setTypedText(TypedText(T_WEATHER_TIME_INFO_0));
        timeAndDateDropShadow.setTypedText(TypedText(T_WEATHER_TIME_INFO_0));
        largeIcon.setBitmap(Bitmap(BITMAP_WEATHER_BIG_ICON_CLOUDS_ID));
        largeIcon.setXY(232, 46);
        startTemperature = 12;
        break;

    case MUMBAI:
        cityName.setTypedText(TypedText(T_WEATHER_CITY_1));
        cityNameDropShadow.setTypedText(TypedText(T_WEATHER_CITY_1));
        timeAndDate.setTypedText(TypedText(T_WEATHER_TIME_INFO_1));
        timeAndDateDropShadow.setTypedText(TypedText(T_WEATHER_TIME_INFO_1));
        largeIcon.setBitmap(Bitmap(BITMAP_WEATHER_BIG_ICON_SUN_ID));
        largeIcon.setXY(232, 40);
        startTemperature = 32;
        break;

    case HONG_KONG:
        cityName.setTypedText(TypedText(T_WEATHER_CITY_2));
        cityNameDropShadow.setTypedText(TypedText(T_WEATHER_CITY_2));
        timeAndDate.setTypedText(TypedText(T_WEATHER_TIME_INFO_2));
        timeAndDateDropShadow.setTypedText(TypedText(T_WEATHER_TIME_INFO_2));
        largeIcon.setBitmap(Bitmap(BITMAP_WEATHER_BIG_ICON_SUN_CLOUDS_ID));
        largeIcon.setXY(232, 38);
        startTemperature = 24;
        break;

    case NEW_YORK:
        cityName.setTypedText(TypedText(T_WEATHER_CITY_3));
        cityNameDropShadow.setTypedText(TypedText(T_WEATHER_CITY_3));
        timeAndDate.setTypedText(TypedText(T_WEATHER_TIME_INFO_3));
        timeAndDateDropShadow.setTypedText(TypedText(T_WEATHER_TIME_INFO_3));
        largeIcon.setBitmap(Bitmap(BITMAP_WEATHER_BIG_ICON_THUNDER_ID));
        largeIcon.setXY(232, 42);
        startTemperature = 16;
        break;

    default:
        break;
    }

    setTemperature(startTemperature);

    timeAndDate.setX(cityName.getX() + cityName.getTextWidth() + 16);
    timeAndDateDropShadow.setX(timeAndDate.getX() + 1);

    cityName.invalidate();
    cityNameDropShadow.invalidate();
    timeAndDate.invalidate();
    timeAndDateDropShadow.invalidate();
    largeIcon.invalidate();
}

void CityInfo::setTemperature(int16_t newTemperature)
{
    currentTemperature = newTemperature;
    Unicode::snprintf(largeTemperatureBuffer, 4, "%d", currentTemperature);
    largeTemperature.invalidate();
    largeTemperatureDropShadow.invalidate();
}

void CityInfo::adjustTemperature()
{
    // Make sure that the temperature does not drift too far from the starting point
    if (currentTemperature - 2 == startTemperature)
    {
        setTemperature(currentTemperature - 1);
    }
    else if (currentTemperature + 2 == startTemperature)
    {
        setTemperature(currentTemperature + 1);
    }
    else
    {
        setTemperature(currentTemperature + ((rand() % 2) ? 1 : -1));
    }


}
