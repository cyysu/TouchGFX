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
#ifndef MAIN_MENU_CAROUSEL_VIEW_HPP
#define MAIN_MENU_CAROUSEL_VIEW_HPP

#include <gui/main_menu_screen/MainMenuView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <gui/common/Carousel.hpp>

class MainMenuCarouselView : public MainMenuView
{
public:
    MainMenuCarouselView();
    virtual ~MainMenuCarouselView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void screenSaverMinorTick();
private:

    enum State
    {
        ELEMENT_SELECTED,
        NO_STATE
    };

    State currentState;

    Image background;

    Carousel carousel;


    TEXTS headlines[NUMBER_OF_DEMO_SCREENS];
    TEXTS texts[NUMBER_OF_DEMO_SCREENS];

    TextArea demoHeadline;
    TextArea demoText;

    int pauses;

    void setupCarousel();

    Callback<MainMenuCarouselView, const Carousel&> carouselAnimationEnded;
    void carouselAnimationEndedhandler(const Carousel& c);

    virtual void toggleMenu();
    void updateDemoText();

    int16_t dragDistance;
    bool dragInsideCarousel;
    bool dragInsideCenterButton;
    bool hasAnimatedDrag;
};

#endif // MAIN_MENU_CAROUSEL_VIEW_HPP
