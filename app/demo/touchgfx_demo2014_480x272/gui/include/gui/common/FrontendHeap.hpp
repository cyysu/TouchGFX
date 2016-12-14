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
#ifndef FRONTENDHEAP_HPP
#define FRONTENDHEAP_HPP

#include <common/Meta.hpp>
#include <common/Partition.hpp>
#include <mvp/MVPHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXView.hpp>
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXPresenter.hpp>
#include <gui/flow_presentation_screen/FlowPresentationView.hpp>
#include <gui/flow_presentation_screen/FlowPresentationPresenter.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsView.hpp>
#include <gui/animated_graphics_screen/AnimatedGraphicsPresenter.hpp>
#include <gui/home_automation_screen/HomeAutomationView.hpp>
#include <gui/home_automation_screen/HomeAutomationPresenter.hpp>
#include <gui/list_navigation_screen/ListNavigationView.hpp>
#include <gui/list_navigation_screen/ListNavigationPresenter.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayView.hpp>
#include <gui/live_data_display_screen/LiveDataDisplayPresenter.hpp>
#include <gui/data_visualization_screen/DataVisualizationView.hpp>
#include <gui/data_visualization_screen/DataVisualizationPresenter.hpp>
#include <gui/chrom_art_screen/ChromArtView.hpp>
#include <gui/chrom_art_screen/ChromArtPresenter.hpp>
#include <gui/clock_screen/ClockView.hpp>
#include <gui/clock_screen/ClockPresenter.hpp>

/**
 * This class provides the memory that shall be used for memory allocations
 * in the frontend. A single instance of the FrontendHeap is allocated once (in heap
 * memory), and all other frontend objects such as views, presenters and data model are
 * allocated within the scope of this FrontendHeap. As such, the RAM usage of the entire
 * user interface is sizeof(FrontendHeap).
 *
 * @note The FrontendHeap reserves memory for the most memory-consuming presenter and
 * view only. The largest of these classes are determined at compile-time using template
 * magic. As such, it is important to add all presenters, views and transitions to the
 * type lists in this class.
 *
 */
class FrontendHeap : public MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< MainView,
            meta::TypeList< NXPAndTouchGFXView,
            meta::TypeList< FlowPresentationView,
            meta::TypeList< AnimatedGraphicsView,
            meta::TypeList< HomeAutomationView,
            meta::TypeList< ListNavigationView,
            meta::TypeList< LiveDataDisplayView,
            meta::TypeList< DataVisualizationView,
            meta::TypeList< ClockView,
            meta::TypeList< ChromArtView,
            meta::Nil
            > > > > > > > > > > ViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef meta::select_type_maxsize< ViewTypes >::type MaxViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< MainPresenter,
            meta::TypeList< NXPAndTouchGFXPresenter,
            meta::TypeList< FlowPresentationPresenter,
            meta::TypeList< AnimatedGraphicsPresenter,
            meta::TypeList< HomeAutomationPresenter,
            meta::TypeList< ListNavigationPresenter,
            meta::TypeList< LiveDataDisplayPresenter,
            meta::TypeList< DataVisualizationPresenter,
            meta::TypeList< ClockPresenter,
            meta::TypeList< ChromArtPresenter,
            meta::Nil
            > > > > > > > > > > PresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef meta::select_type_maxsize< PresenterTypes >::type MaxPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< NoTransition,
            meta::TypeList< SlideTransition<EAST>,
            meta::TypeList< SlideTransition<WEST>,
            meta::Nil
            > > > TransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef meta::select_type_maxsize< TransitionTypes >::type MaxTransitionType;

    static FrontendHeap& getInstance()
    {
        static FrontendHeap instance;
        return instance;
    }

    Partition< PresenterTypes, 1 > presenters;
    Partition< ViewTypes, 1 > views;
    Partition< TransitionTypes, 1 > transitions;
    FrontendApplication app;
    Model model;
private:
    FrontendHeap()
        : MVPHeap(presenters, views, transitions, app),
          presenters(),
          views(),
          transitions(),
          app(model, *this)
    {
        // Goto start screen
        app.gotoMainScreenNoTransition();
    }
};

#endif
