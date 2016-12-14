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
#include <gui/common/DotIndicator.hpp>
#include <BitmapDatabase.hpp>
#include <assert.h>


DotIndicator::DotIndicator() :
    unselectedDots(EAST),
    numberOfDots(0),
    currentDot(0)
{
    unselectedDots.setXY(0, 0);
    dotHighlighted.setXY(0, 0);

    add(unselectedDots);
    add(dotHighlighted);
}

DotIndicator::~DotIndicator()
{
}

void DotIndicator::setNumberOfDots(uint8_t size)
{
    numberOfDots = size;

    assert(numberOfDots > 0 && "At least one dot is needed");
    assert(numberOfDots <= MAX_SIZE && "Above maximum number of dots");

    unselectedDots.removeAll();
    for (int i = 0; i < numberOfDots; i++)
    {
        unselectedDots.add(dotNormal[i]);
    }
    // adjust size of container according to the actual bitmaps
    setWidth(unselectedDots.getWidth());
    setHeight(unselectedDots.getHeight());
    setHighlightPosition(currentDot = 0);
}

void DotIndicator::setBitmaps(const Bitmap& unselected, const Bitmap& selected)
{
    dotHighlighted.setBitmap(selected);
    for (int i = 0; i < MAX_SIZE - 1; i++)
    {
        dotNormal[i].setBitmap(unselected);
    }
    if (numberOfDots > 0)
    {
        setNumberOfDots(numberOfDots);
    }
}

void DotIndicator::goRight()
{
    setHighlightPosition(currentDot = (currentDot + 1) % numberOfDots);
}

void DotIndicator::goLeft()
{
    setHighlightPosition(currentDot = (currentDot + numberOfDots - 1) % numberOfDots);
}

void DotIndicator::setHighlightPosition(uint8_t index)
{
    // note that index is unsigned
    if (index < numberOfDots)
    {
        dotHighlighted.setX(index * dotNormal[0].getWidth());
    }
    invalidate();
}
