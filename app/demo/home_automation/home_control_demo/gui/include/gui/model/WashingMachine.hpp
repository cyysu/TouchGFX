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
#ifndef WASHING_MACHINE_MODEL_HPP
#define WASHING_MACHINE_MODEL_HPP

#include <stdint.h>
#include <touchgfx/Utils.hpp>

class WashingMachine
{
public:
    /**
     * Define washing machine cycles.
     */
    enum Cycle
    {
        READY,
        WASH,
        RINSE,
        SPIN,
        DONE
    };
    static const uint8_t NUMBER_OF_CYCLES = DONE + 1;

    /**
     * Define washing machine programs.
     */
    enum ProgramType
    {
        NO_PROGRAM,
        WOOL,
        QUICK_WASH,
        DARK_COLORS,
        NORMAL,
        HEAVY_DUTY,
        BULKY,
        SHEETS,
        WHITES,
        STEAM,
        RINSE_AND_SPIN
    };
    static const uint8_t NUMBER_OF_PROGRAMS = RINSE_AND_SPIN + 1;

    class Program
    {
    public:
        Program(ProgramType type = NO_PROGRAM, uint8_t temp = 0, uint16_t totalTime = 0) :
            type(type), temperature(temp), totalTime(totalTime)
        {
        }

        ProgramType type;
        uint8_t temperature;
        uint16_t totalTime;
    };

    WashingMachine();
    virtual ~WashingMachine() {};

    bool isWashing() const
    {
        return getCurrentProgram().type != NO_PROGRAM;
    }

    Program getCurrentProgram() const
    {
        return currentProgram;
    }
    uint16_t getRemainingTime()  const
    {
        return remainingTime;
    }

    void setState(const Program& program, uint16_t remainingTime)
    {
        currentProgram = program;
        this->remainingTime = remainingTime;
    }
private:
    Program currentProgram;
    uint16_t remainingTime;
};

#endif
