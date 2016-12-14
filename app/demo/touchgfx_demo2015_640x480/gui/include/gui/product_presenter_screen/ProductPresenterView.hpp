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
#ifndef PRODUCT_PRESENTER_VIEW_HPP
#define PRODUCT_PRESENTER_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/product_presenter_screen/ProductPresenterPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <gui/product_presenter_screen/FeaturePoster.hpp>
#include <gui/common/SwipeContainer.hpp>
#include <gui/common/CollapsibleMenu.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class ProductPresenterView : public DemoView<ProductPresenterPresenter>
{
public:
    ProductPresenterView();
    virtual ~ProductPresenterView();

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void screenSaverMinorTick();

private:
    static const uint8_t NUMBER_OF_POSTERS = 3;

    LANGUAGES languages[NUMBER_OF_LANGUAGES];
    BitmapId inactiveLanguageButtons[NUMBER_OF_LANGUAGES];

    Image background;
    Image paperOverlay;

    FeaturePoster poster[NUMBER_OF_POSTERS];
    Container posters[NUMBER_OF_POSTERS];

    MoveAnimator<SwipeContainer> posterSwipeContainer;
    CollapsibleMenu languageSelector;
    Button activateLanguageSelectorButton;

    int screenSaverCounter;

    Callback<ProductPresenterView, const AbstractButton&> onButtonPressed;
    Callback<ProductPresenterView, const CollapsibleMenu&, const bool> languageSelectorStateChanged;

    void buttonPressedHandler(const AbstractButton& button);
    void languageSelectorStateChangedHandler(const CollapsibleMenu& menu, const bool isExpanded);

    void setLanguage();
};

#endif // PRODUCT_PRESENTER_VIEW_HPP
