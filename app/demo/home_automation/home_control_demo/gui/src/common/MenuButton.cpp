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
#include <gui/common/MenuButton.hpp>


MenuButton::MenuButton() :
    pressed(false),
    selected(false),
    pressedCallback(0)
{
    setTouchable(true);
    updateBackground();

    background.setXY(0, 0);
    add(background);
}

void MenuButton::setCallback(touchgfx::GenericCallback<bool>& newPressedCallback)
{
    pressedCallback = &newPressedCallback;
}

void MenuButton::setBitmaps(const touchgfx::Bitmap& normal, const touchgfx::Bitmap& newSelectedBitmap, const touchgfx::Bitmap& newPressedBitmap)
{
    selectedBitmap = newSelectedBitmap;
    pressedBitmap = newPressedBitmap;
    normalBitmap = normal;

    updateBackground();
    setWidth(background.getWidth());
    setHeight(background.getHeight());

    invalidate();
}

void MenuButton::handleClickEvent(const touchgfx::ClickEvent& evt)
{
    bool wasPressed = pressed;
    pressed = evt.getType() == touchgfx::ClickEvent::PRESSED;
    if (!pressed)
    {
        updateBackground();
    }
    else
    {
        updateBackground();
    }

    if (wasPressed && evt.getType() == touchgfx::ClickEvent::RELEASED &&
            pressedCallback &&
            pressedCallback->isValid())
    {
        pressedCallback->execute(!selected);
    }
    invalidate();
}

void MenuButton::setSelected(bool newSelected)
{
    selected = newSelected;
    updateBackground();
}

void MenuButton::updateBackground()
{
    background.setBitmap(pressed ? pressedBitmap : (selected ? selectedBitmap : normalBitmap));
    invalidate();
}

