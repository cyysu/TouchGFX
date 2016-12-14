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
#include <gui/home_automation_screen/HomeAutomationView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>


HomeAutomationView::HomeAutomationView() :
    DemoView(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    jogWheel(INITIAL_TEMPERATURE, JOGWHEEL_DELTA),
    onButtonPressed(this, &HomeAutomationView::buttonPressedhandler),
    onJogWheelValueChanged(this, &HomeAutomationView::jogWheelValueChanged),
    onJogWheelEndDragEvent(this, &HomeAutomationView::jogWheelEndDragEvent),
    onMenuItemSelected(this, &HomeAutomationView::menuItemSelected),
    onScheduleMenuItemSelected(this, &HomeAutomationView::scheduleMenuItemSelected),
    onScheduleMenuItemValueUpdated(this, &HomeAutomationView::scheduleMenuItemValueUpdated)
{
}

HomeAutomationView::~HomeAutomationView()
{
}

void HomeAutomationView::setupScreen()
{
    menuTopBar.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_TOP_ID));
    menuTopBar.setXY(backButton.getWidth(), 0);

    menuBottomBar.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_BOTTOM_ID));
    menuBottomBar.setXY(backButton.getWidth(), HAL::DISPLAY_HEIGHT - menuBottomBar.getHeight());

    menuTopBarHeadline.setPosition(backButton.getWidth() + 6, 6, 160, 20);
    menuTopBarHeadline.setTypedText(TypedText(T_TEMPERATURE_MENU_HEADLINE));
    menuTopBarHeadline.setColor(Color::getColorFrom24BitRGB(0x11, 0x9A, 0xEB));

    scheduleButton.setBitmaps(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_BUTTON_ID), Bitmap(BITMAP_TEMPERATURE_SCHEDULE_BUTTON_PRESSED_ID));
    scheduleButton.setXY(menuBottomBar.getX() + 8, 232);
    scheduleButton.setAction(onButtonPressed);

    autoButton.setBitmaps(Bitmap(BITMAP_TEMPERATURE_AUTO_BUTTON_ID), Bitmap(BITMAP_TEMPERATURE_AUTO_BUTTON_PRESSED_ID));
    autoButton.setXY(menuBottomBar.getX() + 96, 232);
    autoButton.setAction(onButtonPressed);
    autoButton.forceState(false);

    offButton.setBitmaps(Bitmap(BITMAP_TEMPERATURE_OFF_BUTTON_ID), Bitmap(BITMAP_TEMPERATURE_OFF_BUTTON_PRESSED_ID));
    offButton.setXY(autoButton.getX() + autoButton.getWidth(), 232);
    offButton.setAction(onButtonPressed);
    offButton.forceState(!autoButton.getState());

    setScheduleOkButtonState(false);
    scheduleOkButton.setXY(HAL::DISPLAY_WIDTH - scheduleOkButton.getWidth(), 0);
    scheduleOkButton.setAction(onButtonPressed);

    jogWheel.setBitmaps(Bitmap(BITMAP_TEMPERATURE_JOGWHEEL_ID), Bitmap(BITMAP_TEMPERATURE_JOGWHEEL_PRESSED_ID));
    jogWheelContainer.setPosition(HAL::DISPLAY_WIDTH - jogWheel.getWidth(), 0, jogWheel.getWidth(), jogWheel.getHeight());
    jogWheel.setXY(0, 0);
    jogWheel.setValueUpdatedCallback(onJogWheelValueChanged);
    jogWheel.setEndDragEventCallback(onJogWheelEndDragEvent);

    jogWheelHeadline.setPosition(0, 16, jogWheelContainer.getWidth(), 24);
    jogWheelHeadline.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    jogWheelHeadline.setTypedText(TypedText(T_TEMPERATURE_ROOM0_HEADLINE));

    temperatureText.setPosition(74, 128, 100, 40);
    temperatureText.setTypedText(TypedText(T_TEMPERATUREINDICATOR));
    temperatureText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    temperatureText.setWildcard(temperatureTextBuffer);
    jogWheelValueChanged(INITIAL_TEMPERATURE);

    jogWheelContainer.add(jogWheel);
    jogWheelContainer.add(jogWheelHeadline);
    jogWheelContainer.add(temperatureText);


    scrollableMenu.setXY(backButton.getWidth(), menuTopBar.getY() + menuTopBar.getHeight());
    scrollableMenu.setWidth(scheduleOkButton.getX() - backButton.getWidth());
    scrollableMenu.setHeight(menuBottomBar.getY() - scrollableMenu.getY());
    scrollableMenu.add(menu);
    scrollableMenu.setScrollbarsVisible(false);
    scrollableMenu.enableHorizontalScroll(false);
    menu.setXY(0, 0);
    currentNumberOfRooms = 0;

    scheduleMenuTopBarHeadline.setPosition(menuTopBarHeadline.getX(), menuTopBarHeadline.getY(), 200, 20);
    scheduleMenuTopBarHeadline.setTypedText(TypedText(T_TEMPERATURE_MENU_HEADLINE));
    scheduleMenuTopBarHeadline.setColor(Color::getColorFrom24BitRGB(0x11, 0x9A, 0xEB));
    scheduleMenuTopBarHeadline.setAlpha(0);

    scheduleMenu.setXY(0, 0);
    for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
    {
        scheduleMenuItems[i].setWeekday((RoomTemperatureInfo::weekday)(RoomTemperatureInfo::MONDAY + i));
        scheduleMenuItems[i].setMenuItemSelectedCallback(onScheduleMenuItemSelected);
        scheduleMenuItems[i].setMenuItemValueUpdatedCallback(onScheduleMenuItemValueUpdated);
        scheduleMenu.add(scheduleMenuItems[i]);
    }

    scrollableScheduleMenu.setXY(backButton.getWidth(), menuTopBar.getY() + menuTopBar.getHeight());
    scrollableScheduleMenu.setWidth(scheduleOkButton.getX() - backButton.getWidth());
    scrollableScheduleMenu.setHeight(menuBottomBar.getY() - scrollableMenu.getY());
    scrollableScheduleMenu.add(scheduleMenu);
    scrollableScheduleMenu.setScrollbarsVisible(false);
    scrollableScheduleMenu.enableHorizontalScroll(false);
    scrollableScheduleMenu.setVisible(false);


    setCurrentState(JOG_WHEEL_STATE);

    add(menuTopBar);
    add(menuBottomBar);
    add(menuTopBarHeadline);
    add(scheduleMenuTopBarHeadline);
    add(scrollableMenu);
    add(scrollableScheduleMenu);
    add(scheduleOkButton);
    add(scheduleButton);
    add(autoButton);
    add(offButton);
    add(jogWheelContainer);
}

void HomeAutomationView::tearDownScreen()
{

}

void HomeAutomationView::handleTickEvent()
{
    if (currentState == ANIMATE_SCHEDULE_IN)
    {
        animateScheduleIn();
    }
    else if (currentState == ANIMATE_SCHEDULE_OUT)
    {
        animateScheduleOut();
    }
}

void HomeAutomationView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &scheduleButton)
    {
        if (currentState == JOG_WHEEL_STATE)
        {
            setScheduleOkButtonState(false);
            setCurrentState(ANIMATE_SCHEDULE_IN);
        }
        else
        {
            setCurrentState(ANIMATE_SCHEDULE_OUT);
        }

        // Set button inactive until the animation is done
        scheduleButton.setTouchable(false);
    }
    else if (&button == &scheduleOkButton)
    {
        presenter->newScheduleAccepted();
        setCurrentState(ANIMATE_SCHEDULE_OUT);
    }
    else if (&button == &autoButton)
    {
        // Switch off the off button
        offButton.forceState(!autoButton.getState());
        offButton.invalidate();

        // Auto button has no function in this demo
    }
    else if (&button == &offButton)
    {
        // Switch off the auto button
        autoButton.forceState(!offButton.getState());
        autoButton.invalidate();

        // Off button has no function in this demo
    }
}

void HomeAutomationView::jogWheelValueChanged(int16_t value)
{
    Unicode::snprintf(temperatureTextBuffer, 5, "%d", value);
    temperatureText.invalidate();
}

void HomeAutomationView::jogWheelEndDragEvent(int16_t value)
{
    presenter->newRoomTemperature(value);
}

void HomeAutomationView::menuItemSelected(const TemperatureMenuItem& menuItem)
{
    presenter->roomSelected(menuItem.getRoomId());
}

void HomeAutomationView::scheduleMenuItemSelected(const TemperatureScheduleMenuItem& menuItem)
{
    for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
    {
        scheduleMenuItems[i].setSelected(&scheduleMenuItems[i] == &menuItem);
    }
}

void HomeAutomationView::scheduleMenuItemValueUpdated(const TemperatureScheduleMenuItem&)
{
    setScheduleOkButtonState(true);
}

void HomeAutomationView::setSelectedMenuItem(RoomTemperatureInfo& room)
{
    for (uint8_t i = 0; i < currentNumberOfRooms; i++)
    {
        menuItems[i].setSelected(menuItems[i].getRoomId() == room.getRoomId());
    }
    menu.invalidate();

    for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
    {
        scheduleMenuItems[i].setRoomTemperatureInfo(room);
    }
    scheduleMenu.invalidate();

    scheduleMenuTopBarHeadline.setTypedText(TypedText(room.getRoomScheduleHeadline()));
    scheduleMenuTopBarHeadline.invalidate();


    jogWheelHeadline.setTypedText(TypedText(room.getRoomNameHeadline()));
    jogWheelHeadline.invalidate();

    jogWheel.setValue(room.getCurrentTemperature());
}

void HomeAutomationView::saveScheduleInfo(RoomTemperatureInfo& room)
{
    for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
    {
        room.setScheduleDayTemp((RoomTemperatureInfo::weekday) i, scheduleMenuItems[i].getDayTemperature());
        room.setScheduleNightTemp((RoomTemperatureInfo::weekday) i, scheduleMenuItems[i].getNightTemperature());
    }
}

void HomeAutomationView::insertRoom(RoomTemperatureInfo& room)
{
    menuItems[currentNumberOfRooms].setRoomTemperatureInfo(room);
    menuItems[currentNumberOfRooms].setMenuItemSelectedCallback(onMenuItemSelected);

    // Pair the model object with the graphical representation
    menuItems[currentNumberOfRooms].setRoomId(currentNumberOfRooms);
    room.setRoomId(currentNumberOfRooms);

    menu.add(menuItems[currentNumberOfRooms]);

    currentNumberOfRooms++;

    menu.invalidate();
}

void HomeAutomationView::updateRoom(RoomTemperatureInfo& room)
{
    menuItems[room.getRoomId()].setRoomTemperatureInfo(room);
}

void HomeAutomationView::setCurrentState(States newState)
{
    animationCounter = 0;
    currentState = newState;
}

void HomeAutomationView::animateScheduleIn()
{
    uint8_t duration = 22;

    if (animationCounter == 0)
    {
        menuTopBar.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_TOP_EXTENDED_ID));
        menuTopBar.invalidate();

        for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
        {
            // Preselect row 1
            scheduleMenuItems[i].setSelected(i == 1);
        }
    }

    // Fade Elements in/out
    if (animationCounter <= 10)
    {
        int16_t alpha = 255 - 30 * animationCounter;
        for (uint8_t i = 0; i < currentNumberOfRooms; i++)
        {
            menuItems[i].setTextsAlpha(alpha);
        }
        setMenuTopBarHeadlineAlpha(alpha);
    }
    else
    {
        if (animationCounter == 11)
        {
            scrollableMenu.setVisible(false);
            scrollableScheduleMenu.setVisible(true);
            scrollableScheduleMenu.invalidate();
        }

        int16_t alpha = 30 * (animationCounter - 11);
        setScheduleMenuTopBarHeadlineAlpha(alpha);
        for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
        {
            scheduleMenuItems[i].setAlpha(alpha);
        }
    }

    // Move jogWheel
    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, jogWheelContainer.getWidth(), duration);
        jogWheelContainer.moveTo(HAL::DISPLAY_WIDTH - jogWheelContainer.getWidth() + delta , 0);
    }
    else
    {
        // Final step: stop the animation
        scheduleButton.setTouchable(true);

        setCurrentState(SCHEDULE_STATE);
    }
    animationCounter++;
}

void HomeAutomationView::animateScheduleOut()
{
    uint8_t duration = 20;

    // Fade Elements in/out
    if (animationCounter <= 10)
    {
        int16_t alpha = 255 - 30 * animationCounter;
        for (uint8_t i = 0; i < RoomTemperatureInfo::NUMBER_OF_DAYS; i++)
        {
            scheduleMenuItems[i].setAlpha(alpha);
        }
        setScheduleMenuTopBarHeadlineAlpha(alpha);


    }
    else
    {
        if (animationCounter == 11)
        {
            scrollableMenu.setVisible(true);
            scrollableScheduleMenu.setVisible(false);
            scrollableMenu.invalidate();
        }

        int16_t alpha = 30 * (animationCounter - 11);
        setMenuTopBarHeadlineAlpha(alpha);
        for (uint8_t i = 0; i < currentNumberOfRooms; i++)
        {
            menuItems[i].setTextsAlpha(alpha);
        }
    }

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, jogWheelContainer.getWidth(), duration);
        jogWheelContainer.moveTo(HAL::DISPLAY_WIDTH - delta , 0);
    }
    else
    {
        // Final step: stop the animation
        menuTopBar.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_TOP_ID));
        menuTopBar.invalidate();

        // Force the scheduleButton to be in its unpressed state
        // This is needed since both the scheduleButton and the
        // scheduleOkButton may trigger this animation
        scheduleButton.setTouchable(true);
        scheduleButton.forceState(false);
        scheduleButton.invalidate();

        setCurrentState(JOG_WHEEL_STATE);
    }
    animationCounter++;
}

void HomeAutomationView::setScheduleOkButtonState(bool valuesUpdated)
{
    if (valuesUpdated)
    {
        scheduleOkButton.setBitmaps(Bitmap(BITMAP_TEMPERATURE_OK_BUTTON_ID), Bitmap(BITMAP_TEMPERATURE_OK_BUTTON_PRESSED_ID));
    }
    else
    {
        scheduleOkButton.setBitmaps(Bitmap(BITMAP_TEMPERATURE_OK_BUTTON_INACTIVE_ID), Bitmap(BITMAP_TEMPERATURE_OK_BUTTON_INACTIVE_ID));
    }
    scheduleOkButton.setTouchable(valuesUpdated);

    scheduleOkButton.invalidate();
}

void HomeAutomationView::setMenuTopBarHeadlineAlpha(int16_t alpha)
{
    alpha = (alpha < 0) ? 0 : alpha;
    alpha = (alpha > 255) ? 255 : alpha;
    menuTopBarHeadline.setAlpha((uint8_t) alpha);
    menuTopBarHeadline.invalidate();
}

void HomeAutomationView::setScheduleMenuTopBarHeadlineAlpha(int16_t alpha)
{
    alpha = (alpha < 0) ? 0 : alpha;
    alpha = (alpha > 255) ? 255 : alpha;
    scheduleMenuTopBarHeadline.setAlpha((uint8_t) alpha);
    scheduleMenuTopBarHeadline.invalidate();
}
