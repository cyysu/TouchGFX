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
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/model/Model.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{
}

void MainPresenter::activate()
{
    // Set initial value on main screen
    view.setCount(model->getCount());
    view.setLimitEffects(true, false);
}

void MainPresenter::deactivate()
{

}

void MainPresenter::upPressed()
{
    /* React on input from GUI/user. State is delegated to the model, and
       presentation logic should be is kept in the presenter. */

    uint8_t count = model->getCount();

    if (count < 42)
    {
        count++;
        view.setCount(count);

        if (42 == count)
        {
            view.setLimitEffects(false, true);
        }
        else if (1 == count)
        {
            view.setLimitEffects(true, true);
        }

        model->setCount(count);
    }
}

void MainPresenter::downPressed()
{
    /* React on input from GUI/user. State is delegated to the model, and
       presentation logic should be is kept in the presenter. */

    uint8_t count = model->getCount();

    if (count > 0)
    {
        count--;
        view.setCount(count);

        if (0 == count)
        {
            view.setLimitEffects(true, false);
        }
        else if (41 == count)
        {
            view.setLimitEffects(true, true);
        }

        model->setCount(count);
    }
}
