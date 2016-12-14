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
#ifndef DATA_VISUALIZATION_VIEW_HPP
#define DATA_VISUALIZATION_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/data_visualization_screen/DataVisualizationPresenter.hpp>
#include <gui/data_visualization_screen/InteractiveGraph.hpp>
#include <gui/data_visualization_screen/BarContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>

class DataVisualizationView : public DemoView<DataVisualizationPresenter>
{
public:
    DataVisualizationView();
    virtual ~DataVisualizationView();
    virtual void setupScreen();
    virtual void tearDownScreen();

private:
    InteractiveGraph interactiveGraph;
    Image tabBack;
    Image sixHoursBackTop;
    Image sixHoursBackBottom;
    BarContainer barContainer;
    Image sevenDaysBack;
    ListLayout bottomContainer;
    ToggleButton sixHoursButton;
    ToggleButton twelveHoursButton;
    ToggleButton sevenDaysButton;

    Callback<DataVisualizationView, const AbstractButton&> onTimeIntervalButtonClicked;

    void onTimeIntervalButtonClickedHandler(const AbstractButton& button)
    {
        if (&button == &sixHoursButton)
        {
            sixHoursButton.forceState(true);
            twelveHoursButton.forceState(false);
            sevenDaysButton.forceState(false);

            sixHoursBackTop.setVisible(true);
            sixHoursBackTop.invalidate();
            sixHoursBackBottom.setVisible(true);
            sixHoursBackBottom.invalidate();
            barContainer.setVisible(true);
            barContainer.invalidate();
            barContainer.startAnimation();
            interactiveGraph.setVisible(false);
            interactiveGraph.stopGraph();
            sevenDaysBack.setVisible(false);
        }
        else if (&button == &twelveHoursButton)
        {
            sixHoursButton.forceState(false);
            twelveHoursButton.forceState(true);
            sevenDaysButton.forceState(false);

            sixHoursBackTop.setVisible(false);
            sixHoursBackBottom.setVisible(false);
            barContainer.setVisible(false);
            interactiveGraph.setVisible(true);
            interactiveGraph.invalidate();
            interactiveGraph.startGraph();
            sevenDaysBack.setVisible(false);
        }
        else if (&button == &sevenDaysButton)
        {
            sixHoursButton.forceState(false);
            twelveHoursButton.forceState(false);
            sevenDaysButton.forceState(true);

            sixHoursBackTop.setVisible(false);
            sixHoursBackBottom.setVisible(false);
            barContainer.setVisible(false);
            interactiveGraph.setVisible(false);
            interactiveGraph.stopGraph();
            sevenDaysBack.setVisible(true);
            sevenDaysBack.invalidate();
        }

        bottomContainer.invalidate();
    }

};

#endif // DATA_VISUALIZATION_VIEW_HPP
