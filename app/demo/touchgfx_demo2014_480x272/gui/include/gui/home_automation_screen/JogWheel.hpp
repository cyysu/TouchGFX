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
#ifndef JOG_WHEEL_HPP_
#define JOG_WHEEL_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class JogWheel : public Container
{
public:
    JogWheel(int16_t startValue_, int16_t deltaValueForOneRound_);
    virtual ~JogWheel();

    void setBitmap(Bitmap newBackgroundImage);
    void setBitmaps(Bitmap newBackgroundImage, Bitmap newBackgroundImageWhenDragged_);

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);

    void setValueUpdatedCallback(GenericCallback< int16_t >& callback)
    {
        valueChangedCallback = &callback;
    }
    void setEndDragEventCallback(GenericCallback< int16_t >& callback)
    {
        endDragEventCallback = &callback;
    }

    void setValue(int16_t value);
    int16_t getValue()
    {
        return currentValue;
    }

private:
    Image background;

    Bitmap backgroundImage;
    Bitmap backgroundImageWhenDragged;

    int32_t degreesRotated;
    int16_t startValue;
    int16_t deltaValueForOneRound;
    int16_t currentValue;

    bool firstDragEvent;
    int16_t centerX;
    int16_t centerY;
    int16_t radius;
    int16_t oldX;
    int16_t oldY;
    float oldLength;
    const uint16_t ANGLE_MULTIPLIER;

    GenericCallback< int16_t >* valueChangedCallback;
    GenericCallback< int16_t >* endDragEventCallback;
};


#endif /* JOG_WHEEL_HPP_ */
