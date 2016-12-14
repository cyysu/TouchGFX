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
#include <gui/game2D_screen/Game2DPresenter.hpp>
#include <gui/game2D_screen/Game2DView.hpp>
#include <gui/common/FrontendApplication.hpp>

Game2DPresenter::Game2DPresenter(Game2DView& v) :
    DemoPresenter(v),
    view(v)
{
}

Game2DPresenter::~Game2DPresenter()
{
}

/**
 * Workaround for limitation in exc7200 touch driver on STM32F4 EVAL board:
 * This touch controller requires very frequent sampling in order to appear responsive.
 * On this particular screen, rendering times are quite long, so we must sample touch
 * every frame when running on this board.
 */
#if STM32F429xx || STM32F756xx
static int8_t origTouchSampleRate;
#endif

void Game2DPresenter::activate()
{

#if STM32F429xx || STM32F756xx
    /* Keep track of original samplerate, so we may restore it when leaving this screen */
    origTouchSampleRate = HAL::getInstance()->getTouchSampleRate();
#endif

#if STM32F429xx
    /* Set default touch sample rate (for this screen only) to 1 */
    origTouchSampleRate = HAL::getInstance()->getTouchSampleRate();
    HAL::getInstance()->setTouchSampleRate(1);
#endif

#if STM32F756xx
    /* Set default touch sample rate (for this screen only) to 2 */
    HAL::getInstance()->setTouchSampleRate(2);
#endif
    // ensure the timeliness of the animations
    HAL::getInstance()->setFrameRateCompensation(true);
}

void Game2DPresenter::deactivate()
{
#if STM32F429xx || STM32F756xx
    /* Restore original setting when leaving this screen. */
    HAL::getInstance()->setTouchSampleRate(origTouchSampleRate);
#endif
    HAL::getInstance()->setFrameRateCompensation(false);
}
