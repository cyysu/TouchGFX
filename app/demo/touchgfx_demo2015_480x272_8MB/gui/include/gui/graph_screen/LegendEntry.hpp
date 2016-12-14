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
#ifndef LEGEND_ENTRY_HPP
#define LEGEND_ENTRY_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class LegendEntry : public Container
{
public:
    LegendEntry();
    virtual ~LegendEntry();

    void setBitmaps(BitmapId squareNotSelectedBmp, BitmapId squareSelectedBmp);
    void setText(TEXTS textId);
    void setValueText(int value);
    void setSelected(bool selected);

    void setSelectionCallback(GenericCallback<const LegendEntry&>& callback)
    {
        selectionAction = &callback;
    }

private:
    BitmapId squareNotSelected;
    BitmapId squareSelected;

    Image square;

    TextArea text;
    TextAreaWithOneWildcard valueText;
    Unicode::UnicodeChar valueTextBuffer[6];

    Button selectButton;

    Callback<LegendEntry, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);

    GenericCallback<const LegendEntry&>* selectionAction;
};

#endif
