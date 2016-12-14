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
#ifndef MCU_LOAD_SLIDER_HPP
#define MCU_LOAD_SLIDER_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>


using namespace touchgfx;

class McuLoadSlider : public Container
{
public:
    McuLoadSlider();

    void setValue(uint8_t load);
    void show();
    void showWithNoAnimation();

    void hide();

protected:
    enum AnimationState
    {
        LEFT_ANIMATION,
        RIGHT_ANIMATION,
        NO_ANIMATION
    } state;

    uint8_t mcuLoad; // mcu load in procent
    Image background;

    TextArea mcuLoadHeadline;
    TextAreaWithOneWildcard mcuLoadTxt;
    Unicode::UnicodeChar mcuLoadTxtbuf[5];

    int16_t startPositionX;
    uint8_t animationCounter;

    virtual void handleTickEvent();
};



#endif
