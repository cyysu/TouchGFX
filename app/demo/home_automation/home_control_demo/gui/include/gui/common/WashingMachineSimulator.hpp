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
#ifndef WASHING_MACHINE_SIMULATOR_HPP
#define WASHING_MACHINE_SIMULATOR_HPP

#include <touchgfx/Utils.hpp>
#include <gui/model/WashingMachine.hpp>


class WashingMachineSimulator
{

public:
    WashingMachineSimulator(Model& model) :
        model(model),
        lastWashFinished(System::DateTime::beginning()),
        startTime(System::DateTime::beginning()),
        remainingTime(0)
    {
    }

    void handleTickEvent(const System::DateTime& time)
    {
        if (currentProgram.type == WashingMachine::NO_PROGRAM)
        {
            // wait a short time before a new wash is started
            int64_t diff = model.getCurrentDateTime() - lastWashFinished;
            if (diff > 3)
            {
                switch (previousProgram.type)
                {
                case WashingMachine::QUICK_WASH:
                    start(WashingMachine::NORMAL);
                    break;
                case WashingMachine::NORMAL:
                    start(WashingMachine::WOOL);
                    break;
                case WashingMachine::WOOL:
                default:
                    start(WashingMachine::QUICK_WASH);
                    break;
                }
            }
        }
        else
        {
            int64_t remainingSec = currentProgram.totalTime - (model.getCurrentDateTime() - startTime);
            if (remainingSec < 0)
            {
                stop();
                model.setWashingMachineState(currentProgram, static_cast<uint16_t>(remainingTime));
            }
            else if (remainingSec != remainingTime)
            {
                remainingTime = remainingSec;
                model.setWashingMachineState(currentProgram, static_cast<uint16_t>(remainingTime));
            }
        }
    }

    void start(WashingMachine::ProgramType programType)
    {
        switch (programType)
        {
        case WashingMachine::QUICK_WASH:
            currentProgram = WashingMachine::Program(programType, 60, 1 * 60);
            break;

        case WashingMachine::NORMAL:
            currentProgram = WashingMachine::Program(programType, 40, 3 * 60);
            break;

        case WashingMachine::WOOL:
        default:
            currentProgram = WashingMachine::Program(WashingMachine::WOOL, 30, 2 * 60);
            break;
        }
        startTime = model.getCurrentDateTime();
        remainingTime = currentProgram.totalTime;
    }

    void stop()
    {
        previousProgram = currentProgram;
        currentProgram = WashingMachine::Program();
        remainingTime = 0;
        lastWashFinished = model.getCurrentDateTime();
    }

private:
    Model& model;

    System::DateTime lastWashFinished;

    System::DateTime startTime;
    WashingMachine::Program currentProgram;
    WashingMachine::Program previousProgram;
    int64_t remainingTime;
};

#endif
