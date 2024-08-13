#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <string>

using namespace std;

class Image{
protected:
    int w;
    int h;
    Data_Loader data_loader;
public:
    //Constructor/Destructor
    Image(int width, int height);
    ~Image();

    int get_w();
    int get_h();
    
    //Pure virtual function(let derived class override, all public):
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

};

#endif