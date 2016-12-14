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
#include <gui/model/AlbumManager.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <stdlib.h>

AlbumManager::AlbumManager()
{
    for (uint8_t i = 0; i < NUMBER_OF_ALBUMS; i++)
    {
        albums[i].setAlbumId(i);
        albums[i].setAlbumArtist((TEXTS)(T_ARTIST_0 + i));
        albums[i].setAlbumName((TEXTS)(T_ALBUM_0 + i));
    }

    albums[0].setAlbumCover100(BITMAP_COVER100_0_ID);
    albums[0].setAlbumCover160(BITMAP_COVER160_0_ID);
    albums[0].setAlbumCover200(BITMAP_COVER200_0_ID);
    albums[0].setAlbumCover240(BITMAP_COVER240_0_ID);

    albums[0].addTrack(T_ALBUM_0_TRACK01, T_ALBUM_TRACK_DURATION01);
    albums[0].addTrack(T_ALBUM_0_TRACK02, T_ALBUM_TRACK_DURATION02);
    albums[0].addTrack(T_ALBUM_0_TRACK03, T_ALBUM_TRACK_DURATION03);
    albums[0].addTrack(T_ALBUM_0_TRACK04, T_ALBUM_TRACK_DURATION04);
    albums[0].addTrack(T_ALBUM_0_TRACK05, T_ALBUM_TRACK_DURATION05);
    albums[0].addTrack(T_ALBUM_0_TRACK06, T_ALBUM_TRACK_DURATION06);
    albums[0].addTrack(T_ALBUM_0_TRACK07, T_ALBUM_TRACK_DURATION07);
    albums[0].addTrack(T_ALBUM_0_TRACK08, T_ALBUM_TRACK_DURATION08);
    albums[0].addTrack(T_ALBUM_0_TRACK09, T_ALBUM_TRACK_DURATION09);
    albums[0].addTrack(T_ALBUM_0_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[0].addTrack(T_ALBUM_0_TRACK11, T_ALBUM_TRACK_DURATION11);

    albums[1].setAlbumCover100(BITMAP_COVER100_1_ID);
    albums[1].setAlbumCover160(BITMAP_COVER160_1_ID);
    albums[1].setAlbumCover200(BITMAP_COVER200_1_ID);
    albums[1].setAlbumCover240(BITMAP_COVER240_1_ID);

    albums[1].addTrack(T_ALBUM_1_TRACK01, T_ALBUM_TRACK_DURATION12);
    albums[1].addTrack(T_ALBUM_1_TRACK02, T_ALBUM_TRACK_DURATION05);
    albums[1].addTrack(T_ALBUM_1_TRACK03, T_ALBUM_TRACK_DURATION08);
    albums[1].addTrack(T_ALBUM_1_TRACK04, T_ALBUM_TRACK_DURATION04);
    albums[1].addTrack(T_ALBUM_1_TRACK05, T_ALBUM_TRACK_DURATION02);
    albums[1].addTrack(T_ALBUM_1_TRACK06, T_ALBUM_TRACK_DURATION01);
    albums[1].addTrack(T_ALBUM_1_TRACK07, T_ALBUM_TRACK_DURATION13);
    albums[1].addTrack(T_ALBUM_1_TRACK08, T_ALBUM_TRACK_DURATION14);
    albums[1].addTrack(T_ALBUM_1_TRACK09, T_ALBUM_TRACK_DURATION03);
    albums[1].addTrack(T_ALBUM_1_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[1].addTrack(T_ALBUM_1_TRACK11, T_ALBUM_TRACK_DURATION11);
    albums[1].addTrack(T_ALBUM_1_TRACK12, T_ALBUM_TRACK_DURATION07);

    albums[2].setAlbumCover100(BITMAP_COVER100_2_ID);
    albums[2].setAlbumCover160(BITMAP_COVER160_2_ID);
    albums[2].setAlbumCover200(BITMAP_COVER200_2_ID);
    albums[2].setAlbumCover240(BITMAP_COVER240_2_ID);

    albums[2].addTrack(T_ALBUM_2_TRACK01, T_ALBUM_TRACK_DURATION16);
    albums[2].addTrack(T_ALBUM_2_TRACK02, T_ALBUM_TRACK_DURATION17);
    albums[2].addTrack(T_ALBUM_2_TRACK03, T_ALBUM_TRACK_DURATION18);
    albums[2].addTrack(T_ALBUM_2_TRACK04, T_ALBUM_TRACK_DURATION19);
    albums[2].addTrack(T_ALBUM_2_TRACK05, T_ALBUM_TRACK_DURATION05);
    albums[2].addTrack(T_ALBUM_2_TRACK06, T_ALBUM_TRACK_DURATION01);
    albums[2].addTrack(T_ALBUM_2_TRACK07, T_ALBUM_TRACK_DURATION13);
    albums[2].addTrack(T_ALBUM_2_TRACK08, T_ALBUM_TRACK_DURATION04);

    albums[3].setAlbumCover100(BITMAP_COVER100_3_ID);
    albums[3].setAlbumCover160(BITMAP_COVER160_3_ID);
    albums[3].setAlbumCover200(BITMAP_COVER200_3_ID);
    albums[3].setAlbumCover240(BITMAP_COVER240_3_ID);

    albums[3].addTrack(T_ALBUM_3_TRACK01, T_ALBUM_TRACK_DURATION03);
    albums[3].addTrack(T_ALBUM_3_TRACK02, T_ALBUM_TRACK_DURATION05);
    albums[3].addTrack(T_ALBUM_3_TRACK03, T_ALBUM_TRACK_DURATION07);
    albums[3].addTrack(T_ALBUM_3_TRACK04, T_ALBUM_TRACK_DURATION09);
    albums[3].addTrack(T_ALBUM_3_TRACK05, T_ALBUM_TRACK_DURATION11);
    albums[3].addTrack(T_ALBUM_3_TRACK06, T_ALBUM_TRACK_DURATION13);
    albums[3].addTrack(T_ALBUM_3_TRACK07, T_ALBUM_TRACK_DURATION15);
    albums[3].addTrack(T_ALBUM_3_TRACK08, T_ALBUM_TRACK_DURATION17);
    albums[3].addTrack(T_ALBUM_3_TRACK09, T_ALBUM_TRACK_DURATION19);
    albums[3].addTrack(T_ALBUM_3_TRACK10, T_ALBUM_TRACK_DURATION04);
    albums[3].addTrack(T_ALBUM_3_TRACK11, T_ALBUM_TRACK_DURATION08);

    albums[4].setAlbumCover100(BITMAP_COVER100_4_ID);
    albums[4].setAlbumCover160(BITMAP_COVER160_4_ID);
    albums[4].setAlbumCover200(BITMAP_COVER200_4_ID);
    albums[4].setAlbumCover240(BITMAP_COVER240_4_ID);

    albums[4].addTrack(T_ALBUM_4_TRACK01, T_ALBUM_TRACK_DURATION06);
    albums[4].addTrack(T_ALBUM_4_TRACK02, T_ALBUM_TRACK_DURATION08);
    albums[4].addTrack(T_ALBUM_4_TRACK03, T_ALBUM_TRACK_DURATION10);
    albums[4].addTrack(T_ALBUM_4_TRACK04, T_ALBUM_TRACK_DURATION12);
    albums[4].addTrack(T_ALBUM_4_TRACK05, T_ALBUM_TRACK_DURATION14);
    albums[4].addTrack(T_ALBUM_4_TRACK06, T_ALBUM_TRACK_DURATION16);
    albums[4].addTrack(T_ALBUM_4_TRACK07, T_ALBUM_TRACK_DURATION18);
    albums[4].addTrack(T_ALBUM_4_TRACK08, T_ALBUM_TRACK_DURATION01);
    albums[4].addTrack(T_ALBUM_4_TRACK09, T_ALBUM_TRACK_DURATION05);
    albums[4].addTrack(T_ALBUM_4_TRACK10, T_ALBUM_TRACK_DURATION07);
    albums[4].addTrack(T_ALBUM_4_TRACK11, T_ALBUM_TRACK_DURATION09);

    albums[5].setAlbumCover100(BITMAP_COVER100_5_ID);
    albums[5].setAlbumCover160(BITMAP_COVER160_5_ID);
    albums[5].setAlbumCover200(BITMAP_COVER200_5_ID);
    albums[5].setAlbumCover240(BITMAP_COVER240_5_ID);

    albums[5].addTrack(T_ALBUM_5_TRACK01, T_ALBUM_TRACK_DURATION12);
    albums[5].addTrack(T_ALBUM_5_TRACK02, T_ALBUM_TRACK_DURATION05);
    albums[5].addTrack(T_ALBUM_5_TRACK03, T_ALBUM_TRACK_DURATION08);
    albums[5].addTrack(T_ALBUM_5_TRACK04, T_ALBUM_TRACK_DURATION04);
    albums[5].addTrack(T_ALBUM_5_TRACK05, T_ALBUM_TRACK_DURATION02);
    albums[5].addTrack(T_ALBUM_5_TRACK06, T_ALBUM_TRACK_DURATION01);
    albums[5].addTrack(T_ALBUM_5_TRACK07, T_ALBUM_TRACK_DURATION13);
    albums[5].addTrack(T_ALBUM_5_TRACK08, T_ALBUM_TRACK_DURATION14);
    albums[5].addTrack(T_ALBUM_5_TRACK09, T_ALBUM_TRACK_DURATION03);
    albums[5].addTrack(T_ALBUM_5_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[5].addTrack(T_ALBUM_5_TRACK11, T_ALBUM_TRACK_DURATION11);

    albums[6].setAlbumCover100(BITMAP_COVER100_6_ID);
    albums[6].setAlbumCover160(BITMAP_COVER160_6_ID);
    albums[6].setAlbumCover200(BITMAP_COVER200_6_ID);
    albums[6].setAlbumCover240(BITMAP_COVER240_6_ID);

    albums[6].addTrack(T_ALBUM_6_TRACK01, T_ALBUM_TRACK_DURATION03);
    albums[6].addTrack(T_ALBUM_6_TRACK02, T_ALBUM_TRACK_DURATION06);
    albums[6].addTrack(T_ALBUM_6_TRACK03, T_ALBUM_TRACK_DURATION09);
    albums[6].addTrack(T_ALBUM_6_TRACK04, T_ALBUM_TRACK_DURATION12);
    albums[6].addTrack(T_ALBUM_6_TRACK05, T_ALBUM_TRACK_DURATION15);
    albums[6].addTrack(T_ALBUM_6_TRACK06, T_ALBUM_TRACK_DURATION18);
    albums[6].addTrack(T_ALBUM_6_TRACK07, T_ALBUM_TRACK_DURATION02);
    albums[6].addTrack(T_ALBUM_6_TRACK08, T_ALBUM_TRACK_DURATION04);
    albums[6].addTrack(T_ALBUM_6_TRACK09, T_ALBUM_TRACK_DURATION08);

    albums[7].setAlbumCover100(BITMAP_COVER100_7_ID);
    albums[7].setAlbumCover160(BITMAP_COVER160_7_ID);
    albums[7].setAlbumCover200(BITMAP_COVER200_7_ID);
    albums[7].setAlbumCover240(BITMAP_COVER240_7_ID);

    albums[7].addTrack(T_ALBUM_7_TRACK01, T_ALBUM_TRACK_DURATION05);
    albums[7].addTrack(T_ALBUM_7_TRACK02, T_ALBUM_TRACK_DURATION10);
    albums[7].addTrack(T_ALBUM_7_TRACK03, T_ALBUM_TRACK_DURATION15);
    albums[7].addTrack(T_ALBUM_7_TRACK04, T_ALBUM_TRACK_DURATION19);
    albums[7].addTrack(T_ALBUM_7_TRACK05, T_ALBUM_TRACK_DURATION17);
    albums[7].addTrack(T_ALBUM_7_TRACK06, T_ALBUM_TRACK_DURATION14);
    albums[7].addTrack(T_ALBUM_7_TRACK07, T_ALBUM_TRACK_DURATION12);
    albums[7].addTrack(T_ALBUM_7_TRACK08, T_ALBUM_TRACK_DURATION10);
    albums[7].addTrack(T_ALBUM_7_TRACK09, T_ALBUM_TRACK_DURATION03);
    albums[7].addTrack(T_ALBUM_7_TRACK10, T_ALBUM_TRACK_DURATION09);
    albums[7].addTrack(T_ALBUM_7_TRACK11, T_ALBUM_TRACK_DURATION11);

    albums[8].setAlbumCover100(BITMAP_COVER100_8_ID);
    albums[8].setAlbumCover160(BITMAP_COVER160_8_ID);
    albums[8].setAlbumCover200(BITMAP_COVER200_8_ID);
    albums[8].setAlbumCover240(BITMAP_COVER240_8_ID);

    albums[8].addTrack(T_ALBUM_8_TRACK01, T_ALBUM_TRACK_DURATION07);
    albums[8].addTrack(T_ALBUM_8_TRACK02, T_ALBUM_TRACK_DURATION14);
    albums[8].addTrack(T_ALBUM_8_TRACK03, T_ALBUM_TRACK_DURATION01);
    albums[8].addTrack(T_ALBUM_8_TRACK04, T_ALBUM_TRACK_DURATION08);
    albums[8].addTrack(T_ALBUM_8_TRACK05, T_ALBUM_TRACK_DURATION15);
    albums[8].addTrack(T_ALBUM_8_TRACK06, T_ALBUM_TRACK_DURATION02);
    albums[8].addTrack(T_ALBUM_8_TRACK07, T_ALBUM_TRACK_DURATION09);
    albums[8].addTrack(T_ALBUM_8_TRACK08, T_ALBUM_TRACK_DURATION16);
    albums[8].addTrack(T_ALBUM_8_TRACK09, T_ALBUM_TRACK_DURATION02);
    albums[8].addTrack(T_ALBUM_8_TRACK10, T_ALBUM_TRACK_DURATION09);
    albums[8].addTrack(T_ALBUM_8_TRACK11, T_ALBUM_TRACK_DURATION16);

    albums[9].setAlbumCover100(BITMAP_COVER100_9_ID);
    albums[9].setAlbumCover160(BITMAP_COVER160_9_ID);
    albums[9].setAlbumCover200(BITMAP_COVER200_9_ID);
    albums[9].setAlbumCover240(BITMAP_COVER240_9_ID);

    albums[9].addTrack(T_ALBUM_9_TRACK01, T_ALBUM_TRACK_DURATION09);
    albums[9].addTrack(T_ALBUM_9_TRACK02, T_ALBUM_TRACK_DURATION13);
    albums[9].addTrack(T_ALBUM_9_TRACK03, T_ALBUM_TRACK_DURATION17);
    albums[9].addTrack(T_ALBUM_9_TRACK04, T_ALBUM_TRACK_DURATION01);
    albums[9].addTrack(T_ALBUM_9_TRACK05, T_ALBUM_TRACK_DURATION05);
    albums[9].addTrack(T_ALBUM_9_TRACK06, T_ALBUM_TRACK_DURATION09);
    albums[9].addTrack(T_ALBUM_9_TRACK07, T_ALBUM_TRACK_DURATION13);
    albums[9].addTrack(T_ALBUM_9_TRACK08, T_ALBUM_TRACK_DURATION17);
    albums[9].addTrack(T_ALBUM_9_TRACK09, T_ALBUM_TRACK_DURATION05);
    albums[9].addTrack(T_ALBUM_9_TRACK10, T_ALBUM_TRACK_DURATION10);
    albums[9].addTrack(T_ALBUM_9_TRACK11, T_ALBUM_TRACK_DURATION15);

    setSelectedAlbum((uint8_t)(NUMBER_OF_ALBUMS * (rand() / (float)(RAND_MAX))));
}

Album* AlbumManager::getAlbum(uint8_t albumId)
{
    return &(albums[albumId]);
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
