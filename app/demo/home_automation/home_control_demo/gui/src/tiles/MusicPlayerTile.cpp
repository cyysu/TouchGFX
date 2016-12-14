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
#include <gui/tiles/MusicPlayerTile.hpp>
#include <gui/common/Constants.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/model/Album.hpp>

using namespace touchgfx;

MusicPlayerTile::MusicPlayerTile() :
    BaseTile(),
    tickCounter(0),
    buttonClicked(this, &MusicPlayerTile::handleButtonClicked),
    coverPressedAction(0),
    playPauseAction(0)
{
    touchgfx::Application::getInstance()->registerTimerWidget(this);
    setHeight(Layout::music_player_tile().height);
    setWidth(Layout::music_player_tile().width);

    verticalLine.setBitmap(Bitmap(BITMAP_VERT_LINE_BUTTOM_ID));
    verticalLine.setXY(getWidth() - verticalLine.getWidth(), 30);

    cover.setXY(40, (getHeight() - Bitmap(BITMAP_COVER100_0_ID).getHeight()) / 2);
    cover.setAction(buttonClicked);

    controlButton.setBitmaps(touchgfx::Bitmap(BITMAP_PAUSE_BUTTON_ID), touchgfx::Bitmap(BITMAP_PAUSE_BUTTON_PRESSED_ID));
    controlButton.setXY(160, (getHeight() - controlButton.getHeight()) / 2);
    controlButton.setAction(buttonClicked);

    stateText.setColor(Colors_TEXT_GREY);
    stateText.setTypedText(touchgfx::TypedText(T_PAUSED));
    stateText.setPosition(220, 75, getWidth() - 220);

    artistText.setColor(Colors_TEXT_DARK);
    artistText.setTypedText(touchgfx::TypedText(T_ARTIST_0));
    artistText.setPosition(220, 97, 0);

    artistTextViewPort.setPosition(artistText.getX(), artistText.getY(), getWidth() - 230, artistText.getHeight());
    artistText.setXY(0, 0);
    artistTextViewPort.add(artistText);

    add(cover);
    add(stateText);
    add(artistTextViewPort);
    add(controlButton);
    add(verticalLine);
}

void MusicPlayerTile::update(MusicPlayer& player)
{
    stateText.setTypedText(touchgfx::TypedText(player.isPlaying() ? T_PLAYING : T_PAUSED));
    artistText.setTypedText(TypedText(player.getCurrentAlbum()->getAlbumArtist()));
    cover.setBitmaps(Bitmap(player.getCurrentAlbum()->getAlbumCover100()), Bitmap(player.getCurrentAlbum()->getAlbumCover100()));
    controlButton.setBitmaps(touchgfx::Bitmap(player.isPlaying() ? BITMAP_PAUSE_BUTTON_ID : BITMAP_PLAY_BUTTON_ID),
                             touchgfx::Bitmap(player.isPlaying() ? BITMAP_PAUSE_BUTTON_PRESSED_ID : BITMAP_PLAY_BUTTON_PRESSED_ID));

    artistText.resizeToCurrentText();
    artistTextWidth = artistText.getTextWidth();
    animateArtistTextActive = (artistTextWidth > artistTextViewPort.getWidth());

    invalidate();
}


void MusicPlayerTile::handleButtonClicked(const AbstractButton& button)
{
    if (&button == &cover)
    {
        if (coverPressedAction && coverPressedAction->isValid())
        {
            coverPressedAction->execute();
        }
    }
    else if (&button == &controlButton)
    {
        if (playPauseAction && playPauseAction->isValid())
        {
            playPauseAction->execute();
        }
    }
}

void MusicPlayerTile::handleTickEvent()
{
    tickCounter++;


    if (animateArtistTextActive && tickCounter % 3 == 0)
    {


        if (artistText.getX() + artistTextWidth < 0)
        {
            // When the text has been moved to the left
            // of the viewport move it to the right it
            artistText.setXY(artistTextViewPort.getWidth(), 0);
        }
        else
        {
            artistText.moveRelative(-1, 0);
        }
        artistText.invalidate();
    }
}
