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
    std::fstream *treeStream; // optional

    std::string extractSrc();
    unsigned *getFrequencies(const char *src) const;
    std::vector<Node *> createLeaves(unsigned *table) const;
    HuffmanTable getEncodedTable(std::vector<Node *> &leaves) const;
    HuffmanTable getdecodedTable(std::vector<std::string> &leaves) const;

public:
    HuffmanCode(std::istream &in = std::cin, std::ostream &out = std::cout, std::fstream *treeS = nullptr);
    void encode();
    void decode();
    ~HuffmanCode();
};

#endif