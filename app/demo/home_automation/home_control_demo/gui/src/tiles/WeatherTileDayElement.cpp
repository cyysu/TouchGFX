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
#include <gui/tiles/WeatherTileDayElement.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/Constants.hpp>

using namespace touchgfx;


WeatherTileDayElement::WeatherTileDayElement()
{
    icon.setXY(0, 10);

    dayName.setColor(Colors_TEXT_GREY);
    dayName.setXY(50, 2);

    dayTemperature.setColor(Colors_TEXT_DARK);
    dayTemperature.setTypedText(TypedText(T_DAY_TEMPERATURE));
    dayTemperature.setWildcard(dayTemperatureTextBuffer);
    dayTemperature.setXY(50, 46 - TypedText(T_DAY_TEMPERATURE).getFont()->getFontHeight());

    nightTemperature.setColor(Colors_TEXT_GREY);
    nightTemperature.setTypedText(TypedText(T_NIGHT_TEMPERATURE));
    nightTemperature.setWildcard(nightTemperatureTextBuffer);
    nightTemperature.setXY(98, 46 - TypedText(T_NIGHT_TEMPERATURE).getFont()->getFontHeight());

    add(icon);
    add(dayName);
    add(dayTemperature);
    add(nightTemperature);

    setWidth(140);
    setHeight(56);
}

void WeatherTileDayElement::setIcon(BitmapId iconId)
{
    icon.setBitmap(Bitmap(iconId));
}

void WeatherTileDayElement::setDayName(TEXTS txt)
{
    dayName.setTypedText(TypedText(txt));
    dayName.resizeToCurrentText();
    dayName.invalidate();
}

void WeatherTileDayElement::setDayTemperature(int16_t newTemperature)
{
    Unicode::snprintf(dayTemperatureTextBuffer, TEMP_BUFFER_LENGTH, "%d", newTemperature);
    dayTemperature.resizeToCurrentText();
    dayTemperature.invalidate();
}

void WeatherTileDayElement::setNightTemperature(int16_t newTemperature)
{
    Unicode::snprintf(nightTemperatureTextBuffer, TEMP_BUFFER_LENGTH, "%d", newTemperature);
    nightTemperature.resizeToCurrentText();
    nightTemperature.invalidate();
}
