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
#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
    { 1, Rect(7, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 2, Rect(7 + 28, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 3, Rect(7 + 28 * 2, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 4, Rect(7 + 28 * 3, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 5, Rect(7 + 28 * 4, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 6, Rect(7 + 28 * 5, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 7, Rect(7 + 28 * 6, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 8, Rect(7 + 28 * 7, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 9, Rect(7 + 28 * 8, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {10, Rect(7 + 28 * 9, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {11, Rect(7 + 28 * 10, 61, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {12, Rect(7, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {13, Rect(7 + 28, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {14, Rect(7 + 28 * 2, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {15, Rect(7 + 28 * 3, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {16, Rect(7 + 28 * 4, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {17, Rect(7 + 28 * 5, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {18, Rect(7 + 28 * 6, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {19, Rect(7 + 28 * 7, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {20, Rect(7 + 28 * 8, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {21, Rect(7 + 28 * 9, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {22, Rect(7 + 28 * 10, 105, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {23, Rect(63, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {24, Rect(63 + 28, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {25, Rect(63 + 28 * 2, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {26, Rect(63 + 28 * 3, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {27, Rect(63 + 28 * 4, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {28, Rect(63 + 28 * 5, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {29, Rect(63 + 28 * 6, 149, 26, 40), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {30, Rect(62, 193, 252, 40), BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID}
};

/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
static Keyboard::CallbackArea callbackAreas[3] =
{
    {Rect(5, 149, 56, 40), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_ID},     // caps-lock
    {Rect(258, 149, 56, 40), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_ID},  // backspace
    {Rect(5, 193, 56, 40), 0, BITMAP_KEYBOARD_KEY_NUM_HIGHLIGHTED_ID},       // mode
};

/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layout =
{
    BITMAP_KEYBOARD_BACKGROUND_ID,
    keyArray,
    30,
    callbackAreas,
    3,
    Rect(15, 10, 11 * 28, 40),
    TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
    0xFFFF,
#else
    0xFFFFFF,
#endif
    Typography::KEYBOARD,
    0
};

#endif
