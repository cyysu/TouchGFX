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
#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <platform/core/MCUInstrumentation.hpp>
#include <math.h>

#ifdef SIMULATOR
#include <time.h>
#include <stdlib.h>
#endif

void MainView::setupScreen()
{
#ifdef SIMULATOR
    srand((uint32_t)time(0));
#endif

    backgroundLeft.setPosition(0, 0, HAL::DISPLAY_WIDTH / 2, HAL::DISPLAY_HEIGHT);
    backgroundLeft.setColor(Color::getColorFrom24BitRGB(0, 0, 0));
    backgroundRight.setPosition(HAL::DISPLAY_WIDTH / 2, 0, HAL::DISPLAY_WIDTH / 2, HAL::DISPLAY_HEIGHT);
    backgroundRight.setColor(Color::getColorFrom24BitRGB(255, 255, 255));

    //setup pixel data widget, use the animation storage as buffer for the pixel data
    size = MIN(HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT) / 2;
    pixelDataWidget.setPosition(HAL::DISPLAY_WIDTH / 2 - size / 2, HAL::DISPLAY_HEIGHT / 2 - size / 2, size, size);
    pixelDataWidget.setPixelData((uint8_t*)HAL::getInstance()->getAnimationStorage());
    pixelDataWidget.setBitmapFormat(Bitmap::ARGB8888);

    setupRings();

    add(backgroundLeft);
    add(backgroundRight);
    add(pixelDataWidget);
}

void MainView::setupRings()
{
    //draw a couple of random colorful rings in the pixel buffer
    int red = (int)random(0, 1000);
    int green = (int)random(0, 1000);
    int blue = (int)random(0, 1000);

    int rings = (int)random(0, 10) + 4;

    uint8_t* pixelBuffer = (uint8_t*)HAL::getInstance()->getAnimationStorage();
    uint32_t offset = 0;

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++, offset += 4)
        {
            int dx = x - size / 2;
            int dy = y - size / 2;

            float dist = sqrtf((float)dx * dx + dy * dy);

            uint8_t alpha = 0;
            if (dist < size / 2)
            {
                alpha = (uint8_t)(cosf(dist / (size / 2) * rings * 2 * 3.14159f + 3.14159f) * 127 + 128);
            }

            // Due to endianness, ARGB8888 bytes are written backwards
            pixelBuffer[offset + 0] = (uint8_t)(sinf(dist * 2 * (rings + 10) / size + blue) * 127 + 128);
            pixelBuffer[offset + 1] = (uint8_t)(sinf(dist * 2 * (rings + 10) / size + green) * 127 + 128);
            pixelBuffer[offset + 2] = (uint8_t)(sinf(dist * 2 * (rings + 10) / size + red) * 127 + 128);
            pixelBuffer[offset + 3] = alpha;
        }
    }
}

void MainView::tearDownScreen()
{
}

float MainView::random(float low, float high)
{
    float r;
#ifdef SIMULATOR
    r = (float)rand() / RAND_MAX;
#else
    r = ((HAL::getInstance()->getCPUCycles() * 64397 + 24359) & 0xffff) / (0xffff + 0.0f);
#endif
    return low + (high - low) * r;
}
