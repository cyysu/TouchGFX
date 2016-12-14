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
#include <platform/hal/simulator/sdl/HALSDL.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <common/TouchGFXInit.hpp>
#include <gui/system/Clock.hpp>
#include <platform/driver/touch/SDLTouchController.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <platform/driver/lcd/LCD16bpp.hpp>
#elif USE_BPP==24
#include <platform/driver/lcd/LCD24bpp.hpp>
#elif USE_BPP==1
#include <platform/driver/lcd/LCD1bpp.hpp>
#endif

#include <gui/common/Config.hpp>
#include <time.h>

#ifdef __GNUC__
#include <string.h> // memcpy
#define localtime_s(_tm, time) memcpy(_tm, localtime(time), sizeof(tm))
#endif

/**
 * Implementation of the clock used on windows.
 */
class WindowsClock : public System::Clock
{
public:
    WindowsClock() : differenceInSeconds(0) { }
    virtual ~WindowsClock() { }
    virtual System::DateTime getTime()
    {
        time_t now = time(0);
        time_t result = now + differenceInSeconds;

        tm local;
        localtime_s(&local, &result);

        return System::DateTime(1900 + local.tm_year, 1 + local.tm_mon, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec, local.tm_wday);
    }
protected:
    virtual void setTimeInternal(const System::DateTime& dateTime)
    {
        time_t now = time(0);

        tm local;
        localtime_s(&local, &now);
        local.tm_year = dateTime.getYear() - 1900;
        local.tm_mon  = dateTime.getMonth() - 1;
        local.tm_mday = dateTime.getDay();
        local.tm_hour = dateTime.getHour();
        local.tm_min  = dateTime.getMinute();
        local.tm_sec  = dateTime.getSecond();

        time_t desired = mktime(&local);

        differenceInSeconds = desired - now;
    }

    int64_t differenceInSeconds;
};

int main(int argc, char** argv)
{
    touchgfx::NoDMA dma; //For windows/linux, DMA transfers are simulated
#if !defined(USE_BPP) || USE_BPP==16
    touchgfx::LCD16bpp lcd;
#elif USE_BPP==24
    touchgfx::LCD24bpp lcd;
#elif USE_BPP==1
    touchgfx::LCD1bpp lcd;
#endif
    touchgfx::SDLTouchController tc;
    WindowsClock clock;

#ifdef RESOLUTION_640X480
    // Create hardware layer. Use a display size of 640x480.
    touchgfx::HAL& hal = touchgfx_generic_init<HALSDL>(dma, lcd, tc, 640, 480, 0, 0);
#else
    // Create hardware layer. Use a display size of 800x480.
    touchgfx::HAL& hal = touchgfx_generic_init<HALSDL>(dma, lcd, tc, 800, 480, 0, 0);
#endif

    // Initialize SDL
    if (!dynamic_cast<HALSDL&>(hal).sdl_init(argc, argv))
    {
        return -1;
    }

    System::ClockFactory::setClock(&clock);

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return 0;
}
