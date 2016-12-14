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
#ifndef HOMEAUTOMATIONTILE_HPP_
#define HOMEAUTOMATIONTILE_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/model/RoomTemperatureInfo.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;

class HomeAutomationTile : public Container
{
public:
    HomeAutomationTile();
    virtual ~HomeAutomationTile();

    virtual void handleTickEvent();

    int16_t getWidth()
    {
        return Container::getWidth();
    }
    int16_t getHeight()
    {
        return Container::getHeight();
    }

    void gotoAssociatedScreen()
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoHomeAutomationScreen();
    }

    void addRoom(RoomTemperatureInfo& room);
    void initialize();

private:
    enum States
    {
        ANIMATE_TEXT_OUT,
        ANIMATE_TEXT_IN,
        NO_ANIMATION
    } currentState;

    uint8_t animationCounter;

    Box background;
    Image hiddenBackground;

    int currentRoomIndex;
    TextArea roomName;
    TextArea roomNameDropShadow;
    TextAreaWithOneWildcard temperature;
    TextAreaWithOneWildcard temperatureDropShadow;
    Unicode::UnicodeChar temperatureBuffer[7];
    int tickCounter;

    int dropShadowOffsetX;
    int dropShadowOffsetY;

    TextArea tileId;

    int numberOfRooms;
    RoomTemperatureInfo rooms[10];

    int roomNameY;
    int temperatureY;

    void animateTextOut();
    void animateTextIn();
    void setCurrentState(States newState);

    void setRoom(TEXTS newRoom);
    void setTemperature(int16_t newTemperature);
};

#endif /* HOMEAUTOMATIONTILE_HPP_ */
