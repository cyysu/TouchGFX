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
#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#endif

/**
 * The View for the main screen. In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically.
 */
class MainView : public View<MainPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    MainView()
    {
    }

    virtual ~MainView()
    {
    }

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen()
    {
    }

    virtual void handleTickEvent();

private:

    // A custom shape for the rotating clock hand.
    class CustomShape : public Shape<5>
    {
    public:
        CustomShape()
        {
            ShapePoint<float> points[5] = { { -3.5f, 0}, { -.7f, -47}, {0, -50}, {.7f, -47}, {3.5f, 0} };
            setShape(points);
        }
    };

    int tickCounter;
    Box background;

    // Canvas Widgets
    Line line;
    Circle circle;
    CustomShape clockHand;
    Circle arc;

    // Painters for the different Canvas Widgets
#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 myColorPainter;
    PainterRGB565Bitmap myBitmapPainter;
    PainterRGB565Bitmap myBitmapPainter2;
#elif USE_BPP==24
    PainterRGB888 myColorPainter;
    PainterRGB888Bitmap myBitmapPainter;
    PainterRGB888Bitmap myBitmapPainter2;
#endif

    // Should the arc move forward or backwards
    bool arcAdvance;
};

#endif // MAIN_VIEW_HPP
