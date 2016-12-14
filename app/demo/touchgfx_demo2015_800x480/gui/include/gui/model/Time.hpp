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
#ifndef TIME_HPP
#define TIME_HPP

#include <touchgfx/hal/Types.hpp>

struct Time
{
    Time() : hours(0), minutes(0), seconds(0), milliseconds(0) {}

    explicit Time(int ms)
    {
        hours = ms / 3600000;
        ms -= hours * 3600000;
        minutes = ms / 60000;
        ms -= minutes * 60000;
        seconds = ms / 1000;
        ms -= seconds * 1000;
        milliseconds = ms;
    }

    Time(uint8_t h, uint8_t m, uint8_t s, uint16_t millis) : hours(h), minutes(m), seconds(s), milliseconds(millis) {}

    bool operator==(const Time& other) const
    {
        return ((hours == other.hours) &&
                (minutes == other.minutes) &&
                (seconds == other.seconds) &&
                (milliseconds == other.milliseconds));
    }

    bool operator!=(const Time& other) const
    {
        return !(*this == other);
    }

    // Returns the time difference as count of milliseconds
    long operator-(const Time& other) const
    {
        int diff = (hours - other.hours) * 60 * 60 * 1000 +
                   (minutes - other.minutes) * 60 * 1000 +
                   (seconds - other.seconds) * 1000 +
                   (milliseconds - other.milliseconds);
        if (diff < 0)
        {
            diff += 24 * 60 * 60 * 1000;
        }
        return diff;
    }

    static float toSeconds(long milliseconds)
    {
        return milliseconds / (float) 1000.0;
    }

    bool hasValue() const
    {
        return ((hours > 0) ||
                (minutes > 0) ||
                (seconds > 0) ||
                (milliseconds > 0));
    }

    int getValueInSeconds() const
    {
        return hours * 3600 + minutes * 60 + seconds;
    }

    int getValueInMillis() const
    {
        return getValueInSeconds() * 1000 + milliseconds;
    }

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;
};

#endif /* TIME_HPP */
