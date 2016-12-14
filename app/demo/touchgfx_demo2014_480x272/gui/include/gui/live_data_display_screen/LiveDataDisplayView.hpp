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
#ifndef LIVE_DATA_DISPLAY_VIEW_HPP
#define LIVE_DATA_DISPLAY_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayPresenter.hpp>
#include <gui/live_data_display_screen/CityInfo.hpp>
#include <gui/live_data_display_screen/WeekInfo.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/common/DotIndicator.hpp>

/* The LiveDataDisplay screen implements a weather forecast.
 * The LiveDataDisplayView class handles the visible part of the weather screen.
 * In this demo only static data are used. This data is placed in the
 * view related classes. In a real world example this will be placed in
 * the model and changed dynamically.
 */
class LiveDataDisplayView : public DemoView<LiveDataDisplayPresenter>
{
public:
    LiveDataDisplayView();
    virtual ~LiveDataDisplayView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);

private:
    enum States
    {
        ANIMATE_SWIPE_CANCELLED_LEFT,
        ANIMATE_SWIPE_CANCELLED_RIGHT,
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    } currentState;

    static const uint8_t NUMBER_OF_SCREENS = 4;

    uint8_t animationCounter;
    int32_t tickCounter;

    int16_t dragX;
    int16_t animateDistance;
    int16_t startX;
    uint8_t currentScreen;

    // Shadow next to the back button. Gives an effect that
    // the background image is swiped under the button.
    Image backButtonShadow;

    // Background that becomes visible when trying to swipe
    // beyond the number of screens.
    Image backgroundSwipeAreaLeft;
    Image backgroundSwipeAreaRight;

    DotIndicator dotIndicator;

    // Info screens show the specific data for a city.
    // The viewport represents the visible part of the
    // swipe area
    Container infoScreensViewPort;
    ListLayout infoScreens;

    CityInfo infoScreen[4];

    // Week specific weather data are displayed by the
    // WeekInfo class.
    WeekInfo weekInfoBar;

    void adjustInfoScreens();

    void animateSwipeCancelledLeft();
    void animateSwipeCancelledRight();
    void animateLeft();
    void animateRight();
};

#endif // LIVE_DATA_DISPLAY_VIEW_HPP
