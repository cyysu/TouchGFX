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
 * Copyright (C) 2014-2016 Draupner Graphics A/S <http://www.touchgfx.com>.
 * All rights reserved.
 *
 * TouchGFX is protected by international copyright laws and the knowledge of
 * this source code may not be used to write a similar product. This file may
 * only be used in accordance with a license and should not be re-
 * distributed in any way without the prior permission of Draupner Graphics.
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

#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <platform/hal/ST/mcu/stm32f7xx/STM32F7DMA.hpp>
#include <touchgfx/LCD/LCD.hpp>
#include <cassert>
#include "stm32f7xx_hal.h"


DMA2D_HandleTypeDef     Dma2dHandle;

STM32F7DMA::STM32F7DMA()
    : DMA_Interface(dma_queue), dma_queue(queue_storage, sizeof(queue_storage) / sizeof(queue_storage[0])),
      pBlitOp(0), numLines(0), deadTime(0), use32Bit(0)
{}

STM32F7DMA::~STM32F7DMA()
{
}

void STM32F7DMA::initialize()
{
    __HAL_DMA2D_ENABLE_IT(&Dma2dHandle, DMA2D_IT_TC);
}

volatile bool disableChromArt = false;

BlitOperations STM32F7DMA::getBlitCaps()
{
    if (disableChromArt)
    {
        return static_cast<BlitOperations>(0);
    }
    else
    {
        return static_cast<BlitOperations>(BLIT_OP_FILL | BLIT_OP_COPY | BLIT_OP_COPY_WITH_ALPHA | BLIT_OP_COPY_ARGB8888 | BLIT_OP_COPY_ARGB8888_WITH_ALPHA | BLIT_OP_COPY_A4 | BLIT_OP_COPY_A8);
    }
}

void STM32F7DMA::setupDataCopy(const BlitOp& blitOp)
{
    uint32_t dma2dTransferMode = DMA2D_M2M_BLEND;  //DMA2D transfer mode - Default blending.
    uint32_t dma2dColorMode = 0;                   //DMA2D foreground color mode.

    bool blendingImage   = ((blitOp.operation == BLIT_OP_COPY_ARGB8888) || (blitOp.operation == BLIT_OP_COPY_ARGB8888_WITH_ALPHA) || (blitOp.operation == BLIT_OP_COPY_WITH_ALPHA));
    bool blendingText    = ((blitOp.operation == BLIT_OP_COPY_A4)       || (blitOp.operation == BLIT_OP_COPY_A8));

    uint8_t bitDepth = HAL::lcd().bitDepth();

    //Determine color mode and transfer mode
    switch (blitOp.operation)
    {
    case BLIT_OP_COPY_A4:
        dma2dColorMode = CM_A4;
        break;
    case BLIT_OP_COPY_A8:
        dma2dColorMode = CM_A8;
        break;
    case BLIT_OP_COPY_WITH_ALPHA:
        dma2dTransferMode = DMA2D_M2M_BLEND;
        dma2dColorMode = (bitDepth == 16) ? CM_RGB565 : CM_RGB888;
        break;
    case BLIT_OP_COPY_ARGB8888:
    case BLIT_OP_COPY_ARGB8888_WITH_ALPHA:
        dma2dColorMode = CM_ARGB8888;
        break;
    default:
        //default is to revert to color mode specified by LCD driver
        dma2dTransferMode = DMA2D_M2M;
        dma2dColorMode = (bitDepth == 16) ? CM_RGB565 : CM_RGB888;
        break;
    }

    numLines = blitOp.nLoops;

    NVIC_DisableIRQ(DMA2D_IRQn);
    HAL_DMA2D_DeInit(&Dma2dHandle);

    Dma2dHandle.Init.Mode = dma2dTransferMode;
    Dma2dHandle.Init.ColorMode = (bitDepth == 16) ? DMA2D_RGB565 : DMA2D_RGB888;
    Dma2dHandle.Init.OutputOffset = blitOp.dstLoopStride - blitOp.nSteps;

    Dma2dHandle.LayerCfg[1].InputColorMode = dma2dColorMode;
    Dma2dHandle.LayerCfg[1].InputOffset = blitOp.srcLoopStride - blitOp.nSteps;
    Dma2dHandle.Instance = DMA2D;
    HAL_DMA2D_Init(&Dma2dHandle);

    if (blendingImage || blendingText)
    {
        //Adjust blending for configured alpha value
        if (blitOp.alpha < 255)
        {
            Dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_COMBINE_ALPHA;
            Dma2dHandle.LayerCfg[1].InputAlpha = blitOp.alpha;
        }
        else
        {
            Dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
        }

        if (blendingText)
        {
            if (bitDepth == 16)
            {
                uint32_t red = (((blitOp.color & 0xF800) >> 11) * 255) / 31;
                uint32_t green = (((blitOp.color & 0x7E0) >> 5) * 255) / 63;
                uint32_t blue = (((blitOp.color & 0x1F)) * 255) / 31;
                uint32_t alpha = blitOp.alpha;
                Dma2dHandle.LayerCfg[1].InputAlpha = (alpha << 24) | (red << 16) | (green << 8) | blue;
            }
            else
            {
                Dma2dHandle.LayerCfg[1].InputAlpha = blitOp.color.getColor32() | (blitOp.alpha << 24);
            }
        }

        //Configure background
        Dma2dHandle.LayerCfg[0].InputOffset = blitOp.dstLoopStride - blitOp.nSteps;
        Dma2dHandle.LayerCfg[0].InputColorMode = (bitDepth == 16) ? CM_RGB565 : CM_RGB888;
        HAL_DMA2D_ConfigLayer(&Dma2dHandle, 0);
    }

    HAL_DMA2D_ConfigLayer(&Dma2dHandle, 1);

    NVIC_EnableIRQ(DMA2D_IRQn);

    //invalidate D-Cache before starting DMA
    SCB_CleanInvalidateDCache();

    if (blendingImage || blendingText)
    {
        HAL_DMA2D_BlendingStart_IT(&Dma2dHandle, (unsigned int)blitOp.pSrc, (unsigned int)blitOp.pDst, (unsigned int)blitOp.pDst, blitOp.nSteps, blitOp.nLoops);
    }
    else
    {
        HAL_DMA2D_Start_IT(&Dma2dHandle, (unsigned int)blitOp.pSrc, (unsigned int)blitOp.pDst, blitOp.nSteps, blitOp.nLoops);
    }
}

void STM32F7DMA::setupDataFill(const BlitOp& blitOp)
{
    uint8_t bitDepth = HAL::lcd().bitDepth();
    uint32_t dma2dTransferMode = DMA2D_R2M;
    uint32_t dma2dColorMode = (bitDepth == 16) ? CM_RGB565 : CM_RGB888;
    numLines = blitOp.nLoops;

    NVIC_DisableIRQ(DMA2D_IRQn);
    HAL_DMA2D_DeInit(&Dma2dHandle);

    Dma2dHandle.Init.Mode = dma2dTransferMode;
    Dma2dHandle.Init.ColorMode = (bitDepth == 16) ? DMA2D_RGB565 : DMA2D_RGB888;
    Dma2dHandle.Init.OutputOffset = blitOp.dstLoopStride - blitOp.nSteps;

    Dma2dHandle.LayerCfg[1].InputColorMode = dma2dColorMode;
    Dma2dHandle.LayerCfg[1].InputOffset = 0; //Unused in register-to-memory transfers.
    Dma2dHandle.Instance = DMA2D;

    uint32_t color = 0;
    if (bitDepth == 16)
    {
        uint32_t red = (((blitOp.color & 0xF800) >> 11) * 255) / 31;
        uint32_t green = (((blitOp.color & 0x7E0) >> 5) * 255) / 63;
        uint32_t blue = (((blitOp.color & 0x1F)) * 255) / 31;
        uint32_t alpha = blitOp.alpha;
        color = (alpha << 24) | (red << 16) | (green << 8) | blue;
    }
    else
    {
        color = (blitOp.alpha << 24) | blitOp.color.getColor32();
    }

    HAL_DMA2D_Init(&Dma2dHandle);

    HAL_DMA2D_ConfigLayer(&Dma2dHandle, 1);

    NVIC_EnableIRQ(DMA2D_IRQn);

    HAL_DMA2D_Start_IT(&Dma2dHandle, color, (unsigned int)blitOp.pDst, blitOp.nSteps, blitOp.nLoops);
}
