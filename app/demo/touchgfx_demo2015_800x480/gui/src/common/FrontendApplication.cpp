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
#include <gui/common/FrontendHeap.hpp>
#include <gui/main_menu_screen/MainMenuCarouselView.hpp>
#include <gui/main_menu_screen/MainMenuAnimatingButtonsView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <gui/product_presenter_screen/ProductPresenterView.hpp>
#include <gui/product_presenter_screen/ProductPresenterPresenter.hpp>
#include <gui/game2048_screen/Game2048View.hpp>
#include <gui/game2048_screen/Game2048Presenter.hpp>
#include <gui/game2D_screen/Game2DView.hpp>
#include <gui/game2D_screen/Game2DPresenter.hpp>
#include <gui/custom_controls_screen/CustomControlsView.hpp>
#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <gui/graph_screen/GraphView.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>
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

void FrontendApplication::gotoMainMenuCarouselScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuCarouselScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuCarouselScreenImpl()
{
    makeTransition< MainMenuCarouselView, MainMenuPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainMenuAnimatingButtonsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainMenuAnimatingButtonsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuAnimatingButtonsScreenImpl()
{
    makeTransition< MainMenuAnimatingButtonsView, MainMenuPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoProductPresenterScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoProductPresenterScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoProductPresenterScreenImpl()
{
    makeTransition< ProductPresenterView, ProductPresenterPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoGame2048Screen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoGame2048ScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoGame2048ScreenImpl()
{
    makeTransition< Game2048View, Game2048Presenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoGame2DScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoGame2DScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoGame2DScreenImpl()
{
    makeTransition< Game2DView, Game2DPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoCustomControlsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoCustomControlsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoCustomControlsScreenImpl()
{
    makeTransition< CustomControlsView, CustomControlsPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoGraphScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoGraphScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoGraphScreenImpl()
{
    makeTransition< GraphView, GraphPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
