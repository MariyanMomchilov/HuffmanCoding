#ifndef __HUFFMAN
#define __HUFFMAN
#include "PriorityQueue.h"

class HuffmanTree
{
private:
    Node *root;

public:
    HuffmanTree(PriorityQueue &queue);
    //~HuffmanTree(); to do
};

#endif