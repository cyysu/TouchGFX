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
#ifndef BLINDS_SELECTOR_HPP
#define BLINDS_SELECTOR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/RoomSelector.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

using namespace touchgfx;

class BlindsSelector : public Container
{
public:
    static const int NUMBER_OF_BLINDS = 11;

    BlindsSelector();
    virtual ~BlindsSelector();

    virtual void handleClickEvent(const ClickEvent& evt);

    void setRoomText(Room room, int value);
    void deselectAllBlinds();
    void selectDot(int16_t blindId, bool select);
    bool isSelected(int16_t blindId);

    void setBlindsSelectedCallback(GenericCallback< int16_t, uint16_t >& callback)
    {
        blindsSelectedCallback = &callback;
    }
    uint16_t getNumberOfSelectedBlinds();

    Room getRoomFromBlindId(int16_t blindId);
    bool isSelected(Room room);
private:
    Image background;

    Image selectedDots[NUMBER_OF_BLINDS];
    bool selectedBlinds[NUMBER_OF_BLINDS];
    Room blindsToRoom[NUMBER_OF_BLINDS];

    FadeAnimator<TextAreaWithOneWildcard> roomText[Room::NUMBER_OF_ROOMS];
    Unicode::UnicodeChar roomTextBuffer[Room::NUMBER_OF_ROOMS][5];

    GenericCallback< int16_t, uint16_t >* blindsSelectedCallback;
    int16_t xValueWhenPressed;

    void updateDots();
};


#endif
