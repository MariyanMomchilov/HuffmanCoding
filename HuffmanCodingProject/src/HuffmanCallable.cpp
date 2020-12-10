#include "../include/HuffmanCallable.h"

HuffmanCallable::HuffmanCallable(std::istream *i, std::ostream *o, std::fstream *t, std::ofstream *v) : mode(Mode::Empty), is(i), os(o), treeS(t), treeViz(v) {}

void HuffmanCallable::setMode(Mode m)
{
    mode = m;
}

void HuffmanCallable::setInputStream(std::istream *i)
{
    if (i != nullptr)
        is = i;
}
void HuffmanCallable::setOutputStream(std::ostream *o)
{
    if (os != nullptr)
        os = o;
}
void HuffmanCallable::setTreeStream(std::fstream *t)
{
    treeS = t;
}
void HuffmanCallable::setTreeVizStream(std::ofstream *v)
{
    treeViz = v;
}

Mode HuffmanCallable::getMode() const
{
    return mode;
}

std::istream *HuffmanCallable::getInputStream()
{
    return is;
}

std::ostream *HuffmanCallable::getOutputStream()
{
    return os;
}

std::fstream *HuffmanCallable::getTreeStream()
{
    return treeS;
}

std::ofstream *HuffmanCallable::getTreeVizStream()
{
    return treeViz;
}

void HuffmanCallable::operator()()
{
    HuffmanCode code(*is, *os, treeS);
    code(mode);
    if (treeViz != nullptr)
        code.visualizeTree(*treeViz);
}

HuffmanCallable::~HuffmanCallable()
{
    if (is != &std::cin)
        delete is;
    if (os != &std::cout)
        delete os;
    if (treeS != nullptr)
        delete treeS;
    if (treeViz != nullptr)
        delete treeViz;
}