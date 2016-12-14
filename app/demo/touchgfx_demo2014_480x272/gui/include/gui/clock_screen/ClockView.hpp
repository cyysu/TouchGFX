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
#ifndef CLOCK_VIEW_HPP
#define CLOCK_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/clock_screen/ClockPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#endif

/*
 * ClockView handles the view part of the Clock Screen.
 * It receives the current time from the presenter which is updated by the model
 */

class ClockView : public DemoView<ClockPresenter>
{
public:
    ClockView();
    virtual ~ClockView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void afterTransition();

    /**
     * Updates the hour, minutes and second counters
     * hours: 0-23
     * minutes: 0-59
     * seconds: 0-59
     */
    void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds);

    // Updates the clock view
    void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter);

    class SecondClockHand : public Shape<4>
    {
    public:
        SecondClockHand()
        {
            ShapePoint<int> points[4] = { { -1, 0}, { -1, -74}, {1, -74}, {1, 0} };
            setShape(points);
        }
    };

    class MinuteClockHand : public Shape<5>
    {
    public:
        MinuteClockHand()
        {
            ShapePoint<float> points[5] = { { -3.5f, 0}, { -.7f, -67}, {0, -70}, {.7f, -67}, {3.5f, 0} };
            setShape(points);
        }
    };

    class HourClockHand : public Shape<5>
    {
    public:
        HourClockHand()
        {
            ShapePoint<float> points[5] = { { -4.5f, 2}, { -1, -43}, {0, -45}, {1, -43}, {4.5f, 2} };
            setShape(points);
        }
    };

private:

    uint8_t currentSecondCounter;
    uint8_t currentMinuteCounter;
    uint8_t currentHourCounter;

    bool transitionDone;
    bool firstPresenterCall;

    Image clockBackground;
    Image centerDot;

    SecondClockHand secondHand;
    MinuteClockHand minuteHand;
    HourClockHand hourHand;

#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 handColorRed;
    PainterRGB565 handColorWhite;
#elif USE_BPP==24
    PainterRGB888 handColorRed;
    PainterRGB888 handColorWhite;
#endif
};

#endif // CLOCK_VIEW_HPP
