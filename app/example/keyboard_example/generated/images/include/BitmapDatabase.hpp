// Generated by imageconverter. Please, do not edit!

#ifndef BITMAPDATABASE_HPP
#define BITMAPDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>

const uint16_t BITMAP_ICON_KEYBOARD_EVEN_ROW_ID = 0; // Size: 47x28 pixels
const uint16_t BITMAP_ICON_KEYBOARD_HIGHLIGHTED_ID = 1; // Size: 47x28 pixels
const uint16_t BITMAP_ICON_KEYBOARD_ODD_ROW_ID = 2; // Size: 47x28 pixels
const uint16_t BITMAP_KEYBOARD_BACKGROUND_ID = 3; // Size: 320x240 pixels
const uint16_t BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_ID = 4; // Size: 56x40 pixels
const uint16_t BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID = 5; // Size: 26x40 pixels
const uint16_t BITMAP_KEYBOARD_KEY_NUM_HIGHLIGHTED_ID = 6; // Size: 56x40 pixels
const uint16_t BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_ID = 7; // Size: 56x40 pixels
const uint16_t BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID = 8; // Size: 252x40 pixels

namespace BitmapDatabase
{
#ifndef NO_USING_NAMESPACE_TOUCHGFX
  using namespace touchgfx;
#endif

  class BitmapData;
  const touchgfx::Bitmap::BitmapData* getInstance();
  uint16_t getInstanceSize();
}

#endif