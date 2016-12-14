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
#ifndef ALBUM_SELECTOR_HPP_
#define ALBUM_SELECTOR_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <BitmapDatabase.hpp>
#include <gui/list_navigation_screen/AlbumRow.hpp>
#include <gui/list_navigation_screen/AlbumManager.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <gui/list_navigation_screen/TrackSelector.hpp>

using namespace touchgfx;

class AlbumSelector : public Container
{
public:
    AlbumSelector(AlbumManager& albumManager_);
    virtual ~AlbumSelector();

    virtual void handleTickEvent();

    void setHideAlbumSelectorCallback(GenericCallback< >& callback)
    {
        hideAlbumSelectorCallback = &callback;
    }

    void reset();

private:
    enum AnimationStates
    {
        ANIMATE_TRACK_SELECTOR_IN,
        ANIMATE_TRACK_SELECTOR_OUT,
        ANIMATE_TRACK_SELECTOR_OUT_AND_CLOSE_ALBUM_SELECTOR,
        NO_ANIMATION
    } animationState;

    uint8_t animationCounter;

    AlbumManager& albumManager;

    Image headline;
    Button headlineBackButton;

    static const uint8_t MAX_NUMBER_OF_ALBUMS = 6;
    AlbumRow albumRows[MAX_NUMBER_OF_ALBUMS];

    ScrollableContainer albumScrollableArea;
    ListLayout albumList;

    // The trackSelector is the container that appears if the user
    // presses the trackSelection button displayed to the right in each
    // row.
    Container trackSelectorViewPort;
    TrackSelector trackSelector;

    GenericCallback< >* hideAlbumSelectorCallback;

    Callback<AlbumSelector, const AbstractButton&> onButtonPressed;
    Callback<AlbumSelector, const uint8_t&> onAlbumRowTrackSelectionPressed;
    Callback<AlbumSelector, const uint8_t&> onAlbumSelected;
    Callback<AlbumSelector, const Album*, const uint8_t> onAlbumAndTrackSelected;
    Callback<AlbumSelector> onTrackSelectionCancelled;

    void buttonPressedhandler(const AbstractButton& button);
    void albumRowTrackSelectionPressedhandler(const uint8_t& albumId);
    void albumSelectedhandler(const uint8_t& albumId);
    void albumAndTrackSelected(const Album* album, const uint8_t trackId);
    void trackSelectionCancelled();

    void setAnimationState(AnimationStates newState);

    void animateTrackSelectorIn();
    void animateTrackSelectorOut();
};


#endif /* ALBUM_SELECTOR_HPP_ */
