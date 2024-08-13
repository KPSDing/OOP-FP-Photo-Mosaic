#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;

public:
    //Member function(all public):

    //Constructor/Destructor
    GrayImage();
    GrayImage(int width, int height, int **pixels);
    ~GrayImage();

    //Override Base class vitual function(all public):
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

};

#endif