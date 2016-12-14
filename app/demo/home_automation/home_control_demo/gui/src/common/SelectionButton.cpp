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
#include <gui/common/SelectionButton.hpp>

using namespace touchgfx;

SelectionButton::SelectionButton() :
    Image(),
    pressedAction(0),
    selected(false)
{
    setTouchable(true);
    updateBitmap();
}

SelectionButton::~SelectionButton()
{
}

void SelectionButton::updateBitmap()
{
    setBitmap(selected ? selectedBitmap : unselectedBitmap);
    invalidate();
}

void SelectionButton::setBitmaps(const touchgfx::Bitmap& newUnselectedBitmap, const touchgfx::Bitmap& newSelectedBitmap)
{
    unselectedBitmap = newUnselectedBitmap;
    selectedBitmap = newSelectedBitmap;
    updateBitmap();
}

void SelectionButton::setPressedAction(touchgfx::GenericCallback<>& newPressedAction)
{
    pressedAction = &newPressedAction;
}

void SelectionButton::forceState(bool newSelectedState)
{
    selected = newSelectedState;
    updateBitmap();
}

void SelectionButton::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        selected = !selected;
        updateBitmap();
        invalidate();
        if (pressedAction && pressedAction->isValid())
        {
            pressedAction->execute();
        }
    }
}

bool SelectionButton::isSelected() const
{
    return selected;
}

