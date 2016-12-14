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
#ifndef EASINGEQUATIONSELECTOR_HPP
#define EASINGEQUATIONSELECTOR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <gui/easing_equation_screen/EasingEquationButton.hpp>

using namespace touchgfx;

class EasingEquationSelector : public Container
{
public:
    EasingEquationSelector();
    void setEasingEquationSelectedCallback(GenericCallback<const EasingEquationSelection&>& callback);
    void select(int index);

private:
    static const int NUMBER_OF_EQUATION_TYPES = 11;

    ListLayout easings;
    ScrollableContainer scrollable;
    RadioButtonGroup<NUMBER_OF_EQUATION_TYPES> equationsGroup;
    EasingEquationButton buttons[NUMBER_OF_EQUATION_TYPES];

    Callback<EasingEquationSelector, const AbstractButton&> onSelected;
    void selected(const AbstractButton& btn);

    GenericCallback<const EasingEquationSelection&>* easingEquationSelected;
};

#endif /* EASINGEQUATIONSELECTOR_HPP */
