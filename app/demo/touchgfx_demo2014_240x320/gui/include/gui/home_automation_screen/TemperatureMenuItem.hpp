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
#ifndef TEMPERATURE_MENU_ITEM_HPP_
#define TEMPERATURE_MENU_ITEM_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <gui/model/RoomTemperatureInfo.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class TemperatureMenuItem : public Container
{
public:
    TemperatureMenuItem();
    virtual ~TemperatureMenuItem();

    void setMenuItemSelectedCallback(GenericCallback< const TemperatureMenuItem& >& callback)
    {
        menuItemSelectedCallback = &callback;
    }

    void setRoomTemperatureInfo(RoomTemperatureInfo& info);

    void setSelected(bool sel);

    void setRoomId(uint8_t id)
    {
        roomId = id;
    }
    uint8_t getRoomId() const
    {
        return roomId;
    }

    void setTextsAlpha(int16_t alpha);

private:
    uint8_t roomId;

    Image background;
    TextArea primaryText;
    TextAreaWithOneWildcard currentTemperature;
    Unicode::UnicodeChar currentTemperatureTextBuffer[5];

    TouchArea itemSelectArea;

    bool selected;

    GenericCallback< const TemperatureMenuItem& >* menuItemSelectedCallback;

    Callback<TemperatureMenuItem, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);
};


#endif /* TEMPERATURE_MENU_ITEM_HPP_ */
