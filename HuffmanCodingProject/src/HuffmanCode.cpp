#include "../include/HuffmanCode.h"
#include <cassert>

HuffmanCode::HuffmanCode(std::istream &in, std::ostream &out, std::fstream *treeS) : tree(nullptr), input(in), output(out), treeStream(treeS) {}

unsigned *HuffmanCode::getFrequencies(const char *src) const
{
    unsigned *freqTable = new unsigned[256];

    //initialize with 0's
    for (int i = 0; i < 256; i++)
        freqTable[i] = 0;

    while (*src != 0)
        freqTable[(unsigned)*(src++)]++;

    return freqTable;
}

std::vector<Node *> HuffmanCode::createLeaves(unsigned *table) const
{
    std::vector<Node *> leafs;

    for (unsigned i = 0; i < 256; i++)
    {
        if (table[i])
            leafs.push_back(new Node{(char)i, table[i], nullptr, nullptr});
    }
    return leafs;
}

std::string HuffmanCode::extractSrc()
{
    std::string src;
    std::string crr;
    while (std::getline(input, crr) /*&& crr != ""*/) // DO I NEED crr != "" ?
        src += crr;
    return src;
}

HuffmanTable HuffmanCode::getEncodedTable(std::vector<Node *> &leaves) const
{
    HuffmanTable table;

    for (int i = 0; i < leaves.size(); i++)
    {
        table[leaves[i]->asciiSymbol] = tree->getEncoded(leaves[i]->asciiSymbol);
    }
    return table;
}

void HuffmanCode::encode()
{
    std::string strSource = extractSrc();
    const char *src = strSource.c_str();

    // index - corresponds to char
    // table[index] - occurences of index
    unsigned *table = getFrequencies(src);

    //for every symbol that occurs in src: create leaf node with this symbol
    std::vector<Node *> leafs = createLeaves(table);
    delete table;

    PriorityQueue pq(leafs);
    tree = new HuffmanTree(pq);

    HuffmanTable encodedTable = getEncodedTable(leafs);

    if (treeStream != nullptr)
        tree->toScheme(*treeStream);
    else
    {
        tree->toScheme(output);
        output << '\n';
    }

    //encoding happens here:
    while (*src)
    {
        output << encodedTable[*src++];
    }
}

void HuffmanCode::decode()
{
    tree = new HuffmanTree;
    if (treeStream != nullptr)
        tree->fromScheme(*treeStream);
    else
        tree->fromScheme(input);

    std::string src = extractSrc();
    const char *cSrc = src.c_str();
    while (*cSrc)
    {
        output << tree->getDecoded(cSrc);
    }
}

HuffmanCode::~HuffmanCode()
{
    if (tree != nullptr)
        delete tree;
}