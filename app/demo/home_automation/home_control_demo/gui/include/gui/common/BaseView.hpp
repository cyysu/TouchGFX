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
#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/common/BaseViewInterface.hpp>
#include <gui/common/BasePresenter.hpp>
#include <gui/common/MainMenu.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <gui/common/Layout.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>

using namespace touchgfx;

/**
 * In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically.
 *
 * All the screens in the demo have some common behaviour and functionality.
 * By created a base view and let all other screens derive from the base it is easy
 * to implement common functionality between multiple screens.
 *
 * In the demo all the screens contains a menu at the bottom of the screen. The remaining area is the specific view content always containing a background
 * and a headline.
 */
template<class T>
class BaseView : public View<T>, public BaseViewInterface
{
public:
    typedef BaseView<T> baseview;
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    BaseView() :
        menu()
    {
    }

    virtual ~BaseView() { }

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen()
    {
        menu.bind(*View<T>::presenter);
        menu.setXY(0, 0);

        menuContainer.setPosition(Layout::menu().x, Layout::menu().y, HAL::DISPLAY_WIDTH, menu.getHeight());
        menuContainer.add(menu);

        menuContainer.setScrollbarsVisible(false);

        content.setPosition(Layout::content().x, Layout::content().y, Layout::content().width, Layout::content().height);
        headline.setXY(Layout::headline().x, Layout::headline().y);

        background.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
        content.add(background);
        content.add(headline);

        View<T>::add(menuContainer);
        View<T>::add(content);
    }

    // Save the menu position in the model so that the menu
    // can stay positioned when switching between screen
    virtual int16_t getMenuPosition()
    {
        return menu.getX();
    }
    virtual void setMenuPosition(int16_t x)
    {
        menu.setX(x);
    }

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen() {}

protected:
    Container content;
    Menu menu;
    Image background;
    ScrollableContainer menuContainer;

    // headline must be set by the specific view
    Image headline;
};

#endif
