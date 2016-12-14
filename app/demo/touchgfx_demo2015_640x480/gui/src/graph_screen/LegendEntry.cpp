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
#include <gui/graph_screen/LegendEntry.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

LegendEntry::LegendEntry() :
    onButtonPressed(this, &LegendEntry::buttonPressedHandler)
{
    square.setBitmap(Bitmap(BITMAP_PIE_CHART_LEGEND_BLUE_ID));
    square.setXY(0, 0);
    add(square);

    text.setColor(Color::getColorFrom24BitRGB(0xBE, 0xC0, 0xC4));
    text.setPosition(square.getRect().right() + 6, 6, 60, 16);
    add(text);

    valueText.setWildcard(valueTextBuffer);
    valueText.setTypedText(TypedText(T_GRAPH_LEGEND_VALUE_TEXT));
    valueText.setColor(text.getColor());
    valueText.setPosition(text.getRect().right() + 6, text.getY(), 40, 16);
    add(valueText);

    setWidth(valueText.getRect().right());
    setHeight(square.getRect().bottom() + 20); // Add a little extra height to make it easier to press

    // SelectButton is an invisible button
    selectButton.setPosition(0, 0, getWidth(), getHeight());
    selectButton.setAction(onButtonPressed);
    add(selectButton);
}

LegendEntry::~LegendEntry()
{

}


void LegendEntry::setBitmaps(BitmapId squareNotSelectedBmp, BitmapId squareSelectedBmp)
{
    squareNotSelected = squareNotSelectedBmp;
    squareSelected = squareSelectedBmp;

    setSelected(false);
}

void LegendEntry::setText(TEXTS textId)
{
    text.setTypedText(TypedText(textId));
    text.invalidate();
}

void LegendEntry::setValueText(int value)
{
    Unicode::snprintf(valueTextBuffer, 6, "%i", value);
    valueText.invalidate();
}

void LegendEntry::setSelected(bool selected)
{
    if (selected)
    {
        square.setBitmap(Bitmap(squareSelected));
        text.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));
    }
    else
    {
        square.setBitmap(Bitmap(squareNotSelected));
        text.setColor(Color::getColorFrom24BitRGB(0xBE, 0xC0, 0xC4));
    }
    valueText.setColor(text.getColor());
    valueText.setVisible(selected);

    square.invalidate();
    text.invalidate();
    valueText.invalidate();
}

void LegendEntry::buttonPressedHandler(const AbstractButton& button)
{
    if (selectionAction && selectionAction->isValid())
    {
        selectionAction->execute(*this);
    }
}
