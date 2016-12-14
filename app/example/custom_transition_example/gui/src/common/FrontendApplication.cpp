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
#include <gui/common/CustomTransition.hpp>
#include <gui/first_screen/FirstView.hpp>
#include <gui/first_screen/FirstPresenter.hpp>
#include <gui/second_screen/SecondView.hpp>
#include <gui/second_screen/SecondPresenter.hpp>
#include <gui/common/FrontendHeap.hpp>


FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::gotoFirstScreen()
{
    //Setup the callback to point at the function to be called when ready for transition.
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoFirstScreenImpl);

    //Set the pendingScreenTransitionCallback to indicate that a transition should start.
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoFirstScreenNoTrans()
{
    //Setup the callback to point at the function to be called when ready for transition.
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoFirstScreenNoTransImpl);

    //Set the pendingScreenTransitionCallback to indicate that a transition should start.
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSecondScreen()
{
    //Setup the callback to point at the function to be called when ready for transition.
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSecondScreenImpl);

    //Set the pendingScreenTransitionCallback to indicate that a transition should start.
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoFirstScreenImpl()
{
    //Make the transition. Note that the CustomTransition type is specified.
    //Remember to add the CustomTransition to the TransitionTypes list in the FrontendHeap. The same goes for View, Presenter and Model.
    makeTransition< FirstView, FirstPresenter, CustomTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoFirstScreenNoTransImpl()
{
    //Make the transition using the NoTransition.
    makeTransition< FirstView, FirstPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}


void FrontendApplication::gotoSecondScreenImpl()
{
    //Make the transition. Note that the CustomTransition type is specified.
    //Remember to add the CustomTransition to the TransitionTypes list in the FrontendHeap. The same goes for View, Presenter and Model.
    makeTransition< SecondView, SecondPresenter, CustomTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
