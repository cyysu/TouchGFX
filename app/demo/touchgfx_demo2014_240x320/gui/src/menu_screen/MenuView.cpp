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
#include <gui/menu_screen/MenuView.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Color.hpp>

MenuView::MenuView() :
    onButtonPressed(this, &MenuView::buttonPressedhandler)
{
}

void MenuView::setupScreen()
{
    backgroundTop.setBitmap(Bitmap(BITMAP_BACKGROUND_TOP_ID));
    backgroundTop.setXY(0, 0);

    backgroundBottom.setBitmap(Bitmap(BITMAP_BACKGROUND_BOTTOM_ID));
    backgroundBottom.setXY(0, HAL::DISPLAY_HEIGHT - backgroundBottom.getHeight());


    liveDataDisplayTile.setXY(TILE_OFFSET, HAL::DISPLAY_HEIGHT - liveDataDisplayTile.getHeight() - TILE_OFFSET);

    homeAutomationTile.setXY(TILE_OFFSET, TILE_OFFSET);

    animatedGraphicsTile.setXY(TILE_OFFSET, homeAutomationTile.getY() + homeAutomationTile.getHeight() + TILE_OFFSET);

    chromArtTile.setXY(animatedGraphicsTile.getX() + animatedGraphicsTile.getWidth() + TILE_OFFSET - 3, animatedGraphicsTile.getY());

    add(backgroundTop);
    add(liveDataDisplayTile);
    add(homeAutomationTile);
    add(animatedGraphicsTile);
    add(chromArtTile);
    add(backgroundBottom);
}

void MenuView::tearDownScreen()
{

}

void MenuView::buttonPressedhandler(const AbstractButton& button)
{

}

void MenuView::addRoomToHomeAutomationTile(RoomTemperatureInfo& room)
{
    homeAutomationTile.getTile().addRoom(room);
}

void MenuView::initializeTiles()
{
    homeAutomationTile.getTile().initialize();
}
