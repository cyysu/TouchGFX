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
#ifndef HOME_VIEW_HPP
#define HOME_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/home_screen/HomePresenter.hpp>
#include <gui/tiles/WeatherTile.hpp>
#include <gui/tiles/ClockTile.hpp>
#include <gui/tiles/WashingMachineTile.hpp>
#include <gui/tiles/MusicPlayerTile.hpp>
#include <gui/tiles/TopTile.hpp>
#include <gui/common/SwipeContainer.hpp>
#include <gui/tiles/ImageTile.hpp>

using namespace touchgfx;

/**
 * HomeView - home control overview
 *
 * The home screen contains a number of tiles showing information for a home control system. The screen contains the following
 * information.
 *
 * Date and time
 * Temperature, lighting and blinds setting
 * Weather forecast - animated
 * Music player - current album playing
 * A swipe container containing
 *   - a simulated washing machine
 *   - a tumble dryer
 *   - a dishwasher
 */
class HomeView : public BaseView<HomePresenter>
{
public:
    HomeView();

    virtual ~HomeView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void setTopTilesValue(int16_t airCon, int16_t lighting, int16_t blinds);

    ClockTile clockTile;
    WashingMachineTile washingMachineTile;
    ImageTile tumbleDryerTile;
    ImageTile diskwasherTile;
    MusicPlayerTile musicPlayerTile;
private:
    WeatherTile weatherTile;

    ListLayout topTiles;
    TopTile airConTile;
    TopTile roomLightingTile;
    TopTile windowBlindsTile;

    SwipeContainer swipeContainer;

    Callback<HomePresenter> musicPlayerCoverClicked;
    Callback<HomePresenter> musicPlayerPlayPauseClicked;
};

#endif
