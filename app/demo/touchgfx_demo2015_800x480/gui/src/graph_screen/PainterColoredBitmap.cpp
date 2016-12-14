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
#include <gui/graph_screen/PainterColoredBitmap.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

PainterColoredBitmap::PainterColoredBitmap()
{
    setColor(0);
    setBitmap(Bitmap(BITMAP_INVALID));
    setAlpha(255);
}

PainterColoredBitmap::PainterColoredBitmap(colortype color, const Bitmap& bmp, uint8_t alpha)
{
    setColor(color);
    setBitmap(bmp);
    setAlpha(alpha);
}

void PainterColoredBitmap::setColor(colortype color)
{
    red = Color::getRedColor(color);
    green = Color::getGreenColor(color);
    blue = Color::getBlueColor(color);
}

bool PainterColoredBitmap::renderNext(uint8_t& pixelRed, uint8_t& pixelGreen, uint8_t& pixelBlue, uint8_t& pixelAlpha)
{
    // Get RGBA from the bitmap
#if !defined(USE_BPP) || USE_BPP==16
    if (PainterRGB565Bitmap::renderNext(pixelRed, pixelGreen, pixelBlue, pixelAlpha))
#elif USE_BPP==24
    if (PainterRGB888Bitmap::renderNext(pixelRed, pixelGreen, pixelBlue, pixelAlpha))
#endif
    {
        // Multiply with our color
        pixelRed   = (pixelRed   * this->red) / 255;
        pixelGreen = (pixelGreen * this->green) / 255;
        pixelBlue  = (pixelBlue  * this->blue) / 255;
        return true;
    }
    return false;
}
