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
#include <gui/data_visualization_screen/DataVisualizationView.hpp>
#include "BitmapDatabase.hpp"

DataVisualizationView::DataVisualizationView() :
    DemoView(),
    bottomContainer(EAST),
    onTimeIntervalButtonClicked(this, &DataVisualizationView::onTimeIntervalButtonClickedHandler)
{
}

DataVisualizationView::~DataVisualizationView()
{
}

void DataVisualizationView::setupScreen()
{
    interactiveGraph.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), 232);
    add(interactiveGraph);
    interactiveGraph.initialize();

    tabBack.setBitmap(Bitmap(BITMAP_GRAPH_TAB_BACK_ID));
    tabBack.setXY(backButton.getWidth(), interactiveGraph.getHeight());
    add(tabBack);

    sixHoursButton.setBitmaps(Bitmap(BITMAP_GRAPH_6HOURS_TAB_ID), Bitmap(BITMAP_GRAPH_6HOURS_TAB_PRESSED_ID));
    twelveHoursButton.setBitmaps(Bitmap(BITMAP_GRAPH_12HOURS_TAB_ID), Bitmap(BITMAP_GRAPH_12HOURS_TAB_PRESSED_ID));
    sevenDaysButton.setBitmaps(Bitmap(BITMAP_GRAPH_7DAYS_TAB_ID), Bitmap(BITMAP_GRAPH_7DAYS_TAB_PRESSED_ID));
    sixHoursButton.forceState(false);
    twelveHoursButton.forceState(true);
    sevenDaysButton.forceState(false);
    sixHoursButton.setAction(onTimeIntervalButtonClicked);
    twelveHoursButton.setAction(onTimeIntervalButtonClicked);
    sevenDaysButton.setAction(onTimeIntervalButtonClicked);

    bottomContainer.setXY(backButton.getWidth() + 118, interactiveGraph.getHeight() + 7);
    bottomContainer.add(sixHoursButton);
    bottomContainer.add(twelveHoursButton);
    bottomContainer.add(sevenDaysButton);
    add(bottomContainer);

    sixHoursBackTop.setBitmap(Bitmap(BITMAP_GRAPH_6HOURS_BACK_TOP_ID));
    sixHoursBackTop.setXY(interactiveGraph.getX(), interactiveGraph.getY());
    sixHoursBackTop.setVisible(false);
    add(sixHoursBackTop);
    barContainer.setXY(96, sixHoursBackTop.getHeight() - barContainer.getBarHeight());
    barContainer.setVisible(false);
    add(barContainer);

    sixHoursBackBottom.setBitmap(Bitmap(BITMAP_GRAPH_6HOURS_BACK_BOTTOM_ID));
    sixHoursBackBottom.setXY(interactiveGraph.getX(), interactiveGraph.getY() + sixHoursBackTop.getHeight());
    sixHoursBackBottom.setVisible(false);
    add(sixHoursBackBottom);

    sevenDaysBack.setBitmap(Bitmap(BITMAP_GRAPH_7DAYS_BACK_ID));
    sevenDaysBack.setPosition(interactiveGraph.getX(), interactiveGraph.getY(), interactiveGraph.getWidth(), interactiveGraph.getHeight());
    sevenDaysBack.setVisible(false);
    add(sevenDaysBack);
}

void DataVisualizationView::tearDownScreen()
{

}
