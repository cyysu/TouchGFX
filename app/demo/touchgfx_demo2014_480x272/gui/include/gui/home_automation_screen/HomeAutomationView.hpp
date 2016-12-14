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

#include <gui/common/DemoView.hpp>
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/home_automation_screen/JogWheel.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/home_automation_screen/TemperatureMenuItem.hpp>
#include <gui/home_automation_screen/TemperatureScheduleMenuItem.hpp>

/*
 * HomeAutomation screen implements a temperature control.
 * HomeAutomationView handles the view part of the temperature control.
 * It communicates events to the presenter that takes the appropriate action and
 * stores data in the model.
 */
class HomeAutomationView : public DemoView<HomeAutomationPresenter>
{
public:
    HomeAutomationView();
    virtual ~HomeAutomationView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    // New Info from the presenter
    void insertRoom(RoomTemperatureInfo& room);
    void updateRoom(RoomTemperatureInfo& room);

    void setSelectedMenuItem(RoomTemperatureInfo& room);

    // Save the currently locally held schedule information
    // in the supplied room info object
    void saveScheduleInfo(RoomTemperatureInfo& room);

private:
    enum States
    {
        ANIMATE_SCHEDULE_IN,
        ANIMATE_SCHEDULE_OUT,
        SCHEDULE_STATE,
        JOG_WHEEL_STATE,
        NO_ANIMATION
    } currentState;

    uint8_t animationCounter;

    static const int16_t INITIAL_TEMPERATURE = 10;
    static const int16_t JOGWHEEL_DELTA = 10;

    Image menuTopBar;
    Image menuBottomBar;
    TextArea menuTopBarHeadline;

    // Scrollmenu in jogwheel mode
    ListLayout menu;
    ScrollableContainer scrollableMenu;
    static const uint8_t NUMBER_OF_ROOMS = 8;
    TemperatureMenuItem menuItems[NUMBER_OF_ROOMS];
    uint8_t currentNumberOfRooms;

    // Scrollmenu in schedule mode
    TextArea scheduleMenuTopBarHeadline;
    ListLayout scheduleMenu;
    ScrollableContainer scrollableScheduleMenu;
    TemperatureScheduleMenuItem scheduleMenuItems[RoomTemperatureInfo::NUMBER_OF_DAYS];

    ToggleButton scheduleButton;
    ToggleButton autoButton;
    ToggleButton offButton;

    // Accept schedule button to the right on the screen
    Button scheduleOkButton;

    // Jogwheel widgets
    Container jogWheelContainer;
    JogWheel jogWheel;
    TextAreaWithOneWildcard temperatureText;
    Unicode::UnicodeChar temperatureTextBuffer[5];
    TextArea jogWheelHeadline;

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
    void updateJogWheelOverlay();
    void setupOverlays();

    void setCurrentState(States newState);
    void animateScheduleIn();
    void animateScheduleOut();

    void setScheduleOkButtonState(bool valuesUpdated);
    void setMenuTopBarHeadlineAlpha(int16_t alpha);
    void setScheduleMenuTopBarHeadlineAlpha(int16_t alpha);

};

#endif // HOME_AUTOMATION_VIEW_HPP
