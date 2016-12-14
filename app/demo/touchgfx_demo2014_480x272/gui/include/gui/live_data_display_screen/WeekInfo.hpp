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
#ifndef WEEK_INFO_HPP_
#define WEEK_INFO_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/live_data_display_screen/CityInfo.hpp>

using namespace touchgfx;

class WeekInfo : public Container
{
public:
    WeekInfo();

    void setAlpha(int alpha);
    void setTextColor(colortype color);

    void setInfo(CityInfo::Cities city);

private:
    static const int NUMBER_OF_DAYS = 5;

    Image smallIcons[NUMBER_OF_DAYS];
    TextArea days[NUMBER_OF_DAYS];
    TextAreaWithOneWildcard smallTemperature[NUMBER_OF_DAYS];
    TextAreaWithOneWildcard smallTemperatureDropShadow[NUMBER_OF_DAYS];
    Unicode::UnicodeChar smallTemperatureBuffer[5][NUMBER_OF_DAYS];
};

#endif /* WEEK_INFO_HPP_ */
