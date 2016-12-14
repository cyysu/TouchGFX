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
#ifndef PARALLAX_BACKGROUND_HPP
#define PARALLAX_BACKGROUND_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <gui/game2D_screen/CollectibleItem.hpp>

using namespace touchgfx;

class ParallaxBackground : public Container
{
public:
    ParallaxBackground(int16_t width, int16_t height);
    virtual ~ParallaxBackground();

    void startAnimation();
    void stopAnimation();

    void addPlayerCharacter(AnimatedImage& player);
    void addCollectibleItem(CollectibleItem& item);

    void setActiveTickInterval(int interval);

    virtual void handleTickEvent();
private:

    struct Layer
    {
        Image image0;
        Image image1;
        int animationUpdateSpeed;
        int animationWidth;
    };

    enum AnimationState
    {
        ANIMATION_RUNNING,
        NO_ANIMATION
    };

    AnimationState currentAnimationState;

    int tickInterval;

    int tickCounter;

    Layer background;
    Layer ground;
    Layer leaves;
    Layer treeTops;


    void initializeLayer(Layer& layer, BitmapId bmp, int animationUpdateSpeed, int animationWidth, int y);
    void moveLayer(Layer& layer, int tickCount);
};

#endif /* PARALLAX_BACKGROUND_HPP */
