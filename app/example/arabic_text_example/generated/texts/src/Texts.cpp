#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/TypedText.hpp>
#include <texts/TypedTextDatabase.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/TextProvider.hpp>

#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

touchgfx::Font::StringWidthFunctionPointer touchgfx::Font::getStringWidthFunction = &touchgfx::Font::getStringWidthRTL;
touchgfx::LCD::DrawStringFunctionPointer touchgfx::LCD::drawStringFunction = &touchgfx::LCD::drawStringRTL;
touchgfx::TextProvider::UnicodeConverterInitFunctionPointer touchgfx::TextProvider::unicodeConverterInitFunction = &touchgfx::TextProvider::unicodeConverterInit;
touchgfx::TextProvider::UnicodeConverterFunctionPointer touchgfx::TextProvider::unicodeConverterFunction = &touchgfx::TextProvider::unicodeConverter;

extern const touchgfx::Unicode::UnicodeChar* const textsGb[];
extern const touchgfx::Unicode::UnicodeChar* const textsAr[];

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::Unicode::UnicodeChar* const* languagesArray[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    textsGb,
    textsAr
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
const touchgfx::Unicode::UnicodeChar* const* touchgfx::Texts::currentLanguagePtr = languagesArray[currentLanguage];

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    currentLanguage = id;
    currentLanguagePtr = languagesArray[currentLanguage];

    touchgfx::TypedText::registerTypedTextDatabase(TypedTextDatabase::getInstance(currentLanguage),
            TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
}
