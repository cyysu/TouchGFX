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
#ifndef NXP_AND_TOUCHGFX_VIEW_HPP
#define NXP_AND_TOUCHGFX_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/common/DotIndicator.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/Bitmap.hpp>

using namespace touchgfx;


class NXPAndTouchGFXView : public DemoView<NXPAndTouchGFXPresenter>
{
public:
    NXPAndTouchGFXView();
    virtual ~NXPAndTouchGFXView();
    virtual void setupScreen();
    virtual void tearDownScreen();

private:
    static const uint8_t NUMBER_OF_PAGES = 4;

    enum States
    {
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    } currentState;

    struct PageBitmaps
    {
        BitmapId image;
        BitmapId textTop;
        BitmapId text;
        PageBitmaps(BitmapId image, BitmapId textTop, BitmapId text) :
            image(image),
            textTop(textTop),
            text(text)
        {
        }
        PageBitmaps() {}
    };
    PageBitmaps pageBitmaps[NUMBER_OF_PAGES];

    // animation helper members
    uint8_t animationCounter;
    int16_t animationTextTopStartPositionX;
    int16_t animationNextTextTopStartPositionX;
    int16_t animationTextBoxStartPositionX;
    int16_t animationNextTextBoxStartPositionX;

    uint8_t pageShowing;
    uint8_t nextPageShowing;

    // image (left side)
    Image imageGradient;
    Container imagePanel;
    Image currentImage;
    Image imageBackground;

    // text top
    Container textTopPanel;
    Image currentTextTop, nextTextTop;
    Image textTopBackground;

    // textbox (right side)
    ScrollableContainer textBoxViewPort;
    Image currentTextBox, nextTextBox;
    Image textboxGradient;
    Image textboxBackground;

    // navigation panel + dotIndicator (right side, bottom)
    ListLayout navigationPanel;
    Button leftButton;
    Button rightButton;
    Image buttonGradient;
    DotIndicator dotIndicator;

    Callback<NXPAndTouchGFXView, const AbstractButton&> onAnimateButtonClicked;

    void animateButtonClickedHandler(const AbstractButton& button);

    void updateAnimationButtonStates();
    virtual void handleTickEvent();
    void animate();
};

#endif // NXP_AND_TOUCHGFX_VIEW_HPP
