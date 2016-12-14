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
#include <gui/home_screen/HomeView.hpp>
#include <gui/common/Config.hpp>

HomeView::HomeView() :
#ifdef RESOLUTION_640X480
    tumbleDryerTile(Bitmap(BITMAP_TUMBLE_DRYER_TILE_SMALL_ID), true),
    diskwasherTile(Bitmap(BITMAP_DISHWASHER_TILE_SMALL_ID), false),
#else
    tumbleDryerTile(Bitmap(BITMAP_TUMBLE_DRYER_TILE_ID), true),
    diskwasherTile(Bitmap(BITMAP_DISHWASHER_TILE_ID), false),
#endif
    topTiles(EAST),
    airConTile(Bitmap(BITMAP_AIR_CON_TOP_ID), true),
    roomLightingTile(Bitmap(BITMAP_LIGHTING_TOP_ID), true),
    windowBlindsTile(Bitmap(BITMAP_BLINDS_TOP_ID), false),
    swipeContainer(Layout::appliance_tile().width, Layout::appliance_tile().height)
{
}

void HomeView::setupScreen()
{
    baseview::setupScreen();

    musicPlayerCoverClicked = Callback<HomePresenter>(this->presenter, &HomePresenter::musicPlayerCoverClicked);
    musicPlayerPlayPauseClicked = Callback<HomePresenter>(this->presenter, &HomePresenter::musicPlayerPlayPauseClicked);
    musicPlayerTile.setCoverClickedAction(musicPlayerCoverClicked);
    musicPlayerTile.setPlayPauseAction(musicPlayerPlayPauseClicked);

    weatherTile.setXY(Layout::weather_tile().x, Layout::weather_tile().y);
    musicPlayerTile.setXY(Layout::music_player_tile().x, Layout::music_player_tile().y);
    swipeContainer.setXY(Layout::appliance_tile().x, Layout::appliance_tile().y);

    clockTile.setXY(Layout::clock_tile().x, Layout::clock_tile().y);
    clockTile.setTime(System::DateTime::beginning());

    swipeContainer.add(washingMachineTile);
    swipeContainer.add(tumbleDryerTile);
    swipeContainer.add(diskwasherTile);

    topTiles.setXY(Layout::top_tile().x, Layout::top_tile().y);
    topTiles.add(airConTile);
    topTiles.add(roomLightingTile);
#ifndef RESOLUTION_640X480
    topTiles.add(windowBlindsTile);
#endif

    content.add(topTiles);
    content.add(clockTile);
    content.add(weatherTile);
    content.add(musicPlayerTile);
    content.add(swipeContainer);
}

void HomeView::tearDownScreen()
{
}

void HomeView::setTopTilesValue(int16_t airCon, int16_t lighting, int16_t blinds)
{
    airConTile.setValue(airCon);
    roomLightingTile.setValue(lighting);
    windowBlindsTile.setValue(blinds);
}
