#ifndef __HUFFCODE
#define __HUFFCODE
#include "HuffmanTree.h"
#include <iostream>
#include <fstream>

class HuffmanCode
{
private:
    HuffmanTree *tree; //consider removig this field
    unsigned *getFrequencies(const char *src);

public:
    HuffmanCode(const char *src);
    HuffmanCode(std::istream &input = std::cin);

    ~HuffmanCode();
};

#endif