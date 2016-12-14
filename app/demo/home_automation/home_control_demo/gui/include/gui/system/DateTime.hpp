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
#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <touchgfx/hal/Types.hpp>

namespace System
{

class DateTime
{
public:
    DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour,
             uint8_t minute, uint8_t second, uint8_t wday) :
        year(year), month(month), day(day), hour(hour), minute(minute), second(second), wday(wday)
    {
    }

    DateTime(uint8_t hour, uint8_t minute, uint8_t second) :
        year(1970), month(1), day(1), hour(hour), minute(minute), second(second), wday(0)
    {
    }

    uint16_t getYear() const
    {
        return year;
    }
    uint8_t getMonth() const
    {
        return month;
    }
    uint8_t getDay() const
    {
        return day;
    }
    uint8_t getWeekDay() const
    {
        return wday;
    }
    uint8_t getHour() const
    {
        return hour;
    }

    uint8_t getAmPmHour() const
    {
        return (hour == 0) ? 12 : ((hour > 12) ? hour - 12 : hour);
    }

    bool isAm() const
    {
        return (hour < 12);
    }

    uint8_t getMinute() const
    {
        return minute;
    }
    uint8_t getSecond() const
    {
        return second;
    }

    //NOTE: only approximate difference
    int64_t operator-(DateTime other) const
    {
        return (year - other.getYear())   * 365 * 24 * 60 * 60 +
               (month - other.getMonth()) *  31 * 24 * 60 * 60 +
               (day - other.getDay())           * 24 * 60 * 60 +
               (hour - other.getHour())              * 60 * 60 +
               (minute - other.getMinute())               * 60 +
               (second - other.getSecond());

    }

    bool operator==(const DateTime& other) const
    {
        return year == other.year
               && month == other.month
               && day == other.day
               && hour == other.hour
               && minute == other.minute
               && second == other.second;
    }

    bool operator!=(const DateTime& other) const
    {
        return year != other.year
               || month != other.month
               || day != other.day
               || hour != other.hour
               || minute != other.minute
               || second != other.second;
    }

    static DateTime beginning()
    {
        return DateTime(1970, 1, 1, 0, 0, 0, 0);
    }

private:
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t wday;
};
}

#endif
