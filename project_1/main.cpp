#include <iostream>
#include "xml_validator.hpp"

using namespace std;

int main() {

    char xmlfilename[100];

	
    cin >> xmlfilename;
	XmlValidator xml(xmlfilename);
	for (int i = 0; i < 30; i++) xml.read_line();

    return 0;
}
