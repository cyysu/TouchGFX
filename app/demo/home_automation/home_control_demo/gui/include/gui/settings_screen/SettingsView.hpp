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
#ifndef SETTINGS_VIEW_HPP
#define SETTINGS_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/settings_screen/SettingsSlider.hpp>


using namespace touchgfx;

/**
 * SettingsView - adjust settings of the home control system.
 *
 * The individual settings are adjusted by dragging the circle button along the slider.
 * This demo page consist of a background image with the text and slider embedded.
 * A more correct and flexible way would be to have individual texts and slider images.
 *
 */
class SettingsView : public BaseView<SettingsPresenter>
{
public:
    SettingsView();
    virtual ~SettingsView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void setSliderValue(int sliderId, int16_t value);
private:
    Slider slider0;
    Slider slider1;
    Slider slider2;
    Slider slider3;

    touchgfx::Callback<SettingsView, const Slider&, int16_t> onSliderChanged;

    void sliderChanged(const Slider& slider, int16_t value);

};

#endif
