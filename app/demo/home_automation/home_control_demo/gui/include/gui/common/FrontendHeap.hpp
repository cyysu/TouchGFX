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
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>
#include <gui/home_screen/HomeView.hpp>
#include <gui/home_screen/HomePresenter.hpp>
#include <gui/blinds_screen/BlindsView.hpp>
#include <gui/blinds_screen/BlindsPresenter.hpp>
#include <gui/air_condition_screen/AirConditionView.hpp>
#include <gui/air_condition_screen/AirConditionPresenter.hpp>
#include <gui/lighting_screen/LightingView.hpp>
#include <gui/lighting_screen/LightingPresenter.hpp>
#include <gui/appliances_screen/AppliancesView.hpp>
#include <gui/appliances_screen/AppliancesPresenter.hpp>
#include <gui/entertainment_screen/EntertainmentView.hpp>
#include <gui/entertainment_screen/EntertainmentPresenter.hpp>
#include <gui/security_screen/SecurityView.hpp>
#include <gui/security_screen/SecurityPresenter.hpp>
#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <gui/common/FadeTransition.hpp>

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
class FrontendHeap : public touchgfx::MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< HomeView,
            touchgfx::meta::TypeList< BlindsView,
            touchgfx::meta::TypeList< AirConditionView,
            touchgfx::meta::TypeList< LightingView,
            touchgfx::meta::TypeList< AppliancesView,
            touchgfx::meta::TypeList< EntertainmentView,
            touchgfx::meta::TypeList< SecurityView,
            touchgfx::meta::TypeList< SettingsView,
            touchgfx::meta::Nil
            > > > > > > > > ViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< ViewTypes >::type MaxViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< HomePresenter,
            touchgfx::meta::TypeList< BlindsPresenter,
            touchgfx::meta::TypeList< AirConditionPresenter,
            touchgfx::meta::TypeList< LightingPresenter,
            touchgfx::meta::TypeList< AppliancesPresenter,
            touchgfx::meta::TypeList< EntertainmentPresenter,
            touchgfx::meta::TypeList< SecurityPresenter,
            touchgfx::meta::TypeList< SettingsPresenter,
            touchgfx::meta::Nil
            > > > > > > > > PresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< PresenterTypes >::type MaxPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< touchgfx::NoTransition,
            touchgfx::meta::TypeList< FadeTransition,
            touchgfx::meta::Nil
            > > TransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< TransitionTypes >::type MaxTransitionType;

    static FrontendHeap& getInstance()
    {
        static FrontendHeap instance;
        return instance;
    }

    touchgfx::Partition< PresenterTypes, 1 > presenters;
    touchgfx::Partition< ViewTypes, 1 > views;
    touchgfx::Partition< TransitionTypes, 1 > transitions;
    FrontendApplication app;
    Model model;
private:
    FrontendHeap()
        : touchgfx::MVPHeap(presenters, views, transitions, app),
          presenters(),
          views(),
          transitions(),
          app(model, *this)
    {
        // Goto start screen
        app.gotoInitialHomeScreen();
    }

};

#endif
