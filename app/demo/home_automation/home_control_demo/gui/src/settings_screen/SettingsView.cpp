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
#include <gui/settings_screen/SettingsView.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/Config.hpp>

SettingsView::SettingsView() :
    onSliderChanged(this, &SettingsView::sliderChanged)
{
    menu.set(Menu::Settings);
}

void SettingsView::setupScreen()
{
    baseview::setupScreen();

    int rightSliderXPos;
    int sliderWidth;
#ifdef RESOLUTION_640X480
    background.setBitmap(touchgfx::Bitmap(BITMAP_SETTINGS_BACKGROUND_SMALL_ID));
    rightSliderXPos = 352;
    sliderWidth = 246;
#else
    background.setBitmap(touchgfx::Bitmap(BITMAP_SETTINGS_BACKGROUND_ID));
    rightSliderXPos = 442;
    sliderWidth = 316;
#endif

    slider0.setXY(42, 146);
    slider1.setXY(42, 265);
    slider2.setXY(rightSliderXPos, 146);
    slider3.setXY(rightSliderXPos, 265);

    slider0.setWidth(sliderWidth);
    slider1.setWidth(sliderWidth);
    slider2.setWidth(sliderWidth);
    slider3.setWidth(sliderWidth);

    slider0.setSlider(60);
    slider1.setSlider(180);
    slider2.setSlider(80);
    slider3.setSlider(160);

    slider0.setChangedCallback(onSliderChanged);
    slider1.setChangedCallback(onSliderChanged);
    slider2.setChangedCallback(onSliderChanged);
    slider3.setChangedCallback(onSliderChanged);

    add(slider0);
    add(slider1);
    add(slider2);
    add(slider3);
}

void SettingsView::tearDownScreen()
{

}

void SettingsView::sliderChanged(const Slider& slider, int16_t value)
{
    int16_t sliderId = 0;

    if (&slider == &slider0)
    {
        sliderId = 0;
    }
    else if (&slider == &slider1)
    {
        sliderId = 1;
    }
    else if (&slider == &slider2)
    {
        sliderId = 2;
    }
    else if (&slider == &slider3)
    {
        sliderId = 3;
    }
    presenter->sliderChanged(sliderId, value);
}

void SettingsView::setSliderValue(int sliderId, int16_t value)
{
    if (sliderId == 0)
    {
        slider0.setSlider(value);
    }
    else if (sliderId == 1)
    {
        slider1.setSlider(value);
    }
    else if (sliderId == 2)
    {
        slider2.setSlider(value);
    }
    else if (sliderId == 3)
    {
        slider3.setSlider(value);
    }
}

