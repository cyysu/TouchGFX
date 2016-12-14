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
#include <gui/home_automation_screen/TemperatureScheduleMenuItem.hpp>
#include <touchgfx/Color.hpp>

TemperatureScheduleMenuItem::TemperatureScheduleMenuItem() :
    onSelectionAreaPressed(this, &TemperatureScheduleMenuItem::selectionAreaPressedhandler),
    onSliderUpdated(this, &TemperatureScheduleMenuItem::sliderUpdatedHandler)
{
    background.setXY(0, 0);
    background.setBitmap(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_MENU_ITEM_ID));

    weekdayText.setPosition(10, 7, 160, 30);
    weekdayText.setTypedText(TypedText(T_TEMPERATURE_ROOM7));

    daySelected.setXY(119, 0);
    daySelected.setBitmap(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_BUTTON_SELECTED_ID));
    daySelected.setVisible(false);
    daySelectArea.setPosition(daySelected.getX(), daySelected.getY(), daySelected.getWidth(), daySelected.getHeight());
    daySelectArea.setAction(onSelectionAreaPressed);

    nightSelected.setXY(daySelected.getX() + daySelected.getWidth() + 1, 0);
    nightSelected.setBitmap(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_BUTTON_SELECTED_ID));
    nightSelected.setVisible(false);
    nightSelectArea.setPosition(nightSelected.getX(), nightSelected.getY(), nightSelected.getWidth(), nightSelected.getHeight());
    nightSelectArea.setAction(onSelectionAreaPressed);

    dayTemperature.setPosition(daySelected.getX() + 3, 6, 46, 34);
    dayTemperature.setTypedText(TypedText(T_TEMPERATURE_MENU));
    dayTemperature.setWildcard(dayTemperatureTextBuffer);

    nightTemperature.setPosition(dayTemperature.getX() + daySelected.getWidth(), 6, 46, 34);
    nightTemperature.setTypedText(TypedText(T_TEMPERATURE_MENU));
    nightTemperature.setWildcard(nightTemperatureTextBuffer);

    Unicode::snprintf(dayTemperatureTextBuffer, 5, "%d", 1);
    Unicode::snprintf(nightTemperatureTextBuffer, 5, "%d", 2);

    itemSelectArea.setPosition(0, 0, daySelectArea.getX(), background.getHeight());
    itemSelectArea.setAction(onSelectionAreaPressed);

    currentSelectedIsDay = true;
    setSelected(false);

    add(background);
    add(daySelected);
    add(nightSelected);
    add(weekdayText);
    add(dayTemperature);
    add(nightTemperature);

    add(itemSelectArea);
    add(daySelectArea);
    add(nightSelectArea);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

TemperatureScheduleMenuItem::~TemperatureScheduleMenuItem()
{


}

void TemperatureScheduleMenuItem::selectionAreaPressedhandler(const AbstractButton& button)
{
    if (&button == &daySelectArea)
    {
        currentSelectedIsDay = true;
    }
    else if (&button == &nightSelectArea)
    {
        currentSelectedIsDay = false;
    }

    if (&button == &itemSelectArea && !selected)
    {
        currentSelectedIsDay = true;
    }

    if (menuItemSelectedCallback)
    {
        menuItemSelectedCallback->execute(*this);
    }
}

void TemperatureScheduleMenuItem::sliderUpdatedHandler(int16_t value)
{
    if (currentSelectedIsDay)
    {
        if (value != dayTemperatureValue)
        {
            dayTemperatureValue = value;
            updateTemperatureText();

            if (valueUpdatedCallback)
            {
                valueUpdatedCallback->execute(*this);
            }
        }
    }
    else
    {
        if (value != nightTemperatureValue)
        {
            nightTemperatureValue = value;
            updateTemperatureText();

            if (valueUpdatedCallback)
            {
                valueUpdatedCallback->execute(*this);
            }
        }
    }
}

void TemperatureScheduleMenuItem::setSelected(bool sel)
{
    // Toggle selection from unselected to selected
    if (sel && !selected)
    {
        slider->setValueChangedCallback(onSliderUpdated);

        if (currentSelectedIsDay)
        {
            slider->setValue(dayTemperatureValue);
        }
        else
        {
            slider->setValue(nightTemperatureValue);
        }
        slider->invalidate();
    }


    selected = sel;

    if (selected)
    {
        background.setBitmap(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_MENU_ITEM_SELECTED_ID));
        weekdayText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
        dayTemperature.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
        nightTemperature.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
        daySelected.setVisible(currentSelectedIsDay);
        nightSelected.setVisible(!currentSelectedIsDay);

        slider->setValue(currentSelectedIsDay ? dayTemperatureValue : nightTemperatureValue);
    }
    else
    {
        background.setBitmap(Bitmap(BITMAP_TEMPERATURE_SCHEDULE_MENU_ITEM_ID));
        weekdayText.setColor(Color::getColorFrom24BitRGB(0xA9, 0xAD, 0xB6));
        dayTemperature.setColor(Color::getColorFrom24BitRGB(0xA9, 0xAD, 0xB6));
        nightTemperature.setColor(Color::getColorFrom24BitRGB(0xA9, 0xAD, 0xB6));
        daySelected.setVisible(false);
        nightSelected.setVisible(false);

    }
    background.invalidate();
    weekdayText.invalidate();
    dayTemperature.invalidate();
    nightTemperature.invalidate();
}

void TemperatureScheduleMenuItem::setWeekday(RoomTemperatureInfo::weekday day)
{
    weekday = day;
    weekdayText.setTypedText(TypedText(T_TEMPERATURE_MONDAY + (uint8_t)day));
    weekdayText.invalidate();
}

void TemperatureScheduleMenuItem::setRoomTemperatureInfo(RoomTemperatureInfo& info)
{
    dayTemperatureValue = info.getScheduleDayTemp(weekday);
    nightTemperatureValue = info.getScheduleNightTemp(weekday);
    updateTemperatureText();
}

void TemperatureScheduleMenuItem::updateTemperatureText()
{
    Unicode::snprintf(dayTemperatureTextBuffer, 5, "%d", dayTemperatureValue);
    Unicode::snprintf(nightTemperatureTextBuffer, 5, "%d", nightTemperatureValue);
    dayTemperature.invalidate();
    nightTemperature.invalidate();
}

void TemperatureScheduleMenuItem::setAlpha(int16_t alpha)
{
    alpha = (alpha < 0) ? 0 : alpha;
    alpha = (alpha > 255) ? 255 : alpha;

    weekdayText.setAlpha((uint8_t) alpha);
    dayTemperature.setAlpha((uint8_t) alpha);
    nightTemperature.setAlpha((uint8_t) alpha);
    slider->setAlpha((uint8_t) alpha);
    invalidate();
}
