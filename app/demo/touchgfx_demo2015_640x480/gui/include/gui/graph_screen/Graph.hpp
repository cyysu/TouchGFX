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
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <gui/graph_screen/GraphLine.hpp>
#include <gui/graph_screen/GraphBelow.hpp>
#include <gui/graph_screen/GraphDots.hpp>
#include <gui/graph_screen/PainterVerticalAlpha.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#endif
#include <BitmapDatabase.hpp>

#include <touchgfx/widgets/Box.hpp>

using namespace touchgfx;

/**
 * @class Graph Graph.hpp gui/graph_screen/Graph.hpp
 *
 * @brief A graph with line, area below and dots.
 *
 *        A graph with line, area below and dots. To save space, the 4 graph components are
 *        linked to share the same memory for graph points.
 *
 * @sa Container
 */
class Graph : public Container
{
public:
    /**
     * @fn Graph::Graph();
     *
     * @brief Default constructor.
     */
    Graph();

    /**
     * @fn virtual Graph::~Graph()
     *
     * @brief Destructor.
     */
    virtual ~Graph();

    /**
     * @fn void Graph::setup(int newWidth, int newHeight, colortype lineColor, colortype backgroundColor);
     *
     * @brief Set characteristics of the graph.
     *
     *        Set characteristics of the graph.
     *
     * @param newWidth        Width of the new.
     * @param newHeight       Height of the new.
     * @param lineColor       The line color.
     * @param backgroundColor The background color.
     */
    void setup(int newWidth, int newHeight, colortype lineColor, colortype backgroundColor);

    /**
     * @fn bool Graph::addValue(int x, int y)
     *
     * @brief Adds a point to the graph.
     *
     *        Adds a point to the graph.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     *
     * @return true if it succeeds, false if it fails.
     */
    bool addValue(int x, int y)
    {
        return graphLine.addValue(x, y);
    }

    /**
     * @fn bool Graph::deleteValue(int x)
     *
     * @brief Deletes the value for the given x.
     *
     * @param x The x coordinate.
     *
     * @return true if it succeeds, false if it fails.
     */
    bool deleteValue(int x)
    {
        return graphLine.deleteValue(x);
    }

    /**
     * @fn void Graph::clear()
     *
     * @brief Clears the graph.
     *
     *        Clears the graph.
     */
    void clear()
    {
        graphLine.clearGraph();
    }

    /**
     * @fn void Graph::setRange(int left, int right, int top, int bottom);
     *
     * @brief Sets the range for the graph.
     *
     Sets the range for the graph.
     *
     * @param left   The left.
     * @param right  The right.
     * @param top    The top.
     * @param bottom The bottom.
     */
    void setRange(int left, int right, int top, int bottom) ;

    /**
     * @fn void Graph::setLineVisible(bool lineVisible);
     *
     * @brief Sets line visible.
     *
     *        Sets line visible.
     *
     * @param lineVisible true to show, false to hide.
     */
    void setLineVisible(bool lineVisible);

    /**
     * @fn void Graph::setDotsVisible(bool dotsVisible);
     *
     * @brief Sets dots visible.
     *
     *        Sets dots visible.
     *
     * @param dotsVisible true to show, false to hide.
     */
    void setDotsVisible(bool dotsVisible);

    /**
     * @fn void Graph::setDotsBackgroundVisible(bool dotsBackgroundVisible);
     *
     * @brief Sets dots background visible.
     *
     *        Sets dots background visible.
     *
     * @param dotsBackgroundVisible true to show, false to hide.
     */
    void setDotsBackgroundVisible(bool dotsBackgroundVisible);

    /**
     * @fn void Graph::setAreaVisible(bool areaVisible);
     *
     * @brief Sets area visible.
     *
     *        Sets area visible.
     *
     * @param areaVisible true to show, false to hide.
     */
    void setAreaVisible(bool areaVisible);

    /**
     * @fn void Graph::setDotShape(int startAngle, int angleStep, int lineWidth);
     *
     * @brief Sets dot shape.
     *
     *        Sets dot shape.
     *
     * @param startAngle The start angle.
     * @param angleStep  The angle step.
     * @param lineWidth  Width of the line.
     */
    void setDotShape(int startAngle, int angleStep, int lineWidth);

    /**
     * @fn void Graph::setDotBackgroundShape(int startAngle, int angleStep, int lineWidth);
     *
     * @brief Sets dot background shape.
     *
     *        Sets dot background shape.
     *
     * @param startAngle The start angle.
     * @param angleStep  The angle step.
     * @param lineWidth  Width of the line.
     */
    void setDotBackgroundShape(int startAngle, int angleStep, int lineWidth);

    /**
     * @fn void Graph::setAlpha(uint8_t alpha);
     *
     * @brief Sets the alpha.
     *
     *        Sets the alpha.
     *
     * @param alpha The alpha.
     */
    void setAlpha(uint8_t alpha);

    /**
     * @fn uint8_t Graph::getAlpha();
     *
     * @brief Gets the alpha.
     *
     *        Gets the alpha.
     *
     * @return The alpha.
     */
    uint8_t getAlpha();

protected:
    static const int NUMBER_OF_POINTS = 50; ///< Max number of points in the graph

    GraphLine graphLine;           ///< The line of the graph
    GraphBelow graphArea;          ///< The area below the graph
    GraphDots graphDots;           ///< The dots of the graph
    GraphDots graphDotsBackground; ///< The background of the dots of the graph

    GraphLine::GraphPoint graphBuffer[NUMBER_OF_POINTS]; ///< Memory for the graph points

#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 graphLinePainter;           ///< Painter for the line
    PainterRGB565 graphDotsPainter;           ///< Painter for the dots (usually the same as graphLinePainter)
    PainterRGB565 graphDotsBackgroundPainter; ///< Painter for the background of the dots
#elif USE_BPP==24
    PainterRGB888 graphLinePainter;           ///< Painter for the line
    PainterRGB888 graphDotsPainter;           ///< Painter for the dots (usually the same as graphLinePainter)
    PainterRGB888 graphDotsBackgroundPainter; ///< Painter for the background of the dots
#endif
    PainterVerticalAlpha graphAreaPainter;    ///< Painter for area below graph

    uint8_t myAlpha; ///< Alpha value for entire graph
};


#endif /* GRAPH_HPP */
