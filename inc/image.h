#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <string>

#include "data_loader.h"

using namespace std;

class Image {
protected:
  int w;
  int h;
  Data_Loader data_loader;

public:
  // Constructor/Destructor
  Image(int width, int height);
  virtual ~Image();

  int get_w();
  int get_h();

  // Pure virtual function(let derived class override, all public):
  virtual bool LoadImage(string filename);
  virtual void DumpImage(string filename);
  virtual void Display_X_Server();
  virtual void Display_ASCII();
  virtual void Display_CMD();
};

#endif