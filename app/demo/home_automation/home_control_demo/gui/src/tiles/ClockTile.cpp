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
#include <gui/tiles/ClockTile.hpp>

#include <gui/tiles/ClockTile.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Constants.hpp>
#include <gui/system/DateTime.hpp>
#include <gui/common/Layout.hpp>

using namespace touchgfx;

ClockTile::ClockTile()
{
    setHeight(Layout::clock_tile().height);
    setWidth(Layout::clock_tile().width);

    date.setColor(Colors_TEXT_GREY);
    date.setTypedText(touchgfx::TypedText(T_DATE_PLACEHOLDER));
    date.setPosition(40, 50, getWidth() - 40);
    date.setWildcard(dateBuffer);
    add(date);

    for (uint8_t i = 0; i < 5; ++i)
    {
        timeDigits[i].setColor(Colors_TEXT_DARK);
        timeDigits[i].setWildcard(timeSmallBuffer[i]);
        add(timeDigits[i]);
    }

    timeDigits[0].setTypedText(touchgfx::TypedText(T_TIME_RIGHT_PLACEHOLDER));
    timeDigits[1].setTypedText(touchgfx::TypedText(T_TIME_CENTER_PLACEHOLDER));
    timeDigits[2].setTypedText(touchgfx::TypedText(T_TIME_CENTER_PLACEHOLDER));
    timeDigits[3].setTypedText(touchgfx::TypedText(T_TIME_LEFT_PLACEHOLDER));
    timeDigits[4].setTypedText(touchgfx::TypedText(T_TIME_LEFT_PLACEHOLDER));

    //timeDigits[0].setPosition(-3, 120, 50);
    timeDigits[0].setPosition(37, 120, 50);
    timeDigits[1].setPosition(timeDigits[0].getX() + 45, 120, 50);
    timeDigits[2].setPosition(timeDigits[1].getX() + 34, 120, 50);
    timeDigits[3].setPosition(timeDigits[2].getX() + 35, 120, 50);
    timeDigits[4].setPosition(timeDigits[3].getX() + 45, 120, 50);
}

void ClockTile::setTime(const System::DateTime& time)
{
    touchgfx::Unicode::snprintf(timeBuffer, TIME_LENGTH, "%i%i:%i%i", time.getHour() / 10, time.getHour() % 10, time.getMinute() / 10, time.getMinute() % 10);

    if (time.getMinute() > 9 && time.getMinute() < 20)
    {
        timeDigits[3].setTypedText(touchgfx::TypedText(T_TIME_CENTER_PLACEHOLDER));
    }
    else
    {
        timeDigits[3].setTypedText(touchgfx::TypedText(T_TIME_LEFT_PLACEHOLDER));
    }

    for (uint8_t i = 0; i < 5; ++i)
    {
        timeSmallBuffer[i][0] = timeBuffer[i];
        timeSmallBuffer[i][1] = '\0';
    }

    touchgfx::Unicode::snprintf(dateBuffer, DATE_LENGTH, "%s %s %s %i", getWeekDay(time.getWeekDay()), getMonth(time.getMonth()), getMonthDay(time.getDay()), time.getYear());
    invalidate();
}

const touchgfx::Unicode::UnicodeChar* ClockTile::getMonthDay(uint8_t day)
{
    touchgfx::Unicode::UnicodeChar ordinalIndicator[3];
    memset(ordinalIndicator, 0, sizeof(ordinalIndicator));

    switch (day)
    {
    case 1:
    case 21:
    case 31:
        ordinalIndicator[0] = touchgfx::Unicode::UnicodeChar('S');
        ordinalIndicator[1] = touchgfx::Unicode::UnicodeChar('T');
        break;
    case 2:
    case 22:
        ordinalIndicator[0] = touchgfx::Unicode::UnicodeChar('N');
        ordinalIndicator[1] = touchgfx::Unicode::UnicodeChar('D');
        break;
    case 3:
    case 23:
        ordinalIndicator[0] = touchgfx::Unicode::UnicodeChar('R');
        ordinalIndicator[1] = touchgfx::Unicode::UnicodeChar('D');
        break;
    default:
        ordinalIndicator[0] = touchgfx::Unicode::UnicodeChar('T');
        ordinalIndicator[1] = touchgfx::Unicode::UnicodeChar('H');
        break;
    }

    touchgfx::Unicode::snprintf(monthDayBuffer, MONTH_DAY_LENGTH, "%u%s", day, ordinalIndicator);
    return monthDayBuffer;
}

const touchgfx::Unicode::UnicodeChar* ClockTile::getWeekDay(uint8_t wday)
{
    const uint8_t numberOfWeekDays = 7;
    touchgfx::TypedTextId weekDays[numberOfWeekDays] = { T_DAY_SUNDAY, T_DAY_MONDAY, T_DAY_TUESDAY, T_DAY_WEDNESDAY, T_DAY_THURSDAY, T_DAY_FRIDAY, T_DAY_SATURDAY };

    if (wday < numberOfWeekDays)
    {
        return touchgfx::TypedText(weekDays[wday]).getText();
    }
    return touchgfx::TypedText().getText();
}

// month is between 1..12
const touchgfx::Unicode::UnicodeChar* ClockTile::getMonth(uint8_t month)
{
    month -= 1;

    const uint8_t numberOfMonth = 12;
    touchgfx::TypedTextId months[numberOfMonth] = { T_MONTH_JAN, T_MONTH_FEB, T_MONTH_MAR, T_MONTH_APR, T_MONTH_MAJ, T_MONTH_JUN, T_MONTH_JUL, T_MONTH_AUG, T_MONTH_SEP, T_MONTH_OCT, T_MONTH_NOV, T_MONTH_DEC };

    if (month < numberOfMonth)
    {
        return touchgfx::TypedText(months[month]).getText();
    }
    return touchgfx::TypedText().getText();
}
