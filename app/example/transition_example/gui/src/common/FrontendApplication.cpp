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
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <touchgfx/transitions/NoTransition.hpp>

#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/left_screen/LeftView.hpp>
#include <gui/left_screen/LeftPresenter.hpp>
#include <gui/right_screen/RightView.hpp>
#include <gui/right_screen/RightPresenter.hpp>
#include <gui/down_screen/DownView.hpp>
#include <gui/down_screen/DownPresenter.hpp>
#include <gui/up_screen/UpView.hpp>
#include <gui/up_screen/UpPresenter.hpp>
#include <gui/common/FrontendHeap.hpp>


FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::gotoMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenImpl()
{
    makeTransition< MainView, MainPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenFromLeftScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromLeftScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromLeftScreenImpl()
{
    makeTransition< MainView, MainPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenFromRightScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromRightScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromRightScreenImpl()
{
    makeTransition< MainView, MainPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenFromDownScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromDownScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromDownScreenImpl()
{
    makeTransition< MainView, MainPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenFromUpScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromUpScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromUpScreenImpl()
{
    makeTransition< MainView, MainPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoLeftScreenFromMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoLeftScreenFromMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoLeftScreenFromMainScreenImpl()
{
    makeTransition< LeftView, LeftPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoRightScreenFromMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoRightScreenFromMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoRightScreenFromMainScreenImpl()
{
    makeTransition< RightView, RightPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoDownScreenFromMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoDownScreenFromMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoDownScreenFromMainScreenImpl()
{
    makeTransition< DownView, DownPresenter, SlideTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoUpScreenFromMainScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoUpScreenFromMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoUpScreenFromMainScreenImpl()
{
    makeTransition< UpView, UpPresenter, SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
