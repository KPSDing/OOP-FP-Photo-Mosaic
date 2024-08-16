#include "bit_field_filter.h"
#include "gray_image.h"
#include "image.h"
#include "photo_mosaic.h"
#include "rgb_image.h"
#define RGB false
#define ENABLE_X_SERVER true


int main(int argc, char *argv[]) {
  Image *img1 = new GrayImage();
  img1->LoadImage("Image-Folder/mnist/img_100.jpg");
  img1->DumpImage("img1.jpg"); // output picture to *jpg/*png。
  if(ENABLE_X_SERVER){
    img1->Display_X_Server(); // Display_X_Server in moba_xterm
  }
  img1->Display_ASCII(); // print on terminal based on ASCII
  img1->Display_CMD(); // print on terminal directory

  if (RGB) {
    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    if(ENABLE_X_SERVER){
      img2->Display_X_Server(); // Display_X_Server in moba_xterm
    }
    img2->Display_ASCII();
    img2->Display_CMD();
  }

  // some bit field filter design driven code here

  // some photo mosaic driven code here

  // more ...
  return 0;
}
