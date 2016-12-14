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
#include <gui/easing_equation_screen/EasingEquationSelector.hpp>
#include <touchgfx/Bitmap.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

EasingEquationButton::EasingEquationButton()
{
    buttonText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    buttonTextShadow.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));

    add(radioButton);
    add(buttonTextShadow);
    add(buttonText);
}

void EasingEquationButton::setup(EasingEquationSelection newEasingEquation, const Bitmap& bmpUnselected, const Bitmap& bmpUnselectedPressed, const Bitmap& bmpSelected, const Bitmap& bmpSelectedPressed)
{
    radioButton.setBitmaps(bmpUnselected, bmpUnselectedPressed, bmpSelected, bmpSelectedPressed);
    setWidth(radioButton.getWidth());
    setHeight(radioButton.getHeight());

    easingEquation = newEasingEquation;
    buttonText.setTypedText(TypedText(newEasingEquation.EasingEquationShortName));
    buttonText.resizeToCurrentText();
    buttonTextShadow.setTypedText(buttonText.getTypedText());
    buttonTextShadow.resizeToCurrentText();
    buttonText.setXY((getWidth() - buttonText.getWidth()) / 2, (getHeight() - buttonText.getHeight()) / 2);
    buttonTextShadow.setXY(buttonText.getX() + 1, buttonText.getY() + 1);

    invalidate();
}

RadioButton& EasingEquationButton::getRadioButton()
{
    return radioButton;
}

const EasingEquationSelection& EasingEquationButton::getEasingEquation() const
{
    return easingEquation;
}

void EasingEquationButton::setTextColor(colortype textColor, colortype shadowColor)
{
    buttonText.setColor(textColor);
    buttonTextShadow.setColor(shadowColor);

    buttonText.invalidate();
    buttonTextShadow.invalidate();
}

void EasingEquationButton::setTextShadowVisible(bool textShadowVisible)
{
    buttonTextShadow.setVisible(textShadowVisible);
    buttonTextShadow.invalidate();
}
