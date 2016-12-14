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
#ifndef ALBUM_HPP_
#define ALBUM_HPP_

#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;


class Album
{
public:
    Album() :
        numberOfTracks(0)
    { }

    void setAlbumId(uint8_t id)
    {
        albumId = id;
    }
    uint8_t getAlbumId() const
    {
        return albumId;
    }

    void setAlbumBigCover(BitmapId cover)
    {
        albumBigCover = cover;
    }
    BitmapId getAlbumBigCover() const
    {
        return albumBigCover;
    }

    void setAlbumRowCover(BitmapId cover)
    {
        albumRowCover = cover;
    }
    BitmapId getAlbumRowCover() const
    {
        return albumRowCover;
    }

    void setAlbumTrackListCover(BitmapId cover)
    {
        albumTrackListCover = cover;
    }
    BitmapId getAlbumTrackListCover() const
    {
        return albumTrackListCover;
    }

    void setRecordAnimationStart(BitmapId start)
    {
        recordAnimationStart = start;
    }
    BitmapId getRecordAnimationStart() const
    {
        return recordAnimationStart;
    }

    void setRecordAnimationEnd(BitmapId end)
    {
        recordAnimationEnd = end;
    }
    BitmapId getRecordAnimationEnd() const
    {
        return recordAnimationEnd;
    }

    void setAlbumArtist(TEXTS artist)
    {
        albumArtist = artist;
    }
    TEXTS getAlbumArtist() const
    {
        return albumArtist;
    }

    void setAlbumName(TEXTS name)
    {
        albumName = name;
    }
    TEXTS getAlbumName() const
    {
        return albumName;
    }

    void addTrack(TEXTS trackName, TEXTS trackDuration)
    {
        tracks[numberOfTracks] = trackName;
        trackDurations[numberOfTracks++] = trackDuration;
    }
    TEXTS getTrack(uint8_t trackIndex) const
    {
        return tracks[trackIndex];
    }
    TEXTS getTrackDuration(uint8_t trackIndex) const
    {
        return trackDurations[trackIndex];
    }

    uint8_t getNumberOfTracks() const
    {
        return numberOfTracks;
    }

private:
    uint8_t albumId;
    BitmapId albumBigCover;
    BitmapId albumRowCover;
    BitmapId albumTrackListCover;
    BitmapId recordAnimationStart;
    BitmapId recordAnimationEnd;

    TEXTS albumArtist;
    TEXTS albumName;

    static const uint8_t MAX_NUMBER_OF_TRACKS = 14;
    TEXTS tracks[MAX_NUMBER_OF_TRACKS];
    TEXTS trackDurations[MAX_NUMBER_OF_TRACKS];
    uint8_t numberOfTracks;
};


#endif /* ALBUM_HPP_ */
