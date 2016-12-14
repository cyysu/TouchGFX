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
#ifndef LIVEDATADISPLAYTILE_HPP_
#define LIVEDATADISPLAYTILE_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;

class LiveDataDisplayTile : public Container
{
public:
    LiveDataDisplayTile();
    virtual ~LiveDataDisplayTile();

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
        static_cast<FrontendApplication*>(Application::getInstance())->gotoLiveDataDisplayScreen();
    }

private:
    enum States
    {
        ANIMATE_TEXT_OUT,
        ANIMATE_BACKGROUND,
        NO_ANIMATION
    } currentState;

    uint8_t animationCounter;

    Image background;
    Image hiddenBackground;

    Container textContainer;

    TextArea cityName;
    TextArea cityNameDropShadow;

    TextAreaWithOneWildcard largeTemperature;
    TextAreaWithOneWildcard largeTemperatureDropShadow;
    Unicode::UnicodeChar largeTemperatureBuffer[5];
    int tickCounter;

    TextArea tileId;


    static const int16_t NUMBER_OF_CITIES = 3;
    int currentCityIndex;
    TEXTS cities[NUMBER_OF_CITIES];
    int temperatures[NUMBER_OF_CITIES];
    BitmapId backgrounds[NUMBER_OF_CITIES];

    int textContainerX;

    void animateTextOut();
    void animateBackground();
    void setCurrentState(States newState);

    void setTemperature(int16_t newTemperature);
    void setCity(TEXTS newCity);
    void updateBackground();

};

#endif /* LIVEDATADISPLAYTILE_HPP_ */
