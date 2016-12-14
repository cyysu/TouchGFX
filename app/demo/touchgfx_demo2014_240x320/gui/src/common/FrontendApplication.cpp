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
#include <gui/menu_screen/MenuView.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>
#include <gui/menu_screen/MenuView.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>
#include <gui/home_automation_screen/HomeAutomationView.hpp>
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsView.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsPresenter.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayView.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayPresenter.hpp>
#include <gui/chrom_art_screen/ChromArtView.hpp>
#include <gui/chrom_art_screen/ChromArtPresenter.hpp>
#include <gui/common/FrontendHeap.hpp>


FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::handleTickEvent()
{
    model.tick();
    MVPApplication::handleTickEvent();
}

void FrontendApplication::gotoMenuScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMenuScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMenuScreenImpl()
{
    makeTransition< MenuView, MenuPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMenuScreenNoAnimation()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMenuScreenNoAnimationImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMenuScreenNoAnimationImpl()
{
    makeTransition< MenuView, MenuPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoHomeAutomationScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoHomeAutomationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoHomeAutomationScreenImpl()
{
    makeTransition< HomeAutomationView, HomeAutomationPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoAnimatedGraphicsScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoAnimatedGraphicsScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoAnimatedGraphicsScreenImpl()
{
    makeTransition< AnimatedGraphicsView, AnimatedGraphicsPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoLiveDataDisplayScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoLiveDataDisplayScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoLiveDataDisplayScreenImpl()
{
    makeTransition< LiveDataDisplayView, LiveDataDisplayPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
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
