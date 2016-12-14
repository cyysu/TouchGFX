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
#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

void MainView::setupScreen()
{
    // NOTE: The initial setup of the CanvasWidgetRenderer is done in simulator/main.cpp and target/main.cpp

    /*
     * Setup background
     */
    background.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    background.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));

    /*
     * Setup the painters
     */
    myColorPainter.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0xFF));
    myBitmapPainter.setBitmap(Bitmap(BITMAP_PAINTER_BACKGROUND_ID));
    myBitmapPainter2.setBitmap(Bitmap(BITMAP_PAINTER_BACKGROUND2_ID));

    /*
     * Setup the circle surrounding the clockHand
     */
    circle.setPosition(70, 30, 126, 126);
    circle.setCenter(circle.getWidth() / 2, circle.getHeight() / 2);
    circle.setRadius(60);
    circle.setLineWidth(4);
    circle.setPainter(myBitmapPainter);

    /*
     * Setup the clockHand
     */
    clockHand.setWidth(100);
    clockHand.setHeight(100);
    clockHand.setXY(circle.getX() + ((circle.getWidth() - clockHand.getWidth()) / 2), circle.getY() + ((circle.getHeight() - clockHand.getHeight()) / 2));
    clockHand.setOrigin((float)(clockHand.getWidth() / 2), (float)(clockHand.getHeight() / 2));
    clockHand.setPainter(myBitmapPainter2);

    /*
     * Setup the arc
     */
    arc.setPosition(284, 30, 126, 126);
    arc.setCenter(arc.getWidth() / 2, arc.getHeight() / 2);
    arc.setRadius(60);
    arc.setLineWidth(6);
    arc.setPainter(myColorPainter);
    arc.setArc(0, 0);

    /*
     * Setup the line
     */
    line.setPosition(100, 200, 200, 40);
    line.setStart(6, 6);
    line.setEnd(194, 30);
    line.setLineWidth(4);
    line.setPainter(myColorPainter);

    add(background);
    add(circle);
    add(line);
    add(clockHand);
    add(arc);

    tickCounter = 0;
    arcAdvance = true;
}

void MainView::handleTickEvent()
{
    tickCounter++;

    // Update the clockHand angle
    clockHand.updateAngle((clockHand.getAngle() + 1) % 360);

    // Update the angles of the arc
    int arcStart;
    int arcEnd;

    if (arcAdvance)
    {
        arcStart = (arc.getArcStart() + 1);
        arcEnd = (arc.getArcEnd() + 2);

        arcAdvance = (arcEnd < arcStart + 360);
    }
    else
    {
        arcStart = (arc.getArcStart() - 1);
        arcEnd = (arc.getArcEnd() - 2);

        arcAdvance = (arcEnd <= arcStart);
    }

    arc.updateArcStart(arcStart);
    arc.updateArcEnd(arcEnd);
}

