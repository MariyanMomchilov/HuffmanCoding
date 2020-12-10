#ifndef _NODE
#define _NODE

struct Node
{
    char asciiSymbol;
    unsigned key;
    Node *left;
    Node *right;
};

#endif