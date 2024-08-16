#include "photo_mosaic.h"

#define kernalSize 32

PhotoMosaic::PhotoMosaic()
    : kernalSize_h(kernalSize), kernalSize_w(kernalSize) {}

PhotoMosaic::PhotoMosaic(int width, int height)
    : RGBImage(width, height), kernalSize_h(kernalSize), kernalSize_w(kernalSize) {}

PhotoMosaic::~PhotoMosaic() { cout << "Destructor PhotoMosaic" << endl; }

void PhotoMosaic::Parting_Photo() {

  for (int y = 0; y < this->h; y += kernalSize) {
    for (int x = 0; x < this->w; x += kernalSize) {
      // calculate avg color in every block
      int r_sum = 0, g_sum = 0, b_sum = 0;
      int pixel_count = 0;

      for (int dy = 0; dy < kernalSize && y + dy < h; ++dy) {
        for (int dx = 0; dx < kernalSize && x + dx < w; ++dx) {
          // if pixels stored as RGB style
          r_sum += pixels[y + dy][x + dx][0];
		  r_sum += pixels[y + dy][x + dx][1];
		  r_sum += pixels[y + dy][x + dx][2];
          pixel_count++;
        }
      }

      int avg_r = r_sum / pixel_count / 3;

      // find the most fimilier style
    }
  }
}
