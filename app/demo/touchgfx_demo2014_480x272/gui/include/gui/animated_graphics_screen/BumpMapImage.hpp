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
#ifndef BUMP_MAP_IMAGE_HPP
#define BUMP_MAP_IMAGE_HPP

#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class BumpMapImage : public Widget
{
public:

    BumpMapImage(BitmapId image_, const unsigned int* bump_map_, const unsigned char* light_source_);
    virtual ~BumpMapImage();

    virtual void handleTickEvent();

    virtual void handleClickEvent(const ClickEvent& evt);

    virtual void draw(const touchgfx::Rect&) const;
    virtual void drawOptimized(const touchgfx::Rect&) const;
    virtual void drawNormal(const touchgfx::Rect&) const;

    virtual Rect getSolidRect() const;
    void setLightPosition(uint16_t x, uint16_t y);

    void setImage(Bitmap newImage)
    {
        image = newImage;
    }
    void setBumpMap(const unsigned int* bump_map_)
    {
        bump_map = bump_map_;
    }
    void setDragFinish(bool state);

private:
    static const uint16_t lightSourceWidth = 128;
    static const uint16_t lightSourceHeight = 128;
    static const uint8_t lightMax = 48;

    enum States
    {
        DRAGGING,
        ANIMATE_CATCH,
        ANIMATE_AUTO
    } currentState;

    Bitmap image;
    Bitmap bump;
    const unsigned int* bump_map;
    const unsigned char* light_source;

    int currentTime;
    uint8_t catchTime;
    uint16_t lightPositionX;
    uint16_t lightPositionY;
    uint16_t tempPositionX;
    uint16_t tempPositionY;

    int height(uint16_t value) const;
    void invalidateAccordingToCurrentLightSetting();

#ifdef SIMULATOR
    uint8_t light(int16_t x, int16_t y) const;
    void printBumpMap();
    void printLightTable();
#endif // SIMULATOR
};

#endif // BUMP_MAP_IMAGE_HPP
