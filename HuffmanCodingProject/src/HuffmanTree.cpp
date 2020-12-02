#include "../include/HuffmanTree.h"

HuffmanTree::HuffmanTree(PriorityQueue &queue) : root(nullptr)
{
    Node *child1;
    Node *child2;
    while (!queue.empty())
    {
        child1 = queue.peekPop();

        if (queue.empty())
        {
            root = child1;
            break;
        }
        child2 = queue.peekPop();
        queue.insert(new Node{'a', child1->key + child2->key, child1, child2});
    }
}