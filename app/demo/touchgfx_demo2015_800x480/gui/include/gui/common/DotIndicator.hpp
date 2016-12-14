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
#ifndef DOTINDICATOR_HPP_
#define DOTINDICATOR_HPP_

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ListLayout.hpp>

using namespace touchgfx;

/**
 * @class DotIndicator
 *
 * DotIndicator shows a number of small dots where one of the dots is highlighted.
 *
 * This widget is part of the TouchGFX Open Widget Repository.
 * https://github.com/draupnergraphics/touchgfx-widgets
 *
 * @see DotIndicator
 */
class DotIndicator : public Container
{
public:
    DotIndicator();
    virtual ~DotIndicator();

    /**
     * @fn void DotIndicator::setNumberOfDots(uint8_t size);
     *
     * @brief Sets the number of dots that should be displayed.
     *
     * @param size The size.
     */
    void setNumberOfDots(uint8_t size);

    /**
     * @fn void DotIndicator::setBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot);
     *
     * @brief Sets the bitmaps to be used for normal and highlighted dots. Note that the bitmaps should
     *        include the spacing between the dots and that they must have the same width and height.
     *
     * @param normalDot      The normal dot bitmap.
     * @param highlightedDot The highlighted dot bitmap.
     */
    void setBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot);

    /**
     * @fn void DotIndicator::goRight();
     *
     * @brief Highlight the dot to the right of the current highlighted dot.
     */
    void goRight();

    /**
     * @fn void DotIndicator::goLeft();
     *
     * @brief Highlight the dot to the left of the current highlighted dot
     */
    void goLeft();

    /**
     * @fn void DotIndicator::setHighlightPosition(uint8_t index);
     *
     * @brief Sets highlight position.
     *
     * @param index Zero-based index of the dot to be highlighted.
     */
    void setHighlightPosition(uint8_t index);
private:
    static const uint8_t MAX_SIZE = 10;

    ListLayout unselectedDots;
    Image dotHighlighted;
    Image dotNormal[MAX_SIZE];

    uint8_t numberOfDots;
    uint8_t currentDot;
};

#endif /* DOTINDICATOR_HPP_ */
