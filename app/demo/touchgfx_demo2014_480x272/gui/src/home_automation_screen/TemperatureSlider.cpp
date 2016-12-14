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
#include <gui/home_automation_screen/TemperatureSlider.hpp>


TemperatureSlider::TemperatureSlider() :
    valueChangedCallback(0)
{
    setTouchable(true);

    slider.setBitmap(Bitmap(BITMAP_TEMPERATURE_SLIDER_KNOP_ID));
    slider.setXY(0, 0);
    sliderRadius = slider.getWidth() / 2;

    sliderBackground.setBitmap(Bitmap(BITMAP_TEMPERATURE_SLIDER_ID));
    sliderBackground.setXY(0, sliderRadius - sliderBackground.getHeight() / 2);

    // Set the containers dimensions
    setWidth(sliderBackground.getWidth());
    setHeight(slider.getHeight());

    add(sliderBackground);
    add(slider);

    setSlider(30, true);
}

TemperatureSlider::~TemperatureSlider()
{

}

void TemperatureSlider::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        setSlider(evt.getX(), true);
    }
}

void TemperatureSlider::handleDragEvent(const DragEvent& evt)
{
    setSlider(evt.getNewX(), true);
}

void TemperatureSlider::setLimits(int16_t min, int16_t max)
{
    assert(min < max);
    minLimit = min;
    maxLimit = max;
}

void TemperatureSlider::setValue(int16_t value)
{
    // Round value to the limits if necessary
    value = (value < minLimit) ? minLimit : value;
    value = (value > maxLimit) ? maxLimit : value;

    float placementPercentage = ((float)(value - minLimit) / (maxLimit - minLimit));


    int16_t interval = getWidth() - sliderRadius - sliderRadius;
    setSlider(sliderRadius + (int16_t)(placementPercentage * interval), false);
}

void TemperatureSlider::setSlider(int16_t x, bool callback)
{
    // Cut off x values outside the slider area
    if (x < sliderRadius)
    {
        x = sliderRadius;
    }
    else if (x > getWidth() - sliderRadius)
    {
        x = getWidth() - sliderRadius;
    }

    slider.moveTo(x - sliderRadius, 0);

    invalidate();

    // Communicate the new value if a listener is registered
    if (valueChangedCallback && callback)
    {
        valueChangedCallback->execute(getValue());
    }

}

int16_t TemperatureSlider::getValue()
{
    int16_t interval = getWidth() - sliderRadius - sliderRadius;
    float placementPercentage = (float) slider.getX() / interval;

    return minLimit + ((int16_t)(placementPercentage * (maxLimit - minLimit)));
}

void TemperatureSlider::setAlpha(uint8_t alpha)
{
    sliderBackground.setAlpha(alpha);
    slider.setAlpha(alpha);
    sliderBackground.invalidate();
    slider.invalidate();
}
