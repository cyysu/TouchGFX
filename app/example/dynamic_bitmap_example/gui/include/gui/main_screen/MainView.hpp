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
#ifndef TEMPLATE_VIEW_HPP
#define TEMPLATE_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

/**
 * Basic view showing a scaled image in the center.
 * A text is shown in the top and a play button in the lower right corner.
 */
class MainView : public View<MainPresenter>
{
public:
    /**
     * The view constructor.
     * Links the callback structure with the clicked() method.
     */
    MainView()
        : clickCallback(this, &MainView::clicked)
    {
    }
    virtual ~MainView() { }

    /**
     * Setup all widgets.
     */
    virtual void setupScreen();

    /**
     * Tear down method.
     */
    virtual void tearDownScreen();

    /**
     * Callback routine handling clicks on the screen.
     */
    void clicked(const AbstractButton& source);

    /**
     * Methods called by the Presenter.
     */
    void sdMounted(bool mounted);
    void showError(uint16_t e);
    void showBitmap(BitmapId id);

private:
    Callback<MainView, const AbstractButton&> clickCallback;
    Box background;
    TextAreaWithOneWildcard headlineTxt;
    Unicode::UnicodeChar errBuf[9];
    ScalableImage image;
    TouchArea touchArea; //full screen toucharea catching click on the screen
    Button playButton;   //play button in the lower right corner
};

#endif // TEMPLATE_VIEW_HPP
