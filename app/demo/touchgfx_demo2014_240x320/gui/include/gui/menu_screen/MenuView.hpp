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
#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>
#include <gui/menu_screen/Tile.hpp>
#include <gui/menu_screen/LiveDataDisplayTile.hpp>
#include <gui/menu_screen/HomeAutomationTile.hpp>
#include <gui/menu_screen/AnimatedGraphicsTile.hpp>
#include <gui/menu_screen/ChromArtTile.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>

class MenuView : public View<MenuPresenter>
{
public:

    MenuView();

    virtual ~MenuView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void addRoomToHomeAutomationTile(RoomTemperatureInfo& room);
    void initializeTiles();

private:
    static const int TILE_OFFSET = 17;

    Image backgroundTop;
    Image backgroundBottom;

    Tile<LiveDataDisplayTile> liveDataDisplayTile;
    Tile<HomeAutomationTile> homeAutomationTile;
    Tile<AnimatedGraphicsTile> animatedGraphicsTile;
    Tile<ChromArtTile> chromArtTile;

    Callback<MenuView, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);
};

#endif // MENU_VIEW_HPP
