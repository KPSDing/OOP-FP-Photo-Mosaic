#include "bit_field_filter.h"

#include <iostream>

// using bitwise and to track whtat is the user's option
void loadCase(Image *img, int8_t option) {
    if (option & BOX_FILTER) {cout << "NONE" << endl;}
  if (option & SOBEL_GRADIENT) {cout << "NONE" << endl;}

  if(option &  CONTRAST_STRETCH) {
    img->Apply_Contrast_Stretching();
  }
  if(option & MOSAIC_FILTER) {
    img->Apply_Mosaic_Filter();
  }
}