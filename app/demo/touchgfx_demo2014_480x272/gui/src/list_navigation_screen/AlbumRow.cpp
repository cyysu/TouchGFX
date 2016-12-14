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
#include <gui/list_navigation_screen/AlbumRow.hpp>
#include <touchgfx/Color.hpp>

AlbumRow::AlbumRow() :
    album(0),
    albumSelectedCallback(0),
    numberSelectionPressedCallback(0),
    onButtonPressed(this, &AlbumRow::buttonPressedhandler)
{
    background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ID));
    background.setXY(0, 0);

    albumCover.setXY(9, 9);

    numberSelectionButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_BUTTON_ID), Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_BUTTON_PRESSED_ID));
    numberSelectionButton.setXY(379, 19);
    numberSelectionButton.setAction(onButtonPressed);

    albumSelectArea.setPosition(0, 0, numberSelectionButton.getX() - 20, background.getHeight());
    albumSelectArea.setAction(onButtonPressed);

    albumName.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    albumName.setPosition(92, 16, 250, 34);

    albumArtist.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    albumArtist.setPosition(92, 50, 250, 22);

    add(background);
    add(numberSelectionButton);
    add(albumCover);
    add(albumName);
    add(albumArtist);

    add(albumSelectArea);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

AlbumRow::~AlbumRow()
{

}

void AlbumRow::setAlbum(Album* album_)
{
    album = album_;

    albumCover.setBitmap(Bitmap(album->getAlbumRowCover()));
    albumName.setTypedText(TypedText(album->getAlbumName()));
    albumArtist.setTypedText(TypedText(album->getAlbumArtist()));
    invalidate();
}


void AlbumRow::reset()
{
    background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ID));
    numberSelectionButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_BUTTON_ID), Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_BUTTON_PRESSED_ID));
    numberSelectionButton.setTouchable(true);
}

void AlbumRow::buttonPressedhandler(const AbstractButton& button)
{
    assert(album != 0 && "album pointer is null");

    if (&button == &numberSelectionButton)
    {
        if (numberSelectionPressedCallback)
        {
            numberSelectionPressedCallback->execute(album->getAlbumId());
        }
    }
    else if (&button == &albumSelectArea)
    {
        background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_SELECTED_ID));
        numberSelectionButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_SELECTED_BUTTON_ID), Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_ROW_SELECTED_BUTTON_ID));
        numberSelectionButton.setTouchable(false);
        background.invalidate();
        numberSelectionButton.invalidate();

        if (albumSelectedCallback)
        {
            albumSelectedCallback->execute(album->getAlbumId());
        }
    }
}
