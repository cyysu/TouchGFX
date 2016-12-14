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
#ifndef CANVASWIDGETRENDERER_HPP
#define CANVASWIDGETRENDERER_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/canvas_widget_renderer/Cell.hpp>
#ifdef SIMULATOR

/**
 * @def CWR_OUTPUT
 *
 * @brief Set CWR_OUTPUT to 1 to write memory information on the screen.
 *
 *        Set CWR_OUTPUT to 1 to write memory information on the screen.
 */
#define CWR_OUTPUT 0
#include <touchgfx/canvas_widget_renderer/Cell.hpp>
#if CWR_OUTPUT
#include <stdio.h> // For optional memory footprint reporting
#endif
#endif

/**
 * @def MEMORY_CHECK
 *
 * @brief For debugging purposes only.
 *
 *        Set MEMORY_CHECK to 1 to write markers in the memory area between regions. Method
 *        memCheck() can then be called to validate that the markers are still present.
 */
#define MEMORY_CHECK 0

#if MEMORY_CHECK
#define MEMORY_BYTE1 0xAB
#define MEMORY_BYTE2 0xBA
#include <assert.h>
#endif

namespace touchgfx
{
/**
 * @class CanvasWidgetRenderer CanvasWidgetRenderer.hpp touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp
 *
 * @brief Class for supporting drawing of figures.
 *
 *        Class for supporting drawing of figures. This class holds the memory which is used by
 *        the underlying algorithms. CanvasWidget will not allocate memory dynamically, but
 *        will use memory from the buffer kept in CanvasWidgetRenderer. When using the TouchGFX
 *        simulator, it is also possible to get a report on the actual amount of memory used
 *        for the drawings to help adjusting the buffer size.
 *
 * @see Widget
 */
class CanvasWidgetRenderer : public Widget
{
public:

    /**
     * @fn static void CanvasWidgetRenderer::setupBuffer(uint8_t* buffer, unsigned bufsize)
     *
     * @brief Setup the buffers used by CanvasWidget.
     *
     *        Setup the buffers used by CanvasWidget.
     *
     * @param [in] buffer Buffer reserved for CanvasWidget.
     * @param bufsize     The size of the buffer.
     */
    static void setupBuffer(uint8_t* buffer, unsigned bufsize)
    {
        memoryBuffer = buffer;
        memoryBufferSize = bufsize;

#ifdef SIMULATOR
        scanlineSize = 0;
        maxCellsUsed = 0;
        maxCellsMissing = 0;
#endif
    }

#if MEMORY_CHECK

    /**
     * @fn static void CanvasWidgetRenderer::memCheck()
     *
     * @brief For debugging purposes only.
     *
     *        For debugging purposes only. Perform a memory check if MEMORY_CHECK is set to 1.
     */
    static void memCheck()
    {
        // validate previous buffer
        assert(memoryBuffer[0] == MEMORY_BYTE1);
        assert(memoryBuffer[1] == MEMORY_BYTE2);
        assert(((uint8_t*)scanlineCovers)[-2] == MEMORY_BYTE1);
        assert(((uint8_t*)scanlineCovers)[-1] == MEMORY_BYTE2);
        assert(((uint8_t*)scanlineStartIndices)[-2] == MEMORY_BYTE1);
        assert(((uint8_t*)scanlineStartIndices)[-1] == MEMORY_BYTE2);
        assert(((uint8_t*)scanlineCounts)[-2] == MEMORY_BYTE1);
        assert(((uint8_t*)scanlineCounts)[-1] == MEMORY_BYTE2);
        assert(((uint8_t*)outlineBuffer)[-2] == MEMORY_BYTE1);
        assert(((uint8_t*)outlineBuffer)[-1] == MEMORY_BYTE2);
        assert(memoryBuffer[memoryBufferSize - 2] == MEMORY_BYTE1);
        assert(memoryBuffer[memoryBufferSize - 1] == MEMORY_BYTE2);
    }
#endif

    /**
     * @fn static bool CanvasWidgetRenderer::setScanlineWidth(unsigned width)
     *
     * @brief Sets scanline width.
     *
     *        Sets scanline width. Setting the scanline width will initialize the buffers for
     *        scanline and outline. If the width set is too large to fit the scanline buffers
     *        in the allocated memory buffer, false will be returned and all buffer pointers
     *        will be cleared.
     *
     * @param width The width of the scanline on screen.
     *
     * @return true if it succeeds, false if it fails.
     */
    static bool setScanlineWidth(unsigned width)
    {
#if MEMORY_CHECK
        static bool checkMemory = false;
        if (checkMemory)
        {
            memCheck();
        }
        checkMemory = true;
#endif

        if (width == scanlineWidth)
        {
            return outlineBufferSize > 0;
        }

        uint8_t* buffer = memoryBuffer;
        unsigned int bufsize = memoryBufferSize;

#if MEMORtoutouY_CHECK
        *buffer++ = MEMORY_BYTE1;
        *buffer++ = MEMORY_BYTE2;
        bufsize -= 2;
#endif

        scanlineWidth = width;

#if MEMORY_CHECK
        *buffer++ = MEMORY_BYTE1;
        *buffer++ = MEMORY_BYTE2;
        bufsize -= 2;
#endif
        unsigned size = scanlineWidth * sizeof(uint8_t);
        scanlineCovers = buffer;
        assert(bufsize >= size && "Not enough memory allocated for CWR");
        if (bufsize < size)
        {
            // Do not attempt to use CWR, it has not been properly initialized!
            return false;
        }
        buffer += size, bufsize -= size;
#ifdef SIMULATOR
        scanlineSize = size;
#endif

#if MEMORY_CHECK
        *buffer++ = MEMORY_BYTE1;
        *buffer++ = MEMORY_BYTE2;
        bufsize -= 2;
#endif
        size = (scanlineWidth + 1) / 2 * sizeof(uint16_t);
        scanlineStartIndices = buffer;
        assert(bufsize >= size && "Not enough memory allocated for CWR");
        if (bufsize < size)
        {
            // Do not attempt to use CWR, it has not been properly initialized!
            return false;
        }
        buffer += size, bufsize -= size;
#ifdef SIMULATOR
        scanlineSize += size;
#endif

#if MEMORY_CHECK
        *buffer++ = MEMORY_BYTE1;
        *buffer++ = MEMORY_BYTE2;
        bufsize -= 2;
#endif
        size = (scanlineWidth + 1) / 2 * sizeof(uint16_t);
        scanlineCounts = buffer;
        assert(bufsize >= size && "Not enough memory allocated for CWR");
        if (bufsize < size)
        {
            // Do not attempt to use CWR, it has not been properly initialized!
            return false;
        }
        buffer += size, bufsize -= size;
#ifdef SIMULATOR
        scanlineSize += size;
#endif

#if MEMORY_CHECK
        *buffer++ = MEMORY_BYTE1;
        *buffer++ = MEMORY_BYTE2;
        bufsize -= 2;
        buffer[bufsize - 2] = MEMORY_BYTE1;
        buffer[bufsize - 1] = MEMORY_BYTE2;
        bufsize -= 2;
#endif
        outlineBuffer = (Cell*)buffer;
        outlineBufferSize = bufsize;
        assert(bufsize >= 16 && "Not enough memory allocated for CWR");

        return outlineBufferSize > 0;
    }

    /**
     * @fn static bool CanvasWidgetRenderer::hasBuffer()
     *
     * @brief Query if CanvasWidgetRenderer has been initialized with a buffer.
     *
     *        Query if CanvasWidgetRenderer has been initialized with a buffer.
     *
     * @return True if a buffer has been setup.
     */
    static bool hasBuffer()
    {
        return memoryBuffer != 0 && memoryBufferSize > 0;
    }

    /**
     * @fn static unsigned CanvasWidgetRenderer::getScanlineWidth()
     *
     * @brief The width of a scanline.
     *
     *        The width of a scanline. This is the same as the width of the invalidated area.
     *        Used to optimize the memory layout of the buffer.
     *
     * @return Scanline width (HAL::FRAME_BUFFER_WIDTH).
     */
    static unsigned getScanlineWidth()
    {
        return scanlineWidth;
    }

    /**
     * @fn static void* CanvasWidgetRenderer::getScanlineCovers()
     *
     * @brief Gets pointer to memory used for covers in Scanline.
     *
     *        Gets pointer to memory used for covers in Scanline.
     *
     * @return Pointer to memory used internally by Scanline.
     */
    static void* getScanlineCovers()
    {
        return scanlineCovers;
    }

    /**
     * @fn static void* CanvasWidgetRenderer::getScanlineStartIndices()
     *
     * @brief Gets pointer to memory used for indices in Scanline.
     *
     *        Gets pointer to memory used for indices in Scanline.
     *
     * @return Pointer to memory used internally by Scanline.
     */
    static void* getScanlineStartIndices()
    {
        return scanlineStartIndices;
    }

    /**
     * @fn static void* CanvasWidgetRenderer::getScanlineCounts()
     *
     * @brief Gets pointer to memory used for counts in Scanline.
     *
     *        Gets pointer to memory used for counts in Scanline.
     *
     * @return Pointer to memory used internally by Scanline.
     */
    static void* getScanlineCounts()
    {
        return scanlineCounts;
    }

    /**
     * @fn static Cell* CanvasWidgetRenderer::getOutlineBuffer()
     *
     * @brief Gets pointer to memory used for Cell objects in Outline.
     *
     *        Gets pointer to memory used for Cell objects in Outline.
     *
     * @return Pointer to memory used internally by Outline.
     */
    static Cell* getOutlineBuffer()
    {
        return outlineBuffer;
    }

    /**
     * @fn static unsigned int CanvasWidgetRenderer::getOutlineBufferSize()
     *
     * @brief Gets size of memory area used for Cell objects in Outline.
     *
     *        Gets size of memory area used for Cell objects in Outline.
     *
     * @return Size of memory area used internally by Outline.
     */
    static unsigned int getOutlineBufferSize()
    {
        return outlineBufferSize;
    }

#ifdef SIMULATOR

    /**
     * @fn static void CanvasWidgetRenderer::numCellsUsed(unsigned used)
     *
     * @brief Called by the destructor in Outline to help keep track of the memory requirements of
     *        CanvasWidgets.
     *
     *        Called by the destructor in Outline to help keep track of the memory requirements
     *        of CanvasWidgets.
     *
     * @param used Number of Cell objects used from the dedicated buffer.
     */
    static void numCellsUsed(unsigned used)
    {
        if (used > maxCellsUsed)
        {
            maxCellsUsed = used;
#if CWR_OUTPUT
            printf("CanvasWidgetRenderer memory requirement is now %u bytes\n", getUsedBufferSize());
#endif
        }
    }

    /**
     * @fn static void CanvasWidgetRenderer::numCellsMissing(unsigned missing)
     *
     * @brief Called by the destructor in Outline to help keep track of the memory requirements of
     *        CanvasWidgets.
     *
     *        Called by the destructor in Outline to help keep track of the memory requirements
     *        of CanvasWidgets.
     *
     * @param missing Number of Cell objects required, but not available, to Outline.
     */
    static void numCellsMissing(unsigned missing)
    {
        if (missing > maxCellsMissing)
        {
            maxCellsMissing = missing;
#if CWR_OUTPUT
            printf("CanvasWidgetRenderer memory requirement is now %u bytes (%u bytes missing)\n", getUsedBufferSize() + getMissingBufferSize(), getMissingBufferSize());
#endif
        }
    }

    /**
     * @fn static unsigned CanvasWidgetRenderer::getUsedBufferSize()
     *
     * @brief Calculate how much memory has been required by CanvasWidgets.
     *
     *        Calculate how much memory has been required by CanvasWidgets. This can be used to
     *        fine tune the size of the buffer passed to CanvasWidgetRenderer upon
     *        initialization.
     *
     * @return The number of bytes required.
     */
    static unsigned getUsedBufferSize()
    {
        return scanlineSize + maxCellsUsed * sizeof(Cell);
    }

    /**
     * @fn static unsigned CanvasWidgetRenderer::getMissingBufferSize()
     *
     * @brief Calculate how much memory was required by CanvasWidgets, but was unavailable.
     *
     *        Calculate how much memory was required by CanvasWidgets, but was unavailable. If
     *        the value returned is greater than 0 it means the This can be used to fine tune
     *        the size of the buffer passed to CanvasWidgetRenderer upon initialization.
     *
     * @return The number of bytes required.
     */
    static unsigned getMissingBufferSize()
    {
        return maxCellsMissing * sizeof(Cell);
    }
#endif

private:
    static uint8_t* memoryBuffer;
    static unsigned int memoryBufferSize;
    static unsigned int scanlineWidth;
    static void* scanlineCovers;
    static void* scanlineStartIndices;
    static void* scanlineCounts;
    static Cell* outlineBuffer;
    static unsigned int outlineBufferSize;
#ifdef SIMULATOR
    static unsigned int scanlineSize;
    static unsigned int maxCellsUsed;
    static unsigned int maxCellsMissing;
#endif
}; // class CanvasWidgetRenderer

} // namespace touchgfx

#endif // CANVASWIDGETRENDERER_HPP
