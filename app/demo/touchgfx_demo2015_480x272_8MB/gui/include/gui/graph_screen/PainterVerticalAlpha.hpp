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
#ifndef PAINTERRGB565VERTICALALPHA_HPP
#define PAINTERRGB565VERTICALALPHA_HPP

#include <stdint.h>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#endif

using namespace touchgfx;

/**
 * @class PainterVerticalAlpha PainterVerticalAlpha.hpp gui/common/PainterVerticalAlpha.hpp
 *
 * @brief A Painter that will paint using a fading color.
 *
 *        PainterVerticalAlpha will paint using the given color at y coordinate 0 fading
 *        the color to invisible at the given y coordinate.
 *
 * @see AbstractPainter
 */
class PainterVerticalAlpha :
#if !defined(USE_BPP) || USE_BPP==16
    public AbstractPainterRGB565
#elif USE_BPP==24
    public AbstractPainterRGB888
#endif
{
public:

    /**
     * @fn PainterVerticalAlpha::PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color     The color.
     * @param alpha0atY The y coordinate where alpha has faded to 0.
     */
    PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);

    /**
     * @fn void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color       The color.
     * @param alphaZeroAt The y coordinate where alpha has faded to 0.
     */
    void setColor(colortype color, int alphaZeroAt);

protected:
    /**
     * @fn virtual bool PainterVerticalAlpha::renderInit()
     *
     * @brief Initialize the render.
     *
     *        Initialize the render.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool renderInit();

    virtual bool renderNext(uint8_t& pixelRed, uint8_t& pixelGreen, uint8_t& pixelBlue, uint8_t& pixelAlpha);

    uint8_t red;   ///< The red part of the color
    uint8_t green; ///< The green part of the color
    uint8_t blue;  ///< The blue part of the color
    uint8_t alpha; ///< Current alpha for the scan line
    int alpha0atY; ///< The Y coordinate where alpha has faded to 0

private:
    virtual void renderPixel(uint16_t* p, uint8_t pixelRed, uint8_t pixelGreen, uint8_t pixelBlue);

}; // class PainterVerticalAlpha

#endif /* PAINTERRGB565BITMAP_HPP */
