#ifndef MAIN_H
#define MAIN_H


//A byte will store values from 0-255 (alias for unsigned char)
typedef unsigned char byte;

//Size related constants
const int IMG_HEIGHT = 128;
const int IMG_WIDTH = 128;
const int NUM_CHANNELS = 3;

//Define RED=0, GREEN=1, BLUE=2
enum color_channel {RED, GREEN, BLUE};


/** @brief The Image struct wraps a 3D array of bytes into a package
 *
 *  First two dimensions represent rows and columns of pixels
 *  Third dimension represents color channel of a pixel
 */
struct Image {
    byte data[IMG_HEIGHT][IMG_WIDTH][NUM_CHANNELS];
};

#endif // MAIN_H
