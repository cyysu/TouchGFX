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
#ifndef HOME_AUTOMATION_VIEW_HPP
#define HOME_AUTOMATION_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/home_automation_screen/JogWheel.hpp>
#include <gui/home_automation_screen/TemperatureMenuItem.hpp>
#include <gui/home_automation_screen/TemperatureScheduleMenuItem.hpp>
#include <gui/home_automation_screen/TemperatureSlider.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>

class HomeAutomationView : public View<HomeAutomationPresenter>
{
public:

    HomeAutomationView();

    virtual ~HomeAutomationView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    // New Info from the presenter
    void insertRoom(RoomTemperatureInfo& room);
    void updateRoom(RoomTemperatureInfo& room);

    void setSelectedMenuItem(RoomTemperatureInfo& room);
    void saveScheduleInfo(RoomTemperatureInfo& room);

private:
    enum States
    {
        ANIMATE_JOG_WHEEL_IN,
        ANIMATE_JOG_WHEEL_OUT,
        ANIMATE_SCHEDULE_IN,
        ANIMATE_SCHEDULE_OUT,
        JOG_WHEEL_STATE,
        SCHEDULE_STATE,
        ROOM_STATE
    } currentState;

    uint8_t animationCounter;

    static const int16_t INITIAL_TEMPERATURE = 6;
    static const int16_t JOGWHEEL_DELTA = 6;

    Image menuTopBar;
    TextArea menuTopBarHeadline;
    Button scheduleButton;
    Button adjustTempButton;
    Button exitButton;

    // Scroll menu in jog wheel mode
    ListLayout menu;
    ScrollableContainer scrollableMenu;
    static const uint8_t NUMBER_OF_ROOMS = 8;
    TemperatureMenuItem menuItems[NUMBER_OF_ROOMS];
    uint8_t currentNumberOfRooms;
    TEXTS selectedRoomName;

    // Jog wheel widgets
    Container jogWheelContainer;
    JogWheel jogWheel;
    TextAreaWithOneWildcard temperatureText;
    Unicode::UnicodeChar temperatureTextBuffer[5];
    Button okButton;
    Button backButton;

    // Scrollmenu in schedule mode
    TextArea scheduleMenuTopBarHeadline;
    Image scheduleDayNightImage;
    ListLayout scheduleMenu;
    ScrollableContainer scrollableScheduleMenu;
    TemperatureScheduleMenuItem scheduleMenuItems[RoomTemperatureInfo::NUMBER_OF_DAYS];

    TemperatureSlider slider;
    Image sliderBackground;

    Callback<HomeAutomationView, const AbstractButton&> onButtonPressed;
    Callback<HomeAutomationView, int16_t> onJogWheelValueChanged;
    Callback<HomeAutomationView, int16_t> onJogWheelEndDragEvent;
    Callback<HomeAutomationView, const TemperatureMenuItem&> onMenuItemSelected;
    Callback<HomeAutomationView, const TemperatureScheduleMenuItem&> onScheduleMenuItemSelected;
    Callback<HomeAutomationView, const TemperatureScheduleMenuItem&> onScheduleMenuItemValueUpdated;

    void buttonPressedhandler(const AbstractButton& button);
    void jogWheelValueChanged(int16_t value);
    void jogWheelEndDragEvent(int16_t value);
    void menuItemSelected(const TemperatureMenuItem&);
    void scheduleMenuItemSelected(const TemperatureScheduleMenuItem&);
    void scheduleMenuItemValueUpdated(const TemperatureScheduleMenuItem&);

    void setCurrentState(States newState);
    void animateJogWheelIn();
    void animateJogWheelOut();
    void animateScheduleIn();
    void animateScheduleOut();

    void showRoomElements(uint8_t startAlpha);
    void showScheduleElements(uint8_t startAlpha);
    void setActiveStateForRoomElements(bool active);
    void setActiveStateForScheduleElements(bool active);
    void setAlphaForRoomElements(uint8_t alpha);
    void setAlphaForScheduleElements(uint8_t alpha);
    void hideAllElements();

    void setOkButtonState(bool valuesUpdated);

};

#endif // HOME_AUTOMATION_VIEW_HPP
