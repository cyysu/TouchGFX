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
#ifndef ENTERTAINMENT_VIEW_HPP
#define ENTERTAINMENT_VIEW_HPP

#include <gui/common/BaseView.hpp>
#include <gui/entertainment_screen/EntertainmentPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/model/AlbumManager.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/Config.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

/**
 * EntertainmentView - control of a music player
 *
 * When an album is selected the album will be positioning in the middle using an animation. Tracks are selected by pressing the
 * left and right arrow and when pressing the play button an animation moves the album out of the screen. After a short delay the
 * demo returns to the home screen showing the selected album.
 */
class EntertainmentView : public BaseView<EntertainmentPresenter>
{
public:
    EntertainmentView();
    virtual ~EntertainmentView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void handleGestureEvent(const GestureEvent& evt);

    void setAlbumManager(AlbumManager* albumManager_)
    {
        albumManager = albumManager_;
    }

    void setCurrentCenteredAlbum(uint8_t albumId);
private:
    static const uint8_t NUMBER_OF_VISIBLE_ALBUMS = 5;

    enum States
    {
        ANIMATE_ALBUMS_LEFT,
        ANIMATE_ALBUMS_RIGHT,
        ANIMATE_ALBUM_OUT,
        ANIMATE_ALBUM_OUT_DELAY,
        NO_ANIMATION
    } currentState;

    uint8_t animationCounter;

    AlbumManager* albumManager;

    Image buttons;

    Button playButton;
    Button prevTrackButton;
    Button nextTrackButton;

    TextAreaWithTwoWildcards artistAlbumText;
    static const uint8_t ARTIST_BUFFER_LENGTH = 30;
    Unicode::UnicodeChar artistTextBuffer[ARTIST_BUFFER_LENGTH];

    static const uint8_t ALBUM_BUFFER_LENGTH = 30;
    Unicode::UnicodeChar albumTextBuffer[ALBUM_BUFFER_LENGTH];

    TextAreaWithTwoWildcards durationTrackText;
    static const uint8_t DURATION_BUFFER_LENGTH = 8;
    Unicode::UnicodeChar durationTextBuffer[DURATION_BUFFER_LENGTH];

    static const uint8_t TRACK_BUFFER_LENGTH = 30;
    Unicode::UnicodeChar trackTextBuffer[TRACK_BUFFER_LENGTH];

    Container mainContainerForCovers;
    Container albumsHiddenViewports[NUMBER_OF_VISIBLE_ALBUMS];
    MoveAnimator< FadeAnimator<Button> > albums[NUMBER_OF_VISIBLE_ALBUMS];
    FadeAnimator<Image> albumsHidden[NUMBER_OF_VISIBLE_ALBUMS];
    Image shadowSmallLeft;
    Image shadowLargeLeft;
    Image shadowSmallRight;
    Image shadowLargeRight;

    uint8_t currentCenteredAlbum;
    uint8_t currentSelectedNumber;

    Callback<EntertainmentView, const AbstractButton& > onButtonPressed;

    void setAlbumCover(uint8_t albumPosition, Album* album);
    void setHiddenAlbumCover(uint8_t albumPosition, Album* album);
    void setCenterAlbum(uint8_t albumId);

    uint8_t getPrevAlbumId(uint8_t albumId);
    uint8_t getNextAlbumId(uint8_t albumId);

    void buttonPressedhandler(const AbstractButton& button);

    void setCurrentState(States newState);

    void updateTexts();
    void selectAlbum(uint8_t albumPos);

    void animateAlbumOut();
    void animateAlbums(int direction);

    Callback<EntertainmentView, const FadeAnimator<Button>&> fadeAnimationCallback;
    void handleFadeAnimationEvent(const FadeAnimator<Button>& drawable);

    Callback<EntertainmentView, const MoveAnimator< FadeAnimator<Button> >&> slideAnimationCallback;
    void handleSlideAnimationEvent(const MoveAnimator< FadeAnimator<Button> >& drawable);
};

#endif
