#include "image.h"

Image::Image(int width, int height) : w(width), h(height) {}

Image::~Image() {
  // cout << "~Image()\n";
}

// get the width of the picture
int Image::get_w() { return w; }

// get the height of the picture
int Image::get_h() { return h; }