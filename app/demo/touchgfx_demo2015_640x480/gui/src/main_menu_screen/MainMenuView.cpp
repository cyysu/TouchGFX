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
#include <gui/main_menu_screen/MainMenuView.hpp>
#include <BitmapDatabase.hpp>

MainMenuView::MainMenuView() :
    selectedDemoScreenIndex(0),
    onToggleButtonPressed(this, &MainMenuView::toggleButtonPressedHandler)
{
    // ToggleMenuButton must be added by the specialized menu view (to get correct z-order)
    toggleMenuButton.setBitmaps(Bitmap(BITMAP_MENU_TOGGLE_BUTTON_ID), Bitmap(BITMAP_MENU_TOGGLE_BUTTON_PRESSED_ID));
    toggleMenuButton.setXY(20, 20);
    toggleMenuButton.setAction(onToggleButtonPressed);

    // MCULoad must be added by the specialized menu view (to get correct z-order)
    mcuLoadTxt.setXY(516, 20);
    mcuLoadTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    mcuLoadValueTxt.setPosition(mcuLoadTxt.getRect().right(), mcuLoadTxt.getY(), 34, 14);
    mcuLoadValueTxt.setColor(mcuLoadTxt.getColor());
}

MainMenuView::~MainMenuView()
{
}

void MainMenuView::setSelectedDemoScreen(int demoIndex)
{
    selectedDemoScreenIndex = demoIndex;
}

void MainMenuView::gotoSelectedDemoScreen()
{
    presenter->setSelectedDemoScreenIndex(selectedDemoScreenIndex);

    switch (demoIDs[selectedDemoScreenIndex])
    {
    case MainMenuView::PRODUCT_PRESENTER:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoProductPresenterScreen();
        break;
    case MainMenuView::GAME2048:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoGame2048Screen();
        break;
    case MainMenuView::GAME2D:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoGame2DScreen();
        break;
    case MainMenuView::CUSTOM_CONTROLS:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoCustomControlsScreen();
        break;
    case MainMenuView::GRAPH:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoGraphScreen();
        break;
    case MainMenuView::NO_DEMO_SCREEN:
        break;
    default:
        break;
    }
}

void MainMenuView::toggleButtonPressedHandler(const AbstractButton& button)
{
    // Clear the previous selected menu that is used for returning from
    // a demo screen to the menu. But when toggling between menus this
    // is not needed.
    presenter->setPreviousSelectedMenuType(MainMenuPresenter::NO_MENU);
    presenter->setSelectedDemoScreenIndex(0);
    toggleMenu();
}
