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
#ifndef EASING_EQUATION_BUTTON
#define EASING_EQUATION_BUTTON

#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <gui/easing_equation_screen/EasingEquations.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>

using namespace touchgfx;

class EasingEquationButton : public Container
{
public:
    EasingEquationButton();

    void setBitmaps();
    void setTextColor(colortype textColor, colortype shadowColor);
    void setTextShadowVisible(bool textShadowVisible);

    void setup(EasingEquationSelection newEasingEquation, const Bitmap& bmpUnselected, const Bitmap& bmpUnselectedPressed, const Bitmap& bmpSelected, const Bitmap& bmpSelectedPressed);
    const EasingEquationSelection& getEasingEquation() const;

    RadioButton& getRadioButton();

private:
    RadioButton radioButton;

    EasingEquationSelection easingEquation;

    TextArea buttonText;
    TextArea buttonTextShadow;
};

#endif /* EASING_EQUATION_BUTTON */
