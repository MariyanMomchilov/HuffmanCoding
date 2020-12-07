#include "../include/HuffmanTree.h"
#include <stdexcept>
#include <fstream>
#include <cassert>

HuffmanTree::HuffmanTree() : root(nullptr) {}

Node *HuffmanTree::clone(Node *from) const
{
    if (from == nullptr)
        return nullptr;
    return new Node{from->asciiSymbol, from->key, clone(from->left), clone(from->right)};
}

HuffmanTree::HuffmanTree(const HuffmanTree &other) : root(nullptr)
{
    root = clone(other.root);
}

HuffmanTree::HuffmanTree(HuffmanTree &&rval) noexcept : root(rval.root)
{
    rval.root = nullptr;
}

HuffmanTree &HuffmanTree::operator=(const HuffmanTree &other)
{
    if (this != &other)
    {
        clear(root);
        root = clone(other.root);
    }
    return *this;
}

HuffmanTree &HuffmanTree::operator=(HuffmanTree &&rval) noexcept
{
    clear(root);
    root = rval.root;
    rval.root = nullptr;

    return *this;
}

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

Node *HuffmanTree::fromSchemeRec(std::istream &is) // TO DO REFACTOR ERROR HANDLING
{
    if (is.get() != '(')
        throw std::domain_error("Invalid tree file. Expected \'(\'\n");

    char peeked = is.get();
    if (peeked == ')')
        return nullptr;

    if (peeked != '{')
        throw std::domain_error("Invalid tree file. Expected \'{\'\n");
    char ascii = is.get();
    unsigned key;
    is.get();
    is >> key;
    if (is.get() != '}')
        throw std::domain_error("Invalid tree file. Expected \'}\'\n");
    is.get();
    Node *node = new Node{ascii, key, fromSchemeRec(is), fromSchemeRec(is)};
    if (is.get() != ')')
        throw std::domain_error("Invalid tree file. Expected \')\'\n");
    return node;
}

void HuffmanTree::fromScheme(std::istream &is)
{
    clear(root);
    root = fromSchemeRec(is);
}

void HuffmanTree::toGraphViz(std::ostream &os, Node *node) const
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr)
        os << (std::intptr_t)node << "[label = \"key: " << node->key << "\\n ascii: " << node->asciiSymbol << "\"];\n";
    else
    {
        os << (std::intptr_t)node << " [label = \"key: " << node->key << "\"];\n";
        if (node->left != nullptr)
        {
            os << (std::intptr_t)node << "-> " << (std::intptr_t)node->left << "[label = 0, color = red];\n";
            toGraphViz(os, node->left);
        }
        if (node->right != nullptr)
        {
            os << (std::intptr_t)node << "-> " << (std::intptr_t)node->right << "[label = 1];\n";
            toGraphViz(os, node->right);
        }
    }
}

void HuffmanTree::toGraphViz(std::ostream &os) const
{
    os << "digraph {\n";
    toGraphViz(os, root);
    os << "}";
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

std::ostream &operator<<(std::ostream &os, HuffmanTree &tree)
{
    tree.toScheme(os);
    return os;
}

std::istream &operator>>(std::istream &is, HuffmanTree &tree)
{
    tree.fromScheme(is);
    return is;
}
