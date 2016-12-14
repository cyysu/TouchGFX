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
#include <gui/graph_screen/GraphBelow.hpp>

using namespace touchgfx;

bool GraphBelow::drawCanvasWidget(const Rect& invalidatedArea) const
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
        canvas.moveTo(widgetXindex(firstIndex), widgetYindex(firstIndex));
        for (int index = firstIndex + 1; index <= lastIndex; index++)
        {
            canvas.lineTo(widgetXindex(index), widgetYindex(index));
        }
        canvas.lineTo(widgetXindex(lastIndex), widgetY(0));
        canvas.lineTo(widgetXindex(firstIndex), widgetY(0));
        //            canvas.lineTo(widgetXindex(lastIndex), widgetY(bottom));
        //            canvas.lineTo(widgetXindex(firstIndex), widgetY(bottom));
        return canvas.render();
    }
    return true;
}

Rect GraphBelow::getMinimalRectContainingIndices(int firstIndex, int lastIndex) const
{
    int minX = widgetXindex(firstIndex).to<int>();
    int maxX = widgetXindex(lastIndex).to<int>();
    int zeroY = widgetY(0).to<int>();
    int firstY = widgetYindex(firstIndex).to<int>();
    int minY = MIN(zeroY, firstY);
    int maxY = MAX(zeroY, firstY);
    for (int index = firstIndex + 1; index <= lastIndex; index++)
    {
        int y = widgetYindex(index).to<int>();
        minY = MIN(minY, y);
        maxY = MAX(maxY, y);
    }

    return Rect(minX, minY, maxX - minX + 1, maxY - minY + 1);
}
