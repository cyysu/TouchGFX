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

void MainView::setupScreen()
{
    // Setup background
    imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    imgBackground.setXY(0, 0);

    // Initialize list elements
    listElements[0].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_0_ID));
    listElements[1].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_1_ID));
    listElements[2].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_2_ID));
    listElements[3].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_3_ID));
    listElements[4].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_4_ID));
    listElements[5].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_5_ID));
    listElements[6].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_6_ID));
    listElements[7].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_7_ID));
    listElements[8].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_8_ID));
    listElements[9].setupListElement(Bitmap(BITMAP_LIST_ELEMENT_9_ID));

    for (uint8_t i = 0; i < numberOfListElements; ++i)
    {
        listElements[i].setAction(listElementClickedCallback);
        list.add(listElements[i]);
    }

    // Position and set the size of the scrollable container.
    // The width is the area is the list element width plus some extra
    // for space between element and scrollbar
    scrollCnt.setPosition(29, 24, 273, 192);
    scrollCnt.add(list);

    // Remember to add widgets to container.
    // They must be added from bottom and out, or else upper layer(s)
    // may block view of elements below.
    add(imgBackground);
    add(scrollCnt);
}

void MainView::tearDownScreen()
{

}

void MainView::listElementClicked(CustomListElement& element)
{
    // The button of the list element has been pressed
    // so it is removed from the list
    list.remove(element);
    scrollCnt.invalidate();
}
