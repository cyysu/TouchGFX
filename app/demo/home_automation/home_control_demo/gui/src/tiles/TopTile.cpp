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
#include <gui/tiles/TopTile.hpp>
#include <BitmapDatabase.hpp>

#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Constants.hpp>
#include <gui/common/Layout.hpp>

using namespace touchgfx;

TopTile::TopTile(const touchgfx::Bitmap& bg, bool showVerticalSeparator) :
    background(bg)
{
    memset(valueTextBuffer, 0, sizeof(valueTextBuffer));

    setHeight(Layout::top_tile().height);
    setWidth(Layout::top_tile().width);

    background.setXY(27, 60);

    verticalSeparator.setBitmap(touchgfx::Bitmap(BITMAP_VERT_LINE_TOP_ID));
    verticalSeparator.setXY(getWidth() - verticalSeparator.getWidth(), 60);

    valueText.setTypedText(TypedText(T_TOP_TILE_VALUE));
    valueText.setPosition(43, 110, 90);
    valueText.setColor(Colors_TEXT_DARK);
    valueText.setWildcard(valueTextBuffer);

    add(background);
    add(valueText);
    if (showVerticalSeparator)
    {
        add(verticalSeparator);
    }
}

void TopTile::setValue(int16_t newValue)
{
    Unicode::snprintf(valueTextBuffer, BUFFER_LENGTH, "%d", newValue);
    valueText.invalidate();
}


