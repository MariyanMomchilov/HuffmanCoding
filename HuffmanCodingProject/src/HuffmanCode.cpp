#include "../include/HuffmanCode.h"
#include <cassert>
#include <cstring>
#include <vector>

HuffmanCode::HuffmanCode(std::ifstream &in, std::ofstream &out, std::fstream *treeS) : input(in), output(out), treeStream(treeS) {}

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

std::string HuffmanCode::extractSrcDecode()
{
    std::string src;
    std::string crr;
    while (std::getline(input, crr))
    {
        src += crr;
    }
    return src;
}

std::string HuffmanCode::extractSrcEncode()
{
    std::string src;
    char c;
    while (input.get(c))
    {
        if (input.eof())
            break;
        src += c;
    }
    return src;
}

HuffmanTable HuffmanCode::getEncodedTable(std::vector<Node *> &leaves) const
{
    HuffmanTable table;

    for (int i = 0; i < leaves.size(); i++)
    {
        table[leaves[i]->asciiSymbol] = tree.getEncoded(leaves[i]->asciiSymbol);
    }
    return table;
}

void HuffmanCode::encode()
{
    std::string strSource = extractSrcEncode();
    const char *src = strSource.c_str();

    // index - corresponds to char
    // table[index] - occurences of index
    unsigned *table = getFrequencies(src);

    //for every symbol that occurs in src: create leaf node with this symbol
    std::vector<Node *> leafs = createLeaves(table);
    delete table;

    PriorityQueue pq(leafs);
    tree = HuffmanTree(pq);

    HuffmanTable encodedTable = getEncodedTable(leafs);

    if (treeStream != nullptr)
        *treeStream << tree;
    else
        output << tree << '\n';

    toOutputEncoded(src, encodedTable);
    calculateCompression(src, encodedTable);
    //alternativeEncoding(src, encodedTable);
}

void HuffmanCode::decode()
{
    if (treeStream != nullptr)
        *treeStream >> tree;
    else
        input >> tree;

    std::string src = extractSrcDecode();
    const char *cSrc = src.c_str();
    toOutputDecoded(cSrc);
}

void HuffmanCode::operator()(Mode m)
{

    if (m == Mode::Compression)
        encode();
    else if (m == Mode::Decompression)
        decode();
    else
        throw std::logic_error("Invalid mode\n");
}

void HuffmanCode::visualizeTree()
{
    std::ofstream dot("tree.dot");
    tree.toGraphViz(dot);
    dot.close();
}

void HuffmanCode::visualizeTree(std::ofstream &v)
{
    tree.toGraphViz(v);
}

void HuffmanCode::toOutputEncoded(const char *str, HuffmanTable &t)
{
    while (*str)
        output << t[*str++];
}

void HuffmanCode::calculateCompression(const char *str, HuffmanTable &t) const
{
    if (!*str)
        return;

    size_t originalSize = strlen(str);
    std::string res;
    while (*str)
        res += t[*str++];

    size_t compressedSize = res.size();
    std::cout << "\n------------- Reduced file size by "
              << (100 * ((8 * originalSize) - compressedSize)) / (8 * originalSize) << "%. \n";
    std::cout << "------------- Compressed " << originalSize << " bytes(" << 8 * originalSize << " bits) to ";
    if (compressedSize % 8 == 0)
        std::cout << compressedSize / 8 << " bytes(" << compressedSize << " bits). \n\n";
    else
        std::cout << (compressedSize / 8) + 1 << " bytes(" << compressedSize << " bits). \n\n";
}

void HuffmanCode::toOutputDecoded(const char *str)
{
    while (*str)
        output << tree.getDecoded(str);
}

void HuffmanCode::alternativeEncoding(const char *str, HuffmanTable &t) const
{
    if (*str == 0)
        return;

    std::string result;
    while (*str)
    {
        result += t[*str++];
    }

    size_t resSize = result.size();

    std::vector<std::string> splitted;
    size_t pos = 0;
    std::string toSplitted;
    for (int i = 0; i < resSize; i++)
    {
        if (pos != 0 && pos % 8 == 0)
        {
            splitted.push_back(toSplitted);
            toSplitted = "";
            pos = 0;
        }
        toSplitted += result[i];
        pos++;
    }
    if (toSplitted != "")
        splitted.push_back(toSplitted);

    std::cout << "\n------------- bytes to ints -------------\n";
    for (int i = 0; i < splitted.size(); i++)
        std::cout << std::stoi(splitted[i], nullptr, 2) << ' ';
    std::cout << '\n';
}