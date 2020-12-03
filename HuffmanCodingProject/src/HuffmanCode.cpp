#include "../include/HuffmanCode.h"
#include <cassert>
    
unsigned *HuffmanCode::getFrequencies(const char *src)
{
    unsigned *freqTable = new unsigned[256];

    //initialize with 0's
    for (int i = 0; i < 256; i++)
        freqTable[i] = 0;

    while (*src != 0)
        freqTable[(unsigned)*(src++)]++;

    return freqTable;
}

HuffmanCode::HuffmanCode(const char *src) : tree(nullptr)
{
    // index - corresponds to char
    // table[index] - occurences of index
    unsigned *table = getFrequencies(src);

    //for every symbol that occurs in src: create leaf node with this symbol
    std::vector<Node *> leafs;

    for (unsigned i = 0; i < 256; i++)
    {
        if (table[i])
            leafs.push_back(new Node{(char)i, table[i], nullptr, nullptr});
    }

    PriorityQueue pq(leafs);
    tree = new HuffmanTree(pq);
    delete table;
}

HuffmanCode::HuffmanCode(std::istream &input)
{
    std::string src;
    std::string crr;
    while (std::getline(input, crr) && crr != "")
        src += crr;

    // index - corresponds to char
    // table[index] - occurences of index
    unsigned *table = getFrequencies(src.c_str());

    //for every symbol that occurs in src: create leaf node with this symbol
    std::vector<Node *> leafs;

    for (unsigned i = 0; i < 256; i++)
    {
        if (table[i])
            leafs.push_back(new Node{(char)i, table[i], nullptr, nullptr});
    }

    PriorityQueue pq(leafs);
    tree = new HuffmanTree(pq);
    delete table;
}

HuffmanCode::~HuffmanCode()
{
    if (tree != nullptr)
        delete tree;
}