#ifndef XML_VALIDATOR_H
#define XML_VALIDATOR_H

#include "linked_stack.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class XmlValidator {
 
 public:
    XmlValidator(string xmlfilename);
    ~XmlValidator();
    int validate_line();
    bool validate_file();
    bool is_valid();

 private:
    structures::LinkedStack<string> stack;
    ifstream file;
    size_t xml_read_string(size_t start, string str);
    bool valid;
    bool pop_from_stack(string tag);
};

XmlValidator::XmlValidator(string xmlfilename) {
    file.open(xmlfilename);
    valid = true;
}

XmlValidator::~XmlValidator() {
    file.close();
    stack.clear();
}

bool XmlValidator::validate_file() {
    
    while (validate_line() == 1);
    
    valid = valid && stack.empty();

    return valid;
}

int XmlValidator::validate_line() {
    string line = "";
    file >> line;
    std::size_t start {0};
    
    if (file.eof()) {
        return -1;
    }

    while (start != string::npos) {
        start = xml_read_string(start, line);
    }
    return valid;
}

size_t XmlValidator::xml_read_string(size_t start, string str) {
    start = str.find("<", start);
    if (start == string::npos) return start;

    size_t finish = str.find(">", start);

    string tag = "";
    if (str[start + 1] != '/') { 
        //tag do tipo <hello>
        tag = str.substr(start + 1, finish - start - 1);
        stack.push(tag);
    } else {
        // tag do tipo </hello>
        tag = str.substr(start + 2, finish - start - 2);
        pop_from_stack(tag);
    }
    return finish;
}

bool XmlValidator::pop_from_stack(string tag) {
    if ( stack.empty() || stack.top() != tag) {
        valid = false;
    }
    else {
        valid = true;
    }
    stack.pop();
    return valid;
}

bool XmlValidator::is_valid() {
    return valid;
}

#endif