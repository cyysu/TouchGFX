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
#include <gui/list_navigation_screen/ListNavigationView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/EasingEquations.hpp>
#include <stdlib.h>


ListNavigationView::ListNavigationView() :
    DemoView(),
    animationState(NO_ANIMATION),
    playerState(STOPPED),
    animationCounter(0),
    tickCounter(0),
    albumManager(),
    currentRecordSpeed(MAX_RECORD_SPEED),
    record(BITMAP_RECORD_BEATLES_00000_ID, BITMAP_RECORD_BEATLES_00019_ID, currentRecordSpeed),
    animateTrackNameActive(false),
    albumSelector(albumManager),
    musicPlayerPlay(false),
    onButtonPressed(this, &ListNavigationView::buttonPressedhandler),
    onHideAlbumSelector(this, &ListNavigationView::hideAlbumSelector)
{
}

ListNavigationView::~ListNavigationView()
{
}

void ListNavigationView::setupScreen()
{
    // Place the album player parts in the albumPlayer container
    albumPlayer.setPosition(backButton.getWidth(), 0, HAL::DISPLAY_WIDTH - backButton.getWidth(), HAL::DISPLAY_HEIGHT);

    background.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_BACKGROUND_ID));
    background.setXY(0, 0);

    // Place pickup outside the canvas ready to be animated in
    pickup.setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_PICKUP_ID));
    pickup.setXY(HAL::DISPLAY_WIDTH, 0);

    albumCovers.setXY(0, 0);
    albumCovers.setAction(onButtonPressed);

    jumpToStartButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_JUMP_TO_START_ID), Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_JUMP_TO_START_PRESSED_ID));
    jumpToStartButton.setXY(144, 208);
    jumpToStartButton.setAction(onButtonPressed);

    playButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_PLAY_ID), Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_PLAY_PRESSED_ID));
    playButton.setXY(195, 200);
    playButton.setAction(onButtonPressed);

    nextButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_NEXT_ID), Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_NEXT_PRESSED_ID));
    nextButton.setXY(264, 208);
    nextButton.setAction(onButtonPressed);

    record.setXY(342, 0);
    record.startAnimation(false, false, true);
    record.pauseAnimation();

    volumeSlider.setXY(334, 238);

    trackNameViewPort.setPosition(34, 244, 102, 26);
    trackName.setPosition(0, 0, 250, 26);
    trackNameViewPort.add(trackName);

    albumPlayer.add(background);
    albumPlayer.add(pickup);
    albumPlayer.add(albumCovers);
    albumPlayer.add(jumpToStartButton);
    albumPlayer.add(playButton);
    albumPlayer.add(nextButton);
    albumPlayer.add(record);
    albumPlayer.add(volumeSlider);
    albumPlayer.add(trackNameViewPort);

    for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
    {
        soundLevels[i] = 0;
        soundLevelIndicators[i].setXY(340 + i * 10, 200);
        albumPlayer.add(soundLevelIndicators[i]);
    }

    add(albumPlayer);


    albumSelector.setXY(backButton.getWidth(), HAL::DISPLAY_HEIGHT);
    albumSelector.setHideAlbumSelectorCallback(onHideAlbumSelector);
    add(albumSelector);

    setSelectedAlbum();
}

void ListNavigationView::tearDownScreen()
{

}

void ListNavigationView::handleTickEvent()
{
    tickCounter++;

    if (animationState == ANIMATE_PICKUP_IN)
    {
        animatePickupIn();
    }
    else if (animationState == ANIMATE_PICKUP_OUT)
    {
        animatePickupOut();
    }
    else if (animationState == ANIMATE_ALBUM_SELECTOR_UP)
    {
        animateAlbumSelectorUp();
    }
    else if (animationState == ANIMATE_ALBUM_SELECTOR_DOWN)
    {
        animateAlbumSelectorDown();
    }

    animateSoundLevelIndicators();
    animateTrackName();
}

void ListNavigationView::afterTransition()
{
    DemoView<ListNavigationPresenter>::afterTransition();

    if (musicPlayerPlay)
    {
        setButtonsActiveState(false);
        play();
    }
}

void ListNavigationView::buttonPressedhandler(const AbstractButton& button)
{
    if (&button == &jumpToStartButton)
    {
        albumManager.setSelectedTrack(0);
        resetSoundLevelIndicators();
        updateTrackName();
    }
    else if (&button == &playButton)
    {
        setButtonsActiveState(false);

        if (playerState == STOPPED)
        {
            play();
        }
        else
        {
            setAnimationState(ANIMATE_PICKUP_OUT);
            playerState = STOPPED;
            playButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_PLAY_ID), Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_PLAY_PRESSED_ID));
            playButton.invalidate();
        }
    }
    else if (&button == &nextButton)
    {
        albumManager.gotoNextTrack();
        resetSoundLevelIndicators();
        updateTrackName();
    }
    else if (&button == &albumCovers)
    {
        setButtonsActiveState(false);
        albumSelector.reset();
        setAnimationState(ANIMATE_ALBUM_SELECTOR_UP);
    }
}

void ListNavigationView::setSelectedAlbum()
{
    albumCovers.setBitmaps(Bitmap(albumManager.getSelectedAlbum()->getAlbumBigCover()), Bitmap(albumManager.getSelectedAlbum()->getAlbumBigCover()));
    record.setBitmaps(albumManager.getSelectedAlbum()->getRecordAnimationStart(), albumManager.getSelectedAlbum()->getRecordAnimationEnd());
    record.invalidate();

    updateTrackName();
}

void ListNavigationView::updateTrackName()
{
    trackName.setTypedText(TypedText(albumManager.getSelectedTrack()));
    trackName.setXY(0, 0);
    trackNameCurrentWidth = trackName.getTextWidth();
    animateTrackNameActive = (trackNameCurrentWidth > trackNameViewPort.getWidth());
    trackName.invalidate();
}

void ListNavigationView::hideAlbumSelector()
{
    setSelectedAlbum();
    setButtonsActiveState(false);
    setAnimationState(ANIMATE_ALBUM_SELECTOR_DOWN);
}

void ListNavigationView::setAnimationState(AnimationStates newState)
{
    animationCounter = 0;
    animationState = newState;
}

void ListNavigationView::setButtonsActiveState(bool active)
{
    albumCovers.setTouchable(active);
    jumpToStartButton.setTouchable(active);
    playButton.setTouchable(active);
    nextButton.setTouchable(active);
}

void ListNavigationView::animateSoundLevelIndicators()
{
    if (playerState == PLAYING)
    {
        // Random change of the sound level indicators
        for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
        {
            // Only change sound level sometimes
            if ((rand() / (float)(RAND_MAX) < 0.2f))
            {
                if (soundLevels[i] == 0)
                {
                    soundLevels[i] = 1;
                }
                else if (soundLevels[i] == 4)
                {
                    soundLevels[i] = 3;
                }
                else
                {
                    if ((rand() / (float)(RAND_MAX) < 0.5f))
                    {
                        soundLevels[i]--;
                    }
                    else
                    {
                        soundLevels[i]++;
                    }
                }

                soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_SOUND_LEVEL_0_ID + soundLevels[i]));
                soundLevelIndicators[i].invalidate();
            }

        }
    }
    // Fade out sound level indicators when stopping.
    // Do this at reduced speed
    else if (animationState == ANIMATE_PICKUP_OUT && tickCounter % 3 == 0)
    {
        for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
        {
            if (soundLevels[i] > 0)
            {
                soundLevels[i]--;
                soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_SOUND_LEVEL_0_ID + soundLevels[i]));
                soundLevelIndicators[i].invalidate();
            }
        }
    }
}

void ListNavigationView::animateTrackName()
{
    if (animateTrackNameActive && tickCounter % 3 == 0)
    {
        if (trackName.getX() + trackNameCurrentWidth < 0)
        {
            // When the track name has been moved to the left
            // of the viewport move it to the right it
            trackName.setXY(trackNameViewPort.getWidth(), 0);
        }
        else
        {
            trackName.moveRelative(-1, 0);
        }
        trackName.invalidate();
    }
}

void ListNavigationView::resetSoundLevelIndicators()
{
    for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
    {
        soundLevels[i] = 0;
        soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_MUSIC_PLAYER_SOUND_LEVEL_0_ID + soundLevels[i]));
        soundLevelIndicators[i].invalidate();
    }
}

void ListNavigationView::animatePickupIn()
{
    uint8_t duration = 20;

    if (animationCounter <= duration)
    {
        // Accelerate record
        if (currentRecordSpeed > MAX_RECORD_SPEED && animationCounter % 4 == 0)
        {
            record.setUpdateTicksInterval(--currentRecordSpeed);
        }

        // Move pickup to 372 relative to the albumPlayer container
        uint16_t endPositionPlaying = 372;

        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, albumPlayer.getWidth() - endPositionPlaying, duration);
        pickup.moveTo(albumPlayer.getWidth() - delta, 0);
    }
    else
    {
        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;

        setButtonsActiveState(true);
        playerState = PLAYING;
    }
    animationCounter++;

}

void ListNavigationView::animatePickupOut()
{
    uint8_t duration = 20;

    if (animationCounter <= duration)
    {
        // Decelerate record
        if (animationCounter % 10 == 0)
        {
            currentRecordSpeed += 2;
            record.setUpdateTicksInterval(currentRecordSpeed);
        }

        // Move pickup out of the screen from this position
        uint16_t endPositionPlaying = 372;

        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, albumPlayer.getWidth() - endPositionPlaying, duration);
        pickup.moveTo(endPositionPlaying + delta , 0);
    }
    else
    {
        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;
        record.pauseAnimation();

        setButtonsActiveState(true);

    }
    animationCounter++;
}

void ListNavigationView::animateAlbumSelectorUp()
{
    uint8_t duration = 20;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, HAL::DISPLAY_HEIGHT, duration);
        albumPlayer.moveTo(backButton.getWidth(), 0 - delta);
        albumSelector.moveTo(backButton.getWidth(), HAL::DISPLAY_HEIGHT - delta);
    }
    else
    {
        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;
    }
    animationCounter++;
}

void ListNavigationView::animateAlbumSelectorDown()
{
    uint8_t duration;
#ifdef NXP
    duration = 26;
#else
    duration = 20;
#endif

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, HAL::DISPLAY_HEIGHT, duration);
        albumPlayer.moveTo(backButton.getWidth(), -HAL::DISPLAY_HEIGHT + delta);
        albumSelector.moveTo(backButton.getWidth(), delta);
    }
    else
    {
        // Final step: stop the animation
        setAnimationState(NO_ANIMATION);
        animationCounter = 0;

        setButtonsActiveState(true);
    }
    animationCounter++;
}

void ListNavigationView::StartMusicPlayer(bool play)
{
    musicPlayerPlay = play;
}

void ListNavigationView::play()
{
    // Start animation but do not change playerState before
    // the animation has stopped
    setAnimationState(ANIMATE_PICKUP_IN);

    currentRecordSpeed = 6;
    record.pauseAnimation();

    playButton.setBitmaps(Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_STOP_ID), Bitmap(BITMAP_MUSIC_PLAYER_BUTTON_STOP_PRESSED_ID));
    playButton.invalidate();
}
