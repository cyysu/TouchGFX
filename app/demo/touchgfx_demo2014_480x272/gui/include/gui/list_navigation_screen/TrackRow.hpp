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
#ifndef TRACK_ROW_HPP_
#define TRACK_ROW_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/list_navigation_screen/Album.hpp>

using namespace touchgfx;

class TrackRow : public Container
{
public:
    TrackRow();
    virtual ~TrackRow();

    void setRowPressedCallback(GenericCallback< const TrackRow& >& callback)
    {
        rowPressedCallback = &callback;
    }

    void setData(TEXTS name, TEXTS duration, bool lastElementInList);

    void setSelected(bool newSelectedValue);
    bool isSelected();

private:
    Image background;
    TouchArea trackSelectArea;
    TextArea trackName;
    TextArea trackDuration;

    // Small extra line in the bottom of the last list element
    Image lastElementBackground;

    bool selected;

    GenericCallback< const TrackRow& >* rowPressedCallback;

    Callback<TrackRow, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);
};


#endif /* TRACK_ROW_HPP_ */
