#include "gray_image.h"

GrayImage::GrayImage() : Image(0, 0), pixels(nullptr) {}

GrayImage::GrayImage(int width, int height, int **pixels)
    : Image(width, height), pixels(pixels) {}

GrayImage::~GrayImage() {}

bool GrayImage::LoadImage(string filename) {
  this->pixels =
      this->data_loader.Load_Gray(filename, &this->w, &this->h); // data_loader
  return (pixels != NULL);
}

void GrayImage::DumpImage(string filename) {
  this->data_loader.Dump_Gray(this->w, this->h, this->pixels,
                              filename); // data_loader
  return;
}

void GrayImage::Display_X_Server() {
  this->data_loader.Display_Gray_X_Server(this->w, this->h, this->pixels);
  return;
}

void GrayImage::Display_ASCII() {
  this->data_loader.Display_Gray_ASCII(this->w, this->h, this->pixels);
  return;
}

void GrayImage::Display_CMD() {
  string filename = "temp.png"; // temp image name
  this->data_loader.Dump_Gray(this->w, this->h, this->pixels,
                              filename); // dump the temp image
  this->data_loader.Display_Gray_CMD(filename);
  string del = "rm" + filename;
  system(del.c_str());
  return;
}

void GrayImage::Apply_Contrast_Stretching() {
  cout << "Applying Contrast Stretching Filter" << endl;
  static int minVal = 255, maxVal = 0;

  for (int i = 0; i < this->h; ++i) { // triverse all pixels in the picture
    for (int j = 0; j < this->w; ++j) {
      if (pixels[i][j] < minVal)
        minVal = pixels[i][j]; // find min pixel
      if (pixels[i][j] > maxVal)
        maxVal = pixels[i][j]; // find max pixel
    }
  }

  for (int i = 0; i < this->h; ++i) {
    for (int j = 0; j < this->w; ++j) {
      pixels[i][j] =
          255 * (pixels[i][j] - minVal) / (maxVal - minVal); // refresh pixels
    }
  }
}

void GrayImage::Apply_Mosaic_Filter() {
  cout << "Applying Mosaic Filter" << endl;
  int blockSize = 10;
  cout << "Enter a blockSize (between 3 and 10): ";
  cin >> blockSize;
  while (blockSize < 3 || blockSize > 10) {
    cout << "Invalid input. Please enter a value between 3 and 10: ";
    cin >> blockSize;
  }

  for(int i = 0; i < this->h; i += blockSize){
    for(int j = 0; j < this->w; j += blockSize){
      int sum = 0;
      int count = 0;
      for(int ii = 0; ii < blockSize; ii++){
        for(int jj = 0; jj < blockSize; jj++){
          sum += pixels[i+ii][j+jj]; // sum all pixels in the blockSize
          count++;
        }
      }
      double avg = sum/count; // find the avg pixels in the blockSize
      for(int ii = 0; ii < blockSize; ii++){
        for(int jj = 0; jj < blockSize; jj++){
          pixels[i+ii][j+jj] = avg;
        }
      }
    }
  }
}