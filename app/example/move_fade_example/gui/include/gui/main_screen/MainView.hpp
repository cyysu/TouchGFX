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
#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

/**
 * Example that shows how to use the two mixin classes FadeAnimator and MoveAnimator.
 */
class MainView : public View<MainPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    MainView();

    virtual ~MainView() { }

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen();

    void object0AnimationEndedHandler(const MoveAnimator<Image>& image);
    void object1AnimationEndedHandler(const FadeAnimator<Box>& box);
    void object2FadeAnimationEndedHandler(const FadeAnimator<MoveAnimator<Image> >& image);
    void object2MoveAnimationEndedHandler(const MoveAnimator<Image>& image);

private:
    Image imgBackground;

    MoveAnimator<Image> object0;
    FadeAnimator<Box> object1;
    FadeAnimator<MoveAnimator<Image> > object2;

    bool object0AnimationSwitch;
    bool object1AnimationSwitch;
    bool object2FadeAnimationSwitch;
    bool object2MoveAnimationSwitch;

    Callback<MainView, const MoveAnimator<Image>& > object0AnimationEndedCallback;
    Callback<MainView, const FadeAnimator<Box>& > object1AnimationEndedCallback;
    Callback<MainView, const FadeAnimator<MoveAnimator<Image> >& > object2FadeAnimationEndedCallback;
    Callback<MainView, const MoveAnimator<Image>& > object2MoveAnimationEndedCallback;
};

#endif // MAIN_VIEW_HPP

