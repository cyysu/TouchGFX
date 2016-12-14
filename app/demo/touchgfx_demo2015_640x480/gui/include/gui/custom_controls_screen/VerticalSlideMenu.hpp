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
#ifndef VERTICAL_SLIDE_MENU_HPP_
#define VERTICAL_SLIDE_MENU_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>

using namespace touchgfx;

class VerticalSlideMenu : public Container
{
public:
    VerticalSlideMenu();
    virtual ~VerticalSlideMenu();

    void animateUp();
    void animateDown();
    void setup(int numberOfElements, int selectedElementIndex, Bitmap smallBmp, Bitmap largeBmp);
    void setBitmapsForElement(int elementIndex, BitmapId smallBmp, BitmapId largeBmp);

    void setAnimationDuration(int duration)
    {
        animationDuration = duration;
    }
    int getAnimationDuration()
    {
        return animationDuration;
    }

    void setElementSelectedCallback(touchgfx::GenericCallback<const VerticalSlideMenu&>& callback)
    {
        elementSelectedAction = &callback;
    }
    int getSelectedElementIndex()
    {
        return currentSelected;
    }

    int getSize()
    {
        return size;
    }
private:
    static const uint8_t MAX_SIZE = 10;

    GenericCallback<const VerticalSlideMenu&>* elementSelectedAction;

    ZoomAnimationImage images[MAX_SIZE];

    uint8_t size;
    uint8_t currentSelected;

    int animationDuration;

    int largeImageY;
    int smallImageWidth;
    int largeImageWidth;
    int imagesYPositionDelta;
    int largeImageHeight;
    int smallImageX;
    int smallImageHeight;
    int largeImageX;
    int fixedCenterCorrection;

    Callback<VerticalSlideMenu, const ZoomAnimationImage&> animationEndedCallback;
    void animationEndedHandler(const ZoomAnimationImage& image);
    bool animating();
};

#endif /* VERTICAL_SLIDE_MENU_HPP_ */
