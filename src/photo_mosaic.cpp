#include "photo_mosaic.h"

#define kernalSize 32

PhotoMosaic::PhotoMosaic()
    : kernalSize_h(kernalSize), kernalSize_w(kernalSize), Image(0, 0),
      pixels(NULL) {}

PhotoMosaic::PhotoMosaic(int width, int height, int ***pixels)
    : Image(width, height), pixels(pixels) {}

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
          r_sum += pixels[y + dy][x + dx];
          pixel_count++;
        }
      }

      int avg_r = r_sum / pixel_count;

      // find the most fimilier style
    }
  }
}

int get_avg_color() const {
  int r_sum = 0;
  for (const auto &row : pixels) {
    for (auto p : row) {
      r_sum += p;
    }
  }
  return r_sum / (w * h);
}

uint8_t get_pixel(int y, int x) const { return pixels[y][x]; }