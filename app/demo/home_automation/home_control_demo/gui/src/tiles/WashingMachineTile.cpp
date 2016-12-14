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
#include <gui/tiles/WashingMachineTile.hpp>
#include <gui/common/Constants.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Config.hpp>

using namespace touchgfx;

WashingMachineTile::WashingMachineTile() :
    BaseTile()
{
    setHeight(Layout::appliance_tile().height);
    setWidth(Layout::appliance_tile().width);

    int resolutionModifier = 0;
#ifdef RESOLUTION_640X480
    resolutionModifier = -12;
#endif

    progressIcon.setBitmap(touchgfx::Bitmap(BITMAP_WASHINGPROGRESS_00_ID));
    progressIcon.setXY(42 + resolutionModifier, (getHeight() - progressIcon.getHeight()) / 2);

    washingMachineText.setColor(Colors_TEXT_GREY);
    washingMachineText.setTypedText(touchgfx::TypedText(T_WASHING_MACHINE));
    washingMachineText.setPosition(120 + resolutionModifier, 74, getWidth() - 120);

    currentProgramText.setColor(Colors_TEXT_DARK);
    currentProgramText.setTypedText(touchgfx::TypedText(T_WASHING_PROGRAM_PLACEHOLDER));
    currentProgramText.setPosition(120 + resolutionModifier, 100, getWidth() - 120);
    currentProgramText.setWildcard(currentProgramBuffer);

    verticalLine.setBitmap(Bitmap(BITMAP_VERT_LINE_BUTTOM_ID));
    verticalLine.setXY(getWidth() - verticalLine.getWidth(), 30);

    add(progressIcon);
    add(washingMachineText);
    add(currentProgramText);
    add(verticalLine);
}

void WashingMachineTile::update(const WashingMachine::Program& program, uint16_t remainingTime)
{
    if (program.type == WashingMachine::NO_PROGRAM)
    {
        touchgfx::Unicode::snprintf(currentProgramBuffer, TEXT_LENGTH, "%s", getProgramName(program.type));
        progressIcon.setBitmap(touchgfx::Bitmap(BITMAP_WASHINGPROGRESS_00_ID));
    }
    else
    {
#ifdef RESOLUTION_640X480
        touchgfx::Unicode::snprintf(currentProgramBuffer, TEXT_LENGTH, "%s / %i%s ", getProgramName(program.type), program.temperature, touchgfx::TypedText(T_WASHING_DEGREE).getText());
#else
        touchgfx::Unicode::snprintf(currentProgramBuffer, TEXT_LENGTH, "%s / %i%s / %i %s", getProgramName(program.type), program.temperature, touchgfx::TypedText(T_WASHING_DEGREE).getText(), remainingTime / 60 + 1, touchgfx::TypedText(T_MIN).getText());
#endif

        uint8_t bitmapOffset = 20 - ((remainingTime * 1000 / program.totalTime) * 20) / 1000;
        progressIcon.setBitmap(touchgfx::Bitmap(BITMAP_WASHINGPROGRESS_00_ID + bitmapOffset));
    }
    invalidate();
}

const touchgfx::Unicode::UnicodeChar* WashingMachineTile::getProgramName(const WashingMachine::ProgramType& programType)
{
    switch (programType)
    {
    case WashingMachine::NORMAL:
        return touchgfx::TypedText(T_NORMAL_WASH).getText();
    case WashingMachine::QUICK_WASH:
        return touchgfx::TypedText(T_QUICK_WASH).getText();
    case WashingMachine::WOOL:
        return touchgfx::TypedText(T_WOOL_WASH).getText();
    default:
        ;
        //
    }

    return touchgfx::TypedText(T_READY_WASH).getText();
    //WashingMachine::ProgramName programs[] = {
    //    WashingMachine::WOOL,
    //    WashingMachine::QUICK_WASH,
    //    WashingMachine::DARK_COLORS,
    //    WashingMachine::NORMAL,
    //    WashingMachine::HEAVY_DUTY,
    //    WashingMachine::BULKY,
    //    WashingMachine::SHEETS,
    //    WashingMachine::WHITES,
    //    WashingMachine::STEAM,
    //    WashingMachine::RINSE_AND_SPIN };
    //return 0;
}
