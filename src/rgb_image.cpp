#include "rgb_image.h"

// Constructor/Destructor
RGBImage::RGBImage() : Image(0, 0), pixels(NULL) {
  // Initialize Image w=0, h=0
  // Initialize pixels = NULL
}

RGBImage::RGBImage(int width, int height)
    : Image(width, height){
  // Assign Image w=width, h=height
}


RGBImage::RGBImage(int width, int height, int ***pixels)
    : Image(width, height), pixels(pixels) {
  // Assign Image w=width, h=height
  // Assign pixels = pixels
}

RGBImage::~RGBImage() {
  // Free memory for pixels
  if (pixels) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        delete[] pixels[i][j];
      }
      delete[] pixels[i];
    }
    delete[] pixels;
  }
}

// Override Base class vitual function(all public):
bool RGBImage::LoadImage(string filename) {
  pixels = data_loader.Load_RGB(filename, &w, &h);
  return (pixels != NULL);
}

void RGBImage::DumpImage(string filename) {
  data_loader.Dump_RGB(w, h, pixels, filename);
  return;
}

void RGBImage::Display_X_Server() {
  data_loader.Display_RGB_X_Server(w, h, pixels);
  return;
}

void RGBImage::Display_ASCII() {
  data_loader.Display_RGB_ASCII(w, h, pixels);
  return;
}

void RGBImage::Display_CMD() {
  string filename = "temp.png"; // temp image name

  // Dump the temp image
  data_loader.Dump_RGB(w, h, pixels, filename);

  // Display the image using command line
  data_loader.Display_RGB_CMD(filename);

  // Prepare the command to delete the file
  string del = "rm " + filename;

  // Execute the command to delete the file
  int result = system(del.c_str());
  if (result != 0) {
    // Handle the error if needed
    cerr << "Error: Failed to delete " << filename << endl;
  }

  return;
}

void RGBImage::Apply_Box_Filter() {
  cout << "Applying RGB Box Filter" << endl;
  // Temporary array to store the filtered image
  int ***temp = new int **[h];
  for (int i = 0; i < h; i++) {
    temp[i] = new int *[w];
    for (int j = 0; j < w; j++) {
      temp[i][j] = new int[RGBCHANNEL]; // R, G, B channels
    }
  }

  // Box filter kernel (simple averaging)
  int KERNELSIZE = 3;
  // Sum of kernel elements
  int denominator = 9;

  for (int i = 1; i < h - 1; i++) {
    for (int j = 1; j < w - 1; j++) {
      int red = 0, green = 0, blue = 0;

      for (int ki = 0; ki < KERNELSIZE; ki++) {
        for (int kj = 0; kj < KERNELSIZE; kj++) {
          int ni = i + ki - 1;
          int nj = j + kj - 1;

          red += pixels[ni][nj][RED] * box_fliter_kernel[ki * KERNELSIZE + kj];
          green +=
              pixels[ni][nj][GREEN] * box_fliter_kernel[ki * KERNELSIZE + kj];
          blue +=
              pixels[ni][nj][BLUE] * box_fliter_kernel[ki * KERNELSIZE + kj];
        }
      }

      // Normalize
      red /= denominator;
      green /= denominator;
      blue /= denominator;

      // Clamp to valid range
      red = min(0xff, max(0, red));
      green = min(0xff, max(0, green));
      blue = min(0xff, max(0, blue));

      // Store the result in the temporary array
      temp[i][j][RED] = red;
      temp[i][j][GREEN] = green;
      temp[i][j][BLUE] = blue;
    }
  }

  // Copy the temp array back to the original pixels
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      pixels[i][j][RED] = temp[i][j][RED];
      pixels[i][j][GREEN] = temp[i][j][GREEN];
      pixels[i][j][BLUE] = temp[i][j][BLUE];
    }
  }

  // Free temp array memory
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      delete[] temp[i][j];
    }
    delete[] temp[i];
  }
  delete[] temp;
}

void RGBImage::Apply_Sobel_Gradient() {
  cout << "Applying RGB Sobel Gradient" << endl;

  // Temporary arrays for gradients
  int ***gradient_x_r = new int **[h];
  int ***gradient_y_r = new int **[h];
  int ***gradient_x_g = new int **[h];
  int ***gradient_y_g = new int **[h];
  int ***gradient_x_b = new int **[h];
  int ***gradient_y_b = new int **[h];
  int **edge_r = new int *[h];
  int **edge_g = new int *[h];
  int **edge_b = new int *[h];
  int **edge = new int *[h];

  for (int i = 0; i < h; i++) {
    gradient_x_r[i] = new int *[w]();
    gradient_y_r[i] = new int *[w]();
    gradient_x_g[i] = new int *[w]();
    gradient_y_g[i] = new int *[w]();
    gradient_x_b[i] = new int *[w]();
    gradient_y_b[i] = new int *[w]();
    edge_r[i] = new int[w]();
    edge_g[i] = new int[w]();
    edge_b[i] = new int[w]();
    edge[i] = new int[w]();
  }

  int sobel_x_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int sobel_y_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  // Apply Sobel filters to each color channel
  for (int i = 1; i < h - 1; i++) {
    for (int j = 1; j < w - 1; j++) {
      int gx_r = 0, gy_r = 0;
      int gx_g = 0, gy_g = 0;
      int gx_b = 0, gy_b = 0;

      for (int ki = 0; ki < 3; ki++) {
        for (int kj = 0; kj < 3; kj++) {
          int ni = i + ki - 1;
          int nj = j + kj - 1;

          gx_r += pixels[ni][nj][RED] * sobel_x_kernel[ki][kj];
          gy_r += pixels[ni][nj][RED] * sobel_y_kernel[ki][kj];

          gx_g += pixels[ni][nj][GREEN] * sobel_x_kernel[ki][kj];
          gy_g += pixels[ni][nj][GREEN] * sobel_y_kernel[ki][kj];

          gx_b += pixels[ni][nj][BLUE] * sobel_x_kernel[ki][kj];
          gy_b += pixels[ni][nj][BLUE] * sobel_y_kernel[ki][kj];
        }
      }

      // Calculate gradient magnitude for each channel
      int magnitude_r = static_cast<int>(sqrt(gx_r * gx_r + gy_r * gy_r));
      int magnitude_g = static_cast<int>(sqrt(gx_g * gx_g + gy_g * gy_g));
      int magnitude_b = static_cast<int>(sqrt(gx_b * gx_b + gy_b * gy_b));

      // Normalize and clamp
      edge_r[i][j] = min(255, max(0, magnitude_r));
      edge_g[i][j] = min(255, max(0, magnitude_g));
      edge_b[i][j] = min(255, max(0, magnitude_b));

      // Combine channels into final edge image
      edge[i][j] = (edge_r[i][j] + edge_g[i][j] + edge_b[i][j]) /
                   3; // Averaging the channels for simplicity
    }
  }

  // Copy edge results back to the image pixels
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      pixels[i][j][RED] = edge[i][j];
      pixels[i][j][GREEN] = edge[i][j];
      pixels[i][j][BLUE] = edge[i][j];
    }
  }

  // Free temporary arrays
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      delete[] gradient_x_r[i][j];
      delete[] gradient_y_r[i][j];
      delete[] gradient_x_g[i][j];
      delete[] gradient_y_g[i][j];
      delete[] gradient_x_b[i][j];
      delete[] gradient_y_b[i][j];
    }
    delete[] gradient_x_r[i];
    delete[] gradient_y_r[i];
    delete[] gradient_x_g[i];
    delete[] gradient_y_g[i];
    delete[] gradient_x_b[i];
    delete[] gradient_y_b[i];
    delete[] edge_r[i];
    delete[] edge_g[i];
    delete[] edge_b[i];
    delete[] edge[i];
  }
  delete[] gradient_x_r;
  delete[] gradient_y_r;
  delete[] gradient_x_g;
  delete[] gradient_y_g;
  delete[] gradient_x_b;
  delete[] gradient_y_b;
  delete[] edge_r;
  delete[] edge_g;
  delete[] edge_b;
  delete[] edge;
}

void RGBImage::Apply_Contrast_Stretching() {
  cout << "Applying RGB Contrast Stretching Filter" << endl;
  static int minVal = 255, maxVal = 0;
  for (int k = 0; k < 3; ++k) {
    for (int i = 0; i < this->h; ++i) { // triverse all pixels in the picture
      for (int j = 0; j < this->w; ++j) {
        if (pixels[i][j][k] < minVal)
          minVal = pixels[i][j][k]; // find min pixel
        if (pixels[i][j][k] > maxVal)
          maxVal = pixels[i][j][k]; // find max pixel
      }
    }

    for (int i = 0; i < this->h; ++i) {
      for (int j = 0; j < this->w; ++j) {
        pixels[i][j][k] = 255 * (pixels[i][j][k] - minVal) /
                          (maxVal - minVal); // refresh pixels
      }
    }
  }
}

void RGBImage::Apply_Mosaic_Filter() {
  cout << "Applying RGB Mosaic Filter" << endl;
  int blockSize = 10;
  cout << "Enter a blockSize (between 2 and 6): ";
  cin >> blockSize;
  while (blockSize < 2 || blockSize > 6) {
    cout << "Invalid input. Please enter a value between 2 and 6: ";
    cin >> blockSize;
  }

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < this->h; i += blockSize) {
      for (int j = 0; j < this->w; j += blockSize) {
        int sum = 0;
        int count = 0;
        for (int ii = 0; ii < blockSize; ii++) {
          for (int jj = 0; jj < blockSize; jj++) {
            sum += pixels[i + ii][j + jj][k]; // sum all pixels in the blockSize
            count++;
          }
        }
        double avg = sum / count; // find the avg pixels in the blockSize
        for (int ii = 0; ii < blockSize; ii++) {
          for (int jj = 0; jj < blockSize; jj++) {
            pixels[i + ii][j + jj][k] = avg;
          }
        }
      }
    }
  }
}