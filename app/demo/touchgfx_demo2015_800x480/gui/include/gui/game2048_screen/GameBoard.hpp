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
#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <stdlib.h>

using namespace touchgfx;

class GameBoard : public Container
{
public:
    GameBoard();

    virtual ~GameBoard();

    virtual void handleTickEvent();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    //virtual void handleGestureEvent(const GestureEvent& evt);

    void setMoveCompletedCallback(touchgfx::GenericCallback<const GameBoard&>& callback)
    {
        moveCompletedAction = &callback;
    }
    void setGameWonCallback(touchgfx::GenericCallback<const GameBoard&>& callback)
    {
        gameWonAction = &callback;
    }
    void setGameLostCallback(touchgfx::GenericCallback<const GameBoard&>& callback)
    {
        gameLostAction = &callback;
    }

    int getScore() const
    {
        return score;
    }

    void initiateNewGame();

    void setAutoPlay(bool newAutoPlay);
    bool getAutoPlay()
    {
        return autoPlay;
    }

protected:
    enum AnimationStates
    {
        ANIMATE_TILE_MOVEMENT,
        ANIMATE_PROMOTION,
        ANIMATE_INSERT_RANDOM_TILE,
        NO_ANIMATION
    } currentAnimationState;

    enum GameState
    {
        LOST,
        WON,
        ACTIVE
    };

    enum TileState
    {
        TILE_EMPTY = 0,
        TILE_0002,
        TILE_0004,
        TILE_0008,
        TILE_0016,
        TILE_0032,
        TILE_0064,
        TILE_0128,
        TILE_0256,
        TILE_0512,
        TILE_1024,
        TILE_2048,
        NUMBER_OF_TILE_STATES
    };

    struct Tile
    {
        TileState state;
        ZoomAnimationImage image;
        bool isPromoted;
    };


    static const int NUMBER_OF_VERTICAL_TILES = 4;
    static const int NUMBER_OF_HORIZONTAL_TILES = 4;
    static const int TILE_SPACING = 13;
    static const int DRAG_THRESHOLD = 8;

    static const int TILE_MOVE_DURATION = 3;

    int tileOffset;

    int score;

    GenericCallback<const GameBoard&>* moveCompletedAction;
    GenericCallback<const GameBoard&>* gameWonAction;
    GenericCallback<const GameBoard&>* gameLostAction;

    Tile tilesAlloc[NUMBER_OF_VERTICAL_TILES][NUMBER_OF_HORIZONTAL_TILES];
    Tile* tiles[NUMBER_OF_VERTICAL_TILES][NUMBER_OF_HORIZONTAL_TILES];

    // Backup states for undo move
    TileState tileStateBackup[NUMBER_OF_VERTICAL_TILES][NUMBER_OF_HORIZONTAL_TILES];
    bool tilePromotionBackup[NUMBER_OF_VERTICAL_TILES][NUMBER_OF_HORIZONTAL_TILES];
    int scoreBackup;

    int dragX;
    int dragY;

    GameState gameStatus;

    bool autoPlay;
    int autoPlayPause;

    Callback<GameBoard, const ZoomAnimationImage& > tileMoveEndedCallback;
    void tileMoveEndedHandler(const ZoomAnimationImage& image);

    void updateBoard();
    void updateTile(Tile* tile);

    Bitmap getBitmapForTileState(TileState tileState);
    bool hasEmptyTile();
    Tile* getRandomEmptyTile();


    void moveTileToAndUpdate(int fromX, int fromY, int toX, int toY);
    bool moveTileTo(int fromX, int fromY, int toX, int toY, bool performMove);
    void promoteTile(int x, int y);
    void insertRandomTile();

    int getNumberOfAnimatingTiles();

    void rotateBoard();

    /**
     * @fn int GameBoard::moveTilesRight(bool performMove);
     *
     * @brief Calculates all the tiles that can be moved to the right
     *        The actual tiles are only moved if the parameter performMove
     *        is true.
     *
     * @param performMove true if the method should actually perform the move
     *                    on the board.
     *
     * @return the number of tiles that would be / is moved
     */
    int moveTilesRight(bool performMove);
    int moveTilesLeft(bool performMove);
    int moveTilesUp(bool performMove);
    int moveTilesDown(bool performMove);

    bool hasGameBeenWon();
    bool hasGameBeenLost();

    void takeStateBackup();
    void restoreStateBackup();
    TileState getStartTileState();

};


#endif /* GAME_BOARD_HPP */
