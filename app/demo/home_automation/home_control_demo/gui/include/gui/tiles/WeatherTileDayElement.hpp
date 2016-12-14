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
#ifndef WEATHER_TILE_DAY_ELEMENT_HPP
#define WEATHER_TILE_DAY_ELEMENT_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>


class WeatherTileDayElement : public touchgfx::Container
{
public:
    WeatherTileDayElement();
    virtual ~WeatherTileDayElement() {}

    void setIcon(touchgfx::BitmapId iconId);
    void setDayName(TEXTS txt);
    void setDayTemperature(int16_t newTemperature);
    void setNightTemperature(int16_t newTemperature);
private:
    touchgfx::Image icon;

    static const uint8_t TEMP_BUFFER_LENGTH = 5;
    touchgfx::TextArea dayName;
    touchgfx::TextAreaWithOneWildcard dayTemperature;
    touchgfx::Unicode::UnicodeChar dayTemperatureTextBuffer[TEMP_BUFFER_LENGTH];
    touchgfx::TextAreaWithOneWildcard nightTemperature;
    touchgfx::Unicode::UnicodeChar nightTemperatureTextBuffer[TEMP_BUFFER_LENGTH];
};

#endif
