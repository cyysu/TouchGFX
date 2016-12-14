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
#ifndef FEATUREPOSTER_HPP
#define FEATUREPOSTER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <texts/TextKeysAndLanguages.hpp>


using namespace touchgfx;

class FeaturePoster : public Container
{
public:
    FeaturePoster();
    virtual ~FeaturePoster();

    void setup(BitmapId posterImage, TEXTS posterHeadline, TEXTS posterText, bool showAlphaExample);
    void invalidateText();

    void setHeadlineColor(colortype color);

    void toggleViewMode();

protected:
    enum State
    {
        SHOWING_IMAGE,
        SHOWING_TEXT
    };

    State currentState;

    Image shadow[4]; // Shadows around the poster

    Container posterArea;

    MoveAnimator<Image> posterImage;
    MoveAnimator<Button> startAnimationButton;
    MoveAnimator<AnimatedImage> startAnimationButtonArrow;

    FadeAnimator<Box> alphaBox;

    TextArea headlineBottom;

    MoveAnimator<TextArea> headlineTop;
    int headlineTopStartY;

    MoveAnimator<Container> textAreaContainer;
    Box textBackground;
    TextArea text;
    int textStartY;

    FadeAnimator<Image> gradientOverlay;

    Callback<FeaturePoster, const AbstractButton& > startAnimationCallback;
    void startAnimationHandler(const AbstractButton& button);

    void animate();

    MoveAnimator<Image> redBall;
    MoveAnimator<Image> greenBall;
    MoveAnimator<Image> blueBall;
    Callback<FeaturePoster, const MoveAnimator<Image>& > moveAnimationEnded;
    void moveAnimationEndedHandler(const MoveAnimator<Image>& image);
};

#endif /* FEATUREPOSTER_HPP */
