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
#ifndef CLOCK_TILE_HPP
#define CLOCK_TILE_HPP

#include <gui/tiles/BaseTile.hpp>
#include <gui/system/DateTime.hpp>
#include <gui/model/TimeFormat.hpp>
#include <gui/common/FontPosition.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>


/**
 * Implement date and time
 */
class ClockTile : public BaseTile
{
public:
    ClockTile();

    void setTime(const System::DateTime& time);
private:
    FontPosition<touchgfx::TextAreaWithOneWildcard> date;
    FontPosition<touchgfx::TextAreaWithOneWildcard> timeDigits[5];

    static const uint8_t DATE_LENGTH = 50;
    static const uint8_t TIME_LENGTH = 6;
    static const uint8_t MONTH_DAY_LENGTH = 5;
    touchgfx::Unicode::UnicodeChar dateBuffer[DATE_LENGTH];
    touchgfx::Unicode::UnicodeChar timeBuffer[TIME_LENGTH];
    touchgfx::Unicode::UnicodeChar timeSmallBuffer[5][2];
    touchgfx::Unicode::UnicodeChar monthDayBuffer[MONTH_DAY_LENGTH];

    const touchgfx::Unicode::UnicodeChar* getWeekDay(uint8_t wday);
    const touchgfx::Unicode::UnicodeChar* getMonth(uint8_t month);
    const touchgfx::Unicode::UnicodeChar* getMonthDay(uint8_t day);
};

#endif
