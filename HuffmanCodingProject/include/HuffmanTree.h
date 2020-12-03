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

public:
    HuffmanTree(PriorityQueue &queue);
    std::string getEncoded(char s) const;
    char getDecoded(const char *s) const;
    ~HuffmanTree();
};

#endif