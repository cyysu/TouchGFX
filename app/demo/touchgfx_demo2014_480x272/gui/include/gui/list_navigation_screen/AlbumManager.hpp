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
#ifndef ALBUM_MANAGER_HPP_
#define ALBUM_MANAGER_HPP_

#include <gui/list_navigation_screen/Album.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class AlbumManager
{
public:
    AlbumManager();

    Album* getAlbum(uint8_t albumId);

    Album* getSelectedAlbum();
    void setSelectedAlbum(Album* album);
    void setSelectedAlbum(uint8_t albumId);

    TEXTS getSelectedTrack();
    void setSelectedTrack(uint8_t trackIndex);
    void gotoNextTrack();

    uint8_t size();

private:
    static const uint8_t NUMBER_OF_ALBUMS = 6;

    Album albums[NUMBER_OF_ALBUMS];

    Album* selectedAlbum;
    uint8_t selectedTrackIndex;
};


#endif /* ALBUM_MANAGER_HPP_ */
