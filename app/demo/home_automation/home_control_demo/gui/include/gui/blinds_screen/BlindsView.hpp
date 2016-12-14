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
#ifndef BLINDS_VIEW_HPP
#define BLINDS_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/blinds_screen/BlindsPresenter.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/common/JogWheel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/BlindsSelector.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

/**
 * BlindsView - control of blinds
 *
 * Select a number of blinds and adjust the blinds by turning clockwise or anticlockwise on the jogwheel.
 * When the jogwheel is released the blind setting is updated for the selected blinds.
 */
class BlindsView : public BaseView<BlindsPresenter>
{
public:
    BlindsView();
    virtual ~BlindsView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void setJogwheelActive(int16_t value);
    void setJogwheelInactive(bool animate = true);

    Room getRoomFromBlindId(int16_t selectedBlind);
    void setBlindPercentage(Room room, int16_t value);
private:
    ScrollableContainer blindsSelectorViewPort;
    BlindsSelector blindsSelector;

    static const int16_t INITIAL_TEMPERATURE = 0;
    static const int16_t JOGWHEEL_DELTA = 6;

    JogWheel jogWheel;
    FadeAnimator<TextAreaWithOneWildcard> jogWheelOutput;
    static const uint8_t JOG_WHEEL_OUTPUT_BUFFER_LENGTH = 5;
    Unicode::UnicodeChar jogWheelOutputTextBuffer[JOG_WHEEL_OUTPUT_BUFFER_LENGTH];
    FadeAnimator<Image> jogWheelPercentage;

    Callback<BlindsView, int16_t, uint16_t> onBlindsSelected;
    Callback<BlindsView, int16_t> onJogWheelValueChanged;
    Callback<BlindsView, int16_t> onJogWheelEndDragEvent;

    void blindsSelected(int16_t selectedBlind, uint16_t numberOfSelectedBlinds);
    void jogWheelValueChanged(int16_t value);
    void jogWheelEndDragEvent(int16_t value);
};

#endif
