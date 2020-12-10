#ifndef __HUFFMAN
#define __HUFFMAN
#include "PriorityQueue.h"
#include <string>
#include <stack>

class HuffmanTree
{
private:
    Node *root;

    friend std::ostream &operator<<(std::ostream &os, HuffmanTree &tree);
    friend std::istream &operator>>(std::istream &is, HuffmanTree &tree);

    void clear(Node *node);
    std::string search(Node *node, char s, bool &valid) const;
    void toScheme(std::ostream &os, Node *node) const;
    Node *fromSchemeRec(std::istream &is);
    Node *clone(Node *from) const;

public:
    HuffmanTree();
    HuffmanTree(const HuffmanTree &other);
    HuffmanTree(HuffmanTree &&rval) noexcept;
    HuffmanTree &operator=(const HuffmanTree &other);
    HuffmanTree &operator=(HuffmanTree &&rval) noexcept;
    HuffmanTree(PriorityQueue &queue);
    std::string getEncoded(char s) const;
    char getDecoded(const char *&s) const;
    char getDecoded(std::string &s) const;
    void toScheme(std::ostream &os) const;
    void fromScheme(std::istream &is);
    void toGraphViz(std::ofstream &os) const;
    void toGraphViz(std::ofstream &os, Node *node) const;
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