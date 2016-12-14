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
#include <gui/custom_widgets/FadeButton.hpp>

FadeButton::FadeButton(bool initiallyVisible)
    : Button(),
      fadingOut(false)
{
    if (! initiallyVisible)
    {
        alpha = 0;
        setTouchable(false);
    }
}

void FadeButton::fadeOut()
{
    fadingOut = true;
    Application::getInstance()->registerTimerWidget(this);

    // Deactivate during fade out
    setTouchable(false);
}

void FadeButton::fadeIn()
{
    fadingOut = false;
    Application::getInstance()->registerTimerWidget(this);
}

void FadeButton::handleTickEvent()
{
    if (fadingOut)
    {
        if (alpha <= 2) // Be careful of not underrunning datatype
        {
            alpha = 0;
            Application::getInstance()->unregisterTimerWidget(this);
        }
        else
        {
            alpha -= 3;
        }
    }
    else // fading in
    {
        if (alpha >= 253) // Be careful of not overrunning datatype
        {
            alpha = 255;
            Application::getInstance()->unregisterTimerWidget(this);
            // Activate after fade in is finished
            setTouchable(true);
        }
        else
        {
            alpha += 3;
            invalidate();
        }
    }

    // Force redrawing of FadeButton, since changing alpha does not yield redraw.
    invalidate();
}
