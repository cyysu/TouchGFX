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
#ifndef DEMO_VIEW_HPP
#define DEMO_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/common/DemoViewInterface.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/McuLoadSlider.hpp>

using namespace touchgfx;

template <class T>
class DemoView : public View<T>, public DemoViewInterface
{
public:
    DemoView() :
        onBackButtonClicked(this, &DemoView::backButtonClickedHandler),
        onMcuLoadClicked(this, &DemoView::mcuLoadClickedHandler)
    {
        backButton.setBitmaps(Bitmap(BITMAP_DEMO_BACK_BUTTON_ID), Bitmap(BITMAP_DEMO_BACK_BUTTON_PRESSED_ID));
        backButton.setXY(0, 0);
        backButton.setAction(onBackButtonClicked);

        mcuLoadArea.setPosition(0, HAL::DISPLAY_HEIGHT - 54, backButton.getWidth(), 54);
        mcuLoadArea.setAction(onMcuLoadClicked);

        mcuLoadSlider.setXY(HAL::DISPLAY_WIDTH - mcuLoadSlider.getWidth(), 5);

        View<T>::add(backButton);
    }

    virtual void afterTransition()
    {
        View<T>::presenter->viewStartupDone();

        // These widget must be on top and are therefore added here
        View<T>::add(mcuLoadArea);
        View<T>::add(mcuLoadSlider);
    }

protected:
    Button backButton;
    TouchArea mcuLoadArea;
    McuLoadSlider mcuLoadSlider;

    Callback<DemoView, const AbstractButton&> onBackButtonClicked;
    Callback<DemoView, const AbstractButton&> onMcuLoadClicked;

    void backButtonClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->backOptionSelected();
    }

    void mcuLoadClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->mcuLoadSelected();
    }

    // DemoViewInterface impl
    virtual void showProcessorLoad(bool visible)
    {
        // Added to view here to ensure it is in front
        //if (!View<T>::container.contains(mcuLoadSlider))
        {
            //   View<T>::add(mcuLoadSlider);
        }
        (visible) ? mcuLoadSlider.show() : mcuLoadSlider.hide();
    }

    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    {
        mcuLoadSlider.setValue(mcuLoadInProcent);
    }
};

#endif
