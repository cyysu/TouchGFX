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
#include <gui/game2D_screen/CollectibleItem.hpp>
#include <BitmapDatabase.hpp>


CollectibleItem::CollectibleItem() :
    tickCounter(0),
    speed(0)
{
    add(image);

    image.setBitmaps(BITMAP_COLLECTIBLE_ITEM_00_ID, BITMAP_COLLECTIBLE_ITEM_09_ID);
    image.setUpdateTicksInterval(4);

    setWidth(image.getWidth());
    setHeight(image.getHeight());
}

CollectibleItem::~CollectibleItem()
{
}


void CollectibleItem::setBitmaps(BitmapId start, BitmapId end)
{
    image.setBitmaps(start, end);
}

void CollectibleItem::handleTickEvent()
{
    tickCounter++;

    if (speed != 0)
    {
        moveTo(getX() - speed, getY());
    }
}

void CollectibleItem::startAnimation(int16_t newSpeed)
{
    speed = newSpeed;
    running = true;
    Application::getInstance()->registerTimerWidget(this);
    image.startAnimation(false, true, true);
}

void CollectibleItem::stopAnimation()
{
    running = false;
    Application::getInstance()->unregisterTimerWidget(this);
    image.stopAnimation();
}
