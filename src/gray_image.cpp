#include "gray_image.h"

GrayImage::GrayImage() : Image(0, 0), pixels(nullptr) {}

GrayImage::GrayImage(int width, int height, int **pixels)
    : Image(width, height), pixels(pixels) {}

GrayImage::~GrayImage() {}

bool GrayImage::LoadImage(string filename) {
  this->pixels = this->data_loader.Load_Gray(filename, &w, &h); // data_loader
  return (pixels != NULL);
}

void GrayImage::DumpImage(string filename) {
  this->data_loader.Dump_Gray(w, h, this->pixels, filename); // data_loader
  return;
}

void GrayImage::Display_X_Server() {
  this->data_loader.Display_Gray_X_Server(w, h, this->pixels);
  return;
}

void GrayImage::Display_ASCII() {
  this->data_loader.Display_Gray_ASCII(w, h, this->pixels);
  return;
}

void GrayImage::Display_CMD() {
  string filename = "temp.png"; // temp image name
  this->data_loader.Dump_Gray(w, h, this->pixels,
                              filename); // dump the temp image
  this->data_loader.Display_Gray_CMD(filename);
  string del = "rm" + filename;
  system(del.c_str());
  return;
}