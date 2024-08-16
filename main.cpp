#include "bit_field_filter.h"
#include "gray_image.h"
#include "image.h"
#include "photo_mosaic.h"
#include "rgb_image.h"

#define ENABLE_X_SERVER true
#define STEP2 false

int main(int argc, char *argv[]) {

  if (STEP2) {
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg"); // output picture to *jpg/*png。
    if (ENABLE_X_SERVER) {
      img1->Display_X_Server(); // Display_X_Server in moba_xterm
    }
    img1->Display_ASCII(); // print on terminal based on ASCII
    img1->Display_CMD();   // print on terminal directory

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    if (ENABLE_X_SERVER) {
      img2->Display_X_Server(); // Display_X_Server in moba_xterm
    }
    img2->Display_ASCII();
    img2->Display_CMD();
  }

  // some bit field filter design driven code here

  // Box Filter
  Image *img3 = new RGBImage();
  img3->LoadImage("Image-Folder/lena.jpg");
  img3->DumpImage("img3.jpg");
  loadCase(img3, BOX_FILTER);
  img3->DumpImage("img3_after.jpg");

  // Sobel Gradient
  Image *img4 = new RGBImage();
  img4->LoadImage("img/lose.jpg");
  img4->DumpImage("img4.jpg");
  loadCase(img4, SOBEL_GRADIENT);
  img4->DumpImage("img4_after.jpg");

    // Contrast_Stretching
  Image *img5 = new RGBImage();
  img5->LoadImage("img/str.jpg");
  img5->DumpImage("img5.jpg");
  loadCase(img5, CONTRAST_STRETCH);
  img5->DumpImage("img5_after.jpg");

  // Mosaic_Filter
  Image *img6 = new RGBImage();
  img6->LoadImage("img/good.jpg");
  img6->DumpImage("img6.jpg");
  loadCase(img6, MOSAIC_FILTER);
  img6->DumpImage("img6_after.jpg");

  // some photo mosaic driven code here

  // more ...
  return 0;
}
