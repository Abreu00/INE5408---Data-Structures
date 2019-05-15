#include <iostream>
#include "xml_validator.hpp"

using namespace std;

int main() {

    char xmlfilename[100];

	
    cin >> xmlfilename;
	XmlValidator xml(xmlfilename);
    xml.validate_file();
    if (!xml.is_valid()) cout << "error" << endl;

}
