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
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model()
    : modelListener(0),
      sdstate(UNITIALIZED),
      tickCnt(0),
      playing(false)
{
}

void Model::tick()
{
#ifndef SIMULATOR
    uint32_t r = 1;
    switch (sdstate)
    {
    case UNITIALIZED:
        //wait until SD card is inserted
        if (BSP_SD_IsDetected())
        {
            r = FATFS_LinkDriver(&SD_Driver, sdpath);
            if (r == 0)
            {
                sdstate = LINKED;
            }
            else
            {
                modelListener->showError(0x100 + r);
            }
        }
        break;
    case LINKED:
        //mount the SDCard as drive
        r = f_mount(&SDFatFs, (TCHAR const*)sdpath, 1);
        if (r == 0)
        {
            sdstate = MOUNTED;
        }
        else
        {
            modelListener->showError(0x200 + r);
        }
        break;
    case MOUNTED:
        //Find the first .bmp file
        r = f_findfirst(&d, &info, sdpath, "*.bmp");
        if (r == 0)
        {
            r = f_open(&f, info.fname, FA_READ);
            if (r == 0)
            {
                //remove headline text and show bitmap
                modelListener->mounted(true);
                modelListener->showBitmap(&f);
                sdstate = FILE_OPENED;
            }
            else
            {
                modelListener->showError(0x300 + r);
                sdstate = SDERROR;
            }
        }
        else
        {
            modelListener->showError(0x400 + r);
            sdstate = SDERROR;
        }
        break;
    case REMOVED:
        if (BSP_SD_IsDetected())
        {
            //reinitialize the SD-card interface
            BSP_SD_Init();
            sdstate = LINKED;
        }
        break;
    case FILE_OPENED:
        //as long as SD card is inserted, show the images for a few seconds each.
        if (BSP_SD_IsDetected())
        {
            if (playing)
            {
                if ((++tickCnt & 0x7f) == 0)
                {
                    f_close(&f);
                    r = f_findnext(&d, &info);
                    if (!info.fname[0])
                    {
                        f_closedir(&d);
                        r = f_findfirst(&d, &info, sdpath, "*.bmp");
                    }
                    r = f_open(&f, info.fname, FA_READ);
                    if (r == 0)
                    {
                        modelListener->showBitmap(&f);
                    }
                    else
                    {
                        modelListener->showError(0x500 + r);
                        sdstate = SDERROR;
                    }

                }
            }
        }
        else
        {
            //Show headline text and deinitialize SD card interface
            modelListener->mounted(false);
            playing = false;
            BSP_SD_DeInit();
            sdstate = REMOVED;
        }
        break;
    }
#else
    // For simulator, do nothing
    if (sdstate == UNITIALIZED)
    {
        modelListener->mounted(false);
    }
#endif
}

void Model::play()
{
    playing = true;
    tickCnt = 0x7f;
}

void Model::pause()
{
    playing = false;
}
