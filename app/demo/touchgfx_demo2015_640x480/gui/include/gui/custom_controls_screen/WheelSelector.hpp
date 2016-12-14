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
#ifndef DATE_PICKER_WHEEL_HPP
#define DATE_PICKER_WHEEL_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#include <touchgfx/mixins/MoveAnimator.hpp>

using namespace touchgfx;

/**
 * @class WheelSelector WheelSelector.hpp gui/custom_controls_screen/WheelSelector.hpp
 *
 * @brief A wheel selector. Displays a text in a scrollable wheel.
 *
 *        A wheel selector. Displays a text in a scrollable wheel. Option to display the
 *        text in a different color near the selected element. Snaps to the nearest element
 *        after movement.
 *
 * @note This widget is part of the TouchGFX Open Repository.
 *       https://github.com/draupnergraphics/touchgfx-open-repository
 *
 * @sa Container
 */
class WheelSelector : public Container
{
public:
    /**
     * @fn WheelSelector::WheelSelector();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    WheelSelector();

    /**
     * @fn virtual WheelSelector::~WheelSelector();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~WheelSelector();

    virtual void handleDragEvent(const DragEvent& evt);

    /**
     * @fn virtual void WheelSelector::setup(int width, int height, int textXPosition, int textYPosition, int spaceBetweenTextRows, int selectedYOffset, TEXTS wheelText);
     *
     * @brief Setup method.
     *
     * @param width                The width of the container.
     * @param height               The height of the container.
     * @param textXPosition        The text x coordinate position.
     * @param textYPosition        The text y coordinate position.
     * @param wheelText            The wheel text.
     */
    virtual void setup(int width, int height, int textXPosition, int textYPosition, TEXTS wheelText);

    /**
     * @fn void WheelSelector::setTextColor(colortype normalColor, colortype selectedColor, colortype selectedBackgroundColor, int selectedYOffset = 0, int selectedHeight = 0);
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
    void setTextColor(colortype normalColor, colortype selectedColor, colortype selectedBackgroundColor, int selectedYOffset = 0, int selectedHeight = 0);

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);

    /**
     * @fn int WheelSelector::getSelectedIndex();
     *
     * @brief Gets selected index.
     *
     *        Gets selected index calculated from what is on screen.
     *
     * @return The selected index.
     */
    int getSelectedIndex();

    /**
     * @fn void WheelSelector::setSelectedIndex(int index, int duration, EasingEquation equation = EasingEquations::backEaseInOut);
     *
     * @brief Sets selected index.
     *
     *        Sets selected index by moving the wheel selector using the given easing equation.
     *
     * @param index    Zero-based index of the.
     * @param duration The duration.
     * @param equation The equation.
     */
    void setSelectedIndex(int index, int duration, EasingEquation equation = EasingEquations::backEaseInOut);

    /**
     * @fn void WheelSelector::reset();
     *
     * @brief Resets this object to show first element.
     *
     *        Resets this object to show first element.
     */
    void reset();

    void setElementSelectedCallback(touchgfx::GenericCallback<const WheelSelector&, const int&>& callback)
    {
        elementSelectedAction = &callback;
    }

protected:
    enum AnimationState
    {
        ANIMATING_GESTURE, ///< Animating a gesture
        ANIMATING_SNAP,    ///< Animating a 'snap' after a drag/gesture to align index
        ANIMATING_DRAG,    ///< Animating a click+drag
        NO_ANIMATION       ///< No animation
    };

    AnimationState currentAnimationState;

    Container textContainer; ///< Container for wheel text
    MoveAnimator<TextArea> text; ///< Wheel text
    Container textSelectedContainer; ///< Container for selected text when selection has a different color
    MoveAnimator<TextArea> textSelected; ///<
    Box textSelectedBackground;
    int selectedAreaYOffset;

    int selectedTextYPosition;
    int spaceBetweenTextRows;
    int topCutOff;
    int bottomCutOff;

    GenericCallback<const WheelSelector&, const int&>* elementSelectedAction;

    Callback<WheelSelector, const MoveAnimator<TextArea>& > textMoveEndedCallback;
    void textMoveEndedHandler(const MoveAnimator<TextArea>& textArea);

    virtual void moveText(int newYPosition);
    virtual void animateMoveText(int newYPosition, int duration, EasingEquation equation);

    void snap();
    void adjustForBoundries(int& newYValue);
};


#endif /* DATE_PICKER_WHEEL_HPP */
