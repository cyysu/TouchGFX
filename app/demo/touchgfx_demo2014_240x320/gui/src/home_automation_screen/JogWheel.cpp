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
#include <gui/home_automation_screen/JogWheel.hpp>
#include <math.h>

JogWheel::JogWheel(int16_t startValue_, int16_t deltaValueForOneRound_) :
    degreesRotated(0),
    startValue(startValue_),
    deltaValueForOneRound(deltaValueForOneRound_),
    currentValue(startValue_),
    firstDragEvent(true),
    ANGLE_MULTIPLIER(1000),
    valueChangedCallback(0)
{
    setTouchable(true);

    background.setXY(0, 0);

    add(background);
}

JogWheel::~JogWheel()
{
}

void JogWheel::setBitmap(Bitmap newBackgroundImage)
{
    setBitmaps(newBackgroundImage, newBackgroundImage);
}

void JogWheel::setBitmaps(Bitmap newBackgroundImage, Bitmap newBackgroundImageWhenDragged)
{
    backgroundImage = newBackgroundImage;
    backgroundImageWhenDragged = newBackgroundImageWhenDragged;

    background.setBitmap(backgroundImage);

    setWidth(backgroundImage.getWidth());
    setHeight(backgroundImage.getHeight());

    centerX = getWidth() / 2;
    centerY = getHeight() / 2;
    radius  = getWidth() / 2;
    oldX = centerX;
    oldY = centerY;
    oldLength = 0;
}

void JogWheel::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        firstDragEvent = true;
        background.setBitmap(Bitmap(backgroundImageWhenDragged));
        background.invalidate();
    }
    else
    {
        background.setBitmap(Bitmap(backgroundImage));
        background.invalidate();

        if (endDragEventCallback)
        {
            endDragEventCallback->execute(currentValue);
        }
    }
}

void JogWheel::handleDragEvent(const DragEvent& evt)
{
    int16_t vx = evt.getNewX() - centerX;
    int16_t vy = evt.getNewY() - centerY;

    if (vx == 0 && vy == 0)
    {
        return;
    }

    //Length of new vector
    double length = sqrt((double)(vx * vx + vy * vy));

    //Calc dot product and angle diff
    int16_t dotProduct = (oldX * vx + oldY * vy);

    double angleDiff = acos(dotProduct / (oldLength * length));

    //Calc Z part of X-product = angle sign
    int16_t angleSign = oldX * vy - oldY * vx;

    // set sign of angle
    if (angleSign < 0)
    {
        angleDiff = -1 * angleDiff;
    }
    angleDiff *= ANGLE_MULTIPLIER;

    // Do not update the degreesRotated on the first drag event
    // we need a starting point to do a calculation
    if (firstDragEvent)
    {
        firstDragEvent = false;
    }
    else
    {
        degreesRotated += (int16_t) angleDiff;
    }

    if (valueChangedCallback)
    {
        int16_t newValue = startValue + (int16_t)((degreesRotated / (3.14 * 2 * ANGLE_MULTIPLIER)) * deltaValueForOneRound);
        if (newValue != currentValue)
        {
            currentValue = newValue;
            valueChangedCallback->execute(currentValue);
        }
    }

    // save old data to be used for next input
    oldX = vx;
    oldY = vy;
    oldLength = length;

    vx = (int16_t)(vx * radius / length);
    vy = (int16_t)(vy * radius / length);
}

void JogWheel::setValue(int16_t value)
{
    startValue = value;
    currentValue = value;
    degreesRotated = 0;

    if (valueChangedCallback)
    {
        valueChangedCallback->execute(currentValue);
    }
}
