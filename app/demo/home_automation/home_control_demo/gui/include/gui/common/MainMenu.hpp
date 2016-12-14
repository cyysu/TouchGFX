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
#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/events/ClickEvent.hpp>
#include <touchgfx/Callback.hpp>
#include <gui/common/MenuButton.hpp>
#include <gui/common/BasePresenter.hpp>

/**
 * Handle the menu placed at the bottom in all the demo screens.
 */
class Menu : public Container
{
public:

    enum SelectedMenuItem
    {
        Blinds, AirCondition, Lighting, Appliances, Entertainment, Security, Settings
    };
    static const uint8_t NUMBER_OF_MENU_ITEMS = Settings + 1;

    Menu();

    void bind(BasePresenter& presenter);

    void set(SelectedMenuItem selectedMenuItem);

private:
    MenuButton buttons[NUMBER_OF_MENU_ITEMS];
    Callback<BasePresenter, bool> menuCallbacks[NUMBER_OF_MENU_ITEMS];

    ListLayout buttonLayout;
};

#endif
