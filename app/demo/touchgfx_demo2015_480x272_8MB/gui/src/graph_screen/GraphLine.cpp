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
#include <gui/graph_screen/GraphLine.hpp>

using namespace touchgfx;

bool GraphLine::drawCanvasWidget(const Rect& invalidatedArea) const
{
    if (numPoints < 2)
    {
        // A graph line with a single (or not even a single) point is invisible
        return true;
    }

    int firstIndex = 0;
    int lastIndex = numPoints - 1;

    // We can skip the line from index if the left part of the line at index+1 is to the left of the invalidated area
    while (firstIndex < lastIndex &&
            invalidatedArea.x > (widgetXindex(firstIndex + 1) + lineWidth / 2).to<int>())
    {
        firstIndex++;
    }
    // We can skip the line from index if the left part of the line at index-1 is to the right of the invalidated area
    while (lastIndex > firstIndex &&
            invalidatedArea.right() < (widgetXindex(lastIndex - 1) - lineWidth / 2).to<int>())
    {
        lastIndex--;
    }
    if (firstIndex < lastIndex)
    {
        Canvas canvas(this, invalidatedArea);
        canvas.moveTo(xAboveOutgoing(firstIndex), yAboveOutgoing(firstIndex));
        canvas.lineTo(xAboveIncoming(firstIndex + 1), yAboveIncoming(firstIndex + 1));
        for (int index = firstIndex + 1; index < lastIndex; index++)
        {
            canvas.lineTo(xAboveOutgoing(index), yAboveOutgoing(index));
            canvas.lineTo(xAboveIncoming(index + 1), yAboveIncoming(index + 1));
        }
        for (int index = lastIndex - 1; index >= firstIndex; index--)
        {
            canvas.lineTo(xBelowIncoming(index + 1), yBelowIncoming(index + 1));
            canvas.lineTo(xBelowOutgoing(index), yBelowOutgoing(index));
        }
        return canvas.render();
    }
    return true;
}

Rect GraphLine::getMinimalRectContainingIndices(int firstIndex, int lastIndex) const
{
    int minX = (widgetXindex(firstIndex) - lineWidth / 2).to<int>();
    int maxX = (widgetXindex(lastIndex) + lineWidth / 2).to<int>();
    int minY = (widgetYindex(firstIndex) - lineWidth / 2).to<int>();
    int maxY = (widgetYindex(firstIndex) + lineWidth / 2).to<int>();
    for (int index = firstIndex + 1; index <= lastIndex; index++)
    {
        minY = MIN(minY, (widgetYindex(index) - lineWidth / 2).to<int>());
        maxY = MAX(maxY, (widgetYindex(index) + lineWidth / 2).to<int>());
    }

    Rect minimalRect = Rect(minX, minY, maxX - minX + 1, maxY - minY + 1);

    return minimalRect;
}
