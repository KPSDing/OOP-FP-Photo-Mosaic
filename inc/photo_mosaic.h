#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include <string>
#include <iostream>
#include <vector> 
#include <limits>

#include "image.h"
#include "rgb_image.h"

using namespace std;

class PhotoMosaic{
private:
    // 圖像庫
    vector<string> imagepathLibrary; 
    // 每個馬賽克塊的大小
    int blockSize;
    // 計算顏色之間的距離
    double colorDistance(const int, const int, const int, const int, const int , const int);
    // 添加圖像庫中的圖像
    void CreateRGBImageLibrary();
    Data_Loader data_loader;

public:
    // Constructor/Destructor
    PhotoMosaic(int blockSize);
    ~PhotoMosaic();
    // 創建 Photo Mosaic
    void CreateRGBPhotoMosaic(string targetImagePath, const string& outputFilename);
};

#endif
