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
#ifndef BARCONTAINER_HPP_
#define BARCONTAINER_HPP_

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ListLayout.hpp>

using namespace touchgfx;

class BarContainer : public ListLayout
{
public:
    BarContainer();
    virtual ~BarContainer();
    virtual void handleTickEvent();
    int16_t getBarHeight() const;
    void startAnimation();

private:
    static const uint8_t SIZE = 12;
    static const uint8_t ANIMATION_STEPS = 25;

    uint8_t animationCounter;
    bool animate;

    struct Bar
    {
        Image image;
        int16_t targetValue;
    };

    Bar bars[SIZE];
};

#endif /* BARCONTAINER_HPP_ */
