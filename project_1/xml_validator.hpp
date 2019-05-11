#ifndef XML_VALIDATOR_H
#define XML_VALIDATOR_H

#include "linked_stack.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class XmlValidator {
 
 public:
    XmlValidator(string xmlfilename);
    ~XmlValidator();

    void read_line();

 private:
    structures::LinkedStack<string> stack;
    ifstream file;

};

XmlValidator::XmlValidator(string xmlfilename) {
    file.open(xmlfilename);
}

XmlValidator::~XmlValidator() {
    file.close();
    stack.clear();
}

#endif