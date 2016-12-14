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
#ifndef MAIN_MENU_VIEW_HPP
#define MAIN_MENU_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <gui/common/SwipeContainer.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class MainMenuView : public DemoView<MainMenuPresenter>
{
public:
    MainMenuView();
    virtual ~MainMenuView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    void setSelectedMenuIndex(uint8_t demoIndex);

    virtual void afterTransition();
protected:
    static const int NUMBER_OF_DEMO_SCREENS = 4;

    MainMenuPresenter::DemoID demoScreenIndex[NUMBER_OF_DEMO_SCREENS];

    Image backgroundLeft;
    Image backgroundRight;

    Container demoScreensContainer[NUMBER_OF_DEMO_SCREENS];
    Image demoScreens[NUMBER_OF_DEMO_SCREENS];
    Button demoScreensButton[NUMBER_OF_DEMO_SCREENS];

    SwipeContainer menuContainer;

    Callback<MainMenuView, const AbstractButton& > buttonPressedCallback;

    Callback<MainMenuView, const SwipeContainer&> menuStateChangeInitiatedCallback;
    Callback<MainMenuView, const SwipeContainer&> menuStateChangeEndedCallback;

    void menuStateChangeInitiatedHandler(const SwipeContainer& sc);
    void menuStateChangeEndedHandler(const SwipeContainer& sc);

    void buttonPressedHandler(const AbstractButton& button);

    void gotoSelectedDemoScreen(uint8_t demoIndex);
};

#endif // MAIN_MENU_VIEW_HPP
