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
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <touchgfx/Color.hpp>

/**
 * Color definitions used by the demo
 */
#define Colors_TEXT_LIGHT Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF)
#define Colors_TEXT_GREY  Color::getColorFrom24BitRGB(0x49, 0x69, 0x70)
#define Colors_TEXT_DARK  Color::getColorFrom24BitRGB(0x2E, 0x49, 0x4F)

/**
 * Defines the timeout before the demo returns to the home screen if no interaction occurs.
 */
#define MAX_INACTIVE_SECONDS 5


#endif
