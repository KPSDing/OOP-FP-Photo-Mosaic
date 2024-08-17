#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

#define RGBCHANNEL 3
#define RED 0
#define GREEN 1
#define BLUE 2


class RGBImage : public Image{
private:
    int ***pixels;
    const int box_fliter_kernel[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; 

public:
    //Member function(all public):

    //Constructor/Destructor
    RGBImage();
    RGBImage(int width, int height, int ***pixels);
    ~RGBImage();

    //Override Base class vitual function(all public):
    bool LoadImage(string filename) override;
    void DumpImage(string filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;

    //Image filter design
    void Apply_Box_Filter() override;
    void Apply_Sobel_Gradient() override;
    void Apply_Contrast_Stretching() override;
    void Apply_Mosaic_Filter() override;

    // Existing public methods...
    int*** getPixels() const;
    void setPixel(int x, int y, int r, int g, int b);
};

#endif
