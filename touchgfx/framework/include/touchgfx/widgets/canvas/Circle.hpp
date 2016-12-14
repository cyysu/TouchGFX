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
 * Copyright (C) 2014-2016 Draupner Graphics A/S <http://www.touchgfx.com>.
 * All rights reserved.
 *
 * TouchGFX is protected by international copyright laws and the knowledge of
 * this source code may not be used to write a similar product. This file may
 * only be used in accordance with a license and should not be re-
 * distributed in any way without the prior permission of Draupner Graphics.
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
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/lcd/LCD.hpp>

#include <touchgfx/widgets/canvas/Canvas.hpp>
#include <touchgfx/widgets/canvas/CanvasWidget.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

namespace touchgfx
{
/**
 * @class Circle Circle.hpp touchgfx/widgets/canvas/Circle.hpp
 *
 * @brief Simple widget capable of drawing a circle.
 *
 *        Simple widget capable of drawing a circle. By tweaking the parameters of the circle,
 *        several parameters of the circle can be changed. Center, radius, line width, line cap
 *        and partial circle arc. This opens for creation of fascinating graphics.
 *
 * @see CanvasWidget
 */
class Circle : public CanvasWidget
{
public:

    /**
     * @fn Circle::Circle();
     *
     * @brief Constructs a new Circle.
     *
     *        Constructs a new Circle.
     */
    Circle();

    /**
     * @fn template <class T> void Circle::setCircle(T x, T y, T r)
     *
     * @brief Sets the center and radius of the Circle.
     *
     *        Sets the center and radius of the Circle.
     *
     * @note The area containing the Circle is not invalidated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param x The x coordinate of center.
     * @param y The y coordinate of center.
     * @param r The radius.
     */
    template <class T>
    void setCircle(T x, T y, T r)
    {
        setCenter<T>(x, y);
        setRadius<T>(r);
    }

    /**
     * @fn template <class T> void Circle::setCenter(T x, T y)
     *
     * @brief Sets the center of the Circle.
     *
     *        Sets the center of the Circle.
     *
     * @note The area containing the Circle is not invalidated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param x The x coordinate of center.
     * @param y The y coordinate of center.
     */
    template <class T>
    void setCenter(T x, T y)
    {
        this->circleCenterX = CWRUtil::toQ5(x);
        this->circleCenterY = CWRUtil::toQ5(y);
    }

    /**
     * @fn template <class T> void Circle::getCenter(T& x, T& y)
     *
     * @brief Gets the center coordinates of the Circle.
     *
     *        Gets the center coordinates of the Circle.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param [out] x The x coordinate of the center.
     * @param [out] y The y coordinate of the center.
     */
    template <class T>
    void getCenter(T& x, T& y)
    {
        x = int(this->circleCenterX) / T(Rasterizer::POLY_BASE_SIZE);
        y = int(this->circleCenterY) / T(Rasterizer::POLY_BASE_SIZE);
    }

    /**
     * @fn template <class T> void Circle::setRadius(T r)
     *
     * @brief Sets the radius of the Circle.
     *
     *        Sets the radius of the Circle.
     *
     * @note The area containing the Circle is not invalidated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param r The radius.
     */
    template <class T>
    void setRadius(T r)
    {
        this->circleRadius = CWRUtil::toQ5(r);
    }

    /**
     * @fn template <class T> void Circle::getRadius(T& r)
     *
     * @brief Gets the radius of the Circle.
     *
     *        Gets the radius of the Circle.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param [out] r The radius.
     */
    template <class T>
    void getRadius(T& r)
    {
        r = int(circleRadius) / T(Rasterizer::POLY_BASE_SIZE);
    }

    /**
     * @fn void Circle::setArc(int16_t startAngle, int16_t endAngle);
     *
     * @brief Sets the start and end angles in degrees of the Circle arc.
     *
     *        Sets the start and end angles in degrees of the Circle arc. 0 degrees is straight
     *        up (12 o'clock) and 90 degress is to the left (3 o'clock). Any positive or
     *        negative degrees can be used to specify the part of the Circle to draw.
     *
     * @note The area containing the Circle is not invalidated.
     *
     * @param startAngle The start degrees.
     * @param endAngle   The end degrees.
     *
     * @see getArc
     * @see updateArcStart
     * @see updateArcEnd
     */
    void setArc(int16_t startAngle, int16_t endAngle);

    /**
     * @fn void Circle::getArc(int16_t& startAngle, int16_t& endAngle);
     *
     * @brief Gets the start and end angles in degrees for the circle arc.
     *
     *        Gets the start and end angles in degrees for the circle arc.
     *
     * @param [out] startAngle The start.
     * @param [out] endAngle   The end.
     *
     * @see setArc
     */
    void getArc(int16_t& startAngle, int16_t& endAngle);

    /**
     * @fn int16_t Circle::getArcStart() const;
     *
     * @brief Gets the start angle in degrees for the arc.
     *
     *        Gets the start angle in degrees for the arc.
     *
     * @return The starting angle for the arc.
     *
     * @see getArc
     * @see setArc
     */
    int16_t getArcStart() const;

    /**
     * @fn int16_t Circle::getArcEnd() const;
     *
     * @brief Gets the end angle in degrees for the arc.
     *
     * @return The finishing angle for the arc.
     *
     * @see getArc
     * @see setArc
     */
    int16_t getArcEnd() const;

    /**
     * @fn void Circle::updateArcStart(int16_t startAngle);
     *
     * @brief Updates the start angle in degrees for this Circle arc.
     *
     *        Updates the start angle in degrees for this Circle arc.
     *
     * @note The area containing the updated Circle arc is invalidated.
     *
     * @param startAngle The start angle in degrees.
     *
     * @see setArc
     * @see updateArcEnd
     */
    void updateArcStart(int16_t startAngle);

    /**
     * @fn void Circle::updateArcEnd(int16_t endAngle);
     *
     * @brief Updates the end angle in degrees for this Circle arc.
     *
     *        Updates the end angle in degrees for this Circle arc.
     *
     * @note The area containing the updated Circle arc is invalidated.
     *
     * @param endAngle The end angle in degrees.
     *
     * @see setArc
     * @see updateArcStart
     */
    void updateArcEnd(int16_t endAngle);

    /**
     * @fn template <class T> void Circle::setLineWidth(T width)
     *
     * @brief Sets the width for this Circle.
     *
     *        Sets the width for this Circle. If the line width is set to zero, the circle will
     *        be filled.
     *
     * @note The area containing the Circle is not invalidated.
     * @note if the new line with is smaller than the old width, the circle should be invalidated
     *       before updating the width to ensure that the old circle is completely erased.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param width The width of the line measured in pixels.
     */
    template <class T>
    void setLineWidth(T width)
    {
        this->circleLineWidth = CWRUtil::toQ5(width);
    }

    /**
     * @fn void Circle::setPrecision(int precision);
     *
     * @brief Sets a precision of the Circle drawing function.
     *
     *        Sets a precision of the Circle drawing function. The precision is given in
     *        degrees, five being a sensible value. Higher values results in less nice circles
     *        but faster rendering. The number passed as precision is the number of degrees
     *        used as step counter when drawing smaller line fragments around the circumference
     *        of the circle.
     *
     * @note The circle is not invalidated.
     *
     * @param precision The precision measured in degrees.
     */
    void setPrecision(int precision);

    /**
     * @fn void Circle::setCapPrecision(int precision);
     *
     * @brief Sets a precision of the ends of the Circle arc.
     *
     *        Sets a precision of the ends of the Circle arc. The precision is given in degrees
     *        where 180 is the default which results in a square ended arc (aka "butt cap"). 90
     *        will draw "an arrow head" and smaller values gives a round cap. Larger values of
     *        precision results in faster rendering of the circle.
     *
     * @note The circle is not invalidated.
     *
     * @param precision The new cap precision.
     */
    void setCapPrecision(int precision);

    /**
     * @fn virtual bool Circle::drawCanvasWidget(const Rect& invalidatedArea) const;
     *
     * @brief Draws the Circle.
     *
     *        Draws the Circle. This class supports partial drawing, so only the area described
     *        by the rectangle will be drawn.
     *
     * @param invalidatedArea The rectangle to draw, with coordinates relative to this drawable.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool drawCanvasWidget(const Rect& invalidatedArea) const;

    /**
     * @fn virtual Rect Circle::getMinimalRect() const;
     *
     * @brief Gets minimal rectangle for the current shape of the circle.
     *
     *        Gets minimal rectangle for the current shape of the circle.
     *
     * @return The minimal rectangle.
     */
    virtual Rect getMinimalRect() const;

    /**
     * @fn Rect Circle::getMinimalRect(int16_t arcStart, int16_t arcEnd) const;
     *
     * @brief Gets minimal rectangle containing a given circle arc.
     *
     *        Gets minimal rectangle containing a given circle arc.
     *
     * @param arcStart The arc start.
     * @param arcEnd   The arc end.
     *
     * @return The minimal rectangle.
     */
    Rect getMinimalRect(int16_t arcStart, int16_t arcEnd) const;

private:
    CWRUtil::Q5 circleCenterX, circleCenterY, circleRadius;
    int16_t circleArcAngleStart, circleArcAngleEnd;
    CWRUtil::Q5 circleLineWidth;
    int circleArcIncrement;
    int circleCapArcIncrement;

    CWRUtil::Q10 distanceSquared(CWRUtil::Q5 x1, CWRUtil::Q5 y1, CWRUtil::Q5 x2, CWRUtil::Q5 y2) const;
    void moveToAR2(Canvas& canvas, int angle, CWRUtil::Q5 r2) const;
    void lineToAR2(Canvas& canvas, int angle, CWRUtil::Q5 r2) const;
    void lineToXYAR2(Canvas& canvas, const CWRUtil::Q5& x, const CWRUtil::Q5& y, int angle, CWRUtil::Q5 r2) const;
    void updateMinMax(int a, CWRUtil::Q5 r2, CWRUtil::Q5& xMin, CWRUtil::Q5& xMax, CWRUtil::Q5& yMin, CWRUtil::Q5& yMax) const;
    void updateMinMax(const CWRUtil::Q5& xNew, const CWRUtil::Q5 yNew, CWRUtil::Q5& xMin, CWRUtil::Q5& xMax, CWRUtil::Q5& yMin, CWRUtil::Q5& yMax) const;
    void calculateMinimalRect(int16_t arcStart, int16_t arcEnd, CWRUtil::Q5& xMin, CWRUtil::Q5& xMax, CWRUtil::Q5& yMin, CWRUtil::Q5& yMax) const;
};

} // namespace touchgfx

#endif // CIRCLE_HPP
