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
#ifndef EASINGEQUATIONVIEW_HPP
#define EASINGEQUATIONVIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/easing_equation_screen/EasingEquationPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/easing_equation_screen/EasingEquationSelector.hpp>
#include <gui/easing_equation_screen/EasingEquationInOrOutOrInOut.hpp>
#include <gui/easing_equation_screen/EasingEquationGraph.hpp>

using namespace touchgfx;

class EasingEquationView : public DemoView<EasingEquationPresenter>
{
public:
    EasingEquationView();
    virtual ~EasingEquationView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

private:
    static const int GRAPH_MULT = 6;
    static const int NUMBER_OF_STEPS = 50;
    static const int GRAPH_Y_VALUE_OFFSET = -30;
    static const int PAUSE_DURATION = 20;

    int tickCounter;
    int moveAnimationCounter;

    Image background;
    Image dot;
    EasingEquationSelector selector;
    EasingEquationInOrOutOrInOut inOrOut;
    TextArea easingEquationName;

    EasingEquationSelection easingEquationSelection;
    EasingEquationsInOrOut inOrOutType;
    EasingEquation easingEquation;

    EasingEquationGraph graph;
    Image graphDot;
    bool drawGraph;

    Callback<EasingEquationView, const EasingEquationSelection&> onEasingEquationSelected;
    void easingEquationSelected(const EasingEquationSelection& selection);

    Callback<EasingEquationView, EasingEquationsInOrOut> onInOrOutSelected;
    void inOrOutSelected(EasingEquationsInOrOut newInOrOutType);

    void updateEasingEquation();
};

#endif /* EASINGEQUATIONVIEW_HPP */
