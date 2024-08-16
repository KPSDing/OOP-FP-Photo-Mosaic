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

void GrayImage::Apply_Box_Filter(){
    cout << "Applying Gray Box Filter" << endl;

    // Temporary array to store the filtered image
    int **temp = new int*[h];
    for (int i = 0; i < h; i++) {
        temp[i] = new int[w];
    }

    // Box filter kernel (simple averaging)
    int KERNELSIZE = 3;
    int box_fliter_kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    // Sum of kernel elements
    int denominator = 9;

    for (int i = 1; i < h - 1; i++) {
        for (int j = 1; j < w - 1; j++) {
            int gray = 0;

            for (int ki = 0; ki < KERNELSIZE ; ki++) {
                for (int kj = 0; kj < KERNELSIZE; kj++) {
                    int ni = i + ki - 1;
                    int nj = j + kj - 1;

                    gray += pixels[ni][nj] * box_fliter_kernel[ki * KERNELSIZE + kj];
                }
            }

            // Normalize
            gray /= denominator;

            // Clamp to valid range
            gray = min(255, max(0, gray));

            // Store the result in the temporary array
            temp[i][j] = gray;
        }
    }

    // Copy the temp array back to the original pixels
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i][j] = temp[i][j];
        }
    }

    // Free temp array memory
    for (int i = 0; i < h; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}

void GrayImage::Apply_Sobel_Gradient(){
    cout << "Applying Gray Sobel Gradient" << endl;

    // Temporary arrays to store gradient values
    int **gradient_x = new int*[h];
    int **gradient_y = new int*[h];
    int **edge = new int*[h];
    for (int i = 0; i < h; i++) {
        gradient_x[i] = new int[w]();
        gradient_y[i] = new int[w]();
        edge[i] = new int[w]();
    }

    int sobel_x_kernel[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobel_y_kernel[3][3] = { {-1, -2, -1}, { 0,  0,  0}, { 1,  2,  1}};

    // Apply Sobel filters
    for (int i = 1; i < h - 1; i++) {
        for (int j = 1; j < w - 1; j++) {
            int gx = 0, gy = 0;

            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    int ni = i + ki - 1;
                    int nj = j + kj - 1;
                    gx += pixels[ni][nj] * sobel_x_kernel[ki][kj];
                    gy += pixels[ni][nj] * sobel_y_kernel[ki][kj];
                }
            }

            // Calculate gradient magnitude
            int magnitude = static_cast<int>(sqrt(gx * gx + gy * gy));
            
            // Normalize and clamp
            edge[i][j] = min(0xff, max(0, magnitude));
        }
    }

    // Copy the edge data back to the original pixels
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pixels[i][j] = edge[i][j];
        }
    }

    // Free temporary arrays
    for (int i = 0; i < h; i++) {
        delete[] gradient_x[i];
        delete[] gradient_y[i];
        delete[] edge[i];
    }
    delete[] gradient_x;
    delete[] gradient_y;
    delete[] edge;
}

void GrayImage::Apply_Contrast_Stretching() {
  cout << "Applying Gray Contrast Stretching Filter" << endl;
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
  cout << "Applying Gray Mosaic Filter" << endl;
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
