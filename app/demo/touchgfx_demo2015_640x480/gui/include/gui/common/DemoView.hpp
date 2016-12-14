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
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

template <class T>
class DemoView : public View<T>, public DemoViewInterface
{
public:
    DemoView() :
        onGotoMenuButtonClicked(this, &DemoView::gotoMenuClickedHandler)
    {
        gotoMenuButton.setAction(onGotoMenuButtonClicked);

        mcuLoadTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_TEXT));
        mcuLoadTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

        Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", 0);
        mcuLoadValueTxt.setWildcard(mcuLoadTxtValueBuffer);
        mcuLoadValueTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_VALUE));
        mcuLoadValueTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    }

    virtual void afterTransition()
    {
        if (HAL::DISPLAY_WIDTH > getActiveDisplayWidth())
        {
            marginBox.setPosition(getActiveDisplayWidth(), 0, HAL::DISPLAY_WIDTH - getActiveDisplayWidth(), HAL::DISPLAY_HEIGHT);
            marginBox.setColor(0);
            DemoView::add(marginBox);
        }
    }

protected:
    Button gotoMenuButton;
    Box marginBox; // If the demo is executed on a different resolution than 640x480 cover the extra width by a black box

    TextArea mcuLoadTxt;
    TextAreaWithOneWildcard mcuLoadValueTxt;
    Unicode::UnicodeChar mcuLoadTxtValueBuffer[5];

    Callback<DemoView, const AbstractButton&> onGotoMenuButtonClicked;

    void gotoMenuClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->backOptionSelected();
    }

    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    {
        Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", mcuLoadInProcent);
        mcuLoadValueTxt.invalidate();
    }

    int getActiveDisplayWidth()
    {
        return 640;
    }

    int getActiveDisplayHeight()
    {
        return 480;
    }
};

#endif
