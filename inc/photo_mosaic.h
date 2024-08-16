#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"

class PhotoMosaic : public RGBImage {

public:
  PhotoMosaic();
  PhotoMosaic(int width, int height, int ***pixels);
  ~PhotoMosaic();
};

#endif