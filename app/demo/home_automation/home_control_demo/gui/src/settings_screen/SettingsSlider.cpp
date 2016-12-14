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
#include <gui/settings_screen/SettingsSlider.hpp>


using namespace touchgfx;

Slider::Slider() :
    changedCallback(0)
{
    setTouchable(true);

    slider.setBitmap(Bitmap(BITMAP_SLIDER_BUTTON_ID));
    slider.setXY(0, 0);
    sliderRadius = slider.getWidth() / 2;

    // Set the containers dimensions
    setWidth(316);
    setHeight(slider.getHeight());

    add(slider);

    setSlider(60);
}

Slider::~Slider()
{

}

void Slider::handleClickEvent(const ClickEvent& evt)
{
    setSlider(evt.getX());
}

void Slider::handleDragEvent(const DragEvent& evt)
{
    setSlider(evt.getNewX());
}

void Slider::setSlider(int16_t x)
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
    if (changedCallback)
    {
        changedCallback->execute(*this, x);
    }

}
