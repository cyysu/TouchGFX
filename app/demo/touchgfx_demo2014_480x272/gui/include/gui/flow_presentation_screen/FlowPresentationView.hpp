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
#ifndef FLOW_PRESENTATION_VIEW_HPP
#define FLOW_PRESENTATION_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/flow_presentation_screen/FlowPresentationPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/common/DotIndicator.hpp>

class FlowPresentationView : public DemoView<FlowPresentationPresenter>
{
public:
    FlowPresentationView();
    virtual ~FlowPresentationView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

private:
    enum States
    {
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    } currentState;

    uint8_t animationCounter;
    uint8_t foregroundIndex;
    uint16_t portViewWidth;
    uint16_t portViewHeight;
    uint8_t numberOfForegroundImages;

    Image background;
    Image backgroundExtension;

    Image foregroundImage0;
    Image foregroundImage1;
    Image foregroundImage2;
    Image foregroundImage3;

    Container foreground;
    Container flowPresentationViewPort;

    Button leftButton;
    Button rightButton;

    DotIndicator dotIndicator;

    Callback<FlowPresentationView, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);

    void setState(States newState);
    void animateLeft();
    void animateRight();
    void setButtonActiveState();

};

#endif // FLOW_PRESENTATION_VIEW_HPP
