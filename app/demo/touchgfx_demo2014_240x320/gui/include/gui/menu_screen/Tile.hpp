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
#ifndef TILE_HPP_
#define TILE_HPP_

#include <touchgfx/mixins/ClickListener.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

/**
 * Container wrapping tile classes. Adding pressed and clicked events to the tile.
 */
template<class T>
class Tile : public Container
{
public:
    Tile() :
        pressedActive(false),
        onTileClicked(this, &Tile::tileClickedhandler)
    {
        setWidth(tile.getWidth() + 6);
        setHeight(tile.getHeight() + 6);

        tile.setXY(3, 3);
        tile.setClickAction(onTileClicked);

        add(tile);
    }

    virtual ~Tile()
    {

    }

    T& getTile()
    {
        return tile;
    }

private:

    ClickListener<T> tile;

    bool pressedActive;

    Callback<Tile, const T&, const ClickEvent& > onTileClicked;

    void tileClickedhandler(const T& t, const ClickEvent& event)
    {
        if (&t == &tile)
        {
            if (event.getType() == ClickEvent::RELEASED)
            {
                if (pressedActive)
                {
                    tile.gotoAssociatedScreen();
                }
            }
            else if (event.getType() == ClickEvent::PRESSED)
            {
                pressedActive = true;
            }
            else if (event.getType() == ClickEvent::CANCEL)
            {
                pressedActive = false;
            }
        }
    }
};

#endif /* TILE_HPP_ */
