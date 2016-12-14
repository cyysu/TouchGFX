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
#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <stdint.h>
#include <touchgfx/hal/HAL.hpp>
#include <gui/common/Config.hpp>

#define position(name, x, y, width, height) \
    static pos name() {      \
    pos _ = { static_cast<uint16_t>(x), static_cast<uint16_t>(y), static_cast<uint16_t>(width), static_cast<uint16_t>(height) };      \
    return _;             \
  }

/**
 * Layout is used to define position and size of graphical elements in the demo.
 * Example of how to use the Layout when positioning the menu
 *
 *         menu.setXY(Layout::menu().x, Layout::menu().y);
 *
 */
class Layout
{
public:
    struct pos
    {
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;
    };


    position(menu, 0, touchgfx::HAL::DISPLAY_HEIGHT - 80, touchgfx::HAL::DISPLAY_WIDTH, 80);
    position(content, 0, 0, touchgfx::HAL::DISPLAY_WIDTH, touchgfx::HAL::DISPLAY_HEIGHT - menu().height);
    position(headline, 36, 38, 0, 0); // width and height not used for the headline
    position(clock_tile, 0, 0, 340, 160);

#ifdef RESOLUTION_640X480
    position(appliance_tile, 340, 240, 302, 160);
    position(music_player_tile, 0, 240, 340, 160);
    position(top_tile, 280, 0, 182, 160);
#else
    position(appliance_tile, 400, 240, 402, 160);
    position(music_player_tile, 0, 240, 400, 160);
    position(top_tile, 260, 0, 182, 160);
#endif

    position(weather_tile, 0, 160, touchgfx::HAL::DISPLAY_WIDTH, 80);

};


#endif
