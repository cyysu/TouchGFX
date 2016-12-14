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
#include <gui/common/FadeTransition.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <gui/system/Clock.hpp>
#ifdef SIMULATOR
#include <stdio.h>
#endif

using namespace touchgfx;

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m),
      washingMachineSimulator(m),
      lastInteraction(System::ClockFactory::getClock()->getTime()),
      timeoutDisabled(false)
{
}

void FrontendApplication::handleKeyEvent(uint8_t key)
{
#ifdef SIMULATOR
    if (static_cast<uint8_t>('t') == key)
    {
        timeoutDisabled = !timeoutDisabled;
        printf("Timeout is: %s\n", (timeoutDisabled ? "Disabled" : "Enabled"));
    }
#endif
}

void FrontendApplication::handleTickEvent()
{
    MVPApplication::handleTickEvent();

    model.setCurrentDateTime(System::ClockFactory::getClock()->getTime());

    // goto home screen if no activation
    if (model.isInactivationNeeded() && System::ClockFactory::getClock()->getTime() - lastInteraction > MAX_INACTIVE_SECONDS && (! timeoutDisabled))
    {
        // the functionality has been disabled in the demo
        //gotoHomeScreen();
    }

    // simulation of physical units
    washingMachineSimulator.handleTickEvent(System::ClockFactory::getClock()->getTime());
}

void FrontendApplication::handleClickEvent(const touchgfx::ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);
    lastInteraction = System::ClockFactory::getClock()->getTime();
}

void FrontendApplication::handleDragEvent(const touchgfx::DragEvent& evt)
{
    MVPApplication::handleDragEvent(evt);
    lastInteraction = System::ClockFactory::getClock()->getTime();
}
void FrontendApplication::handleGestureEvent(const touchgfx::GestureEvent& evt)
{
    MVPApplication::handleGestureEvent(evt);
    lastInteraction = System::ClockFactory::getClock()->getTime();
}

void FrontendApplication::gotoInitialHomeScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoInitialHomeScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoInitialHomeScreenImpl()
{
    makeTransition< HomeView, HomePresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoHomeScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoHomeScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoHomeScreenImpl()
{
    makeTransition< HomeView, HomePresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoBlindsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoBlindsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoBlindsScreenImpl()
{
    makeTransition< BlindsView, BlindsPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoAirConditionScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoAirConditionScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoAirConditionScreenImpl()
{
    makeTransition< AirConditionView, AirConditionPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoLightingScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoLightingScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoLightingScreenImpl()
{
    makeTransition< LightingView, LightingPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoAppliancesScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoAppliancesScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoAppliancesScreenImpl()
{
    makeTransition< AppliancesView, AppliancesPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoEntertainmentScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoEntertainmentScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoEntertainmentScreenImpl()
{
    makeTransition< EntertainmentView, EntertainmentPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSecurityScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSecurityScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}
void FrontendApplication::gotoSecurityScreenImpl()
{
    makeTransition< SecurityView, SecurityPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSettingsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSettingsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSettingsScreenImpl()
{
    makeTransition< SettingsView, SettingsPresenter, FadeTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
