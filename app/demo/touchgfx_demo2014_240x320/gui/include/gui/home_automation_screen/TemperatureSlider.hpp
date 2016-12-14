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
#ifndef TEMPERATURE_SLIDER_HPP_
#define TEMPERATURE_SLIDER_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class TemperatureSlider : public Container
{
public:
    TemperatureSlider();
    virtual ~TemperatureSlider();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);

    void setValueChangedCallback(GenericCallback< int16_t >& callback)
    {
        valueChangedCallback = &callback;
    }

    void setLimits(int16_t min, int16_t max);
    void setValue(int16_t value);

    int16_t getValue();

    void setAlpha(uint8_t alpha);

private:
    Image sliderBackground;
    Image slider;

    int16_t minLimit;
    int16_t maxLimit;

    uint8_t sliderRadius;

    GenericCallback< int16_t >* valueChangedCallback;

    void setSlider(int16_t x, bool callback);
};


#endif /* TEMPERATURE_SLIDER_HPP_ */
