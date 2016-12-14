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
#include <gui/list_navigation_screen/AlbumManager.hpp>
#include <stdlib.h>

AlbumManager::AlbumManager()
{
    for (uint8_t i = 0; i < NUMBER_OF_ALBUMS; i++)
    {
        albums[i].setAlbumId(i);
    }

    albums[0].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_RIHANNA_ID);
    albums[0].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_RIHANNA_ID);
    albums[0].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_RIHANNA_ID);
    albums[0].setRecordAnimationStart(BITMAP_RECORD_RIHANNA_00000_ID);
    albums[0].setRecordAnimationEnd(BITMAP_RECORD_RIHANNA_00019_ID);
    albums[0].setAlbumArtist(T_ALBUM_ROW_RIHANNA);
    albums[0].setAlbumName(T_ALBUM_ROW_RIHANNA_ALBUM);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK01, T_ALBUM_TRACK_DURATION01);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK02, T_ALBUM_TRACK_DURATION02);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK03, T_ALBUM_TRACK_DURATION03);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK04, T_ALBUM_TRACK_DURATION04);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK05, T_ALBUM_TRACK_DURATION05);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK06, T_ALBUM_TRACK_DURATION06);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK07, T_ALBUM_TRACK_DURATION07);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK08, T_ALBUM_TRACK_DURATION08);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK09, T_ALBUM_TRACK_DURATION09);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[0].addTrack(T_ALBUM_RIHANNA_TRACK11, T_ALBUM_TRACK_DURATION11);

    albums[1].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_METALLICA_ID);
    albums[1].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_METALLICA_ID);
    albums[1].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_METALLICA_ID);
    albums[1].setRecordAnimationStart(BITMAP_RECORD_METALLICA_00000_ID);
    albums[1].setRecordAnimationEnd(BITMAP_RECORD_METALLICA_00019_ID);
    albums[1].setAlbumArtist(T_ALBUM_ROW_METALLICA);
    albums[1].setAlbumName(T_ALBUM_ROW_METALLICA_ALBUM);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK01, T_ALBUM_TRACK_DURATION12);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK02, T_ALBUM_TRACK_DURATION13);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK03, T_ALBUM_TRACK_DURATION14);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK04, T_ALBUM_TRACK_DURATION01);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK05, T_ALBUM_TRACK_DURATION02);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK06, T_ALBUM_TRACK_DURATION04);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK07, T_ALBUM_TRACK_DURATION06);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK08, T_ALBUM_TRACK_DURATION08);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK09, T_ALBUM_TRACK_DURATION09);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[1].addTrack(T_ALBUM_METALLICA_TRACK11, T_ALBUM_TRACK_DURATION03);

    albums[2].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_BEATLES_ID);
    albums[2].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_BEATLES_ID);
    albums[2].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_BEATLES_ID);
    albums[2].setRecordAnimationStart(BITMAP_RECORD_BEATLES_00000_ID);
    albums[2].setRecordAnimationEnd(BITMAP_RECORD_BEATLES_00019_ID);
    albums[2].setAlbumArtist(T_ALBUM_ROW_BEATLES);
    albums[2].setAlbumName(T_ALBUM_ROW_BEATLES_ALBUM);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK01, T_ALBUM_TRACK_DURATION04);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK02, T_ALBUM_TRACK_DURATION03);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK03, T_ALBUM_TRACK_DURATION02);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK04, T_ALBUM_TRACK_DURATION09);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK05, T_ALBUM_TRACK_DURATION07);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK06, T_ALBUM_TRACK_DURATION06);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK07, T_ALBUM_TRACK_DURATION11);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK08, T_ALBUM_TRACK_DURATION13);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK09, T_ALBUM_TRACK_DURATION05);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK10, T_ALBUM_TRACK_DURATION14);
    albums[2].addTrack(T_ALBUM_BEATLES_TRACK11, T_ALBUM_TRACK_DURATION01);

    albums[3].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_MADONNA_ID);
    albums[3].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_MADONNA_ID);
    albums[3].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_MADONNA_ID);
    albums[3].setRecordAnimationStart(BITMAP_RECORD_MADONNA_00000_ID);
    albums[3].setRecordAnimationEnd(BITMAP_RECORD_MADONNA_00019_ID);
    albums[3].setAlbumArtist(T_ALBUM_ROW_MADONNA);
    albums[3].setAlbumName(T_ALBUM_ROW_MADONNA_ALBUM);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK01, T_ALBUM_TRACK_DURATION06);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK02, T_ALBUM_TRACK_DURATION08);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK03, T_ALBUM_TRACK_DURATION10);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK04, T_ALBUM_TRACK_DURATION11);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK05, T_ALBUM_TRACK_DURATION13);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK06, T_ALBUM_TRACK_DURATION02);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK07, T_ALBUM_TRACK_DURATION03);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK08, T_ALBUM_TRACK_DURATION04);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK09, T_ALBUM_TRACK_DURATION07);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK10, T_ALBUM_TRACK_DURATION09);
    albums[3].addTrack(T_ALBUM_MADONNA_TRACK11, T_ALBUM_TRACK_DURATION14);

    albums[4].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_MJ_ID);
    albums[4].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_MJ_ID);
    albums[4].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_MJ_ID);
    albums[4].setRecordAnimationStart(BITMAP_RECORD_MJ_00000_ID);
    albums[4].setRecordAnimationEnd(BITMAP_RECORD_MJ_00019_ID);
    albums[4].setAlbumArtist(T_ALBUM_ROW_MJ);
    albums[4].setAlbumName(T_ALBUM_ROW_MJ_ALBUM);
    albums[4].addTrack(T_ALBUM_MJ_TRACK01, T_ALBUM_TRACK_DURATION12);
    albums[4].addTrack(T_ALBUM_MJ_TRACK02, T_ALBUM_TRACK_DURATION14);
    albums[4].addTrack(T_ALBUM_MJ_TRACK03, T_ALBUM_TRACK_DURATION01);
    albums[4].addTrack(T_ALBUM_MJ_TRACK04, T_ALBUM_TRACK_DURATION02);
    albums[4].addTrack(T_ALBUM_MJ_TRACK05, T_ALBUM_TRACK_DURATION05);
    albums[4].addTrack(T_ALBUM_MJ_TRACK06, T_ALBUM_TRACK_DURATION04);
    albums[4].addTrack(T_ALBUM_MJ_TRACK07, T_ALBUM_TRACK_DURATION08);
    albums[4].addTrack(T_ALBUM_MJ_TRACK08, T_ALBUM_TRACK_DURATION07);
    albums[4].addTrack(T_ALBUM_MJ_TRACK09, T_ALBUM_TRACK_DURATION09);
    albums[4].addTrack(T_ALBUM_MJ_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[4].addTrack(T_ALBUM_MJ_TRACK11, T_ALBUM_TRACK_DURATION11);

    albums[5].setAlbumBigCover(BITMAP_MUSIC_PLAYER_ALBUM_BEYONCE_ID);
    albums[5].setAlbumRowCover(BITMAP_MUSIC_PLAYER_ALBUM_ROW_ALBUM_BEYONCE_ID);
    albums[5].setAlbumTrackListCover(BITMAP_MUSIC_PLAYER_TRACK_SELECTOR_BEYONCE_ID);
    albums[5].setRecordAnimationStart(BITMAP_RECORD_BEYONCE_00000_ID);
    albums[5].setRecordAnimationEnd(BITMAP_RECORD_BEYONCE_00019_ID);
    albums[5].setAlbumArtist(T_ALBUM_ROW_BEYONCE);
    albums[5].setAlbumName(T_ALBUM_ROW_BEYONCE_ALBUM);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK01, T_ALBUM_TRACK_DURATION11);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK02, T_ALBUM_TRACK_DURATION10);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK03, T_ALBUM_TRACK_DURATION09);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK04, T_ALBUM_TRACK_DURATION08);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK05, T_ALBUM_TRACK_DURATION07);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK06, T_ALBUM_TRACK_DURATION06);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK07, T_ALBUM_TRACK_DURATION05);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK08, T_ALBUM_TRACK_DURATION04);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK09, T_ALBUM_TRACK_DURATION14);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK10, T_ALBUM_TRACK_DURATION02);
    albums[5].addTrack(T_ALBUM_BEYONCE_TRACK11, T_ALBUM_TRACK_DURATION01);


    setSelectedAlbum((uint8_t)(NUMBER_OF_ALBUMS * (rand() / (float)(RAND_MAX))));
}

Album* AlbumManager::getAlbum(uint8_t albumId)
{
    return &albums[albumId];
}

uint8_t AlbumManager::size()
{
    return NUMBER_OF_ALBUMS;
}

Album* AlbumManager::getSelectedAlbum()
{
    return selectedAlbum;
}

void AlbumManager::setSelectedAlbum(Album* album)
{
    selectedAlbum = album;
    selectedTrackIndex = 0;
}

void AlbumManager::setSelectedAlbum(uint8_t albumId)
{
    setSelectedAlbum(getAlbum(albumId));
}

TEXTS AlbumManager::getSelectedTrack()
{
    return selectedAlbum->getTrack(selectedTrackIndex);
}

void AlbumManager::setSelectedTrack(uint8_t trackIndex)
{
    selectedTrackIndex = trackIndex;
}

void AlbumManager::gotoNextTrack()
{
    if (selectedTrackIndex >= selectedAlbum->getNumberOfTracks() - 1)
    {
        selectedTrackIndex = 0;
    }
    else
    {
        selectedTrackIndex++;
    }
}
