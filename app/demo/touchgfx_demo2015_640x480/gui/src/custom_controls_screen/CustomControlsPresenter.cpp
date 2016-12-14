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
#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <gui/custom_controls_screen/CustomControlsView.hpp>
#include <gui/common/FrontendApplication.hpp>

CustomControlsPresenter::CustomControlsPresenter(CustomControlsView& v) :
    DemoPresenter(v),
    view(v)
{
}

CustomControlsPresenter::~CustomControlsPresenter()
{
}

/**
 * Workaround for limitation in touch driver on STM32F7 EVAL board:
 * This touch controller requires very frequent sampling in order to appear responsive.
 */
#if STM32F756xx
static int8_t origTouchSampleRate;
#endif

void CustomControlsPresenter::activate()
{
#if STM32F756xx
    /* Keep track of original samplerate, so we may restore it when leaving this screen */
    origTouchSampleRate = HAL::getInstance()->getTouchSampleRate();

    /* Set default touch sample rate (for this screen only) to 2 */
    HAL::getInstance()->setTouchSampleRate(2);
#endif
}

void CustomControlsPresenter::deactivate()
{
#if STM32F756xx
    /* Restore original setting when leaving this screen. */
    HAL::getInstance()->setTouchSampleRate(origTouchSampleRate);
#endif
}

void CustomControlsPresenter::screenSaverMinorTick()
{
    view.screenSaverMinorTick();
}
