#include "../include/HuffmanTree.h"
#include <stdexcept>
#include <fstream>
#include <cassert>

HuffmanTree::HuffmanTree() : root(nullptr) {}

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
        queue.insert(new Node{'!', child1->key + child2->key, child1, child2});
    }
}

void HuffmanTree::clear(Node *node)
{
    if (node == nullptr)
        return;

    clear(node->left);
    clear(node->right);
    delete node;
}

std::string HuffmanTree::search(Node *node, char s, bool &valid) const
{
    if (node == nullptr)
    {
        valid = false;
        return "";
    }

    if (node->asciiSymbol == s && node->left == nullptr && node->right == nullptr)
    {

        valid = true;
        if (node == root)
            return "0";
        return "";
    }

    bool l = true;
    bool r = true;
    std::string leftRes = "0" + search(node->left, s, l);
    if (l)
        return leftRes;
    std::string rightRes = "1" + search(node->right, s, r);
    if (r)
        return rightRes;

    valid = false;
    return "";
}

std::string HuffmanTree::getEncoded(char s) const
{
    bool valid = true;
    std::string encoded = search(root, s, valid);
    if (encoded == "")
        throw std::logic_error("Node with symbol \'s\' is not in the tree!\n");
    return encoded;
}

char HuffmanTree::getDecoded(const char *&s) const
{

    if (root->left == nullptr && root->right == nullptr && *s == '0')
    {
        s++;
        return root->asciiSymbol;
    }

    Node *crr = root;

    while (crr != nullptr && *s)
    {
        if (crr->left == nullptr && crr->right == nullptr)
            return crr->asciiSymbol;

        if (*s == '0')
            crr = crr->left;
        else
            crr = crr->right;
        s++;
    }
    if (crr == nullptr)
        throw std::logic_error("Node not found! The program assumes valid \'s\' path!\n");

    return crr->asciiSymbol;
}

// for testing only
char HuffmanTree::getDecoded(std::string &s) const
{
    Node *crr = root;
    unsigned i = 0;
    while (crr != nullptr && s[i])
    {
        if (crr->left == nullptr && crr->right == nullptr)
            return crr->asciiSymbol;

        if (s[i] == '0')
            crr = crr->left;
        else
            crr = crr->right;
        i++;
    }
    if (crr == nullptr)
        throw std::logic_error("Node not found! The program assumes valid \'s\' path!\n");

    return crr->asciiSymbol;
}

void HuffmanTree::toScheme(std::ostream &os, Node *node) const
{
    if (node == nullptr)
        os << "()";
    else
    {
        os << "({" << node->asciiSymbol << ", " << node->key << "} ";
        toScheme(os, node->left);
        toScheme(os, node->right);
        os << ')';
    }
}

void HuffmanTree::toScheme(std::ostream &os) const
{
    toScheme(os, root);
}

Node *HuffmanTree::fromSchemeRec(std::istream &is)
{
    assert(is.get() == '(');
    char peeked = is.get();
    if (peeked == ')')
        return nullptr;

    assert(peeked == '{');
    char ascii;
    unsigned key;
    is >> ascii;
    is.get();
    is >> key;
    assert(is.get() == '}');
    is.get();
    Node *node = new Node{ascii, key, fromSchemeRec(is), fromSchemeRec(is)};
    assert(is.get() == ')');
    return node;
}

void HuffmanTree::fromScheme(std::istream &is)
{
    clear(root);
    root = fromSchemeRec(is);
}

HuffmanTree::~HuffmanTree()
{
    clear(root);
}

HuffmanTree::Iterator::Iterator(Node *start) : prev(nullptr)
{
    if (start != nullptr)
        s.push(start);
}

typename HuffmanTree::Iterator &HuffmanTree::Iterator::operator++()
{
    if (s.empty())
        return *this;

    Node *crr = s.top();
    if (crr->right != nullptr)
    {
        if (prev != crr->right && prev != crr->left)
            s.push(crr->right);
        else if (prev == crr->right)
        {
            prev = s.top();
            s.pop();
            if (crr->left != nullptr)
                s.push(crr->left);
        }
    }
    else if (crr->left != nullptr && prev != crr->left)
        s.push(crr->left);
    else
    {
        prev = s.top();
        s.pop();
        if (!s.empty() && s.top()->right == prev)
        {
            prev = s.top();
            s.pop();
            if (prev->left != nullptr)
                s.push(prev->left);
        }
    }
    return *this;
}

bool HuffmanTree::Iterator::operator!=(const Iterator &rh) const
{
    return ((s.empty() && !rh.s.empty()) || (!s.empty() && rh.s.empty())) || (!s.empty() && !rh.s.empty() && s.top() != rh.s.top());
}

Node *HuffmanTree::Iterator::operator*()
{
    if (s.empty())
        throw std::logic_error("Read/Write to an end iterator\n");

    return s.top();
}

typename HuffmanTree::Iterator HuffmanTree::begin() { return Iterator(root); }
typename HuffmanTree::Iterator HuffmanTree::end() { return Iterator(); }
