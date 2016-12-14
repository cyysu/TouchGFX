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
#ifndef CITY_INFO_HPP_
#define CITY_INFO_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace touchgfx;

class CityInfo : public Container
{
public:
    enum Cities
    {
        COPENHAGEN,
        HONG_KONG,
        MUMBAI,
        NEW_YORK,
        NUMBER_OF_CITIES
    } city;


    CityInfo();

    void setBitmap(BitmapId bg);

    // Set the text color of background related text
    void setTextColor(colortype color)
    {
        textColor = color;
    }
    colortype getTextColor()
    {
        return textColor;
    }

    void setCity(Cities c);
    Cities getCity()
    {
        return city;
    }

    void setTemperature(int16_t newTemperature);
    int16_t getTemperature()
    {
        return currentTemperature;
    }

    // Randomly adjust temperature.
    void adjustTemperature();

private:
    colortype textColor;

    Image background;

    TextArea cityName;
    TextArea cityNameDropShadow;
    TextArea timeAndDate;
    TextArea timeAndDateDropShadow;

    TextAreaWithOneWildcard largeTemperature;
    TextAreaWithOneWildcard largeTemperatureDropShadow;
    Unicode::UnicodeChar largeTemperatureBuffer[5];

    int16_t startTemperature;
    int16_t currentTemperature;
};

#endif /* CITY_INFO_HPP_ */
