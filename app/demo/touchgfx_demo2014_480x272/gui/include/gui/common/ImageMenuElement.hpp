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
#ifndef IMAGEMENUELEMENT_HPP_
#define IMAGEMENUELEMENT_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>

using namespace touchgfx;

class ImageMenuElement : public Container
{
public:
    ImageMenuElement()
    {
        add(boarder);
        add(image);
    }

    void initialize(BitmapId imageBitmap)
    {
        image.setXY(0, 0);
        image.setBitmaps(Bitmap(imageBitmap), Bitmap(imageBitmap));

        setWidth(image.getWidth());
        setHeight(image.getHeight());
    }

    void initialize(BitmapId imageBitmap, BitmapId boarderBitmap)
    {
        boarder.setXY(0, 0);
        boarder.setBitmap(Bitmap(boarderBitmap));

        image.setXY(boarder.getWidth(), 0);
        image.setBitmaps(Bitmap(imageBitmap), Bitmap(imageBitmap));

        setWidth(boarder.getWidth() + image.getWidth());
        setHeight(image.getHeight());
    }

    void setAlpha(uint8_t alpha)
    {
        boarder.setAlpha(alpha);
        image.setAlpha(alpha);
        boarder.invalidate();
        image.invalidate();
    }

    uint8_t getAlpha()
    {
        return image.getAlpha();
    }

    Button& getImage()
    {
        return image;
    }

    uint16_t getBoarderWidth()
    {
        return boarder.getWidth();
    }
private:
    Image boarder;
    Button image;
};


#endif /* IMAGEMENUELEMENT_HPP_ */
