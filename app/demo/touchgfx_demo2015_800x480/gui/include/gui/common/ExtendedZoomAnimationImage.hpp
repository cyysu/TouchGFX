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
#ifndef EXTENDED_ZOOM_ANIMATION_IMAGE_HPP
#define EXTENDED_ZOOM_ANIMATION_IMAGE_HPP

#include <touchgfx/containers/ZoomAnimationImage.hpp>

using namespace touchgfx;

/**
 * @class ExtendedZoomAnimationImage
 *
 * @brief This widget is part of the TouchGFX Open Widget Repository.
 *
 *        Extends the ZoomAnimationImage with an additional bitmap size.
 *
 * @see ZoomAnimationImage
 */
class ExtendedZoomAnimationImage : public ZoomAnimationImage
{
public:
    /**
     * @fn ExtendedZoomAnimationImage::ExtendedZoomAnimationImage()
     *
     * @brief Default constructor.
     */
    ExtendedZoomAnimationImage() :
        ZoomAnimationImage()
    {

    }

    /**
     * @fn ExtendedZoomAnimationImage::~ExtendedZoomAnimationImage()
     *
     * @brief Destructor.
     */
    virtual ~ExtendedZoomAnimationImage()
    {
    }

    /**
     * @fn void ExtendedZoomAnimationImage::setBitmaps(const Bitmap& smallBitmap, const Bitmap& mediumBitmap, const Bitmap& largeBitmap)
     *
     * @brief Initializes the bitmap of the image to be used. The bitmaps should represent the same
     *        image in the three needed static resolutions. Note that it is possible to scale the
     *        image beyond the sizes of these bitmaps.
     *
     * @param smallBitmap  The image in the smallest resolution.
     * @param mediumBitmap The image in the medium resolution.
     * @param largeBitmap  The image in the largest resolution.
     */
    void setBitmaps(const Bitmap& smallBitmap, const Bitmap& mediumBitmap, const Bitmap& largeBitmap)
    {
        ZoomAnimationImage::setBitmaps(smallBitmap, largeBitmap);
        mediumBmp = mediumBitmap;

    }

    /**
     * @fn void ExtendedZoomAnimationImage::updateRenderingMethod()
     *
     * @brief Handles the rendering of the medium bitmap
     */
    virtual void updateRenderingMethod()
    {
        if ((mediumBmp.getWidth() == getWidth()) && (mediumBmp.getHeight() == getHeight()))
        {
            image.setVisible(true);
            scalableImage.setVisible(false);
            image.setBitmap(mediumBmp);
            image.invalidate();
            scalableImage.invalidate();
        }
        else
        {
            ZoomAnimationImage::updateRenderingMethod();
        }
    }

private:

    touchgfx::Bitmap mediumBmp; ///< The bitmap representing the medium image
};

#endif /* EXTENDED_ZOOM_ANIMATION_IMAGE_HPP */
