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
#include <gui/home_screen/HomePresenter.hpp>
#include <gui/home_screen/HomeView.hpp>
#include <gui/model/Model.hpp>
#include <gui/common/FrontendApplication.hpp>

HomePresenter::HomePresenter(HomeView& v)
    : BasePresenter(v), view(v),
      lastUpdatedTime(System::DateTime::beginning())
{
}

void HomePresenter::activate()
{
    BasePresenter::activate();
    model->setInactivationNeeded(false);

    view.clockTile.setTime(lastUpdatedTime = model->getCurrentDateTime());

    view.setTopTilesValue(model->getRoomAirConTemp(Room::LIVINGROOM), model->getRoomLighting(Room::LIVINGROOM), model->getBlindsPercentage(Room::LIVINGROOM));
    washingMachineChanged();
    musicPlayerChanged();
}

void HomePresenter::deactivate()
{
    BasePresenter::deactivate();
    model->setInactivationNeeded(true);
}

void HomePresenter::timeChanged()
{
    System::DateTime time = model->getCurrentDateTime();
    if (time.getMinute() != lastUpdatedTime.getMinute())
    {
        lastUpdatedTime = time;
        view.clockTile.setTime(lastUpdatedTime);
    }
}

void HomePresenter::washingMachineChanged()
{
    view.washingMachineTile.update(model->getWashingMachine().getCurrentProgram(), model->getWashingMachine().getRemainingTime());
}

void HomePresenter::musicPlayerChanged()
{
    view.musicPlayerTile.update(model->getMusicPlayer());
}

void HomePresenter::musicPlayerCoverClicked()
{
    static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoEntertainmentScreen();
}

void HomePresenter::musicPlayerPlayPauseClicked()
{
    model->getMusicPlayer().isPlaying() ? model->getMusicPlayer().pause() : model->getMusicPlayer().play();
}
