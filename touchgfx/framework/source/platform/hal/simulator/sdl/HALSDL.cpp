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
#include <platform/hal/simulator/sdl/HALSDL.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <SDL/SDL.h> //Run: "sudo apt-get install libsdl1.2-dev" to install SDL
#ifdef __APPLE__
#include <SDL/SDL_video.h>
#else
#include <SDL/SDL_image.h>
#endif

#if defined(WIN32)
#include <windows.h>
#elif defined(__GNUC__)
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef __GNUC__
#define sprintf_s snprintf
#define freopen_s(pFile,filename,mode,pStream) (((*(pFile))=freopen((filename),(mode),(pStream)))==NULL)
#endif

namespace touchgfx
{

static bool isAlive = true;
static bool sdl_initialized = false;

static uint16_t* rotated = NULL;
static uint16_t* tft16bpp = NULL;
static SDL_Surface* simulatorSurface = 0;

static uint16_t* tft;

void HALSDL::renderLCD_FrameBufferToMemory(const Rect& rectToUpdate, uint16_t* frameBuffer)
{
    int bitDepth = HAL::lcd().bitDepth();
    int bytesPerPixel = bitDepth / 8;
    if (bitDepth == 1)
    {
        bitDepth = 16;
        bytesPerPixel = 2;
    }
    SDL_Surface* srcSurfaceTemp = SDL_CreateRGBSurfaceFrom((void*)frameBuffer, screenArea.width, screenArea.height, bitDepth, bytesPerPixel * screenArea.width, 0, 0, 0, 0);
    SDL_Surface* srcSurface = SDL_DisplayFormat(srcSurfaceTemp);
    SDL_FreeSurface(srcSurfaceTemp);

    SDL_Rect srcRect;
    srcRect.x = rectToUpdate.x;
    srcRect.y = rectToUpdate.y;
    srcRect.h = rectToUpdate.height;
    srcRect.w = rectToUpdate.width;

    SDL_Rect dstRect;
    dstRect.x = screenArea.x + rectToUpdate.x;
    dstRect.y = screenArea.y + rectToUpdate.y;

    SDL_BlitSurface(srcSurface, &srcRect, simulatorSurface, &dstRect);
    SDL_Flip(simulatorSurface);

    SDL_FreeSurface(srcSurface);
}

static void sdlCleanup()
{
    if (sdl_initialized)
    {
        SDL_FreeSurface(simulatorSurface);
        SDL_VideoQuit();
        SDL_Quit();
    }
}

Uint32 myTimerCallback(Uint32 interval, void* param);

Uint32 myTimerCallback(Uint32 interval, void* param)
{
    (void)param; // Unused

    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
     * into the queue, and causes ourself to be called again at the
     * same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = 0;
    userevent.data2 = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    return interval;
}

bool HALSDL::sdl_init(int argcount, char** args)
{
    (void)argcount; // Unused
    (void)args;     // Unused

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return false;
    }

    SDL_EnableUNICODE(1);

    uint8_t bitDepth = lcd().bitDepth();
    // Allocate frame buffers
    if (bitDepth < 16)
    {
        // Round up to nearest byte alignment, then divide by 2 as it is measured in uint16's
        tft = new uint16_t[((FRAME_BUFFER_WIDTH * bitDepth + 7) / 8) * FRAME_BUFFER_HEIGHT / 2];
        setFrameBufferStartAddress(tft, bitDepth, false, false);
        tft16bpp = new uint16_t[FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT];
    }
    else if (bitDepth == 16)
    {
        // Allocate size for three frame buffers
        tft = new uint16_t[FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * 3];
        setFrameBufferStartAddress(tft, bitDepth);
        tft16bpp = NULL;
    }
    else if (bitDepth == 24 || bitDepth == 32)
    {
        // Allocate size for three frame buffers
        tft = reinterpret_cast<uint16_t*>(new uint8_t[(bitDepth / 8) * FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * 3]);
        setFrameBufferStartAddress(tft, bitDepth);
        tft16bpp = NULL;
    }
    if (bitDepth < 24)
    {
        rotated = new uint16_t[FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT];
    }
    else
    {
        rotated = reinterpret_cast<uint16_t*>(new uint8_t[FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * (bitDepth / 8)]);
    }

    SDL_WM_SetCaption("TouchGFX simulator", "TouchGFX simulator");

#ifndef __APPLE__
    // alpha transparency http://sdl.beuc.net/sdl.wiki/SDL_WM_SetIcon
    SDL_WM_SetIcon(IMG_ReadXPMFromArray(const_cast<char**>(icon)), NULL);
#endif

    simulatorSurface = SDL_SetVideoMode(HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT, bitDepth < 16 ? 16 : bitDepth, SDL_DOUBLEBUF | SDL_HWSURFACE);
    if (simulatorSurface == NULL)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }

#ifdef WIN32
    FILE* stream;
    //sdl has hijacked output and error on windows
    const char* confile = "CONOUT$";
    // ignore error codes from calling freopen_s
    if (!freopen_s(&stream, confile, "w", stdout)) {}
    if (!freopen_s(&stream, confile, "w", stderr)) {}
#endif

    lcd().init();
    lockDMAToFrontPorch(false);
    atexit(sdlCleanup);
    sdl_initialized = true;

    return true;
}

void HALSDL::performDisplayOrientationChange()
{
    HAL::performDisplayOrientationChange();

    screenArea.width = DISPLAY_WIDTH;
    screenArea.height = DISPLAY_HEIGHT;
    uint8_t bitDepth = lcd().bitDepth();
    simulatorSurface = SDL_SetVideoMode(screenArea.width, screenArea.height, bitDepth < 16 ? 16 : bitDepth, SDL_DOUBLEBUF | SDL_HWSURFACE);
}

static int32_t _x = 0;
static int32_t _y = 0;
static bool _touch = false;
bool HALSDL::doSampleTouch(int32_t& x, int32_t& y)
{
    x = _x - screenArea.x;
    y = _y - screenArea.y;

    if (HAL::DISPLAY_ROTATION == rotate90)
    {
        int32_t tmp = x;
        x = y;
        y = DISPLAY_WIDTH - tmp;
    }
    return _touch;
}

static uint8_t keyPressed = 0;

bool HALSDL::sampleKey(uint8_t& key)
{
    if (keyPressed)
    {
        key = keyPressed;
        keyPressed = 0;
        return true;
    }
    return false;
}

void HALSDL::taskEntry()
{
    SDL_AddTimer(21, myTimerCallback, 0); // Start timer

    SDL_Event event;
    while (SDL_WaitEvent(&event) && isAlive)
    {
        switch (event.type)
        {
        case SDL_USEREVENT:
            {
                backPorchExited();
                frontPorchEntered();
                break;
            }

        case SDL_MOUSEMOTION:
            {
                if ((event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
                {
                    _x = event.motion.x;
                    _y = event.motion.y;
                    _touch = true;
                }
                break;
            }

        case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    _x = event.motion.x;
                    _y = event.motion.y;
                    _touch = true;
                }
                break;
            }

        case SDL_MOUSEBUTTONUP:
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    _touch = false;
                }
                break;
            }

        case SDL_KEYDOWN:
            {
                // Discard values above 0xFF, since it will overflow keyPressed
                if (event.key.keysym.unicode < 0x100)
                {
                    keyPressed = (uint8_t)(event.key.keysym.unicode & 0xFF);
                }
                break;
            }

        case SDL_KEYUP:
            {
                if (event.key.keysym.sym == SDLK_F3)
                {
                    saveScreenshot();
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isAlive = false;
                }
                break;
            }

        case SDL_QUIT:
            {
                isAlive = false;
                break;
            }

        default:
            break;
        }
    }
}

uint16_t* HALSDL::getTFTFrameBuffer() const
{
    return tft;
}

static Rect dirty(0, 0, 0, 0);

static uint16_t* upscaleTo16bpp(uint16_t* src, uint16_t width, uint16_t height, uint16_t depth)
{
    if (depth >= 16)
    {
        return src;
    }
    if (depth < 1 || (depth & (depth - 1)) != 0)
    {
        assert(0 && "unsupported screen depth");
    }
    if (HAL::DISPLAY_ROTATION == rotate90)
    {
        uint16_t tmp = width;
        width = height;
        height = tmp;
    }
    assert(tft16bpp != NULL && "Output buffer for TFT not allocated");
    uint16_t* dest = tft16bpp;
    uint16_t pixelsPerByte = 8 / depth;
    uint16_t pixelFactor = (depth == 1) ? 0xFF : ((depth == 2) ? 0x55 : ((depth == 4) ? 0x11 : 0x01));
    uint8_t* buffer = reinterpret_cast<uint8_t*>(src);
    uint8_t bitDepth = HAL::lcd().bitDepth();
    for (int srcY = 0; srcY < height; srcY++)
    {
        for (int srcXbyte = 0; srcXbyte < width * bitDepth / 8; srcXbyte++)
        {
            uint8_t byte = *buffer++;
            for (int srcXpixel = 0; srcXpixel < pixelsPerByte; srcXpixel++)
            {
                uint8_t pixel = ((byte << (srcXpixel * depth)) & 0xFF) >> (8 - depth);
                uint8_t pixelByte = pixel * pixelFactor;
                uint16_t rgb = ((pixelByte & 0xF8) << 8) | ((pixelByte & 0xFC) << 3) | ((pixelByte & 0xF8) >> 3);
                *dest++ = rgb;
            }
        }
        // Check if there is a partial byte left
        if ((width * bitDepth) % 8 != 0)
        {
            uint8_t byte = *buffer++;
            for (int srcXpixel = 0; srcXpixel < width * bitDepth % 8; srcXpixel++)
            {
                uint8_t pixel = ((byte << (srcXpixel * depth)) & 0xFF) >> (8 - depth);
                uint8_t pixelByte = pixel * pixelFactor;
                uint16_t rgb = ((pixelByte & 0xF8) << 8) | ((pixelByte & 0xFC) << 3) | ((pixelByte & 0xF8) >> 3);
                *dest++ = rgb;
            }
        }
    }
    return tft16bpp;
}

static uint16_t* doRotate(uint16_t* src, int16_t width, int16_t height)
{
    if (HAL::DISPLAY_ROTATION == rotate0)
    {
        return src;
    }
    else if (HAL::DISPLAY_ROTATION == rotate90)
    {
        int bitDepth = HAL::lcd().bitDepth();
        if (bitDepth <= 16)
        {
            uint16_t* dest = rotated;
            for (int srcX = 0; srcX < height; srcX++)
            {
                for (int srcY = 0; srcY < width; srcY++)
                {
                    int dstX = width - 1 - srcY;
                    int dstY = srcX;
                    dest[dstX + dstY * width] = src[srcX + srcY * height];
                }
            }
        }
        else
        {
            uint8_t* source = reinterpret_cast<uint8_t*>(src);
            uint8_t* dest = reinterpret_cast<uint8_t*>(rotated);
            for (int srcX = 0; srcX < height; srcX++)
            {
                for (int srcY = 0; srcY < width; srcY++)
                {
                    int dstX = width - 1 - srcY;
                    int dstY = srcX;
                    for (int i = 0; i < bitDepth / 8; i++)
                    {
                        dest[(dstX + dstY * width) * (bitDepth / 8) + i] = source[(srcX + srcY * height) * (bitDepth / 8) + i];
                    }
                }
            }
        }
        return rotated;
    }
    else
    {
        return 0;
    }
}

void HALSDL::setTFTFrameBuffer(uint16_t* adr)
{
    tft = adr;
    renderLCD_FrameBufferToMemory(dirty, doRotate(upscaleTo16bpp(adr, DISPLAY_WIDTH, DISPLAY_HEIGHT, lcd().bitDepth()), DISPLAY_WIDTH, DISPLAY_HEIGHT));
    dirty = Rect(0, 0, 0, 0);
}

void HALSDL::flushFrameBuffer()
{
    Rect display(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    flushFrameBuffer(display);
}

void HALSDL::flushFrameBuffer(const Rect& rect)
{
    dirty.expandToFit(rect);
    HAL::flushFrameBuffer(rect);
}

bool HALSDL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return HAL::blockCopy(dest, src, numBytes);
}

void HALSDL::blitSetTransparencyKey(uint16_t key)
{
    (void)key; // Unused
}

void HALSDL::saveScreenshot(char* folder, char* filename)
{
    const char* dir = "screenshots";
#if defined(WIN32)
    CreateDirectory(dir, 0);
#elif defined(__GNUC__)
    mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    char fullPathAndName[100];
    if (folder)
    {
        sprintf_s(fullPathAndName, sizeof(fullPathAndName), "%s//%s", dir, folder);
#if defined(WIN32)
        CreateDirectory(fullPathAndName, 0);
#elif defined(__GNUC__)
        mkdir(fullPathAndName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
        sprintf_s(fullPathAndName, sizeof(fullPathAndName), "%s//%s//%s", dir, folder, filename);
    }
    else
    {
        sprintf_s(fullPathAndName, sizeof(fullPathAndName), "%s//%s", dir, filename);
    }
    SDL_SaveBMP(simulatorSurface, fullPathAndName);
}

void HALSDL::saveScreenshot()
{
    static int imgCount = 0;

    char fileName[100];
    sprintf_s(fileName, sizeof(fileName), "img%02d.bmp", imgCount);
    imgCount++;

    saveScreenshot(0, fileName);
}

} // namespace touchgfx
