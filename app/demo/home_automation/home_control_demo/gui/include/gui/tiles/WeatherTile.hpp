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
#ifndef WEATHER_TILE_HPP
#define WEATHER_TILE_HPP

#include <gui/tiles/BaseTile.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/tiles/WeatherTileDayElement.hpp>
#include <gui/common/Config.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

/**
 * Shows the weather forecast. An animation slides the individual days from right to left.
 *
 * All data is hardcoded in the view. No model is used.
 */
class WeatherTile : public BaseTile
{
public:
    WeatherTile();
    virtual ~WeatherTile() {}

    virtual void handleTickEvent();
private:

#ifdef RESOLUTION_640X480
    static const int NUMBER_OF_DAYS = 4;
    static const int startPosOfIcons = 40;
#else
    static const int NUMBER_OF_DAYS = 5;
    static const int startPosOfIcons = 30;
#endif

    enum States
    {
        ANIMATE_IN,
        ANIMATE_OUT,
        WEATHER_IN,
        WEATHER_OUT
    } currentState;

    int counter;

    Image background;

    MoveAnimator<WeatherTileDayElement> days[NUMBER_OF_DAYS];
    int daysVisiblePosX[NUMBER_OF_DAYS];
    int daysHiddenPosX[NUMBER_OF_DAYS];
    bool showingCurrentWeek;
    int currentDay; // 0 = monday, 1 = tuesday...

    void setupCurrentFiveDays();
    void setupNextFiveDays();

    void setCurrentState(States newState);

    Callback<WeatherTile, const MoveAnimator<WeatherTileDayElement>&> animationCallback;
    void handleAnimationEvent(const MoveAnimator<WeatherTileDayElement>& obj);
};

#endif
