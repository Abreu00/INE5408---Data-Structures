#include <iostream>
#include <fstream>
#include "xml_validator.hpp"
#include "linked_queue.hpp"
#include "reads_image.hpp"
#include "count_related.hpp"
#include "Image.h"
#include "dealloc_matrix.hpp"

using namespace std;

int main() {
    // Gets a dataset*.xml file as input
    // If input is a valid xml, counts the number of related components on each image
    // found on the xml file

    char xmlfilename[100];
	
    cin >> xmlfilename;
    string path = "./datasets/" + string(xmlfilename);
	XmlValidator xml(path);
    xml.validate_file();

    if (!xml.is_valid()) {
        cout << "error" << endl;
        return 1;
    }
    ifstream file;
    file.open(path);
    string line = "";
    
    while (line != "</dataset>") {
        Image img = parse(file, line);
        if (img.name != "EOF") {
            int related_components = count_related(img);
            cout << img.name << " " << related_components << endl;
            deallocMatrix(img.data, img.height, img.width);
            img.data = nullptr;
        }
    }
    file.close();
}

