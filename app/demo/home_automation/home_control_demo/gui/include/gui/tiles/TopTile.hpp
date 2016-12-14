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
#ifndef AIRCON_TILE_HPP
#define AIRCON_TILE_HPP

#include <gui/tiles/BaseTile.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/Constants.hpp>
#include <gui/common/FontPosition.hpp>

/**
 * TopTile used to show a simple value with a fixed background.
 */
class TopTile : public BaseTile
{
public:
    TopTile(const touchgfx::Bitmap& bg, bool showVerticalSeparator);

    void setValue(int16_t newValue);
private:
    static const uint8_t BUFFER_LENGTH = 5;

    touchgfx::Image background;
    touchgfx::Image verticalSeparator;
    FontPosition<touchgfx::TextAreaWithOneWildcard> valueText;
    touchgfx::Unicode::UnicodeChar valueTextBuffer[BUFFER_LENGTH];
};

#endif
