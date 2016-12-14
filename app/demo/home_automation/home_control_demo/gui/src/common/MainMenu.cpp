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
#include <gui/common/MainMenu.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Menu::Menu() :
    buttonLayout(touchgfx::EAST)
{
    buttons[Blinds].setBitmaps(touchgfx::Bitmap(BITMAP_BLINDS_NORMAL_ID), touchgfx::Bitmap(BITMAP_BLINDS_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLINDS_HOVER_ID));
    buttons[AirCondition].setBitmaps(touchgfx::Bitmap(BITMAP_AIRCON_NORMAL_ID), touchgfx::Bitmap(BITMAP_AIRCON_PRESSED_ID), touchgfx::Bitmap(BITMAP_AIRCON_HOVER_ID));
    buttons[Lighting].setBitmaps(touchgfx::Bitmap(BITMAP_LIGHTING_NORMAL_ID), touchgfx::Bitmap(BITMAP_LIGHTING_PRESSED_ID), touchgfx::Bitmap(BITMAP_LIGHTING_HOVER_ID));
    buttons[Appliances].setBitmaps(touchgfx::Bitmap(BITMAP_APPLIANCES_NORMAL_ID), touchgfx::Bitmap(BITMAP_APPLIANCES_PRESSED_ID), touchgfx::Bitmap(BITMAP_APPLIANCES_HOVER_ID));
    buttons[Entertainment].setBitmaps(touchgfx::Bitmap(BITMAP_ENTERTAINMENT_NORMAL_ID), touchgfx::Bitmap(BITMAP_ENTERTAINMENT_PRESSED_ID), touchgfx::Bitmap(BITMAP_ENTERTAINMENT_HOVER_ID));
    buttons[Security].setBitmaps(touchgfx::Bitmap(BITMAP_SECURITY_NORMAL_ID), touchgfx::Bitmap(BITMAP_SECURITY_PRESSED_ID), touchgfx::Bitmap(BITMAP_SECURITY_HOVER_ID));
    buttons[Settings].setBitmaps(touchgfx::Bitmap(BITMAP_SETTINGS_NORMAL_ID), touchgfx::Bitmap(BITMAP_SETTINGS_PRESSED_ID), touchgfx::Bitmap(BITMAP_SETTINGS_HOVER_ID));

    int width = 0;

    for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++)
    {
        buttons[i].setCallback(menuCallbacks[i]);
        buttonLayout.add(buttons[i]);
        width += buttons[i].getWidth();
    }
    buttonLayout.setPosition(0, 0, width, buttons[Blinds].getHeight());
    add(buttonLayout);

    setHeight(buttons[Blinds].getHeight());
    setWidth(buttonLayout.getWidth());
}

void Menu::set(SelectedMenuItem selectedMenuItem)
{
    for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++)
    {
        buttons[i].setSelected(i == selectedMenuItem);
    }
    invalidate();
}

void Menu::bind(BasePresenter& presenter)
{
    menuCallbacks[Blinds] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onBlindsClicked);
    menuCallbacks[AirCondition] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onAirConditionClicked);
    menuCallbacks[Lighting] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onLightingClicked);
    menuCallbacks[Appliances] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onAppliancesClicked);
    menuCallbacks[Entertainment] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onEntertainmentClicked);
    menuCallbacks[Security] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onSecurityClicked);
    menuCallbacks[Settings] = touchgfx::Callback<BasePresenter, bool>(&presenter, &BasePresenter::onSettingsClicked);
}
