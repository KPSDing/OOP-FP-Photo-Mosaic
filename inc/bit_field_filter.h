#ifndef _BIT_FIELD_FILTER_H_
#define _BIT_FIELD_FILTER_H_

// using bitfield to not to force user to passing all of the arguments
// using bitwise or to passing the options
// using bitwise and to get the info of the bitfield

#include "image.h"

#include <stdint.h>
#include <stdio.h>

#define BOX_FILTER 0b00000001
#define SOBEL_GRADIENT 0b00000010
#define CONTRAST_STRETCH 0b00000100 // Contrast Stretching
#define MOSAIC_FILTER 0b00001000     // Mosaic_Filter

void loadCase(Image *img, int8_t option);
// void printAndResult(int32_t option);

// Step 2

// void Apply_Box_Fileter(Image* img); // Case1
// void Apply_Sobel_Gradient(Image* img); // Case2

// void Apply_Contrast_Stretching(Image* img); // Case3
// void Apply_Mosaic_Filter(Image* img); // Case4

#endif