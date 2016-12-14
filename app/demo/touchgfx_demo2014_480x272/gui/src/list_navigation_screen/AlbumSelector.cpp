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
#include <gui/list_navigation_screen/AlbumSelector.hpp>
#include <touchgfx/EasingEquations.hpp>

AlbumSelector::AlbumSelector(AlbumManager& albumManager_) :
    animationState(NO_ANIMATION),
    animationCounter(0),
    albumManager(albumManager_),
    trackSelector(albumManager),
    hideAlbumSelectorCallback(0),
    onButtonPressed(this, &AlbumSelector::buttonPressedhandler),
    onAlbumRowTrackSelectionPressed(this, &AlbumSelector::albumRowTrackSelectionPressedhandler),
    onAlbumSelected(this, &AlbumSelector::albumSelectedhandler),
    onAlbumAndTrackSelected(this, &AlbumSelector::albumAndTrackSelected),
    onTrackSelectionCancelled(this, &AlbumSelector::trackSelectionCancelled)
{
    Application::getInstance()->registerTimerWidget(this);

    headline.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_SELECTOR_HEADLINE_ID));
    headline.setXY(0, 0);

    headlineBackButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_SELECTOR_HEADLINE_BUTTON_ID), Bitmap(BITMAP_MUSIC_PLAYER_ALBUM_SELECTOR_HEADLINE_BUTTON_ID));
    headlineBackButton.setXY(headline.getWidth(), 0);
    headlineBackButton.setAction(onButtonPressed);

    albumScrollableArea.setPosition(0, headline.getHeight(), headline.getWidth() + headlineBackButton.getWidth(), HAL::DISPLAY_HEIGHT - headline.getHeight());
    albumScrollableArea.add(albumList);
    albumScrollableArea.setTouchable(true);
    albumScrollableArea.setScrollThreshold(10);
    albumList.setXY(0, 0);

    for (uint8_t i = 0; i < MAX_NUMBER_OF_ALBUMS; i++)
    {
        albumRows[i].setNumberSelectionPressedCallback(onAlbumRowTrackSelectionPressed);
        albumRows[i].setAlbumSelectedCallback(onAlbumSelected);
        albumRows[i].setAlbum(albumManager.getAlbum(i));
        albumList.add(albumRows[i]);
    }

    trackSelector.setXY(0, -trackSelector.getHeight());
    trackSelector.setAlbumAndTrackSelectedCallback(onAlbumAndTrackSelected);
    trackSelector.setTrackSelectionCancelledCallback(onTrackSelectionCancelled);
    trackSelectorViewPort.setPosition(0, headline.getHeight(), trackSelector.getWidth(), trackSelector.getHeight());
    trackSelectorViewPort.setTouchable(false);

    trackSelectorViewPort.add(trackSelector);

    add(headline);
    add(headlineBackButton);
    add(albumScrollableArea);
    add(trackSelectorViewPort);

    setWidth(albumList.getWidth());
    setHeight(HAL::DISPLAY_HEIGHT);
}

AlbumSelector::~AlbumSelector()
{
    Application::getInstance()->unregisterTimerWidget(this);
}

void AlbumSelector::handleTickEvent()
{
    if (animationState == ANIMATE_TRACK_SELECTOR_IN)
    {
        animateTrackSelectorIn();
    }
    else if (animationState == ANIMATE_TRACK_SELECTOR_OUT || animationState == ANIMATE_TRACK_SELECTOR_OUT_AND_CLOSE_ALBUM_SELECTOR)
    {
        animateTrackSelectorOut();
    }
}

void AlbumSelector::reset()
{
    albumScrollableArea.reset();
    for (uint8_t i = 0; i < MAX_NUMBER_OF_ALBUMS; i++)
    {
        albumRows[i].reset();
    }

    trackSelector.setXY(0, -trackSelector.getHeight());
    trackSelectorViewPort.setTouchable(false);
    albumScrollableArea.setTouchable(true);
}

void AlbumSelector::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &headlineBackButton)
    {
        if (hideAlbumSelectorCallback)
        {
            hideAlbumSelectorCallback->execute();
        }
    }

}

void AlbumSelector::albumRowTrackSelectionPressedhandler(const uint8_t& albumId)
{
    trackSelector.setAlbum(albumManager.getAlbum(albumId));
    setAnimationState(ANIMATE_TRACK_SELECTOR_IN);
}

void AlbumSelector::albumSelectedhandler(const uint8_t& albumId)
{
    albumManager.setSelectedAlbum(albumId);

    if (hideAlbumSelectorCallback)
    {
        hideAlbumSelectorCallback->execute();
    }
}

void AlbumSelector::albumAndTrackSelected(const Album* album, const uint8_t trackId)
{
    albumManager.setSelectedAlbum(album->getAlbumId());
    albumManager.setSelectedTrack(trackId);

    setAnimationState(ANIMATE_TRACK_SELECTOR_OUT_AND_CLOSE_ALBUM_SELECTOR);
}

void AlbumSelector::trackSelectionCancelled()
{
    setAnimationState(ANIMATE_TRACK_SELECTOR_OUT);
}

void AlbumSelector::setAnimationState(AnimationStates newState)
{
    animationCounter = 0;
    animationState = newState;
}

void AlbumSelector::animateTrackSelectorIn()
{
    uint8_t duration;
#ifdef NXP
    duration = 26;
#else
    duration = 20;
#endif

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, trackSelector.getHeight(), duration);
        trackSelector.moveTo(0, -trackSelector.getHeight() + delta);
    }
    else
    {
        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;

        trackSelectorViewPort.setTouchable(true);
        albumScrollableArea.setTouchable(false);
    }
    animationCounter++;

}

void AlbumSelector::animateTrackSelectorOut()
{
    uint8_t duration;
#ifdef NXP
    duration = 26;
#else
    duration = 20;
#endif

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, trackSelector.getHeight(), duration);
        trackSelector.moveTo(0, -delta);
    }
    else
    {
        if (animationState == ANIMATE_TRACK_SELECTOR_OUT_AND_CLOSE_ALBUM_SELECTOR)
        {
            if (hideAlbumSelectorCallback)
            {
                hideAlbumSelectorCallback->execute();
            }
        }

        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;

        trackSelectorViewPort.setTouchable(false);
        albumScrollableArea.setTouchable(true);
    }
    animationCounter++;

}
