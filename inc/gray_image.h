#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image {
private:
  int **pixels;

public:
  // Member function(all public):

  // Constructor/DestructorF
  GrayImage();
  GrayImage(int width, int height, int **pixels);
  ~GrayImage();

  // Override Base class vitual function(all public):
  bool LoadImage(string filename) override;
  void DumpImage(string filename) override;
  void Display_X_Server() override;
  void Display_ASCII() override;
  void Display_CMD() override;

    //Image filter design
  void Apply_Contrast_Stretching() override;
  void Apply_Mosaic_Filter() override;
};

#endif