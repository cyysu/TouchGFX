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
#include <gui/common/ZoomAnimationBox.hpp>

ZoomAnimationBox::ZoomAnimationBox() :
    Box(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    animationEndedAction(0)
{

}

ZoomAnimationBox::~ZoomAnimationBox()
{
}

void ZoomAnimationBox::startZoomAnimation(int16_t endWidth, int16_t endHeight, uint16_t duration, touchgfx::EasingEquation widthProgressionEquation /*= &touchgfx::EasingEquations::linearEaseNone*/, EasingEquation heightProgressionEquation /*= &touchgfx::EasingEquations::linearEaseNone*/)
{
    touchgfx::Application::getInstance()->registerTimerWidget(this);

    zoomAnimationStartX = getX();
    zoomAnimationStartY = getY();
    zoomAnimationStartWidth = getWidth();
    zoomAnimationStartHeight = getHeight();
    zoomAnimationEndWidth = endWidth;
    zoomAnimationEndHeight = endHeight;
    animationDuration = duration;

    zoomAnimationWidthEquation = widthProgressionEquation;
    zoomAnimationHeightEquation = heightProgressionEquation;

    zoomAnimationDeltaX = (zoomAnimationStartWidth - zoomAnimationEndWidth) / 2;
    zoomAnimationDeltaY = (zoomAnimationStartHeight - zoomAnimationEndHeight) / 2;

    setCurrentState(ANIMATE_ZOOM);
}

void ZoomAnimationBox::handleTickEvent()
{
    if (currentState == ANIMATE_ZOOM)
    {
        if (animationCounter <= animationDuration)
        {

            int16_t deltaWidth = zoomAnimationWidthEquation(animationCounter, 0, zoomAnimationEndWidth - zoomAnimationStartWidth, animationDuration);
            int16_t deltaHeight = zoomAnimationHeightEquation(animationCounter, 0, zoomAnimationEndHeight - zoomAnimationStartHeight, animationDuration);

            invalidate();
            int16_t newWidth = zoomAnimationStartWidth + deltaWidth;
            if (newWidth < 0)
            {
                newWidth = 0;
            }
            int16_t newHeight = zoomAnimationStartHeight + deltaHeight;
            if (newHeight < 0)
            {
                newHeight = 0;
            }
            setWidth(newWidth);
            setHeight(newHeight);

            moveTo(zoomAnimationStartX - (deltaWidth / 2), zoomAnimationStartY - (deltaHeight / 2));

            invalidate();
            animationCounter++;
        }
        else
        {
            touchgfx::Application::getInstance()->unregisterTimerWidget(this);
            setCurrentState(NO_ANIMATION);

            if (animationEndedAction && animationEndedAction->isValid())
            {
                animationEndedAction->execute(*this);
            }
        }
    }
}

void ZoomAnimationBox::setCurrentState(States state)
{
    currentState = state;
    animationCounter = 0;
}

