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
#include <gui/nxp_and_touchgfx_screen/NXPAndTouchGFXView.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/FrontendApplication.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>


NXPAndTouchGFXView::NXPAndTouchGFXView() :
    DemoView(),
    currentState(NO_ANIMATION),
    animationCounter(0),
    navigationPanel(EAST),
    onAnimateButtonClicked(this, &NXPAndTouchGFXView::animateButtonClickedHandler)
{
}

NXPAndTouchGFXView::~NXPAndTouchGFXView()
{
}

void NXPAndTouchGFXView::setupScreen()
{
    // configuration of 4 pages
    pageBitmaps[0] = PageBitmaps(BITMAP_NXP_TOUCHGFX_IMAGE_ID, BITMAP_NXP_TOUCHGFX_TEXT_TOP_ID, BITMAP_NXP_TOUCHGFX_TEXT_ID);
    pageBitmaps[1] = PageBitmaps(BITMAP_NXP_KEIL_IMAGE_ID,     BITMAP_NXP_KEIL_TEXT_TOP_ID,     BITMAP_NXP_KEIL_TEXT_ID);
    pageBitmaps[2] = PageBitmaps(BITMAP_NXP_FDI_IMAGE_ID,      BITMAP_NXP_FDI_TEXT_TOP_ID,      BITMAP_NXP_FDI_TEXT_ID);
    pageBitmaps[3] = PageBitmaps(BITMAP_NXP_EMBEDDED_IMAGE_ID, BITMAP_NXP_EMBEDDED_TEXT_TOP_ID, BITMAP_NXP_EMBEDDED_TEXT_ID);

    // image panel
    imageGradient.setBitmap(Bitmap(BITMAP_NXP_IMAGE_GRADIENT_ID));
    imageGradient.setXY(0, 0);
    imageBackground.setBitmap(Bitmap(BITMAP_NXP_IMAGE_BOX_BACKGROUND_ID));
    imageBackground.setXY(imageGradient.getWidth(), 0);
    imagePanel.setPosition(backButton.getWidth(), 0, imageGradient.getWidth() + imageBackground.getWidth(), imageGradient.getHeight());
    currentImage.setBitmap(Bitmap(pageBitmaps[0].image));
    currentImage.setXY(imageGradient.getWidth(), 0);
    imagePanel.add(imageBackground);
    imagePanel.add(imageGradient);
    imagePanel.add(currentImage);

    textboxGradient.setBitmap(Bitmap(BITMAP_NXP_TEXTBOX_GRADIENT_ID));
    textboxGradient.setXY(imagePanel.getX() + imagePanel.getWidth(), 0);

    // text top panel
    currentTextTop.setBitmap(Bitmap(pageBitmaps[0].textTop));
    textTopPanel.setPosition(textboxGradient.getX() + textboxGradient.getWidth(), 0, currentTextTop.getWidth(), currentTextTop.getHeight());
    currentTextTop.setXY(0, 0);
    nextTextTop.setXY(textTopPanel.getWidth(), 0);
    textTopPanel.add(currentTextTop);
    textTopPanel.add(nextTextTop);
    textTopBackground.setBitmap(Bitmap(BITMAP_NXP_TEXT_TOP_BACKGROUND_ID));
    textTopBackground.setXY(textTopPanel.getX(), textTopPanel.getY());

    // text box
    textboxBackground.setBitmap(Bitmap(BITMAP_NXP_TEXTBOX_BACKGROUND_ID));
    textboxBackground.setXY(textTopPanel.getX(), textTopPanel.getHeight());
    currentTextBox.setBitmap(Bitmap(pageBitmaps[0].text));
    textBoxViewPort.setPosition(textTopPanel.getX(), textTopPanel.getHeight(), textboxBackground.getWidth(), textboxBackground.getHeight());
    currentTextBox.setXY(0, 0);
    nextTextBox.setXY(textBoxViewPort.getWidth(), 0);

    textBoxViewPort.setScrollbarsVisible(true);
    textBoxViewPort.enableVerticalScroll(true);
    textBoxViewPort.enableHorizontalScroll(false);
    textBoxViewPort.setScrollbarsColor(Color::getColorFrom24BitRGB(0xA3, 0xA3, 0xA3));
    textBoxViewPort.add(currentTextBox);
    textBoxViewPort.add(nextTextBox);

    // navigation panel (right side, bottom)
    leftButton.setBitmaps(Bitmap(BITMAP_NXP_BUTTON_LEFT_ID), Bitmap(BITMAP_NXP_BUTTON_LEFT_PRESSED_ID));
    buttonGradient.setBitmap(Bitmap(BITMAP_NXP_BUTTON_MIDDLE_GRADIENT_ID));
    rightButton.setBitmaps(Bitmap(BITMAP_NXP_BUTTON_RIGHT_ID), Bitmap(BITMAP_NXP_BUTTON_RIGHT_PRESSED_ID));

    navigationPanel.add(leftButton);
    navigationPanel.add(buttonGradient);
    navigationPanel.add(rightButton);
    leftButton.setAction(onAnimateButtonClicked);
    rightButton.setAction(onAnimateButtonClicked);
    navigationPanel.setXY(textboxGradient.getX(), textboxGradient.getHeight());

    dotIndicator.setNumberOfDots(NUMBER_OF_PAGES);
    dotIndicator.setBitmaps(Bitmap(BITMAP_NXP_DOT_NORMAL_ID), Bitmap(BITMAP_NXP_DOT_PRESSED_ID));
    dotIndicator.setXY(navigationPanel.getX() + (navigationPanel.getWidth() - dotIndicator.getWidth()) / 2, navigationPanel.getY());

    pageShowing = 0;
    updateAnimationButtonStates();

    add(textboxBackground);
    add(textTopBackground);

    add(textBoxViewPort);
    add(imagePanel);
    add(textTopPanel);
    add(textboxGradient);
    add(navigationPanel);
    add(dotIndicator);
}

void NXPAndTouchGFXView::tearDownScreen()
{
}

void NXPAndTouchGFXView::handleTickEvent()
{
    if (currentState == ANIMATE_LEFT ||
            currentState == ANIMATE_RIGHT)
    {
        animate();
    }
}

void NXPAndTouchGFXView::updateAnimationButtonStates()
{
    leftButton.setTouchable(currentState == NO_ANIMATION);
    rightButton.setTouchable(currentState == NO_ANIMATION);
}

void NXPAndTouchGFXView::animateButtonClickedHandler(const AbstractButton& button)
{
    if (&button == &leftButton)
    {
        currentState = ANIMATE_LEFT;

        nextPageShowing = (pageShowing + NUMBER_OF_PAGES - 1) % NUMBER_OF_PAGES;
    }
    else if (&button == &rightButton)
    {
        currentState = ANIMATE_RIGHT;

        nextPageShowing = (pageShowing + 1) % NUMBER_OF_PAGES;
    }
    dotIndicator.setHighlightPosition(nextPageShowing);

    int8_t direction = (currentState == ANIMATE_RIGHT) ? 1 : -1;
    nextTextTop.setBitmap(Bitmap(pageBitmaps[nextPageShowing].textTop));
    nextTextTop.setXY(direction * textTopPanel.getWidth(), 0);
    nextTextBox.setBitmap(Bitmap(pageBitmaps[nextPageShowing].text));
    nextTextBox.setXY(direction * textBoxViewPort.getWidth(), 0);

    // store x positions used by animation method
    animationTextTopStartPositionX = currentTextTop.getX();
    animationNextTextTopStartPositionX = nextTextTop.getX();

    animationTextBoxStartPositionX = currentTextBox.getX();
    animationNextTextBoxStartPositionX = nextTextBox.getX();

    leftButton.setTouchable(false);
    rightButton.setTouchable(false);
    dotIndicator.invalidate();
}

void NXPAndTouchGFXView::animate()
{
    uint8_t duration = 26; // duration for sliding an image in or out
    uint8_t alphaDelay = 10; // alpha animation of the image is delayed (sliding animation starts before alpha animation)
    int8_t animateDirection = (currentState == ANIMATE_LEFT) ? 1 : -1;

    if (animationCounter > duration * 2)
    {
        // animation completed
        currentState = NO_ANIMATION;
        animationCounter = 0;
        pageShowing = nextPageShowing;
        updateAnimationButtonStates();

        currentTextTop.setBitmap(Bitmap(pageBitmaps[pageShowing].textTop));
        currentTextTop.setXY(textTopPanel.getWidth() - currentTextTop.getWidth(), 0);
        currentTextTop.invalidate();
        nextTextTop.setXY(textTopPanel.getWidth(), 0);

        currentTextBox.setBitmap(Bitmap(pageBitmaps[pageShowing].text));
        currentTextBox.setXY(textBoxViewPort.getWidth() - currentTextBox.getWidth(), 0);
        currentTextBox.invalidate();
        nextTextBox.setXY(textBoxViewPort.getWidth(), 0);
    }
    else if (animationCounter > duration)
    {
        if (animationCounter > duration + alphaDelay)
        {
            // animate alpha value of the image
            currentImage.setBitmap(Bitmap(pageBitmaps[nextPageShowing].image));
            uint8_t alpha = static_cast<uint8_t>(EasingEquations::linearEaseNone(animationCounter - duration - alphaDelay, 0, 255, duration - alphaDelay));
            currentImage.setAlpha(alpha);
            currentImage.invalidate();
        }
        // animation of new page entering screen
        nextTextTop.moveTo(animationNextTextTopStartPositionX + animateDirection * EasingEquations::cubicEaseInOut(animationCounter - duration, 0, nextTextTop.getWidth(), duration), 0);
        nextTextBox.moveTo(animationNextTextBoxStartPositionX + animateDirection * EasingEquations::cubicEaseInOut(animationCounter - duration, 0, nextTextBox.getWidth(), duration), 0);
        animationCounter++;
    }
    else
    {
        if (animationCounter > alphaDelay)
        {
            // animate alpha value of the image
            uint8_t alpha = static_cast<uint8_t>(EasingEquations::linearEaseNone(animationCounter - alphaDelay, 255, -255, duration - alphaDelay));
            currentImage.setAlpha(alpha);
            currentImage.invalidate();
        }
        // animation of current page leaving screen
        currentTextTop.moveTo(animationTextTopStartPositionX + animateDirection * EasingEquations::cubicEaseInOut(animationCounter, 0, currentTextTop.getWidth(), duration), 0);
        currentTextBox.moveTo(animationTextBoxStartPositionX + animateDirection * EasingEquations::cubicEaseInOut(animationCounter, 0, currentTextBox.getWidth(), duration), currentTextBox.getY());
        animationCounter++;
    }
}
