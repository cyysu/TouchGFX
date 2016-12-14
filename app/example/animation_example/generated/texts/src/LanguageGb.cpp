#include <stdint.h>
#include <touchgfx/Unicode.hpp>

#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

// Language Gb: No substitution
TEXT_LOCATION_FLASH_PRAGMA
KEEP const touchgfx::Unicode::UnicodeChar T_Start_Gb[5] TEXT_LOCATION_FLASH_ATTRIBUTE = { 0x50, 0x4c, 0x41, 0x59, 0x0 };
TEXT_LOCATION_FLASH_PRAGMA
KEEP const touchgfx::Unicode::UnicodeChar T_Stop_Gb[6] TEXT_LOCATION_FLASH_ATTRIBUTE = { 0x50, 0x41, 0x55, 0x53, 0x45, 0x0 };

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar* const textsGb[2] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
T_Start_Gb,
T_Stop_Gb
};

