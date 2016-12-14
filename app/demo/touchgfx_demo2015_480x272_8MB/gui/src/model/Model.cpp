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
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>

#ifdef SIMULATOR
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
#else

static volatile long lastUs;
extern uint32_t SystemCoreClock;
static int freqMHz;
#endif /* SIMULATOR */

Model::Model() :
    modelListener(0),
    mcuLoadActive(true),
    selectedMenuIndex(0)
{
#ifndef SIMULATOR
    lastUs = touchgfx::HAL::getInstance()->getCPUCycles();
    freqMHz = SystemCoreClock / 1000000;
#endif
}

#ifndef SIMULATOR
//extern volatile uint32_t mcu_load_pct;
static uint8_t mcuLoadLast = 0;
#endif // SIMULATOR

void Model::tick()
{
    Time previousTime = currentTime;

#ifdef SIMULATOR
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    currentTime.hours =   timenow.tm_hour;
    currentTime.minutes = timenow.tm_min;
    currentTime.seconds = timenow.tm_sec;
    currentTime.milliseconds = 0;

#else
    timeval timenow;
    gettimeofday(&timenow, NULL);

    currentTime.hours = (timenow.tv_sec / 60 / 60) % 24;
    currentTime.minutes = (timenow.tv_sec / 60) % 60;
    currentTime.seconds = timenow.tv_sec % 60;
    currentTime.milliseconds = timenow.tv_usec / 1000;
#endif  /*_MSC_VER*/
#else
    static int milliseconds = 123456;
    uint8_t mcuLoadPct = touchgfx::HAL::getInstance()->getMCULoadPct();
    if (mcuLoadLast != /*mcu_load_pct*/ mcuLoadPct)
    {
        mcuLoadLast = mcuLoadPct;
        modelListener->mcuLoadUpdated(mcuLoadLast);
    }

    //long now = cpu_cycles();
    long now = touchgfx::HAL::getInstance()->getCPUCycles();
    milliseconds += (now - lastUs + freqMHz / 2) / freqMHz / 1000;
    lastUs = now;
    currentTime.hours = (milliseconds / 1000 / 60 / 60) % 24;
    currentTime.minutes = (milliseconds / 1000 / 60) % 60;
    currentTime.seconds = (milliseconds / 1000) % 60;
    currentTime.milliseconds = milliseconds % 1000;

#endif /* SIMULATOR */

    if (currentTime.seconds != previousTime.seconds)
    {
        if (modelListener)
        {
            modelListener->timeUpdated(currentTime);
        }
    }
}

void Model::screenSaverMinorTick()
{
    modelListener->screenSaverMinorTick();
}

void Model::screenSaverMajorTick()
{
    modelListener->screenSaverMajorTick();
}

