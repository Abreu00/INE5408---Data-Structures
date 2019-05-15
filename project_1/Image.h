#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
 
 public:
    std::string name;
    int width;
    int height;
    int** data;   
};

#endif