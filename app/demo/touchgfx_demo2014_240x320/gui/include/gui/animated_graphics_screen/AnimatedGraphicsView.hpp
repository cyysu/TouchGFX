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
#ifndef ANIMATED_GRAPHICS_VIEW_HPP
#define ANIMATED_GRAPHICS_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsPresenter.hpp>
#include <gui/animated_graphics_screen/BumpMapImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Box.hpp>

class AnimatedGraphicsView : public View<AnimatedGraphicsPresenter>
{
public:
    AnimatedGraphicsView();
    virtual ~AnimatedGraphicsView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void handleDragEvent(const DragEvent& evt);

private:

    enum States
    {
        ANIMATE_SHADE_UP,
        NO_ANIMATION
    } currentState;

    struct
    {
        BitmapId image;
        const unsigned int* bump_map;
    } bumpMapInfo;

    uint32_t animationCounter;

    Box shade;
    BumpMapImage bumpMapImage;
    Button exitButton;

    Callback<AnimatedGraphicsView, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);
    void updateBumpMapImage();

    void animateShadeUp();
};

#endif // ANIMATED_GRAPHICS_VIEW_HPP
