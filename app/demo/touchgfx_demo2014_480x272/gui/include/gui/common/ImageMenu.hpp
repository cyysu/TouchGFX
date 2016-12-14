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
#ifndef IMAGEMENU_HPP_
#define IMAGEMENU_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ImageMenuElement.hpp>

using namespace touchgfx;

class ImageMenu : public Container
{
public:
    ImageMenu(uint16_t imageMenuWidth, uint16_t imageMenuHeight, uint16_t elementWidth_, BitmapId logoImage, BitmapId backButtonImage, BitmapId backButtonPressedImage, BitmapId backgroundItemsImage);
    virtual ~ImageMenu();

    virtual void handleTickEvent();

    void setMenuItemSelectedCallback(GenericCallback< const uint8_t >& callback);

    void addMenuItem(BitmapId buttonId, BitmapId selectedImageId, uint8_t callbackId, TEXTS headline, TEXTS text, bool showDemoButton, bool active = true);

private:

    enum States
    {
        ANIMATE_TO_SINGLE_ELEMENT,
        ANIMATE_TO_ALL_ELEMENTS,
        SINGLE_ELEMENT_SHOWING,
        ALL_ELEMENTS_SHOWING
    } currentState;

    uint8_t animationCounter;
    int16_t horizontalScrollAdjustmentTotalDistance;
    int16_t horizontalScrollStartingPosition;

    uint16_t elementWidth;
    uint8_t elementsInList;
    uint8_t selectedIndex;

    static const uint8_t SIZE = 15;

    struct MenuItem
    {
        Button button;
        Image selectedImage;
        uint8_t callbackId;
        TEXTS headline;
        TEXTS text;
        bool active;
        bool showDemoButton;
    } menuItems[SIZE];

    Image backgroundItems;

    Image logo;
    Button backButton;

    Container viewPortDescriptionField;
    Container descriptionField;
    Image descriptionFieldBackground;
    Button descriptionFieldSelectButton;
    TextArea descriptionFieldHeadline;
    TextArea descriptionFieldText;

    Container menuItemContainer;
    ScrollableContainer scrollablemenuItemContainer;

    GenericCallback< const uint8_t >* menuItemSelectedCallback;
    Callback<ImageMenu, const AbstractButton&> onMenuItemSelected;
    Callback<ImageMenu, const AbstractButton&> onDescriptionFieldPressed;

    void menuItemSelectedhandler(const AbstractButton& button);
    void descriptionFieldPressedhandler(const AbstractButton& button);

    void setState(States newState);
    void animateToSingleElement();
    void animateToAllElements();
    void animateToNewSelected();
};


#endif /* IMAGEMENU_HPP_ */
