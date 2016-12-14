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
#include <gui/list_navigation_screen/TrackRow.hpp>
#include <touchgfx/Color.hpp>

TrackRow::TrackRow() :
    selected(false),
    onButtonPressed(this, &TrackRow::buttonPressedhandler)
{
    setSelected(selected);
    background.setXY(0, 0);

    trackSelectArea.setPosition(0, 0, background.getWidth(), background.getHeight());
    trackSelectArea.setAction(onButtonPressed);

    trackName.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    trackName.setPosition(34, 6, 200, 20);
    trackName.setTypedText(TypedText(T_ALBUM_BEATLES_TRACK01));

    trackDuration.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    trackDuration.setPosition(236, 6, 30, 20);
    trackDuration.setTypedText(TypedText(T_ALBUM_TRACK_DURATION04));

    // The last element has a slightly larger horizontal line at the buttom
    // This is done by using a small image
    lastElementBackground.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_ROW_LAST_ELEMENT_ID));
    lastElementBackground.setXY(0, background.getHeight() - lastElementBackground.getHeight());
    lastElementBackground.setVisible(false);

    add(background);
    add(trackDuration);
    add(trackName);
    add(trackSelectArea);
    add(lastElementBackground);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

TrackRow::~TrackRow()
{

}

void TrackRow::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &trackSelectArea)
    {
        setSelected(!selected);

        if (rowPressedCallback)
        {
            rowPressedCallback->execute(*this);
        }
    }
}

void TrackRow::setData(TEXTS name, TEXTS duration, bool lastElementInList)
{
    trackName.setTypedText(TypedText(name));
    trackDuration.setTypedText(TypedText(duration));
    lastElementBackground.setVisible(lastElementInList);
}

void TrackRow::setSelected(bool newSelectedValue)
{
    selected = newSelectedValue;

    if (selected)
    {
        background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_ROW_SELECTED_ID));
    }
    else
    {
        background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_ROW_ID));
    }
    background.invalidate();
}

bool TrackRow::isSelected()
{
    return selected;
}
