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
#include <platform/hal/simulator/sdl/HALSDL.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <common/TouchGFXInit.hpp>
#include <platform/driver/touch/SDLTouchController.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <platform/driver/lcd/LCD16bpp.hpp>
#elif USE_BPP==24
#include <platform/driver/lcd/LCD24bpp.hpp>
#elif USE_BPP==1
#include <platform/driver/lcd/LCD1bpp.hpp>
#endif

#include <stdlib.h>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <common/TouchGFXInit.hpp>

#define CANVAS_BUFFER_SIZE (3600)

int main(int argc, char** argv)
{
    NoDMA dma; //For windows/linux, DMA transfers are simulated
#if !defined(USE_BPP) || USE_BPP==16
    LCD16bpp lcd;
#elif USE_BPP==24
    LCD24bpp lcd;
#elif USE_BPP==1
    LCD1bpp lcd;
#endif
    SDLTouchController tc;

    // Create hardware layer. Use a display size of 480x272.
    HAL& hal = touchgfx_generic_init<HALSDL>(dma, lcd, tc, 480, 272, 0, 0);

    // Initialize SDL
    if (!dynamic_cast<HALSDL&>(hal).sdl_init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
    CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    // Print out size information
    printf("*** Memory usage: ***\r\n");
    printf("Largest view      %lu\r\n", (long unsigned int) sizeof(FrontendHeap::MaxViewType));
    printf("Largest presenter %lu\r\n", (long unsigned int) sizeof(FrontendHeap::MaxPresenterType));
    printf("Datamodel         %lu\r\n", (long unsigned int) sizeof(Model));
    printf("Total:            %lu\r\n", (long unsigned int) sizeof(FrontendHeap));
    printf("*** Screens: ***\r\n");
    printf("Animated graphics      %lu\r\n", (long unsigned int) sizeof(AnimatedGraphicsView));
    printf("Chrome-art             %lu\r\n", (long unsigned int) sizeof(ChromArtView));
    printf("Clock                  %lu\r\n", (long unsigned int) sizeof(ClockView));
    printf("Data Visualization     %lu\r\n", (long unsigned int) sizeof(DataVisualizationView));
    printf("Flow Presentation      %lu\r\n", (long unsigned int) sizeof(FlowPresentationView));
    printf("Home Automation        %lu\r\n", (long unsigned int) sizeof(HomeAutomationView));
    printf("List Navigation        %lu\r\n", (long unsigned int) sizeof(ListNavigationView));
    printf("Live Data Display      %lu\r\n", (long unsigned int) sizeof(LiveDataDisplayView));
    printf("Main Screen            %lu\r\n", (long unsigned int) sizeof(MainView));
    printf("NXP and TouchGFX       %lu\r\n", (long unsigned int) sizeof(NXPAndTouchGFXView));

    fflush(0);

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return EXIT_SUCCESS;
}
