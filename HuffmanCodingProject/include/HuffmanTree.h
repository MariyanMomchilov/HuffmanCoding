#ifndef __HUFFMAN
#define __HUFFMAN
#include "PriorityQueue.h"
#include <string>
#include <stack>

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
    void toGraphViz(std::ostream &os) const;
    void toGraphViz(std::ostream &os, Node *node) const;
    ~HuffmanTree();

    class Iterator
    {
    private:
        std::stack<Node *> s;
        Node *prev;

    public:
        Iterator(Node *start = nullptr);
        Iterator &operator++();
        bool operator!=(const Iterator &rh) const;
        Node *operator*();
        ~Iterator() = default;
    };

    Iterator begin();
    Iterator end();
};

#endif