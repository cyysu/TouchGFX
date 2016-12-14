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
#include <gui/entertainment_screen/EntertainmentView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/Constants.hpp>
#include <touchgfx/EasingEquations.hpp>

using namespace touchgfx;

EntertainmentView::EntertainmentView() :
    currentState(NO_ANIMATION),
    animationCounter(0),
    onButtonPressed(this, &EntertainmentView::buttonPressedhandler),
    fadeAnimationCallback(this, &EntertainmentView::handleFadeAnimationEvent),
    slideAnimationCallback(this, &EntertainmentView::handleSlideAnimationEvent)
{
    menu.set(Menu::Entertainment);
    currentCenteredAlbum = 0;
}

void EntertainmentView::setupScreen()
{
    baseview::setupScreen();

    headline.setBitmap(Bitmap(BITMAP_ENTERTAINMENT_HEADLINE_ID));

    buttons.setBitmap(Bitmap(BITMAP_TOP_NAVI_ID));
    buttons.setXY(636, 40);

    mainContainerForCovers.setPosition(Layout::content().x, Layout::content().y, Layout::content().width, Layout::content().height);

#ifdef RESOLUTION_640X480
    int visibleWidthSmallAlbum = 60;
    int visibleWidthMediumAlbum = 100;
    int visibleWidthLargeAlbum = 240;
#else
    int visibleWidthSmallAlbum = 80;
    int visibleWidthMediumAlbum = 160;
    int visibleWidthLargeAlbum = 240;
#endif

    albums[0].setXY(40, 130);
    albums[1].setXY(albums[0].getX() + visibleWidthSmallAlbum, 110);
    albums[2].setXY(albums[1].getX() + visibleWidthMediumAlbum, 90);
    albums[3].setXY(albums[2].getX() + visibleWidthLargeAlbum - (Bitmap(BITMAP_COVER200_0_ID).getWidth() - visibleWidthMediumAlbum), 110);
    albums[4].setXY(albums[3].getX() + Bitmap(BITMAP_COVER200_0_ID).getWidth() - (Bitmap(BITMAP_COVER160_0_ID).getWidth() - visibleWidthSmallAlbum), 130);

    /*
    albums[0].setXY(0, 0);
    albums[1].setXY(0, 0);
    albums[2].setXY(0, 0);
    albums[3].setXY(visibleWidthMediumAlbum - Bitmap(BITMAP_COVER200_0_ID).getWidth(), 0);
    albums[4].setXY(visibleWidthSmallAlbum - Bitmap(BITMAP_COVER160_0_ID).getWidth(), 0);
    */

    for (int i = 0; i < NUMBER_OF_VISIBLE_ALBUMS; i++)
    {
        albumsHidden[i].setPosition(albums[i].getX(), albums[i].getY(), albums[i].getWidth(), albums[i].getHeight());
    }

    // Remove shadow beneath albums when animating (performance optimization)


    albumsHidden[0].setHeight(albumsHidden[0].getHeight() - 10);
    albumsHidden[1].setHeight(albumsHidden[1].getHeight() - 15);
    albumsHidden[2].setHeight(albumsHidden[2].getHeight() - 20);
    albumsHidden[3].setHeight(albumsHidden[3].getHeight() - 15);
    albumsHidden[4].setHeight(albumsHidden[4].getHeight() - 10);


    // it is only necessary to attach a fade animation callback to album 0 and 4 because it is always these two albums that finish the left/right animation
    albums[0].setFadeAnimationEndedAction(fadeAnimationCallback);
    albums[4].setFadeAnimationEndedAction(fadeAnimationCallback);

    // it is only necessary to attach a slide animation callback to album 1 because it is always this album that finish the slide animation
    albums[1].setMoveAnimationEndedAction(slideAnimationCallback);

    for (int i = 0; i < NUMBER_OF_VISIBLE_ALBUMS; i++)
    {
        albumsHidden[i].setVisible(false);
        albums[i].setAction(onButtonPressed);
    }

    currentSelectedNumber = 0;

    shadowSmallLeft.setBitmap(Bitmap(BITMAP_SHADOW_SMALL_LEFT_ID));
    shadowSmallLeft.setXY(albums[0].getX() + visibleWidthSmallAlbum - shadowSmallLeft.getWidth(), albums[0].getY());

    shadowLargeLeft.setBitmap(Bitmap(BITMAP_SHADOW_LARGE_LEFT_ID));
    shadowLargeLeft.setXY(albums[1].getX() + visibleWidthMediumAlbum - shadowLargeLeft.getWidth(), albums[1].getY());

    shadowSmallRight.setBitmap(Bitmap(BITMAP_SHADOW_SMALL_RIGHT_ID));
    shadowSmallRight.setXY(albums[3].getX() + Bitmap(BITMAP_COVER200_0_ID).getWidth(), albums[4].getY());

    shadowLargeRight.setBitmap(Bitmap(BITMAP_SHADOW_LARGE_RIGHT_ID));
    shadowLargeRight.setXY(albums[2].getX() + Bitmap(BITMAP_COVER240_0_ID).getWidth(), albums[3].getY());

    playButton.setXY(albums[2].getX() + 57, albums[2].getY() + 57);
    playButton.setBitmaps(Bitmap(BITMAP_PLAY_NORMAL_ID), Bitmap(BITMAP_PLAY_PRESSED_ID));
    playButton.setAction(onButtonPressed);

#ifdef RESOLUTION_640X480
    int xAdjustment = -80;
#else
    int xAdjustment = 0;
#endif

    prevTrackButton.setXY(164 + xAdjustment, 335);
    prevTrackButton.setBitmaps(Bitmap(BITMAP_BACK_NORMAL_ID), Bitmap(BITMAP_BACK_PRESSED_ID));
    prevTrackButton.setAction(onButtonPressed);

    nextTrackButton.setXY(584 + xAdjustment, 335);
    nextTrackButton.setBitmaps(Bitmap(BITMAP_NEXT_NORMAL_ID), Bitmap(BITMAP_NEXT_PRESSED_ID));
    nextTrackButton.setAction(onButtonPressed);

    artistAlbumText.setColor(Colors_TEXT_DARK);
    artistAlbumText.setTypedText(TypedText(T_ENT_ARTIST_ALBUM));
    artistAlbumText.setWildcard1(artistTextBuffer);
    artistAlbumText.setWildcard2(albumTextBuffer);
    artistAlbumText.setPosition(218 + xAdjustment, 360 - TypedText(T_ENT_ARTIST_ALBUM).getFont()->getFontHeight(), 366, 20);

    durationTrackText.setColor(Colors_TEXT_DARK);
    durationTrackText.setTypedText(TypedText(T_ENT_DURATION_TITLE));
    durationTrackText.setWildcard1(durationTextBuffer);
    durationTrackText.setWildcard2(trackTextBuffer);
    durationTrackText.setPosition(218 + xAdjustment, 380 - TypedText(T_ENT_DURATION_TITLE).getFont()->getFontHeight(), 366, 20);

    content.add(mainContainerForCovers);

    mainContainerForCovers.add(albumsHidden[0]);
    mainContainerForCovers.add(albums[0]);
    mainContainerForCovers.add(albumsHidden[4]);
    mainContainerForCovers.add(albums[4]);
    mainContainerForCovers.add(albumsHidden[1]);
    mainContainerForCovers.add(albums[1]);
    mainContainerForCovers.add(albumsHidden[3]);
    mainContainerForCovers.add(albums[3]);
    mainContainerForCovers.add(albumsHidden[2]);
    mainContainerForCovers.add(albums[2]);

    content.add(shadowSmallLeft);
    content.add(shadowLargeLeft);
    content.add(shadowLargeRight);
    content.add(shadowSmallRight);

    content.add(playButton);
    content.add(prevTrackButton);
    content.add(nextTrackButton);
    content.add(artistAlbumText);
    content.add(durationTrackText);
}

void EntertainmentView::tearDownScreen()
{
}

void EntertainmentView::handleTickEvent()
{
    if (currentState == ANIMATE_ALBUMS_LEFT)
    {
        animateAlbums(-1);
    }
    else if (currentState == ANIMATE_ALBUMS_RIGHT)
    {
        animateAlbums(1);
    }
    else if (currentState == ANIMATE_ALBUM_OUT)
    {
        animateAlbumOut();
    }
    else if (currentState == ANIMATE_ALBUM_OUT_DELAY)
    {
        if (animationCounter > 30)
        {
            setCurrentState(NO_ANIMATION);
            static_cast<FrontendApplication*>(Application::getInstance())->gotoHomeScreen();
        }
    }
    animationCounter++;
}

void EntertainmentView::handleGestureEvent(const GestureEvent& evt)
{
    if (currentState == NO_ANIMATION && evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        if (evt.getY() > menuContainer.getY())
        {
            // Swipe inside the menu area
            return;
        }
        if (evt.getVelocity() < -10)
        {
            selectAlbum(3);
        }
        else if (evt.getVelocity() > 10)
        {
            selectAlbum(1);
        }
    }
}

void EntertainmentView::buttonPressedhandler(const AbstractButton& button)
{
    if (currentState == NO_ANIMATION)
    {
        if (&button == &albums[0])
        {
            selectAlbum(0);
        }
        else if (&button == &albums[1])
        {
            selectAlbum(1);
        }
        else if (&button == &albums[3])
        {
            selectAlbum(3);
        }
        else if (&button == &albums[4])
        {
            selectAlbum(4);
        }
        else if (&button == &prevTrackButton)
        {
            uint8_t numberOfTracks = albumManager->getAlbum(currentCenteredAlbum)->getNumberOfTracks();
            currentSelectedNumber = (numberOfTracks + currentSelectedNumber - 1) % numberOfTracks;
            updateTexts();
        }
        else if (&button == &nextTrackButton)
        {
            uint8_t numberOfTracks = albumManager->getAlbum(currentCenteredAlbum)->getNumberOfTracks();
            currentSelectedNumber = (currentSelectedNumber + 1) % numberOfTracks;
            updateTexts();
        }
        else if (&button == &playButton)
        {
            setCurrentState(ANIMATE_ALBUM_OUT);
        }
    }
}

void EntertainmentView::setCenterAlbum(uint8_t albumId)
{
    assert(albumId < AlbumManager::NUMBER_OF_ALBUMS);

    setHiddenAlbumCover(0, albumManager->getAlbum(getPrevAlbumId(getPrevAlbumId(albumId))));
    setHiddenAlbumCover(1, albumManager->getAlbum(getPrevAlbumId(albumId)));
    setHiddenAlbumCover(2, albumManager->getAlbum(albumId));
    setHiddenAlbumCover(3, albumManager->getAlbum(getNextAlbumId(albumId)));
    setHiddenAlbumCover(4, albumManager->getAlbum(getNextAlbumId(getNextAlbumId(albumId))));
}

void EntertainmentView::setAlbumCover(uint8_t albumPosition, Album* album)
{
    assert(albumPosition < NUMBER_OF_VISIBLE_ALBUMS);

    if (albumPosition == 0 || albumPosition == 4)
    {
        albums[albumPosition].setBitmaps(Bitmap(album->getAlbumCover160()), Bitmap(album->getAlbumCover160()));
        albums[albumPosition].invalidate();
    }
    else if (albumPosition == 1 || albumPosition == 3)
    {
        albums[albumPosition].setBitmaps(Bitmap(album->getAlbumCover200()), Bitmap(album->getAlbumCover200()));
        albums[albumPosition].invalidate();
    }
    else
    {
        albums[albumPosition].setBitmaps(Bitmap(album->getAlbumCover240()), Bitmap(album->getAlbumCover240()));
        albums[albumPosition].invalidate();
    }
}

void EntertainmentView::setHiddenAlbumCover(uint8_t albumPosition, Album* album)
{
    assert(albumPosition < NUMBER_OF_VISIBLE_ALBUMS);

    if (albumPosition == 0 || albumPosition == 4)
    {
        albumsHidden[albumPosition].setBitmap(Bitmap(album->getAlbumCover160()));
        albumsHidden[albumPosition].invalidate();
    }
    else if (albumPosition == 1 || albumPosition == 3)
    {
        albumsHidden[albumPosition].setBitmap(Bitmap(album->getAlbumCover200()));
        albumsHidden[albumPosition].invalidate();
    }
    else
    {
        albumsHidden[albumPosition].setBitmap(Bitmap(album->getAlbumCover240()));
        albumsHidden[albumPosition].invalidate();
    }
    int shadowSize = (albumPosition == 2) ? 20 : (albumPosition == 1 || albumPosition == 3) ? 15 : 10;
    albumsHidden[albumPosition].setHeight(albumsHidden[albumPosition].getHeight() - shadowSize);


}

uint8_t EntertainmentView::getPrevAlbumId(uint8_t albumId)
{
    return ((albumId + AlbumManager::NUMBER_OF_ALBUMS) - 1) % AlbumManager::NUMBER_OF_ALBUMS;
}

uint8_t EntertainmentView::getNextAlbumId(uint8_t albumId)
{
    return (albumId + 1) % AlbumManager::NUMBER_OF_ALBUMS;
}

void EntertainmentView::setCurrentState(States newState)
{
    animationCounter = 0;
    currentState = newState;
}

void EntertainmentView::animateAlbums(int direction)
{
#ifdef SIMULATOR
    uint8_t animationInterval = 3;
    uint8_t singleAnimationDuration = 5;
#elif defined(USE_STM324x9I_EVAL)
    // STM32F439 5.7" eval board
    uint8_t animationInterval = 1;
    uint8_t singleAnimationDuration = 3;
#elif defined(NXP)
    uint8_t animationInterval = 1;
    uint8_t singleAnimationDuration = 5;
#else
    uint8_t animationInterval = 1;
    uint8_t singleAnimationDuration = 3;
#endif

    uint8_t startAlbum = (direction == -1) ? 4 : 0;
    if (animationCounter == 0)
    {
        for (int i = 0; i < NUMBER_OF_VISIBLE_ALBUMS; i++)
        {
            albums[i].setTouchable(false);
            albumsHidden[i].setVisible(true);
        }
        playButton.setVisible(false);
        playButton.invalidate();
    }
    if ((animationCounter % animationInterval == 0) && (animationCounter / animationInterval < NUMBER_OF_VISIBLE_ALBUMS))
    {
        uint8_t albumIndex = startAlbum + direction * animationCounter / animationInterval;

        albums[albumIndex].startFadeAnimation(0, singleAnimationDuration, &EasingEquations::linearEaseNone);
        albums[albumIndex].invalidate();
    }
}

void EntertainmentView::animateAlbumOut()
{
#ifdef SIMULATOR
    uint8_t animationBlocks = 2;
    uint8_t animationInterval = 10;
    uint8_t singleAnimationDuration = 16;
#elif defined(NXP)
    uint8_t animationBlocks = 2;
    uint8_t animationInterval = 4;
    uint8_t singleAnimationDuration = 12;
#else
    uint8_t animationBlocks = 2;
    uint8_t animationInterval = 4;
    uint8_t singleAnimationDuration = 7;
#endif

    if (animationCounter == 0)
    {
        playButton.setVisible(false);
        playButton.invalidate();
    }
    // First start animation of album 0 and 4, after animationInterval start animation of album 1 and 3
    if ((animationCounter % animationInterval == 0) && (animationCounter / animationInterval < animationBlocks))
    {
        uint8_t block = animationCounter / animationInterval;

        albums[block].startMoveAnimation(albums[block].getX(), albums[block].getY() + 400, singleAnimationDuration, &EasingEquations::linearEaseNone, &EasingEquations::quintEaseIn);
        albums[4 - block].startMoveAnimation(albums[4 - block].getX(), albums[4 - block].getY() + 400, singleAnimationDuration, &EasingEquations::linearEaseNone, &EasingEquations::quintEaseIn);
    }

    // adjust shadows between the small and medium album covers
    if (albums[0].isRunning())
    {
        shadowSmallLeft.setY(albums[0].getY());
        // 200 = height of the album without bottom shadow
        shadowSmallLeft.setHeight((albums[1].getY() + 200) - shadowSmallLeft.getY());
        shadowSmallLeft.invalidate();

        shadowSmallRight.setY(albums[4].getY());
        // 200 = height of the album without bottom shadow
        shadowSmallRight.setHeight((albums[3].getY() + 200) - shadowSmallRight.getY());
        shadowSmallRight.invalidate();
    }

    // Adjust shadows between the medium and large album covers
    if (albums[1].isRunning())
    {
        shadowLargeLeft.setY(albums[1].getY());
        // 240 = height of the album without bottom shadow
        shadowLargeLeft.setHeight((albums[2].getY() + 240) - shadowLargeLeft.getY());
        shadowLargeLeft.invalidate();

        shadowLargeRight.setY(albums[3].getY());
        // 240 = height of the album without bottom shadow
        shadowLargeRight.setHeight((albums[2].getY() + 240) - shadowLargeRight.getY());
        shadowLargeRight.invalidate();

    }
}

void EntertainmentView::updateTexts()
{
    Unicode::snprintf(artistTextBuffer, ARTIST_BUFFER_LENGTH, "%s", TypedText(albumManager->getAlbum(currentCenteredAlbum)->getAlbumArtist()).getText());
    Unicode::snprintf(albumTextBuffer, ALBUM_BUFFER_LENGTH, "%s", TypedText(albumManager->getAlbum(currentCenteredAlbum)->getAlbumName()).getText());
    artistAlbumText.invalidate();

    Unicode::snprintf(durationTextBuffer, DURATION_BUFFER_LENGTH, "%s", TypedText(albumManager->getAlbum(currentCenteredAlbum)->getTrackDuration(currentSelectedNumber)).getText());
    Unicode::snprintf(trackTextBuffer, TRACK_BUFFER_LENGTH, "%s", TypedText(albumManager->getAlbum(currentCenteredAlbum)->getTrack(currentSelectedNumber)).getText());
    durationTrackText.invalidate();
}

void EntertainmentView::selectAlbum(uint8_t albumPos)
{
    if (albumPos == 0)
    {
        currentCenteredAlbum = getPrevAlbumId(getPrevAlbumId(currentCenteredAlbum));
        setCurrentState(ANIMATE_ALBUMS_RIGHT);
        setCenterAlbum(currentCenteredAlbum);
    }
    else if (albumPos == 1)
    {
        currentCenteredAlbum = getPrevAlbumId(currentCenteredAlbum);
        setCurrentState(ANIMATE_ALBUMS_RIGHT);
        setCenterAlbum(currentCenteredAlbum);
    }
    else if (albumPos == 3)
    {
        currentCenteredAlbum = getNextAlbumId(currentCenteredAlbum);
        setCurrentState(ANIMATE_ALBUMS_LEFT);
        setCenterAlbum(currentCenteredAlbum);
    }
    else if (albumPos == 4)
    {
        currentCenteredAlbum = getNextAlbumId(getNextAlbumId(currentCenteredAlbum));
        setCurrentState(ANIMATE_ALBUMS_LEFT);
        setCenterAlbum(currentCenteredAlbum);
    }
}

void EntertainmentView::handleFadeAnimationEvent(const FadeAnimator<Button>& drawable)
{
    // Verify if the complete animation has finished
    if ((&drawable == &albums[0] && currentState == ANIMATE_ALBUMS_LEFT) ||
            (&drawable == &albums[4] && currentState == ANIMATE_ALBUMS_RIGHT))
    {
        for (int i = 0; i < NUMBER_OF_VISIBLE_ALBUMS; i++)
        {
            albumsHidden[i].setVisible(false);
            //albumsHidden[i].setAlpha(0);
            albums[i].setAlpha(255);
            albums[i].setBitmaps(Bitmap(albumsHidden[i].getBitmap()), Bitmap(albumsHidden[i].getBitmap()));
            albumsHidden[i].invalidate();
            albums[i].invalidate();
            albums[i].setTouchable(true);
        }
        playButton.setVisible(true);
        playButton.invalidate();
        currentSelectedNumber = 0;
        updateTexts();
        setCurrentState(NO_ANIMATION);
    }
}

void EntertainmentView::handleSlideAnimationEvent(const MoveAnimator< FadeAnimator<Button> >& drawable)
{
    if (currentState == ANIMATE_ALBUM_OUT)
    {
        if (&drawable == &albums[1])
        {
            setCurrentState(ANIMATE_ALBUM_OUT_DELAY);
            presenter->setCurrentAlbum(currentCenteredAlbum);
            presenter->setCurrentNumber(currentSelectedNumber);
        }
    }
}

void EntertainmentView::setCurrentCenteredAlbum(uint8_t albumId)
{
    currentCenteredAlbum = albumId;

    updateTexts();
    setAlbumCover(0, albumManager->getAlbum(getPrevAlbumId(getPrevAlbumId(currentCenteredAlbum))));
    setAlbumCover(1, albumManager->getAlbum(getPrevAlbumId(currentCenteredAlbum)));
    setAlbumCover(2, albumManager->getAlbum(currentCenteredAlbum));
    setAlbumCover(3, albumManager->getAlbum(getNextAlbumId(currentCenteredAlbum)));
    setAlbumCover(4, albumManager->getAlbum(getNextAlbumId(getNextAlbumId(currentCenteredAlbum))));
    setCenterAlbum(currentCenteredAlbum);
}
