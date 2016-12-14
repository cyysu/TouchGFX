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
#include <gui/blinds_screen/BlindsPresenter.hpp>
#include <gui/blinds_screen/BlindsView.hpp>
#include <gui/model/Room.hpp>

BlindsPresenter::BlindsPresenter(BlindsView& v)
    : BasePresenter(v), view(v)
{
}

void BlindsPresenter::activate()
{
    BasePresenter::activate();

    anyBlindsSelected = false;

    for (int i = 0; i < Room::NUMBER_OF_ROOMS; i++)
    {
        view.setBlindPercentage((Room) i, model->getBlindsPercentage((Room) i));
    }
}

void BlindsPresenter::deactivate()
{
    BasePresenter::deactivate();
}

void BlindsPresenter::blindsSelected(int16_t selectedBlind, uint16_t numberOfSelectedBlinds)
{
    if (numberOfSelectedBlinds == 0)
    {
        anyBlindsSelected = false;
        view.setJogwheelInactive(true);
    }
    else
    {
        if (!anyBlindsSelected)
        {
            anyBlindsSelected = true;
            view.setJogwheelActive(model->getBlindsPercentage(view.getRoomFromBlindId(selectedBlind)));
        }
    }
}

void BlindsPresenter::roomBlindsPercentageUpdated(Room room, int16_t value)
{
    model->setBlindsPercentage(room, value);
    view.setBlindPercentage(room, model->getBlindsPercentage(room));
}
