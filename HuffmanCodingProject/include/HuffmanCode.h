#ifndef __HUFFCODE
#define __HUFFCODE
#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

using HuffmanTable = std::unordered_map<char, std::string>;

enum class Mode
{
    Compression,
    Decompression,
    Empty
};

class HuffmanCode
{
private:
    HuffmanTree tree;
    std::istream &input;
    std::ostream &output;
    std::fstream *treeStream; // optional

    std::string extractSrcDecode();
    std::string extractSrcEncode();
    unsigned *getFrequencies(const char *src) const;
    std::vector<Node *> createLeaves(unsigned *table) const;
    HuffmanTable getEncodedTable(std::vector<Node *> &leaves) const;
    HuffmanTable getdecodedTable(std::vector<std::string> &leaves) const;
    void toOutputEncoded(const char *str, HuffmanTable &t);
    void toOutputDecoded(const char *str);
    void calculateCompression(const char *str, HuffmanTable &t) const;

public:
    HuffmanCode(std::istream &in = std::cin, std::ostream &out = std::cout, std::fstream *treeS = nullptr);
    void operator()(Mode m);
    void encode();
    void decode();
    void visualizeTree();
    void visualizeTree(std::ofstream &v);
    ~HuffmanCode() = default;
};

#endif