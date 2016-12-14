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
#include <touchgfx/hal/HAL.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/main_screen/MainView.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v),
      bmpId(BITMAP_INVALID)
{
}

void MainPresenter::activate()
{
}

void MainPresenter::deactivate()
{
}

void MainPresenter::backgroundClicked()
{
    model->pause();
}

void MainPresenter::playPressed()
{
    model->play();
}

void MainPresenter::showError(uint16_t e)
{
    view.showError(e);
}

void MainPresenter::mounted(bool m)
{
    view.sdMounted(m);
}

void MainPresenter::showBitmap(BMPFileLoader::FileHdl f)
{
    //if we have loaded a bitmap already, delete it
    if (bmpId != BITMAP_INVALID)
    {
        Bitmap::dynamicBitmapDelete(bmpId);
    }

    //find the width and height in the file header
    uint16_t width, height;
    BMPFileLoader::getBMP24Dimensions(f, width, height);

    //24 or 16 bit
    //create dynamic bitmap matching file dimensions
    if (HAL::lcd().bitDepth() == 16)
    {
        bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);
    }
    else
    {
        bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB888);
    }
    if (bmpId != BITMAP_INVALID)
    {
        //read the bitmap file into the dynamic bitmap
        BMPFileLoader::readBMP24File(Bitmap(bmpId), (BMPFileLoader::FileHdl)f);
        view.showBitmap(bmpId);
    }
}
