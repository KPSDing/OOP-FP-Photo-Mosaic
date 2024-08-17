#include "photo_mosaic.h"
#include "stb_image.h"
#include "stb_image_write.h"

PhotoMosaic::PhotoMosaic(int blockSize) : blockSize(blockSize) {
    CreateRGBImageLibrary();
}

PhotoMosaic::~PhotoMosaic() {
    imagepathLibrary.clear();
}

double PhotoMosaic::colorDistance(const int tragetred, const int tragetgreen, const int tragetblue, const int smallimagered, const int smallimagegreen, const int smallimageblue) {
    int dr = tragetred - smallimagered;
    int dg = tragetgreen - smallimagegreen;
    int db = tragetblue - smallimageblue;
    return sqrt(dr * dr + dg * dg + db * db);
}

void PhotoMosaic::CreateRGBImageLibrary(){
    string folderPath = "./Image-Folder/cifar10";  // CIFAR-10 圖像文件夾路徑
    // 遍歷資料夾中的每個文件
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string filePath = entry.path().string();
            cout << "Loading image: " << filePath << std::endl;

            Image* img = new RGBImage();  // 假設CIFAR-10圖像是RGB圖像
            if (img->LoadImage(filePath)) {
                imagepathLibrary.push_back(filePath);  // 將加載的圖像路徑添加到列表中
            } else {
                delete img;  // 如果加載失敗，釋放記憶體
                cerr << "Failed to load image: " << filePath << std::endl;
            }
        }
    }
}

void PhotoMosaic::CreateRGBPhotoMosaic(string targetImagePath, const string& outputFilename){

    Image *targetImgData = newRGBImage();
    targetImgData->LoadImage(targetImagePath);
    
    int targetWidth = targetImgData->get_w();
    int targetHeight = targetImgData->get_h();

    RGBImage mosaicImage(targetWidth, targetHeight);

    int*** targetPixels = dynamic_cast<RGBImage*>(targetImgData)->getPixels();

    int*** bestsmallpixels = nullptr;

    for (int i = 0; i < targetHeight; i += blockSize) {
        for (int j = 0; j < targetWidth; j += blockSize) {
            
            // 取的block的顏色
            long long int sumR = 0, sumG = 0, sumB = 0;
            int blockHeight = blockSize;
            int blockWidth = blockSize;

            for(int bi = i; bi < i + blockSize; bi++) {
                if (bi >= targetHeight) {
                    blockHeight = bi - i;
                    break;
                }

                for (int bj = j; bj < j + blockSize; bj++) {
                    if (bj >= targetWidth) {
                        blockWidth = bj - j;
                        break;
                    }
                    sumR  += targetPixels[bi][bj][RED];
                    sumG  += targetPixels[bi][bj][GREEN];
                    sumB  += targetPixels[bi][bj][BLUE];
                }
            }

            int pixelCount = blockHeight * blockWidth;

            int avgred   = min(255, max(0, static_cast<int>(sumR / pixelCount)));
            int avggreen = min(255, max(0, static_cast<int>(sumG / pixelCount)));
            int avgblue  = min(255, max(0, static_cast<int>(sumB / pixelCount)));


            // 找到最接近的小圖
            double minDist = numeric_limits<double>::max();

            for (int k = 0; k < imagepathLibrary.size(); k++) {
                // 假設都是 RGB
                Image *findbestsmallimage = newRGBImage();
                findbestsmallimage->LoadImage(imagepathLibrary[k]);

                int*** smallimagePixels = dynamic_cast<RGBImage*>(findbestsmallimage)->getPixels();

                // 取得小圖顏色
                long long int smallimagesumR = 0, smallimagesumG = 0, smallimagesumB = 0;
                int smallBlockHeight = blockSize;
                int smallBlockWidth = blockSize;

                for (int bi = 0; bi < smallBlockHeight; bi++) {
                    if (i + bi >= targetHeight) {
                        smallBlockHeight = bi;
                        break;
                    }

                    for (int bj = 0; bj < smallBlockWidth; bj++) {
                        if (j + bj >= targetWidth) {
                            smallBlockWidth = bj;
                            break;
                        }
                        smallimagesumR  += smallimagePixels[bi][bj][RED];
                        smallimagesumG  += smallimagePixels[bi][bj][GREEN];
                        smallimagesumB  += smallimagePixels[bi][bj][BLUE];
                    }
                }

                int smallPixelCount = smallBlockHeight * smallBlockWidth;

                int smallimageavgred   = min(255, max(0, static_cast<int>(smallimagesumR / smallPixelCount)));
                int smallimageavggreen = min(255, max(0, static_cast<int>(smallimagesumG / smallPixelCount)));
                int smallimageavgblue  = min(255, max(0, static_cast<int>(smallimagesumB / smallPixelCount)));

                double dist = colorDistance(avgred, avggreen, avgblue, smallimageavgred, smallimageavggreen, smallimageavgblue);
                
                if (dist < minDist) {
                    minDist = dist;
                    if (bestsmallpixels) {
                        delete[] bestsmallpixels;
                    }
                    bestsmallpixels = smallimagePixels;
                } 
                delete[] smallimagePixels;
                delete findbestsmallimage;
            }

            // 更新馬賽克圖片
            if (bestsmallpixels) {
                for (int bi = 0; bi < blockSize; ++bi) {
                    if (i + bi >= targetHeight) break;
                    for (int bj = 0; bj < blockSize; ++bj) {
                        if (j + bj >= targetWidth) break;
                        mosaicImage.setPixel(i + bi, j + bj, 
                                            bestsmallpixels[bi][bj][RED], 
                                            bestsmallpixels[bi][bj][GREEN], 
                                            bestsmallpixels[bi][bj][BLUE]);
                    }
                }
            }
        }
    }

    // 保存馬賽克圖片
    mosaicImage.DumpImage(outputFilename);
    delete targetImgData;

    if (bestsmallpixels) {
        delete[] bestsmallpixels;
    }
}
