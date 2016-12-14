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
#ifndef MUSIC_PLAYER_TILE_HPP
#define MUSIC_PLAYER_TILE_HPP

#include <gui/tiles/BaseTile.hpp>
#include <gui/common/Layout.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/model/MusicPlayer.hpp>
#include <gui/common/FontPosition.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Button.hpp>

/**
 * Shows the current playing album
 *
 * Possible to play and pause the music player. If the cover is pressed the screen is changed to EntertainmentView.
 */
class MusicPlayerTile : public BaseTile
{
public:
    MusicPlayerTile();
    virtual ~MusicPlayerTile() {};

    void update(MusicPlayer& player);

    void setCoverClickedAction(touchgfx::GenericCallback<>& callback)
    {
        coverPressedAction = &callback;
    }
    void setPlayPauseAction(touchgfx::GenericCallback<>& callback)
    {
        playPauseAction = &callback;
    }

    virtual void handleTickEvent();
protected:
    uint32_t tickCounter;
    touchgfx::Image verticalLine;

    touchgfx::Button cover;
    touchgfx::Button controlButton;

    uint16_t artistTextWidth;
    bool animateArtistTextActive;

    FontPosition<touchgfx::TextArea> stateText;
    FontPosition<touchgfx::TextArea> artistText;

    touchgfx::Container artistTextViewPort;

    touchgfx::Callback<MusicPlayerTile, const touchgfx::AbstractButton&> buttonClicked;
    void handleButtonClicked(const touchgfx::AbstractButton& button);

    touchgfx::GenericCallback<>* coverPressedAction;
    touchgfx::GenericCallback<>* playPauseAction;
};

#endif
