#include <string>
#include <fstream>
#include "Image.h"
#include <stdexcept>
#include <iostream>

using namespace std;

//! creates_image.hpp has the necessary functions to read the image
//! from the xml file

string getContent(string line, string tagName) {
    
    //! Returns content of xml element
    //! Element has to be on line given otherwise it returns an empty string

    string tag = '<' + tagName + '>';
    
    std::size_t start = line.find(tag);
    std::size_t finish = line.find(tag.insert(1, "/"));
    
    if (start == string::npos || finish == string::npos) {
        return "";
    }
    start += tag.length() - 1; //Position where tag data starts
    finish -= 1; // Position where tag data finishes
    return line.substr(start, finish - start + 1);
}

int** getImageBin(ifstream &file, string &line, int width, int height) {
    if ( line !=  "<data>") {
        throw invalid_argument("Line should be <data> in order to file read the matrix");
    }

    int** data = new int*[height];
    char c = 'c';
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            file >> c;
            data[i][j] = c - '0';
        }
    }
    return data;
} 

void dealocMatrix(int**& matrix, int lines, int cols) {
    for (int i = 0; i < lines; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

Image parse(ifstream &file, string &line) {
    //! Retuns an Image obj based on data from xml file
    Image img;
    while (line != "</dataset>") {
        file >> line;
        string content = "";
        content = getContent(line, "name");
        
        if (content != "") {
            img.name = content;
            file >> line;
            img.height = stoi(getContent(line, "height"));
            img.width = stoi(getContent(line, "width"));
            file >> line;
            img.data = getImageBin(file, line, img.width, img.height);
            return img;
        }
    }
    img.name = "EOF";
    return img;
}