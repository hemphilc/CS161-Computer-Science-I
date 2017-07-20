#include <iostream>
#include <QApplication>
#include <QFrame>

#include "imageiolib.h"
#include "main.h"

using namespace std;


//-------------------------------------------------------------
//Custom Filters:
Image redShift(const Image& source, int shiftAmount);
Image blur(const Image& source);
Image makeGradient();
Image makeAqua();
//Corey's filters:
Image invert(const Image& source);
Image grayScaleRed(const Image& source);
Image onlyRed(const Image& source);
Image blueScreen(const Image& source);
Image eightBitLook(const Image& source);
Image sharpen(const Image& source);
Image revealSecretMessage(const Image& source, const Image& source2);
Image horizontalReflect(const Image& source);


//-------------------------------------------------------------
//Helpers and Main:
/** @brief clamp Forces a value into range 0-255
 * @param value double value to clamp
 * @return 0 if value < 0, 255 if value > 255, value otherwise
 */
byte clamp(double value) {
    value = min(value, 255.0);
    value = max(value, 0.0);
    return static_cast<byte>(value);
}



int main(int argc, char *argv[])
{
    //Setup work for the GUI that will draw the images
    QApplication myApp(argc, argv);
    QFrame mainWindow;
    QHBoxLayout mainLayout;
    mainWindow.setLayout(&mainLayout);

    //Read Original Image:

    Image crabOriginal = readImage("crab.bmp");
    displayImage(crabOriginal, "Crab Original", mainLayout);


    Image crabMessageOriginal = readImage("crabMessage.bmp");
    displayImage(crabMessageOriginal, "Crab Message Original", mainLayout);


    Image benderOriginal = readImage("Bender.bmp");
    displayImage(benderOriginal, "Bender", mainLayout);


    //Givens:


    Image redCrab = redShift(crabOriginal, 100);
    displayImage(redCrab, "Red", mainLayout);


    Image blurCrab = blur(crabOriginal);
    displayImage(blurCrab, "Blurred", mainLayout);


    Image gradient = makeGradient();
    displayImage(gradient, "Gradient", mainLayout);


    Image aqua = makeAqua();
    displayImage(aqua, "Aqua", mainLayout);

    //Corey's:

    Image invertCrab = invert(crabOriginal);
    displayImage(invertCrab, "Inverted", mainLayout);


    Image grayScaleRedCrab = grayScaleRed(crabOriginal);
    displayImage(grayScaleRedCrab, "Grayscale Red", mainLayout);


    Image onlyRedCrab = onlyRed(crabOriginal);
    displayImage(onlyRedCrab, "Only Red", mainLayout);


    Image blueScreenCrab = blueScreen(crabOriginal);
    displayImage(blueScreenCrab, "Blue Screened", mainLayout);


    Image eightBitCrab = eightBitLook(crabOriginal);
    displayImage(eightBitCrab, "8-Bit Look", mainLayout);


    Image eightBitBender = eightBitLook(benderOriginal);
    displayImage(eightBitBender, "8-Bit Look", mainLayout);


    Image sharpenCrab = sharpen(crabOriginal);
    displayImage(sharpenCrab, "Sharpened", mainLayout);


    Image revealCrabSecret = revealSecretMessage(crabMessageOriginal, crabOriginal);
    displayImage(revealCrabSecret, "Secret Message", mainLayout);


    Image horizontalReflectBender = horizontalReflect(benderOriginal);
    displayImage(horizontalReflectBender, "Horizontal Reflection", mainLayout);


    //Show the GUI... exec will keep program running until GUI window is closed
    mainWindow.show();
    return myApp.exec();
}


//-------------------------------------------------------------
//Filter Implementation

/**
 * @brief redShift copy an image but add the given amount to the red value of each pixel
 */
Image redShift(const Image& source, int shiftAmount) {
    Image newImage = {0}; //all black

    for(int i = 0; i < IMG_HEIGHT; i++) {            //for each row
        for(int j = 0; j < IMG_WIDTH; j++) {         //for each column
            //clamp function makes sure we don't go past 255 and wrap back around to 0
            newImage.data[i][j][RED] = clamp(source.data[i][j][RED] + shiftAmount);
            //blue and green are not modified
            newImage.data[i][j][BLUE] = source.data[i][j][BLUE];
            newImage.data[i][j][GREEN] = source.data[i][j][GREEN];
        }
    }

    return newImage;
}

/**
 * @brief blur Blend each pixel with its neighbors to blur the image
 */
Image blur(const Image& source) {
    Image newImage = {0}; //all black

    //skip first and last row and column... avoids stepping off edges when do neighbors
    // alternative would be special logic to handle those cases
    for(int i = 1; i < IMG_HEIGHT - 1; i++) {            //for each row
        for(int j = 1; j < IMG_WIDTH - 1; j++) {         //for each column
            for(int k = 0; k < NUM_CHANNELS; k++) {      //for each color channel
                //get value of this and 4 neighbors
                byte currentPixelValue = source.data[i][j][k];
                byte abovePixelValue = source.data[i - 1][j][k];
                byte belowPixelValue = source.data[i + 1][j][k];
                byte leftPixelValue = source.data[i][j - 1][k];
                byte rightPixelValue = source.data[i][j + 1][k];

                byte avgValue = (currentPixelValue + abovePixelValue + belowPixelValue +
                                 leftPixelValue + rightPixelValue) / 5;


                newImage.data[i][j][k] = avgValue;
            }
        }
    }

    return newImage;
}

/**
 * @brief makeGradient Make an image with black to white gradient
 */
Image makeGradient() {
    Image newImage = {0}; //all black

    for(int i = 0; i < IMG_HEIGHT; i++) {            //for each row
        for(int j = 0; j < IMG_WIDTH; j++) {         //for each column
            for(int k = 0; k < NUM_CHANNELS; k++) {  //for each color channel
                //set each color to the row index * 2... will make 0-254
                newImage.data[i][j][k] = i * 2;
            }
        }
    }
    return newImage;
}

/**
 * @brief makeAqua Make an image with pure aqua color
 */
Image makeAqua() {
    Image newImage = {0}; //all black

    for(int i = 0; i < IMG_HEIGHT; i++) {            //for each row
        for(int j = 0; j < IMG_WIDTH; j++) {         //for each column
            newImage.data[i][j][GREEN] = 128;
            newImage.data[i][j][BLUE] = 255;
            //no red needed...
        }
    }
    return newImage;
}

//Corey's Functions:

/**
 * @brief invert Sets each color pixel to be (255 - original color value)
 */
Image invert(const Image& source) {
    Image newImage = {0};

    for(int i = 0; i < IMG_HEIGHT; i++) {
        for(int j = 0; j < IMG_WIDTH; j++) {
            newImage.data[i][j][RED] = clamp(255 - (source.data[i][j][RED]));
            newImage.data[i][j][BLUE] = clamp(255 - (source.data[i][j][BLUE]));
            newImage.data[i][j][GREEN] = clamp(255 - (source.data[i][j][GREEN]));
        }
    }
    return newImage;
}

/**
 * @brief grayScaleRed Sets the blue and green values for each pixel equal to their red value
 */
Image grayScaleRed(const Image& source) {
    Image newImage = {0};

    for(int i = 0; i < IMG_HEIGHT; i++) {
        for(int j = 0; j < IMG_WIDTH; j++) {
            newImage.data[i][j][RED] = source.data[i][j][RED];
            newImage.data[i][j][BLUE] = source.data[i][j][RED];
            newImage.data[i][j][GREEN] = source.data[i][j][RED];
        }
    }
    return newImage;
}

/**
 * @brief onlyRed Sets the blue and green values for each pixel to be 0
 */
Image onlyRed(const Image& source) {
    Image newImage = {0};

    for(int i = 0; i < IMG_HEIGHT; i++) {
        for(int j = 0; j < IMG_WIDTH; j++) {
            newImage.data[i][j][RED] = source.data[i][j][RED];
            newImage.data[i][j][BLUE] = 0;
            newImage.data[i][j][GREEN] = 0;
        }
    }
    return newImage;
}

/**
 * @brief blueScreen Identifies pixels where blue values are greater than the red. If yes, turns the pixel white.
 */
Image blueScreen(const Image& source) {
    Image newImage = {0};

    for(int i = 0; i < IMG_HEIGHT; i++) {
        for(int j = 0; j < IMG_WIDTH; j++) {
            int blueValue = source.data[i][j][BLUE];
            int redValue = source.data[i][j][RED];
            if (blueValue > redValue) {
                newImage.data[i][j][RED] = 255;
                newImage.data[i][j][BLUE] = 255;
                newImage.data[i][j][GREEN] = 255;
            }
            else {
                newImage.data[i][j][RED] = source.data[i][j][RED];
                newImage.data[i][j][BLUE] = source.data[i][j][BLUE];
                newImage.data[i][j][GREEN] = source.data[i][j][GREEN];
            }
        }
    }
    return newImage;
}

/**
 * @brief eightBitLook Copies pixels that are on an even row and column into their "odd numbered" neighbors
 */
Image eightBitLook(const Image& source) {
    Image newImage = {0};

    for(int i = 1; i < IMG_HEIGHT - 1; i++) {
        for(int j = 1; j < IMG_WIDTH - 1; j++) {
            for(int k = 0; k < NUM_CHANNELS; k++) {
                if ((i % 2) == 0) {
                    if ((j % 2) == 0) {
                        byte currentPixelValue = source.data[i][j][k];
                        newImage.data[i + 1][j][k] = currentPixelValue;
                        newImage.data[i][j + 1][k] = currentPixelValue;
                        newImage.data[i + 1][j + 1][k] = currentPixelValue;
                    }
                }
            }
        }
    }
    return newImage;
}

/**
 * @brief sharpen Multiplies current pixel RGB by 5, neighbors by -1, then sums them and sets current value to sum
 */
Image sharpen(const Image& source) {
    Image newImage = {0};

    for(int i = 1; i < IMG_HEIGHT - 1; i++) {
        for(int j = 1; j < IMG_WIDTH - 1; j++) {
            for(int k = 0; k < NUM_CHANNELS; k++) {
                byte currentPixelValue = source.data[i][j][k];
                byte abovePixelValue = source.data[i - 1][j][k];
                byte belowPixelValue = source.data[i + 1][j][k];
                byte leftPixelValue = source.data[i][j - 1][k];
                byte rightPixelValue = source.data[i][j + 1][k];
                clamp(currentPixelValue *= 5);
                clamp(abovePixelValue *= -1);
                clamp(belowPixelValue *= -1);
                clamp(leftPixelValue *= -1);
                clamp(rightPixelValue *= -1);
                byte sum = clamp(currentPixelValue + abovePixelValue + belowPixelValue +
                                 leftPixelValue + rightPixelValue);


                newImage.data[i][j][k] = sum;
            }
        }
    }

    return newImage;
}

/**
 * @brief revealSecretMessage Determines if pixels from two images have the same green value. If same, sets pixel black. If different, sets pixel white.
 */
Image revealSecretMessage(const Image& source1, const Image& source2) {
    Image newImage = {0};

    for(int i = 0; i < IMG_HEIGHT; i++) {
        for(int j = 0; j < IMG_WIDTH; j++) {
            int greenValue1 = source1.data[i][j][GREEN];
            int greenValue2 = source2.data[i][j][GREEN];
            if (greenValue1 == greenValue2) {
                newImage.data[i][j][RED] = 0;
                newImage.data[i][j][BLUE] = 0;
                newImage.data[i][j][GREEN] = 0;
            }
            else {
                newImage.data[i][j][RED] = 255;
                newImage.data[i][j][BLUE] = 255;
                newImage.data[i][j][GREEN] = 255;
            }
        }
    }
    return newImage;
}

Image horizontalReflect(const Image& source) {
    Image newImage = {0};
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            newImage.data[i][IMG_WIDTH - 1 - j][RED] = source.data[i][j][RED];
            newImage.data[i][IMG_WIDTH - 1 - j][GREEN] = source.data[i][j][GREEN];
            newImage.data[i][IMG_WIDTH - 1 - j][BLUE] = source.data[i][j][BLUE];
        }
    }
    return newImage;
}
