#include "bit_field_filter.h"
#include "gray_image.h"
#include "image.h"
#include "photo_mosaic.h"
#include "rgb_image.h"
#include <cmath>

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

  for (int i = 3; i < 7; i++) {
    Image *img = new RGBImage();
    string name = "img/" + to_string(i);
    string out = to_string(i);

    img->LoadImage(name + ".jpg");
    img->DumpImage("out/" + out + "_ori.jpg");
    int8_t option = 1 << (i-3);  // Use bit shift instead of pow(2, i)
    loadCase(img, option); 
    img->DumpImage("out/" + out + ".jpg"); 
    delete img; // free memory
  }

  // some photo mosaic driven code here

  cout<<"Step 4: Photo mosaic"<<endl;
  PhotoMosaic* img8 new PhotoMosaic();
  img8->CreateRGBPhotoMosaic("Image-Folder/4k_owl.jpg", "img_after_photo_mosaic");

  // more ...
  return 0;
}
