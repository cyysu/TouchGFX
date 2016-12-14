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
#ifndef SYSTEM_CLOCK_HPP
#define SYSTEM_CLOCK_HPP

#include <gui/system/DateTime.hpp>


namespace System
{


class TimeChangeListener
{
public:
    virtual ~TimeChangeListener() {}
    virtual void handleTimeChange(const DateTime& dateTime) {}
};


class Clock
{
public:
    Clock() :
        listener(0)
    {}

    virtual ~Clock() {}
    void setTimeChangeListener(TimeChangeListener* listener)
    {
        this->listener = listener;
    }
    void setTime(const DateTime& dateTime)
    {
        setTimeInternal(dateTime);
        if (listener)
        {
            listener->handleTimeChange(dateTime);
        }
    }
    virtual DateTime getTime()
    {
        return DateTime::beginning();
    }
protected:
    virtual void setTimeInternal(const DateTime& dateTime) {}

    TimeChangeListener* listener;
};

class ClockFactory
{
public:
    static Clock* getClock();
    static void setClock(Clock* c);
private:
    static Clock* clock;
};
}

#endif

