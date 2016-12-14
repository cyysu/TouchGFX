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
#ifndef TEMPERATURE_SCHEDULE_MENU_ITEM_HPP_
#define TEMPERATURE_SCHEDULE_MENU_ITEM_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <gui/model/RoomTemperatureInfo.hpp>
#include <gui/home_automation_screen/TemperatureSlider.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class TemperatureScheduleMenuItem : public Container
{
public:
    TemperatureScheduleMenuItem();
    virtual ~TemperatureScheduleMenuItem();

    void setMenuItemSelectedCallback(GenericCallback< const TemperatureScheduleMenuItem& >& callback)
    {
        menuItemSelectedCallback = &callback;
    }
    void setMenuItemValueUpdatedCallback(GenericCallback< const TemperatureScheduleMenuItem& >& callback)
    {
        valueUpdatedCallback = &callback;
    }

    void setWeekday(RoomTemperatureInfo::weekday day);
    RoomTemperatureInfo::weekday getWeekday()
    {
        return weekday;
    }

    void setRoomTemperatureInfo(RoomTemperatureInfo& info);

    void setSelected(bool sel);

    void setAlpha(int16_t alpha);

    int16_t getDayTemperature()
    {
        return dayTemperatureValue;
    }
    int16_t getNightTemperature()
    {
        return nightTemperatureValue;
    }

    void setSlider(TemperatureSlider* temperatureSlider)
    {
        slider = temperatureSlider;
    }

private:
    RoomTemperatureInfo::weekday weekday;

    Image background;
    TextArea weekdayText;
    TextAreaWithOneWildcard dayTemperature;
    Unicode::UnicodeChar dayTemperatureTextBuffer[5];
    TextAreaWithOneWildcard nightTemperature;
    Unicode::UnicodeChar nightTemperatureTextBuffer[5];

    TouchArea itemSelectArea;
    Image daySelected;
    TouchArea daySelectArea;
    Image nightSelected;
    TouchArea nightSelectArea;
    bool currentSelectedIsDay;

    int16_t dayTemperatureValue;
    int16_t nightTemperatureValue;

    TemperatureSlider* slider;

    bool selected;

    GenericCallback< const TemperatureScheduleMenuItem& >* menuItemSelectedCallback;
    GenericCallback< const TemperatureScheduleMenuItem& >* valueUpdatedCallback;

    Callback<TemperatureScheduleMenuItem, const AbstractButton&> onSelectionAreaPressed;
    Callback<TemperatureScheduleMenuItem, int16_t> onSliderUpdated;

    void selectionAreaPressedhandler(const AbstractButton& button);
    void sliderUpdatedHandler(int16_t value);

    void updateTemperatureText();

};


#endif /* TEMPERATURE_SCHEDULE_MENU_ITEM_HPP_ */
