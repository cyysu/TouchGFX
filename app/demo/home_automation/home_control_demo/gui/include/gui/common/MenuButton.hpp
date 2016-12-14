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
#ifndef MENU_BUTTON_HPP
#define MENU_BUTTON_HPP

#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/Bitmap.hpp>
#include <BitmapDatabase.hpp>

/**
 * A MenuButton handle 3 graphical states used by the menu - normal, pressed and selected.
 */
class MenuButton : public touchgfx::Container
{
public:
    MenuButton();

    void setCallback(touchgfx::GenericCallback<bool>& newPressedCallback);

    void setBitmaps(const touchgfx::Bitmap& normal, const touchgfx::Bitmap& newSelectedBitmap, const touchgfx::Bitmap& newPressedBitmap);
    virtual void handleClickEvent(const touchgfx::ClickEvent& evt);
    void setSelected(bool newSelected);
    void updateBackground();

private:
    touchgfx::Image background;

    bool pressed;
    bool selected;
    touchgfx::GenericCallback<bool>* pressedCallback;

    touchgfx::Bitmap normalBitmap;
    touchgfx::Bitmap selectedBitmap;
    touchgfx::Bitmap pressedBitmap;
};

#endif
