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
#include <new>
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <gui/main_menu_screen/MainMenuView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <gui/custom_controls_screen/CustomControlsView.hpp>
#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <gui/graph_screen/GraphView.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>
#include <gui/easing_equation_screen/EasingEquationView.hpp>
#include <gui/easing_equation_screen/EasingEquationPresenter.hpp>
#include <gui/product_presenter_screen/ProductPresenterView.hpp>
#include <gui/product_presenter_screen/ProductPresenterPresenter.hpp>
#include <stdlib.h>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m),
      tickCounter(0),
      screenSaverTick(0),
      lastClickTime(0)
{
}

void FrontendApplication::handleTickEvent()
{
    model.tick();
    MVPApplication::handleTickEvent();
    tickCounter++;

    // Screen saver functionality:
    if (lastClickTime.hasValue() && (model.getCurrentTime() - lastClickTime) >= SCREEN_SAVER_TIMEOUT)
    {
        screenSaverTick++;
        if (screenSaverTick % MINOR_TICK_FREQ == 0)
        {
            model.screenSaverMinorTick();
        }
        else if (screenSaverTick % MAJOR_TICK_FREQ == 0)
        {
            model.screenSaverMajorTick();
        }
    }

}

void FrontendApplication::handleClickEvent(const ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);

    // A click event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::handleDragEvent(const DragEvent& evt)
{
    MVPApplication::handleDragEvent(evt);

    // A drag event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::resetScreenSaver()
{
    lastClickTime = model.getCurrentTime();
    screenSaverTick = 0;
}

void FrontendApplication::gotoMainMenuScreenNoTransition()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuScreenNoTransitionImpl()
{
    makeTransition< MainMenuView, MainMenuPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainMenuScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuScreenImpl()
{
    makeTransition< MainMenuView, MainMenuPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoCustomControlsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoCustomControlsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoCustomControlsScreenImpl()
{
    makeTransition< CustomControlsView, CustomControlsPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoGraphScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoGraphScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoGraphScreenImpl()
{
    makeTransition< GraphView, GraphPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoEasingEquationScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoEasingEquationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoEasingEquationScreenImpl()
{
    makeTransition< EasingEquationView, EasingEquationPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoProductPresenterScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoProductPresenterScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoProductPresenterScreenImpl()
{
    makeTransition< ProductPresenterView, ProductPresenterPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
