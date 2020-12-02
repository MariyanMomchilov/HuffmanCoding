#ifndef _NODE
#define _NODE

class PriorityQueue;

struct Node
{
    //private:
    friend class PriorityQueue;
    char asciiSymbol;
    unsigned key;
    Node *left, *right;
};

#endif