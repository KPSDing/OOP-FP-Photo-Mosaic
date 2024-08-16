#ifndef _BIT_FIELD_FILTER_H_
#define _BIT_FIELD_FILTER_H_

//using bitfield to not to force user to passing all of the arguments
//using bitwise or to passing the options
//using bitwise and to get the info of the bitfield

#include <stdio.h>
#include <stdint.h>

#define CASE_ONE    0b00000001
#define CASE_TWO    0b00000010
#define CASE_THREE  0b00000100
#define CASE_FOUR   0b00001000

void loadCase(int8_t option);
void printAndResult(int32_t option)

// Step 2

// void Apply_Box_Fileter(Image* img);
// void Apply_Sobel_Gradient(Image* img);

void Apply_Contrast_Stretching(Image* img);
void Apply_Mosaic_filter(Image* img);


#endif