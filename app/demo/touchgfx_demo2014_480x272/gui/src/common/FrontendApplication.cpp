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
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXView.hpp>
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXPresenter.hpp>
#include <gui/flow_presentation_screen/FlowPresentationView.hpp>
#include <gui/flow_presentation_screen/FlowPresentationPresenter.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsView.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsPresenter.hpp>
#include <gui/home_automation_screen/HomeAutomationView.hpp>
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/list_navigation_screen/ListNavigationView.hpp>
#include <gui/list_navigation_screen/ListNavigationPresenter.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayView.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayPresenter.hpp>
#include <gui/data_visualization_screen/DataVisualizationView.hpp>
#include <gui/data_visualization_screen/DataVisualizationPresenter.hpp>
#include <gui/clock_screen/ClockView.hpp>
#include <gui/clock_screen/ClockPresenter.hpp>
#include <gui/chrom_art_screen/ChromArtView.hpp>
#include <gui/chrom_art_screen/ChromArtPresenter.hpp>
#include <stdlib.h>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m),
      tickCounter(0),
      lastClickTime(0)
{
}

void FrontendApplication::handleTickEvent()
{
    model.tick();
    MVPApplication::handleTickEvent();

    // Screen saver functionality:
    // Jump to one of the preselected screens if
    // no action has been registered for a screenSaverTimeout (time in milliseconds)
    // (Only do the time check sometimes and not in the start)
    tickCounter++;
    if ((tickCounter % 100 == 0) && (tickCounter > 10000))
    {
        if ((model.getCurrentTime() - lastClickTime) >= SCREEN_SAVER_TIMEOUT)
        {
            uint8_t randomScreen = rand() % 3;

            switch (randomScreen)
            {
            case 0:
#ifdef REDUCED_PERFORMANCE
                gotoListNavigationScreen(true);
#else
                gotoAnimatedGraphicsScreen();
#endif
                break;
            case 1:
                gotoDataVisualizationScreen();
                break;
            case 2:
                gotoListNavigationScreen(true);
                break;
            default:
                break;
            }
            lastClickTime = model.getCurrentTime();
        }
    }

}

void FrontendApplication::handleClickEvent(const ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);

    // A click event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::resetScreenSaver()
{
    lastClickTime = model.getCurrentTime();
}

void FrontendApplication::gotoMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenImpl()
{
    makeTransition< MainView, MainPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenNoTransition()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenNoTransitionImpl()
{
    makeTransition< MainView, MainPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoNXPAndTouchGFXScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoNXPAndTouchGFXScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoNXPAndTouchGFXScreenImpl()
{
    makeTransition< NXPAndTouchGFXView, NXPAndTouchGFXPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoFlowPresentationScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoFlowPresentationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoFlowPresentationScreenImpl()
{
    makeTransition< FlowPresentationView, FlowPresentationPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoAnimatedGraphicsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoAnimatedGraphicsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoAnimatedGraphicsScreenImpl()
{
    makeTransition< AnimatedGraphicsView, AnimatedGraphicsPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoHomeAutomationScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoHomeAutomationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoHomeAutomationScreenImpl()
{
    makeTransition< HomeAutomationView, HomeAutomationPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoListNavigationScreen(bool play)
{
    musicPlayerPlay = play;
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoListNavigationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoListNavigationScreenImpl()
{
    ListNavigationPresenter* p = makeTransition< ListNavigationView, ListNavigationPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
    p->StartMusicPlayer(musicPlayerPlay);
}

void FrontendApplication::gotoLiveDataDisplayScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoLiveDataDisplayScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoLiveDataDisplayScreenImpl()
{
    makeTransition< LiveDataDisplayView, LiveDataDisplayPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoDataVisualizationScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoDataVisualizationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoDataVisualizationScreenImpl()
{
    makeTransition< DataVisualizationView, DataVisualizationPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoClockScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoClockScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoClockScreenImpl()
{
    makeTransition< ClockView, ClockPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoChromArtScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoChromArtScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoChromArtScreenImpl()
{
    makeTransition< ChromArtView, ChromArtPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
