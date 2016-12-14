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
#include <gui/drag_screen/DragView.hpp>

void DragView::setupScreen()
{
    //Set the background bitmap and its position
    background.setBitmap((Bitmap(BITMAP_DRAGNDROP_BG_ID)));
    background.setXY(0, 0);

    //Set the bitmap of the snapRegion and its position.
    snapRegion.setBitmap(Bitmap(BITMAP_DROP_INDICATOR_ID));
    snapRegion.setXY(276, 58);
    snapRegion.setVisible(false);

    //Set the bitmaps of the dragButton and set the position to where the originSnapRegion is located.
    snapButton.setBitmaps(Bitmap(BITMAP_CHIP_DROPPED_ID), Bitmap(BITMAP_CHIP_DRAG_ID));
    snapButton.setXY(origSnapX, origSnapY);

    //Set a callback to handle events when the snapButton being dragged.
    snapButton.setDragAction(buttonDraggedCallback);

    //Set a callback to handle events when the snapButton snappes (drag ends).
    snapButton.setSnappedAction(buttonSnappedCallback);

    //Add the content to the container.
    add(background);
    add(snapRegion);
    add(snapButton);
}

void DragView::buttonDragged(const touchgfx::DragEvent& evt)
{
    //Check if the button is inside the snapRegion
    if (snapButton.getAbsoluteRect().intersect(snapRegion.getAbsoluteRect()))
    {
        //If the dragButton intersects with the snapRegion we want it to snap to this region if the drag ends.
        snapButton.setSnapPosition(snapRegion.getX() + 44, snapRegion.getY() + 44);

        // Graphically show that the snapregion is the target drop point
        snapRegion.setVisible(true);
        snapRegion.invalidate();
    }
    else
    {
        //If the dragButton does not intersect with the snapRegion, make it snap back to the original position.
        snapButton.setSnapPosition(origSnapX, origSnapY);

        // Graphically show that the snapregion is not the target drop point
        snapRegion.setVisible(false);
        snapRegion.invalidate();
    }
}

void DragView::buttonSnapped()
{
    // A drag of the snapButton has ended so he
    // snapregion is not the target drop point anymore
    snapRegion.setVisible(false);
    snapRegion.invalidate();
}


