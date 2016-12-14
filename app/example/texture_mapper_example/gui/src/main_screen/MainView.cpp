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
#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

MainView::MainView() :
    xAngle3D(0.0f),
    yAngle3D(0.0f),
    zAngle3D(0.0f),
    deltaXangle3D(0.032f),
    deltaYangle3D(0.029f),
    deltaZangle3D(0.027f),
    zAngle2D(0.0f),
    deltaZangle2D(0.019f)
{

}

void MainView::setupScreen()
{
    // Setup background box
    // Only visible on displays larger than the backgroundImage (480x272)
    backgroundBox.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));
    backgroundBox.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);

    // Setup the background image
    backgroundImage.setBitmap(Bitmap(BITMAP_BG_ID));
    backgroundImage.setXY(0, 0);

    // Setup the texture mapper image that does 3D rotation
    textureMapperImage3D.setBitmap(Bitmap(BITMAP_IMAGE00_ID));

    // Extra space for the image to rotate in
    int borderWidth = 40;
    int borderHeight = 40;

    int imageWidth = textureMapperImage3D.getBitmap().getWidth();
    int imageHeight = textureMapperImage3D.getBitmap().getHeight();

    // Position the texture mapper image on the screen
    textureMapperImage3D.setXY(40, 40);

    // Set the width and height of the texture mapper image widget, including
    // space for the image to rotate (border)
    textureMapperImage3D.setWidth(imageWidth + borderWidth * 2);
    textureMapperImage3D.setHeight(imageHeight + borderHeight * 2);

    // Place the actual bitmap inside the texture mapper image.
    textureMapperImage3D.setBitmapPosition(borderWidth, borderHeight);

    // Set the camera distance which is the distance to the image in the z direction.
    // This has an effect of the perspective ratio of the image when it rotates
    textureMapperImage3D.setCameraDistance(300.0f);

    // Set the center of rotation of the texture mapper image (here it is the center of the image)
    textureMapperImage3D.setOrigo(textureMapperImage3D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage3D.getBitmapPositionY() + (imageHeight / 2), textureMapperImage3D.getCameraDistance());

    // Place the camera/eye of the viewer relative the image (here it is the center of the image)
    textureMapperImage3D.setCamera(textureMapperImage3D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage3D.getBitmapPositionY() + (imageHeight / 2));

    // Set the rendering algorithm. Here the fast lower image quality NEAREST_NEIGHBOR algorithm is chosen.
    // Another option is the slower but high image quality Bilinear Interpolation algorithm.
    textureMapperImage3D.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);

    // Setup the texture mapper image that does 2D rotation
    // Similar to the setup of the 3D rotating image above.
    textureMapperImage2D.setBitmap(Bitmap(BITMAP_IMAGE01_ID));

    imageWidth = textureMapperImage2D.getBitmap().getWidth();
    imageHeight = textureMapperImage2D.getBitmap().getHeight();

    textureMapperImage2D.setXY(240, 40);
    textureMapperImage2D.setWidth(imageWidth + borderWidth * 2);
    textureMapperImage2D.setHeight(imageHeight + borderHeight * 2);
    textureMapperImage2D.setBitmapPosition(borderWidth, borderHeight);
    textureMapperImage2D.setCameraDistance(300.0f);
    textureMapperImage2D.setOrigo(textureMapperImage2D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage2D.getBitmapPositionY() + (imageHeight / 2), textureMapperImage2D.getCameraDistance());
    textureMapperImage2D.setCamera(textureMapperImage2D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage2D.getBitmapPositionY() + (imageHeight / 2));
    textureMapperImage2D.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);


    add(backgroundBox);
    add(backgroundImage);
    add(textureMapperImage3D);
    add(textureMapperImage2D);
}

void MainView::handleTickEvent()
{
    // Update angle values
    xAngle3D += deltaXangle3D;
    yAngle3D += deltaYangle3D;
    zAngle3D += deltaZangle3D;

    zAngle2D += deltaZangle2D;

    // Update the images with the new angles
    // The image is automatically invalidated (the optimal minimal area).
    // If any of the set..() methods (e.g. setOrigo, setCamera, setRenderingAlgorithm...) are used
    // remember to manually invalidate the image afterwards (textureMapperImage2D.invalidate()).
    textureMapperImage3D.updateAngles(xAngle3D, yAngle3D, zAngle3D);
    textureMapperImage2D.updateAngles(0.0F, 0.0F, zAngle2D);
}

