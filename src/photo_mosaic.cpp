#include "photo_mosaic.h"

PhotoMosaic::PhotoMosaic() : Image(0, 0), pixels(NULL) {}

PhotoMosaic::PhotoMosaic(int width, int height, int ***pixels)
    : Image(width, height), pixels(pixels) {}

PhotoMosaic::~PhotoMosaic() {}
