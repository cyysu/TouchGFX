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
#ifndef WASHING_MACHINE_TILE_HPP
#define WASHING_MACHINE_TILE_HPP

#include <gui/tiles/BaseTile.hpp>
#include <gui/common/Layout.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/model/WashingMachine.hpp>
#include <gui/common/FontPosition.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>


/**
 * Show the actual status of the washing machine. The progress icon shows the remaining wash time.
 */
class WashingMachineTile : public BaseTile
{
public:
    WashingMachineTile();
    virtual ~WashingMachineTile() {};

    void update(const WashingMachine::Program& program, uint16_t remainingTime);
protected:
    touchgfx::Image progressIcon;
    touchgfx::Image verticalLine;

    FontPosition<touchgfx::TextArea> washingMachineText;
    FontPosition<touchgfx::TextAreaWithOneWildcard> currentProgramText;
    static const uint8_t TEXT_LENGTH = 50;
    touchgfx::Unicode::UnicodeChar currentProgramBuffer[TEXT_LENGTH];

    const touchgfx::Unicode::UnicodeChar* getProgramName(const WashingMachine::ProgramType& program);
};

#endif
