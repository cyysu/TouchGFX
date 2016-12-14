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
#ifndef CUSTOM_CONTROLS_VIEW_HPP
#define CUSTOM_CONTROLS_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <gui/custom_controls_screen/ThreeWayProgressBar.hpp>
#include <gui/custom_controls_screen/CircularProgress.hpp>
#include <gui/custom_controls_screen/DatePicker.hpp>
#include <gui/custom_controls_screen/Gauge.hpp>
#include <gui/custom_controls_screen/VerticalSlideMenu.hpp>

class CustomControlsView : public DemoView<CustomControlsPresenter>
{
public:
    CustomControlsView();
    virtual ~CustomControlsView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    virtual void screenSaverMinorTick();

private:
    Image menuBackground;
    Image background;
    Button menuUp;
    Button menuDown;
    Callback<CustomControlsView, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);


    VerticalSlideMenu slideMenu;
    Callback<CustomControlsView, const VerticalSlideMenu& > slideMenuElementSelectedCallback;
    void slideMenuElementSelectedHandler(const VerticalSlideMenu& menu);

    FadeAnimator<TextArea> statusMessage;

    ThreeWayProgressBar threeWayProgressBar;
    Callback<CustomControlsView, const ThreeWayProgressBar& > threeWayButtonPressedCallback;
    void threeWayButtonPressedHandler(const ThreeWayProgressBar& button);

    CircularProgress percentageBar;
    DatePicker datePicker;
    Gauge gauge;

    // Animation members
    enum AnimationState
    {
        ANIMATION_THREE_WAY_RUNNING,
        ANIMATION_GAUGE,
        NO_ANIMATION
    };

    AnimationState currentAnimationState;

    int animationCounter;
    int tickCounter;

    // ThreeWayProgressBar animation
    static const int NUMBER_OF_BARS = 3;
    AnimationState barAnimationState[NUMBER_OF_BARS];
    int animationDuration[NUMBER_OF_BARS];
    EasingEquation animationEquation[NUMBER_OF_BARS];

    AnimationState getAnimationState();
    EasingEquation getRandomEasingEquation();
    void startThreeWayProgressBarAnimation();
    void stopThreeWayProgressBarAnimation();
};

#endif // CUSTOM_CONTROLS_VIEW_HPP
