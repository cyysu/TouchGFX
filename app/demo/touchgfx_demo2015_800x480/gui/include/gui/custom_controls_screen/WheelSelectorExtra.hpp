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
#ifndef DATE_PICKER_WHEEL_DAY_HPP
#define DATE_PICKER_WHEEL_DAY_HPP

#include <gui/custom_controls_screen/WheelSelector.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

/**
 * @class WheelSelectorExtra WheelSelectorExtra.hpp gui/custom_controls_screen/WheelSelectorExtra.hpp
 *
 * @brief A wheel selector that introduces a number of extra text areas in the bottom of the date
 *        picker.
 *
 *        A wheel selector that introduces a number of extra text areas in the bottom of the
 *        date picker. This allows the contents of the wheel selector to be changed.
 *
 * @note This widget is part of the TouchGFX Open Repository.
 *       https://github.com/draupnergraphics/touchgfx-open-repository
 *
* @see WheelSelector
 */
class WheelSelectorExtra : public WheelSelector
{
public:
    /**
     * @fn WheelSelectorDay::WheelSelectorDay();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    WheelSelectorExtra();

    /**
     * @fn virtual WheelSelectorDay::~WheelSelectorDay();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~WheelSelectorExtra();

    /**
     * @fn void WheelSelectorExtra::setupDatePickerWheelDay(int width, int height, int textXPosition, int textYPositionOfIndex0Selected, TEXTS wheelText, TEXTS wheelTextExtra0, TEXTS wheelTextExtra1, TEXTS wheelTextExtra2);
     *
     * @brief Sets up the date picker wheel.
     *
     *        Sets up the date picker wheel.
     *
     * @param width                         The width.
     * @param height                        The height.
     * @param textXPosition                 The text x coordinate position.
     * @param textYPositionOfIndex0Selected The text y coordinate position of index 0 selected.
     * @param wheelText                     The wheel text.
     * @param wheelTextExtra0               The wheel extra text 1.
     * @param wheelTextExtra1               The wheel extra text 2.
     * @param wheelTextExtra2               The wheel extra text 3.
     */
    void setupDatePickerWheelDay(int width, int height, int textXPosition, int textYPositionOfIndex0Selected, TEXTS wheelText, TEXTS wheelTextExtra0, TEXTS wheelTextExtra1, TEXTS wheelTextExtra2);

    /**
     * @fn virtual void WheelSelectorExtra::setTextColor(colortype normalColor, colortype selectedColor, colortype selectedBackgroundColor, int selectedYOffset = 0, int selectedHeight = 0);
     *
     * @brief Sets text color of normal/selected text.
     *
     *        Sets text color of normal/selected text. If the colors are the same, the overlays
     *        for showing selected text is hidden, otherwise it is setup with the given y
     *        coordinate offset.
     *
     * @param normalColor             The color of normal text.
     * @param selectedColor           The color of selected text.
     * @param selectedBackgroundColor The selected background color.
     * @param selectedYOffset         The selected area (where the text changes color) y coordinate
     *                                offset.
     * @param selectedHeight          The selected height.
     */
    virtual void setTextColor(colortype normalColor, colortype selectedColor, colortype selectedBackgroundColor, int selectedYOffset = 0, int selectedHeight = 0);
    /**
     * @fn void WheelSelectorExtra::fadeExtraText(int extraTextIndex, uint8_t endAlpha, uint16_t duration);
     *
     * @brief Fade extra texts.
     *
     *        Fade extra texts so the text list is smoothly extended or retracted.
     *
     * @param extraTextIndex Zero-based index of the extra text.
     * @param endAlpha       The end alpha.
     * @param duration       The duration.
     */
    void fadeExtraText(int extraTextIndex, uint8_t endAlpha, uint16_t duration);

protected:
    static const int NUMBER_OF_EXTRA_TEXTS = 3;

    FadeAnimator<MoveAnimator<TextArea> > textExtra[NUMBER_OF_EXTRA_TEXTS];
    FadeAnimator<MoveAnimator<TextArea> > textExtraSelected[NUMBER_OF_EXTRA_TEXTS];
    bool textExtraIsVisible[NUMBER_OF_EXTRA_TEXTS];

    virtual void moveText(int newYPosition);
    virtual void animateMoveText(int newYPosition, int duration, EasingEquation equation);
    void adjustBottomCutOff();
};


#endif /* DATE_PICKER_WHEEL_DAY_HPP */
