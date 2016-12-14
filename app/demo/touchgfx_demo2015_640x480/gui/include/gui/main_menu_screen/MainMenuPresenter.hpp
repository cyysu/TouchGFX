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
#ifndef MAIN_MENU_PRESENTER_HPP
#define MAIN_MENU_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class MainMenuView;

class MainMenuPresenter : public DemoPresenter
{
public:
    enum MainMenuType
    {
        ANIMATING_BUTTONS_MENU = 0,
        CAROUSEL_MENU,
        NO_MENU
    };

    MainMenuPresenter(MainMenuView& v);
    virtual ~MainMenuPresenter() {};

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    void setSelectedDemoScreenIndex(int elementIndex);
    void setPreviousSelectedMenuType(MainMenuType menuType);

    int getSelectedDemoScreenIndex();

    /**
     * @fn MainMenuType MainMenuPresenter::getPreviousSelectedMenuType();
     *
     * @brief Gets the previous selected menu type.
     *        Menu types are saved so that you can return to the same menu type
     *        when leaving a demo screen. NO_MENU is used when toggling between
     *        menus.
     *
     * @return The previous selected menu type.
     */
    MainMenuType getPreviousSelectedMenuType();

    virtual void screenSaverMinorTick();

private:
    MainMenuPresenter();
    MainMenuView& view;
};

#endif // MAIN_MENU_PRESENTER_HPP
