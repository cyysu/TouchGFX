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
#ifndef TRACK_SELECTOR_HPP_
#define TRACK_SELECTOR_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/list_navigation_screen/Album.hpp>
#include <gui/list_navigation_screen/AlbumManager.hpp>
#include <gui/list_navigation_screen/TrackRow.hpp>

using namespace touchgfx;

class TrackSelector : public Container
{
public:
    TrackSelector(AlbumManager& albumManager_);
    virtual ~TrackSelector();

    void setAlbumAndTrackSelectedCallback(GenericCallback< const Album*, const uint8_t >& callback)
    {
        albumAndTrackSelectedCallback = &callback;
    }
    void setTrackSelectionCancelledCallback(GenericCallback< >& callback)
    {
        trackSelectionCancelledCallback = &callback;
    }

    void setAlbum(Album* album_);

private:
    AlbumManager& albumManager;
    Album* album;

    Image background;
    Image albumCover;
    Image headlineBackground;
    Button headlineButton;
    TextArea albumName;
    TextArea albumArtist;
    Button playButton;

    static const uint8_t MAX_NUMBER_OF_TRACKS = 14;
    TrackRow trackRows[MAX_NUMBER_OF_TRACKS];

    ScrollableContainer trackScrollableArea;
    ListLayout trackList;

    GenericCallback< const Album*, const uint8_t >* albumAndTrackSelectedCallback;
    GenericCallback< >* trackSelectionCancelledCallback;

    Callback<TrackSelector, const AbstractButton&> onButtonPressed;
    Callback<TrackSelector, const TrackRow&> onTrackRowSelected;

    void buttonPressedhandler(const AbstractButton& button);
    void trackRowSelectedHandler(const TrackRow& track);
};


#endif /* TRACK_SELECTOR_HPP_ */
