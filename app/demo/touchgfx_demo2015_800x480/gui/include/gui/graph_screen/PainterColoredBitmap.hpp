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
#ifndef PAINTERCOLOREDBITMAP_HPP
#define PAINTERCOLOREDBITMAP_HPP

#include <stdint.h>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#endif

using namespace touchgfx;

/**
 * @class PainterColoredBitmap PainterColoredBitmap.hpp gui/graph_screen/PainterColoredBitmap.hpp
 *
 * @brief A Painter that will paint using a bitmap with a given color.
 *
 *        PainterColoredBitmap will take the color for a given point from a bitmap. The pixel
 *        from the bitmap is 'multiplied' with the given color. This means that if the given
 *        color is red (255,0,0), the blue and green parts of the image will be masked out.
 *        Interesting effects can be obtained if the given image contains colors from the
 *        entire spectrum, but usually the bitmap will be a gray scale bitmap and in this case
 *        the painter can be used to get various shades of the selected color.
 *
 * @see AbstractPainter
 */
class PainterColoredBitmap :
#if !defined(USE_BPP) || USE_BPP==16
    public PainterRGB565Bitmap
#elif USE_BPP==24
    public PainterRGB888Bitmap
#endif
{
public:
    /**
     * @fn PainterColoredBitmap::PainterColoredBitmap();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    PainterColoredBitmap();

    /**
     * @fn PainterColoredBitmap::PainterColoredBitmap(colortype color, const Bitmap& bmp = Bitmap(BITMAP_INVALID), uint8_t alpha = 255);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color The color.
     * @param bmp   The bitmap.
     * @param alpha the alpha.
     */
    PainterColoredBitmap(colortype color, const Bitmap& bmp = Bitmap(BITMAP_INVALID), uint8_t alpha = 255);

    /**
     * @fn void PainterColoredBitmap::setColor(colortype color);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color The color.
     *
     * ### param alpha (Optional) The alpha.
     */
    void setColor(colortype color);

protected:
    /**
     * @fn virtual bool PainterColoredBitmap::renderNext(uint8_t &pixelRed, uint8_t &pixelGreen, uint8_t &pixelBlue, uint8_t &pixelAlpha);
     *
     * @brief Gets the color and alpha for the next pixel.
     *
     *        Gets the color and alpha for the next pixel.
     *
     * @param [out] pixelRed   The red.
     * @param [out] pixelGreen The green.
     * @param [out] pixelBlue  The blue.
     * @param [out] pixelAlpha The alpha.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool renderNext(uint8_t& pixelRed, uint8_t& pixelGreen, uint8_t& pixelBlue, uint8_t& pixelAlpha);

    uint8_t red;   ///< The red part of the color
    uint8_t green; ///< The green part of the color
    uint8_t blue;  ///< The blue part of the color
};

#endif /* PAINTERCOLOREDBITMAP_HPP */
