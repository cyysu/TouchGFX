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
#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <gui/graph_screen/Graph.hpp>
#include <gui/graph_screen/PieChart.hpp>
#include <gui/graph_screen/LegendEntry.hpp>
#include <gui/graph_screen/PainterColoredBitmap.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class GraphView : public DemoView<GraphPresenter>
{
public:
    GraphView();
    virtual ~GraphView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    virtual void screenSaverMinorTick();
    virtual void screenSaverMajorTick();

private:
    static const int NUMBER_OF_GRID_LINES = 4;
    static const int NUMBER_OF_PIE_CHART_SECTIONS = 6;

    enum State
    {
        GRAPH,
        PIE_CHART
    };

    State currentState;

    Image backgroundTop;
    Image backgroundBottom;

    Container graphArea;
    Box graphBackground;
    Box graphGridLines[NUMBER_OF_GRID_LINES];
    TextAreaWithOneWildcard graphYValues[NUMBER_OF_GRID_LINES];
    Unicode::UnicodeChar graphYValuesbuf[NUMBER_OF_GRID_LINES][5];

    Graph primaryGraph;
    Graph secondaryGraph;

    Button newButton;

    Button graphOrPieButton;

    ToggleButton primaryGraphLineSetting;
    ToggleButton primaryGraphDotSetting;
    ToggleButton primaryGraphAreaSetting;

    ToggleButton secondaryGraphLineSetting;
    ToggleButton secondaryGraphDotSetting;
    ToggleButton secondaryGraphAreaSetting;

    Button donutOrPieButton;

    MoveAnimator<PieChart> pieChart;
    PainterColoredBitmap pieChartPainter[6];
    MoveAnimator<LegendEntry> legendEntries[NUMBER_OF_PIE_CHART_SECTIONS];

    Callback<GraphView, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);

    Callback<GraphView, const MoveAnimator<LegendEntry>&> legendMoveEnded;
    void legendMoveEndedHandler(const MoveAnimator<LegendEntry>& legend);

    Callback<GraphView, const PieChart&, int> legendSelected;
    void legendSelectedHandler(const PieChart& thePieChart, int item);

    Callback<GraphView, const PieChart&> pieChartAnimationEnded;
    void pieChartAnimationEndedHandler(const PieChart& thePieChart);

    Callback<GraphView, const LegendEntry&> legendPressed;
    void legendPressedHandler(const LegendEntry& legend);

    int tickCount;
    int graphX;
    int graphType;
    int leftX;
    int pointCounter;
    bool pieChartIsFull; ///< false means semi-donut

    enum PieChartAnimationType
    {
        REDRAW_PIECHART, // Fold+new slices
        REDRAW_PIECHART2, // Unfold
        SWITCH_TO_PIECHART,
        SWITCH_TO_GRAPH,
        SWITCH_TO_FULL_CIRCLE,
        SWITCH_TO_SEMI_DONUT
    };
    int pieChartAnimationType;

    void setCurrentState(State newState);
    void clearGraphs();
    void resetPieChart();
    void updateButtonSettings();
    void updateGraphSettings();
    void setAllButtonsTouchable(bool touchable);
};

#endif // GRAPHVIEW_HPP
