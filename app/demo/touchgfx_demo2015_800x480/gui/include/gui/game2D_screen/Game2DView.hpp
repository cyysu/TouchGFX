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
#ifndef GAME_2D_VIEW_HPP
#define GAME_2D_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/game2D_screen/Game2DPresenter.hpp>
#include <gui/game2D_screen/CollectibleItem.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <gui/game2D_screen/ParallaxBackground.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/TouchArea.hpp>

class Game2DView : public DemoView<Game2DPresenter>
{
public:
    Game2DView();
    virtual ~Game2DView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

private:
    static const int NUMBER_OF_COLLECTIBLE_ITEMS = 5;

    Image background;

    Container gameArea;
    ParallaxBackground parallaxBackground;
    TouchArea touchArea;

    MoveAnimator<AnimatedImage> playerCharacter;
    int playerCharacterStartX;
    int playerCharacterStartY;
    int playerCharacterMaxY;

    CollectibleItem collectibleItem[NUMBER_OF_COLLECTIBLE_ITEMS];
    CollectibleItem bullet;

    bool chromArtOff;

    Button flyButton;
    Button chromArtOnOffButton;

    TextArea chromArtDescription;
    TextArea chromArtHeader;

    TextArea scoreText;
    TextAreaWithOneWildcard scoreValue;
    Unicode::UnicodeChar scoreValueBuf[16];

    int velocity;
    int collectibleItemCatched;
    int collectibleItemMissed;
    int playerDeadCounter;

    Callback<Game2DView, const AbstractButton&> onButtonPressed;
    void buttonPressedhandler(const AbstractButton& button);

    void restartGame();
    void updateScoreText();
    void updateChromArtButtonBitmaps();
};

#endif // GAME_2D_VIEW_HPP
