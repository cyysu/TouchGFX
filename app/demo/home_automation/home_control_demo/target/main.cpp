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
volatile bool overrideBlitcaps = false;

#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <gui/system/Clock.hpp>

using namespace touchgfx;

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * Define the FreeRTOS task priorities and stack sizes
 */
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )

#define configGUI_TASK_STK_SIZE                 ( 1500 )


static volatile long lastUs;
extern uint32_t SystemCoreClock;
static int freqMHz;

class TargetClock : public System::Clock
{
public:
    TargetClock() : differenceInSeconds(0)
    {
        lastUs = HAL::getInstance()->getCPUCycles();
        freqMHz = SystemCoreClock / 1000000;
    }
    virtual ~TargetClock() { }
    virtual System::DateTime getTime()
    {

        static int milliseconds = 100000;

        long now = HAL::getInstance()->getCPUCycles();
        milliseconds += (now - lastUs + freqMHz / 2) / freqMHz / 1000;
        lastUs = now;

        return System::DateTime(2014, 8, 2, (9 + (milliseconds / 1000 / 60 / 60)) % 24, (milliseconds / 1000 / 60) % 60, (milliseconds / 1000) % 60, 1);
    }

protected:
    virtual void setTimeInternal(const System::DateTime& dateTime)
    {
        differenceInSeconds = 32400;
    }

    int64_t differenceInSeconds;
};

static void GUITask(void* params)
{
    touchgfx::HAL::getInstance()->taskEntry();
}

static System::Clock* getClock()
{
    static TargetClock clock;
    return &clock;
}

int main(void)
{
    hw_init();
    touchgfx_init();

    System::ClockFactory::setClock(getClock());

    xTaskCreate(GUITask, (TASKCREATE_NAME_TYPE)"GUITask",
                configGUI_TASK_STK_SIZE,
                NULL,
                configGUI_TASK_PRIORITY,
                NULL);

    vTaskStartScheduler();

    for (;;);
}

