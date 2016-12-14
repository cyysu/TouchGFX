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


class MainMenuView : public DemoView<MainMenuPresenter>
{
public:
    enum DemoID
    {
        PRODUCT_PRESENTER = 0,
        GAME2048,
        GAME2D,
        CUSTOM_CONTROLS,
        GRAPH,
        NUMBER_OF_DEMO_SCREENS,
        NO_DEMO_SCREEN
    };

    MainMenuView();
    virtual ~MainMenuView();

    virtual void setupScreen() = 0;
    virtual void tearDownScreen() = 0;

    virtual void screenSaverMinorTick() = 0;
protected:

    DemoID demoIDs[NUMBER_OF_DEMO_SCREENS];
    int selectedDemoScreenIndex;

    Button toggleMenuButton;
    Callback<MainMenuView, const AbstractButton&> onToggleButtonPressed;
    void toggleButtonPressedHandler(const AbstractButton& button);

    void setSelectedDemoScreen(int demoIndex);
    void gotoSelectedDemoScreen();

    virtual void toggleMenu() = 0;
};

#endif // MAIN_MENU_VIEW_HPP
