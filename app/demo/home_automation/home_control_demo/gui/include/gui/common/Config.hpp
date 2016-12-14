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
#ifndef CONFIG_HPP_
#define CONFIG_HPP_

// This file chooses between two resolutions
// 640X480 mode: Insert #define RESOLUTION_640X480
// 800x480 mode: Default mode, do not insert any #define


#ifdef ST
#ifdef STM32F469xx
#else
// STM32F439 5.7" eval board
#define RESOLUTION_640X480
#endif
#elif defined(DISPLAY_UMSH_8596MD_T)
// TouchGFXDemoBoard 7.0"
// Uses 800x480

#elif defined(SIMULATOR)
// Simulator - can run both resolutions
// To use 640x480 insert the define
// To use 800x480 remove/comment the define

//#define RESOLUTION_640X480
#else

#endif


#endif
