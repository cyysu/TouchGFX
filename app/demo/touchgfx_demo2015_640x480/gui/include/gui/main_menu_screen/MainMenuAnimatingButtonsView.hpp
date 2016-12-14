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
#ifndef MAIN_MENU_ANIMATING_BUTTONS_VIEW_HPP
#define MAIN_MENU_ANIMATING_BUTTONS_VIEW_HPP

#include <gui/main_menu_screen/MainMenuView.hpp>
#include <gui/main_menu_screen/MainMenuPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/common/ZoomAnimationBox.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class MainMenuAnimatingButtonsView : public MainMenuView
{
public:
    MainMenuAnimatingButtonsView();
    virtual ~MainMenuAnimatingButtonsView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void screenSaverMinorTick();
private:
    enum AnimationState
    {
        ANIMATE_BOX_IN,
        ANIMATE_BOX_OUT,
        ANIMATE_BUTTONS_FROM_BOX,
        ANIMATE_BUTTONS_INTO_BOX,
        ANIMATE_ICONS_AND_TEXT_IN,
        NO_ANIMATION
    };

    AnimationState currentAnimationState;

    static const int NUMBER_OF_BUTTONS = NUMBER_OF_DEMO_SCREENS;

    static const int BUTTONS_WIDTH = 250;
    static const int BUTTONS_HEIGHT = BUTTONS_WIDTH / NUMBER_OF_BUTTONS;
    static const int BUTTONS_SPACE = 10;

    Image background;
    ZoomAnimationBox startUpAnimationBox;

    MoveAnimator<Container> buttonContainers[NUMBER_OF_BUTTONS];
    Button buttons[NUMBER_OF_BUTTONS];
    FadeAnimator<Image> icons[NUMBER_OF_BUTTONS];
    FadeAnimator<MoveAnimator<TextArea> > texts[NUMBER_OF_BUTTONS];

    Callback<MainMenuAnimatingButtonsView, const ZoomAnimationBox&> startUpAnimationBoxDone;
    void StartupAnimationBoxDoneHandler(const ZoomAnimationBox& box);

    Callback<MainMenuAnimatingButtonsView, const MoveAnimator<Container>&> buttonAnimationDone;
    void buttonAnimationDoneHandler(const MoveAnimator<Container>& box);

    Callback<MainMenuAnimatingButtonsView, const AbstractButton&> buttonClicked;
    void buttonClickedHandler(const AbstractButton& button);

    Callback<MainMenuAnimatingButtonsView, const MoveAnimator<TextArea>&> textAnimationDone;
    void textAnimationDoneHandler(const MoveAnimator<TextArea>& t);

    virtual void toggleMenu();
};

#endif // MAIN_MENU_ANIMATING_BUTTONS_VIEW_HPP
