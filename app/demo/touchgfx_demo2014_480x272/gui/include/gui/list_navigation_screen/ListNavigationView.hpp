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
#ifndef LIST_NAVIGATION_VIEW_HPP
#define LIST_NAVIGATION_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/list_navigation_screen/ListNavigationPresenter.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <gui/list_navigation_screen/VolumeSlider.hpp>
#include <gui/list_navigation_screen/AlbumSelector.hpp>
#include <gui/list_navigation_screen/AlbumManager.hpp>

/**
 * The List Navigation view is a implementation of a musicplayer.
 * The view consists of to main containers. The albumPlayer
 * and the albumSelector. The albumPlayer is the start screen with the
 * record player and play button. The albumSelector is the screen that is
 * slided in when the user presses the album covers. This screen lets the
 * user choose an album from a scrollable list.
 * The information about each album is handled by the albumManager.
 *
 */
class ListNavigationView : public DemoView<ListNavigationPresenter>
{
public:
    ListNavigationView();
    virtual ~ListNavigationView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    virtual void afterTransition();

    void StartMusicPlayer(bool play);

private:
    enum AnimationStates
    {
        ANIMATE_PICKUP_IN,
        ANIMATE_PICKUP_OUT,
        ANIMATE_ALBUM_SELECTOR_UP,
        ANIMATE_ALBUM_SELECTOR_DOWN,
        NO_ANIMATION
    } animationState;

    enum PlayerStates
    {
        STOPPED,
        PLAYING
    } playerState;

    uint8_t animationCounter;
    uint32_t tickCounter;

    // The album manager is placed in the view in this demo
    // In a real application this would probably be placed
    // in the model.
    AlbumManager albumManager;

    Container albumPlayer;

    Image background;
    Image pickup;
    Button albumCovers;

    static const uint8_t NUMBER_OF_SOUND_LEVEL_INDICATORS = 9;
    Image soundLevelIndicators[9];
    uint8_t soundLevels[9];

    Button jumpToStartButton;
    Button playButton;
    Button nextButton;

#ifdef NXP
    static const uint8_t MAX_RECORD_SPEED = 5;
#else
    static const uint8_t MAX_RECORD_SPEED = 3;
#endif

    uint8_t currentRecordSpeed;
    AnimatedImage record;

    VolumeSlider volumeSlider;

    Container trackNameViewPort;
    TextArea trackName;
    uint16_t trackNameCurrentWidth;
    bool animateTrackNameActive;

    AlbumSelector albumSelector;

    bool musicPlayerPlay;

    Callback<ListNavigationView, const AbstractButton&> onButtonPressed;
    Callback<ListNavigationView> onHideAlbumSelector;

    void buttonPressedhandler(const AbstractButton& button);
    void setSelectedAlbum();
    void updateTrackName();
    void hideAlbumSelector();

    void setAnimationState(AnimationStates newState);
    void setButtonsActiveState(bool active);

    void animateSoundLevelIndicators();
    void animateTrackName();
    void resetSoundLevelIndicators();
    void animatePickupIn();
    void animatePickupOut();
    void animateAlbumSelectorUp();
    void animateAlbumSelectorDown();

    void play();
};

#endif // LIST_NAVIGATION_VIEW_HPP
