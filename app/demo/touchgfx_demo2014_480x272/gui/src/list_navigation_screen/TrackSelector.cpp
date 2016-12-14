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
#include <gui/list_navigation_screen/TrackSelector.hpp>
#include <touchgfx/Color.hpp>

TrackSelector::TrackSelector(AlbumManager& albumManager_) :
    albumManager(albumManager_),
    onButtonPressed(this, &TrackSelector::buttonPressedhandler),
    onTrackRowSelected(this, &TrackSelector::trackRowSelectedHandler)
{
    background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_BACKGROUND_ID));
    background.setXY(0, 0);

    albumCover.setBitmap(Bitmap(albumManager.getSelectedAlbum()->getAlbumTrackListCover()));
    albumCover.setXY(4, 13);

    playButton.setBitmaps(Bitmap(BITMAP_TRACK_PLAY_BUTTON_ID), Bitmap(BITMAP_TRACK_PLAY_BUTTON_PRESSED_ID));
    //playButton.setXY(albumCover.getX() + (albumCover.getWidth() / 2) - (playButton.getWidth() / 2), albumCover.getY() + albumCover.getHeight() + 6);
    playButton.setXY(albumCover.getX() + 8, albumCover.getY() + albumCover.getHeight() + 6);
    playButton.setAction(onButtonPressed);

    headlineBackground.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_HEADLINE_ID));
    headlineBackground.setXY(166, 0);

    headlineButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_HEADLINE_BUTTON_ID), Bitmap(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_HEADLINE_BUTTON_ID));
    headlineButton.setXY(headlineBackground.getX() + headlineBackground.getWidth(), 0);
    headlineButton.setAction(onButtonPressed);

    albumName.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    albumName.setPosition(172, 8, 250, 34);
    albumName.setTypedText(TypedText(T_ALBUM_ROW_BEATLES_ALBUM));

    albumArtist.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
    albumArtist.setPosition(172, 38, 250, 22);
    albumArtist.setTypedText(TypedText(T_ALBUM_ROW_BEATLES));

    trackScrollableArea.setPosition(headlineBackground.getX(),
                                    headlineBackground.getY() + headlineBackground.getHeight(),
                                    headlineBackground.getWidth() + headlineButton.getWidth(),
                                    background.getHeight() - headlineBackground.getHeight());

    trackScrollableArea.setScrollThreshold(10);
    trackScrollableArea.add(trackList);

    add(background);
    add(albumCover);
    add(playButton);
    add(headlineBackground);
    add(headlineButton);
    add(albumName);
    add(albumArtist);
    add(trackScrollableArea);

    setWidth(background.getWidth() + headlineBackground.getWidth() + headlineButton.getWidth());
    setHeight(background.getHeight());
}

TrackSelector::~TrackSelector()
{

}

void TrackSelector::setAlbum(Album* album_)
{
    album = album_;

    albumCover.setBitmap(Bitmap(album->getAlbumTrackListCover()));

    albumName.setTypedText(TypedText(album->getAlbumName()));
    albumArtist.setTypedText(TypedText(album->getAlbumArtist()));

    trackList.removeAll();

    for (uint8_t i = 0; i < album->getNumberOfTracks(); i++)
    {
        trackRows[i].setData(album->getTrack(i), album->getTrackDuration(i), i == (album->getNumberOfTracks() - 1)) ;
        trackRows[i].setRowPressedCallback(onTrackRowSelected);
        trackRows[i].setSelected(i == 0);
        trackList.add(trackRows[i]);
    }

    invalidate();
}

void TrackSelector::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &playButton)
    {
        if (albumAndTrackSelectedCallback)
        {
            uint8_t selectedTrack = 0;
            for (uint8_t i = 0; i < album->getNumberOfTracks(); i++)
            {
                if (trackRows[i].isSelected())
                {
                    selectedTrack = i;
                    break;
                }
            }
            albumAndTrackSelectedCallback->execute(album, selectedTrack);
        }
    }
    else if (&button == &headlineButton)
    {
        if (trackSelectionCancelledCallback)
        {
            trackSelectionCancelledCallback->execute();
        }
    }
}

void TrackSelector::trackRowSelectedHandler(const TrackRow& track)
{
    // Only one track can be selected at a time
    for (uint8_t i = 0; i < album->getNumberOfTracks(); i++)
    {
        if (&trackRows[i] != &track)
        {
            trackRows[i].setSelected(false);
        }
    }
}


