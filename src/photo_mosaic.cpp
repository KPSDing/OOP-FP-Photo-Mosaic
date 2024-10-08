#include "photo_mosaic.h"

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
    string folderPath = "Image-Folder/cifar10";  // CIFAR-10 圖像文件夾路徑
    // 遍歷資料夾中的每個文件
    data_loader.List_Directory(folderPath, imagepathLibrary);
}

void PhotoMosaic::CreateRGBPhotoMosaic(const string targetImagePath, const string& outputFilename){
    Image *targetImgData = new RGBImage();
    cout << "targetImagePath: " << targetImagePath << endl;
    targetImgData->LoadImage(targetImagePath);

    int targetWidth = targetImgData->get_w();
    int targetHeight = targetImgData->get_h();

    RGBImage mosaicImage(targetWidth, targetHeight, nullptr);
    
    int*** targetPixels = dynamic_cast<RGBImage*>(targetImgData)->getPixels();

    for (int i = 0; i < targetHeight; i += blockSize) {
        for (int j = 0; j < targetWidth; j += blockSize) {
            long long int sumR = 0, sumG = 0, sumB = 0;
            int blockHeight = blockSize;
            int blockWidth = blockSize;

            for (int bi = i; bi < i + blockSize; bi++) {
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

            double minDist = numeric_limits<double>::max();
            int*** bestsmallpixels = nullptr;

            for (vector<string>::size_type k = 0; k < imagepathLibrary.size(); k++) {
                Image *findbestsmallimage = new RGBImage();
                cout << "Load: " << imagepathLibrary[k] << endl;
                findbestsmallimage->LoadImage(imagepathLibrary[k]);
                int*** smallimagePixels = dynamic_cast<RGBImage*>(findbestsmallimage)->getPixels();

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
                        for (int bi = 0; bi < blockSize; ++bi) {
                            for (int bj = 0; bj < blockSize; ++bj) {
                                delete[] bestsmallpixels[bi][bj];
                            }
                            delete[] bestsmallpixels[bi];
                        }
                        delete[] bestsmallpixels;
                    }
                    bestsmallpixels = new int**[blockSize];
                    for (int bi = 0; bi < blockSize; ++bi) {
                        bestsmallpixels[bi] = new int*[blockSize];
                        for (int bj = 0; bj < blockSize; ++bj) {
                            bestsmallpixels[bi][bj] = new int[3];
                            copy(smallimagePixels[bi][bj], smallimagePixels[bi][bj] + 3, bestsmallpixels[bi][bj]);
                        }
                    }
                }
                for (int bi = 0; bi < blockSize; ++bi) {
                    for (int bj = 0; bj < blockSize; ++bj) {
                        delete[] smallimagePixels[bi][bj];
                    }
                    delete[] smallimagePixels[bi];
                }
                delete[] smallimagePixels;
                delete findbestsmallimage;
            }

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
                for (int bi = 0; bi < blockSize; ++bi) {
                    for (int bj = 0; bj < blockSize; ++bj) {
                        delete[] bestsmallpixels[bi][bj];
                    }
                    delete[] bestsmallpixels[bi];
                }
                delete[] bestsmallpixels;
            }
        }
    }

    mosaicImage.DumpImage(outputFilename);
    delete targetImgData;
}
