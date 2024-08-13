#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
    int ***pixels;

public:
    //Member function(all public):

    //Constructor/Destructor
    RGBImage();
    RGBImage(int width, int height, int ***pixels);
    ~RGBImage();

    //Override Base class vitual function(all public):
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
};

#endif