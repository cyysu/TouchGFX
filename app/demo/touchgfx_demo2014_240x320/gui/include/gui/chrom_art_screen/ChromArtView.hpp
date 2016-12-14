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
#ifndef CHROM_ART_VIEW_HPP
#define CHROM_ART_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/chrom_art_screen/ChromArtPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/mixins/Draggable.hpp>

class ChromArtView : public View<ChromArtPresenter>
{
public:
    ChromArtView();
    virtual ~ChromArtView();
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    void updateMCULoad(uint8_t mcuLoad);
private:
    static const uint8_t CLOUD_SPACING = 100;

    enum States
    {
        ANIMATE_STARTUP,
        ANIMATE_TO_NEXT_SETUP,
        NO_ANIMATION
    } currentState;

    uint32_t animationCounter;
    uint32_t tickCounter;

    Container viewPort;

    Image background;
    Button exitButton;

    TextArea mcuLoadHeadline;
    TextAreaWithOneWildcard mcuLoadTxt;
    Unicode::UnicodeChar mcuLoadTxtbuf[5];

    Image tree;
    Draggable<Image> stLogo;
    Draggable<Image> touchGFXLogo;
    ToggleButton chromArtOnOffButton;

    Image clouds0;
    Image clouds1;

    Button nextButton;

    // The element that the next step animation should
    // use as previous element when inserting elements
    Drawable* nextInsertElement;

    Callback<ChromArtView, const AbstractButton&> onButtonPressed;
    void buttonPressedhandler(const AbstractButton& button);

    void animateStartUp();
    void animateToNextSetup();
    void animateClouds();
};

#endif // CHROM_ART_VIEW_HPP
