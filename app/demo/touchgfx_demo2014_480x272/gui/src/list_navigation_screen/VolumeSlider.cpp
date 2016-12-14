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
#include <gui/list_navigation_screen/VolumeSlider.hpp>


VolumeSlider::VolumeSlider() :
    volumeChangedCallback(0)
{
    setTouchable(true);

    slider.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_VOLUME_SLIDER_BUTTON_ID));
    slider.setXY(0, 0);
    sliderRadius = slider.getWidth() / 2;

    sliderBackground.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_VOLUME_SLIDER_ID));
    sliderBackground.setXY(0, 8);

    sliderBackgroundActive.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_VOLUME_SLIDER_ACTIVE_ID));
    sliderBackgroundActive.setXY(0, 8);

    // Set the containers dimensions
    setWidth(sliderBackground.getWidth());
    setHeight(slider.getHeight());

    // View port handles which part of the active slider is visible
    sliderBackgroundActiveViewPort.setPosition(0, 0, getWidth(), getHeight());
    sliderBackgroundActiveViewPort.add(sliderBackgroundActive);

    add(sliderBackground);
    add(sliderBackgroundActiveViewPort);
    add(slider);

    setSlider(30);
}

VolumeSlider::~VolumeSlider()
{

}

void VolumeSlider::handleClickEvent(const ClickEvent& evt)
{
    setSlider(evt.getX());
}

void VolumeSlider::handleDragEvent(const DragEvent& evt)
{
    setSlider(evt.getNewX());
}

void VolumeSlider::setSlider(int16_t x)
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

    sliderBackgroundActiveViewPort.setPosition(0, 0, x, getHeight());
    invalidate();

    // Communicate the new value if a listener is registered
    if (volumeChangedCallback)
    {
        volumeChangedCallback->execute(x);
    }

}
