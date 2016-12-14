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
#include <gui/graph_screen/PainterVerticalAlpha.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

PainterVerticalAlpha::PainterVerticalAlpha(colortype color /*= 0*/, int alpha0atY /*= 100*/)
{
    setColor(color, alpha0atY);
}

void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt)
{
    red = Color::getRedColor(color);
    green = Color::getGreenColor(color);
    blue = Color::getBlueColor(color);
    alpha0atY = alphaZeroAt;
}

bool PainterVerticalAlpha::renderInit()
{
    int gradientAlpha = 255 - (currentY * 255 / alpha0atY);
    if (gradientAlpha < 0)
    {
        gradientAlpha = 0;
    }
    if (gradientAlpha > 255)
    {
        gradientAlpha = 255;
    }
    alpha = gradientAlpha;
    return true;
}

bool PainterVerticalAlpha::renderNext(uint8_t& pixelRed, uint8_t& pixelGreen, uint8_t& pixelBlue, uint8_t& pixelAlpha)
{
    pixelRed = this->red;
    pixelGreen = this->green;
    pixelBlue = this->blue;
    pixelAlpha = this->alpha;
    return true;
}

void PainterVerticalAlpha::renderPixel(uint16_t* p, uint8_t pixelRed, uint8_t pixelGreen, uint8_t pixelBlue)
{
#if !defined(USE_BPP) || USE_BPP==16
#define fastrand(g_seed) ((214013*(uint32_t)(g_seed)+2531011)>>16)
    uint8_t rand = fastrand((currentX + *p) * (currentY + *p));

    if (pixelRed   < 0xF8)
    {
        pixelRed   = pixelRed   + ((rand >> 5));    // Add bit 7-5 of rand to red to get rounding
    }
    if (pixelGreen < 0xFC)
    {
        pixelGreen = pixelGreen + ((rand >> 3) & 0x3);    // Add bit 4-3 of rand to green to get rounding
    }
    if (pixelBlue  < 0xF8)
    {
        pixelBlue  = pixelBlue  + ((rand) & 0x7);    // Add bit 2-0 of rand to blue to get rounding
    }

    AbstractPainterRGB565::renderPixel(p, pixelRed, pixelGreen, pixelBlue);
#elif USE_BPP==24
    AbstractPainterRGB888::renderPixel(p, pixelRed, pixelGreen, pixelBlue);
#endif
}
