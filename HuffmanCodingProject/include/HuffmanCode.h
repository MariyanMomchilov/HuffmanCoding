#ifndef __HUFFCODE
#define __HUFFCODE
#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

using HuffmanTable = std::unordered_map<char, std::string>;

class HuffmanCode
{
private:
    HuffmanTree *tree;
    std::istream &input;
    std::ostream &output;

    std::string extractSrc();
    unsigned *getFrequencies(const char *src) const;
    std::vector<Node *> createLeaves(unsigned *table) const;
    HuffmanTable getEncodedTable(std::vector<Node *> &leaves) const;

public:
    HuffmanCode(std::istream &in = std::cin, std::ostream &out = std::cout);
    void encode();
    void decode(); // TO DO

    ~HuffmanCode();
};

#endif