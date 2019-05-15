#include <iostream>
#include "xml_validator.hpp"
#include "linked_queue.hpp"

using namespace std;

int main() {

    char xmlfilename[100];

	
    cin >> xmlfilename;
    string path = "./datasets/" + string(xmlfilename);
	XmlValidator xml(path);
    xml.validate_file();
    if (!xml.is_valid()) cout << "error" << endl;

}

