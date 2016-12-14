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
#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Color.hpp>

MainView::MainView() :
    imageMenu(HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT, Bitmap(BITMAP_MENU_ITEM_DATA_VISUALIZATION_NORMAL_ID).getWidth(), BITMAP_MENU_LOGO_ID, BITMAP_DEMO_BACK_BUTTON_ID, BITMAP_DEMO_BACK_BUTTON_PRESSED_ID, BITMAP_MENU_DEMO_IN_PROGRESS_ID),
    onImageMenuItemSelected(this, &MainView::imageMenuItemSelected)
{
}

void MainView::setupScreen()
{
    background.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    background.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

    imageMenu.setXY(0, 0);

    imageMenu.addMenuItem(BITMAP_MENU_ITEM_FLOW_PRESENTATION_NORMAL_ID, BITMAP_MENU_ITEM_FLOW_PRESENTATION_PRESSED_ID, FLOW_PRESENTATION_SCREEN_ID, T_IMAGE_MENU_FLOW_PRESENTATION_HEADLINE, T_IMAGE_MENU_FLOW_PRESENTATION_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_DATA_VISUALIZATION_NORMAL_ID, BITMAP_MENU_ITEM_DATA_VISUALIZATION_PRESSED_ID, DATA_VISUALIZATION_SCREEN_ID, T_IMAGE_MENU_DATA_VISUALIZATION_HEADLINE, T_IMAGE_MENU_DATA_VISUALIZATION_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_LIST_NAVIGATION_NORMAL_ID, BITMAP_MENU_ITEM_LIST_NAVIGATION_PRESSED_ID, LIST_NAVIGATION_SCREEN_ID, T_IMAGE_MENU_LIST_NAVIGATION_HEADLINE, T_IMAGE_MENU_LIST_NAVIGATION_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_LIVE_DATA_DISPLAY_NORMAL_ID, BITMAP_MENU_ITEM_LIVE_DATA_DISPLAY_PRESSED_ID, LIVE_DATA_DISPLAY_SCREEN_ID, T_IMAGE_MENU_LIVE_DATA_DISPLAY_HEADLINE, T_IMAGE_MENU_LIVE_DATA_DISPLAY_TEXT, true);
#ifndef REDUCED_PERFORMANCE
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_ANIMATED_GRAPHICS_NORMAL_ID, BITMAP_MENU_ITEM_ANIMATED_GRAPHICS_PRESSED_ID, ANIMATED_GRAPHICS_SCREEN_ID, T_IMAGE_MENU_ANIMATED_GRAPHICS_HEADLINE, T_IMAGE_MENU_ANIMATED_GRAPHICS_TEXT, true);
#endif
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_HOME_AUTOMATION_NORMAL_ID, BITMAP_MENU_ITEM_HOME_AUTOMATION_PRESSED_ID, HOME_AUTOMATION_SCREEN_ID, T_IMAGE_MENU_HOME_AUTOMATION_HEADLINE, T_IMAGE_MENU_HOME_AUTOMATION_TEXT, true);

    // Choose between vendor specific screens
#ifdef SIMULATOR
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_NXP_AND_TOUCHGFX_NORMAL_ID, BITMAP_MENU_ITEM_NXP_AND_TOUCHGFX_PRESSED_ID, NXP_AND_TOUCHGFX_ID, T_IMAGE_MENU_NXP_AND_TOUCHGFX_HEADLINE, T_IMAGE_MENU_NXP_AND_TOUCHGFX_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_CHROM_ART_NORMAL_ID, BITMAP_MENU_ITEM_CHROM_ART_PRESSED_ID, CHROM_ART_SCREEN_ID, T_IMAGE_MENU_CHROM_ART_HEADLINE, T_IMAGE_MENU_CHROM_ART_TEXT, true);
#elif NXP
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_NXP_AND_TOUCHGFX_NORMAL_ID, BITMAP_MENU_ITEM_NXP_AND_TOUCHGFX_PRESSED_ID, NXP_AND_TOUCHGFX_ID, T_IMAGE_MENU_NXP_AND_TOUCHGFX_HEADLINE, T_IMAGE_MENU_NXP_AND_TOUCHGFX_TEXT, true);
#elif ST
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_CHROM_ART_NORMAL_ID, BITMAP_MENU_ITEM_CHROM_ART_PRESSED_ID, CHROM_ART_SCREEN_ID, T_IMAGE_MENU_CHROM_ART_HEADLINE, T_IMAGE_MENU_CHROM_ART_TEXT, true);
#endif

    imageMenu.addMenuItem(BITMAP_MENU_ITEM_CLOCK_NORMAL_ID, BITMAP_MENU_ITEM_CLOCK_PRESSED_ID, CLOCK_SCREEN_ID, T_IMAGE_MENU_CLOCK_HEADLINE, T_IMAGE_MENU_CLOCK_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MENU_ITEM_ABOUT_TOUCHGFX_NORMAL_ID, BITMAP_MENU_ITEM_ABOUT_TOUCHGFX_PRESSED_ID, ABOUT_TOUCHGFX_SCREEN_ID, T_IMAGE_MENU_ABOUT_HEADLINE, T_IMAGE_MENU_ABOUT_TEXT, false);


    imageMenu.setMenuItemSelectedCallback(onImageMenuItemSelected);

    add(background);
    add(imageMenu);
}

void MainView::tearDownScreen()
{

}

void MainView::imageMenuItemSelected(const uint8_t callbackID)
{
    switch (callbackID)
    {
    case FLOW_PRESENTATION_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoFlowPresentationScreen();
        break;
    case NXP_AND_TOUCHGFX_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoNXPAndTouchGFXScreen();
        break;
    case ANIMATED_GRAPHICS_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoAnimatedGraphicsScreen();
        break;
    case HOME_AUTOMATION_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoHomeAutomationScreen();
        break;
    case LIST_NAVIGATION_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoListNavigationScreen(false);
        break;
    case LIVE_DATA_DISPLAY_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoLiveDataDisplayScreen();
        break;
    case DATA_VISUALIZATION_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoDataVisualizationScreen();
        break;
    case CALENDER_SCREEN_ID:
        //static_cast<FrontendApplication*>(Application::getInstance())->gotoDataVisualizationScreen();
        break;
    case CLOCK_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoClockScreen();
        break;
    case CHROM_ART_SCREEN_ID:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoChromArtScreen();
        break;
    case SETTINGS_SCREEN_ID:
        //static_cast<FrontendApplication*>(Application::getInstance())->gotoDataVisualizationScreen();
        break;
    case ABOUT_TOUCHGFX_SCREEN_ID:
        break;
    default:
        break;
    }
}


