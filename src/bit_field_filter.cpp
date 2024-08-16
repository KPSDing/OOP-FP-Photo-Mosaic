#include "bit_field_filter.h"

#include <iostream>

// using bitwise and to track whtat is the user's option
void loadCase(Image *img, int8_t option) {
  if (option & BOX_FILTER){
    img->Apply_Box_Filter();
  }
  if (option & SOBEL_GRADIENT){
    img->Apply_Sobel_Gradient();
  }
  if(option &  CONTRAST_STRETCH) {
    img->Apply_Contrast_Stretching();
  }
  if(option & MOSAIC_FILTER) {
    img->Apply_Mosaic_Filter();
  }
}
