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
#include <gui/home_automation_screen/TemperatureMenuItem.hpp>
#include <touchgfx/Color.hpp>

TemperatureMenuItem::TemperatureMenuItem() :
    onButtonPressed(this, &TemperatureMenuItem::buttonPressedhandler)
{
    background.setXY(0, 0);
    background.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_ITEM_ID));

    primaryText.setPosition(10, 9, 160, 20);

    currentTemperature.setPosition(144, 5, 55, 24);
    currentTemperature.setTypedText(TypedText(T_TEMPERATURE_MENU));
    currentTemperature.setWildcard(currentTemperatureTextBuffer);

    itemSelectArea.setPosition(0, 0, background.getWidth(), background.getHeight());
    itemSelectArea.setAction(onButtonPressed);

    setSelected(false);

    add(background);
    add(primaryText);
    add(currentTemperature);
    add(itemSelectArea);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

TemperatureMenuItem::~TemperatureMenuItem()
{

}

void TemperatureMenuItem::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &itemSelectArea)
    {
        if (menuItemSelectedCallback)
        {
            menuItemSelectedCallback->execute(*this);
        }
    }
}

void TemperatureMenuItem::setRoomTemperatureInfo(RoomTemperatureInfo& info)
{
    primaryText.setTypedText(TypedText(info.getRoomName()));
    primaryText.invalidate();

    Unicode::snprintf(currentTemperatureTextBuffer, 5, "%d", info.getCurrentTemperature());
    currentTemperature.invalidate();
}

void TemperatureMenuItem::setSelected(bool sel)
{
    selected = sel;

    if (selected)
    {
        background.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_ITEM_SELECTED_ID));
        primaryText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
        currentTemperature.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    }
    else
    {
        background.setBitmap(Bitmap(BITMAP_TEMPERATURE_MENU_ITEM_ID));
        primaryText.setColor(Color::getColorFrom24BitRGB(0xA9, 0xAD, 0xB6));
        currentTemperature.setColor(Color::getColorFrom24BitRGB(0xA9, 0xAD, 0xB6));
    }
    background.invalidate();
    primaryText.invalidate();
    currentTemperature.invalidate();
}

void TemperatureMenuItem::setTextsAlpha(int16_t alpha)
{
    alpha = (alpha < 0) ? 0 : alpha;
    alpha = (alpha > 255) ? 255 : alpha;

    primaryText.setAlpha((uint8_t) alpha);
    currentTemperature.setAlpha((uint8_t) alpha);

    primaryText.invalidate();
    currentTemperature.invalidate();
}
