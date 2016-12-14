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
#include <gui/easing_equation_screen/EasingEquationInOrOutOrInOut.hpp>
#include <gui/easing_equation_screen/EasingEquationSelector.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

EasingEquationInOrOutOrInOut::EasingEquationInOrOutOrInOut() :
    onSelected(this, &EasingEquationInOrOutOrInOut::selected),
    inOrOutSelectedCallback(0)
{

    // Only the text id is used in this group.
    EasingEquationSelection selections[] =
    {
        { EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        T_EASING_EQUATION_EASE_IN,        T_EASING_EQUATION_EASE_IN         },
        { EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        T_EASING_EQUATION_EASE_OUT,       T_EASING_EQUATION_EASE_OUT       },
        { EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        EasingEquations::linearEaseNone,        T_EASING_EQUATION_EASE_INOUT,     T_EASING_EQUATION_EASE_INOUT   }
    };


    in.setup(selections[0], Bitmap(BITMAP_EASING_BOTTOM_MENU_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID),
             Bitmap(BITMAP_EASING_BOTTOM_MENU_SELECTED_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID));
    in.setXY(0, 0);
    in.setTextShadowVisible(false);

    out.setup(selections[1], Bitmap(BITMAP_EASING_BOTTOM_MENU_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID),
              Bitmap(BITMAP_EASING_BOTTOM_MENU_SELECTED_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID));
    out.setXY(in.getRect().right(), 0);
    out.setTextShadowVisible(false);

    inOut.setup(selections[2], Bitmap(BITMAP_EASING_BOTTOM_MENU_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID),
                Bitmap(BITMAP_EASING_BOTTOM_MENU_SELECTED_ID), Bitmap(BITMAP_EASING_BOTTOM_MENU_ACTIVE_ID));
    inOut.setXY(out.getRect().right(), 0);
    inOut.setTextShadowVisible(false);

    buttons.setRadioButtonSelectedHandler(onSelected);
    buttons.add(in.getRadioButton());
    buttons.add(out.getRadioButton());
    buttons.add(inOut.getRadioButton());

    add(in);
    add(out);
    add(inOut);

    setWidth(inOut.getRect().right());
    setHeight(in.getHeight());

    setButtonColors();
}

void EasingEquationInOrOutOrInOut::setInOrOutSelectedCallback(GenericCallback<EasingEquationsInOrOut>& callback)
{
    inOrOutSelectedCallback = &callback;
}

void EasingEquationInOrOutOrInOut::selected(const AbstractButton& btn)
{
    EasingEquationsInOrOut inOrOut = (&btn == &(in.getRadioButton())) ? EASING_EQUATION_IN : (&btn == &(out.getRadioButton())) ? EASING_EQUATION_OUT : EASING_EQUATION_IN_OUT;
    setButtonColors();
    if (inOrOutSelectedCallback && inOrOutSelectedCallback->isValid())
    {
        inOrOutSelectedCallback->execute(inOrOut);
    }
}

void EasingEquationInOrOutOrInOut::selectFirst()
{
    buttons.setSelected(in.getRadioButton());
}

void EasingEquationInOrOutOrInOut::setButtonColors()
{
    int selected = buttons.getSelectedRadioButtonIndex();

    in.setTextColor(Color::getColorFrom24BitRGB(0x9D, 0xC9, 0xD1), 0);
    out.setTextColor(Color::getColorFrom24BitRGB(0x9D, 0xC9, 0xD1), 0);
    inOut.setTextColor(Color::getColorFrom24BitRGB(0x9D, 0xC9, 0xD1), 0);

    switch (selected)
    {
    case 0:
        in.setTextColor(Color::getColorFrom24BitRGB(0xFF, 0x61, 0x14), 0);
        break;
    case 1:
        out.setTextColor(Color::getColorFrom24BitRGB(0xFF, 0x61, 0x14), 0);
        break;
    case 2:
        inOut.setTextColor(Color::getColorFrom24BitRGB(0xFF, 0x61, 0x14), 0);
        break;
    default:
        break;
    }
}
