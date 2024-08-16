#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"

class PhotoMosaic : public RGBImage {
private:
	int kernalSize_h;
	int kernalSize_w;
	vector<Image> tile_images;

public:
  PhotoMosaic();
  PhotoMosaic(int width, int height);
  ~PhotoMosaic();
  void Parting_Photo();
};

#endif