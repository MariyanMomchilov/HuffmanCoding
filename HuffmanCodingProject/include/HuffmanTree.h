#ifndef __HUFFMAN
#define __HUFFMAN
#include "PriorityQueue.h"
#include <string>

class HuffmanTree
{
private:
    Node *root;

    void clear(Node *node);
    std::string search(Node *node, char s, bool &valid) const;
    void toScheme(std::ostream &os, Node *node) const;
    Node *fromSchemeRec(std::istream &is);

public:
    HuffmanTree();
    HuffmanTree(PriorityQueue &queue);
    std::string getEncoded(char s) const;
    char getDecoded(const char *&s) const;
    char getDecoded(std::string &s) const;
    void toScheme(std::ostream &os) const;
    void fromScheme(std::istream &is);
    ~HuffmanTree();
};

#endif