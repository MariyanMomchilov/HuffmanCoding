#include "../include/HuffmanCallable.h"

HuffmanCallable::HuffmanCallable(std::ifstream *i, std::ofstream *o, std::fstream *t, std::ofstream *v) : mode(Mode::Empty), is(i), os(o), treeS(t), treeViz(v) {}

void HuffmanCallable::setMode(Mode m)
{
    mode = m;
}

void HuffmanCallable::setInputStream(std::ifstream *i)
{
    if (i != nullptr)
        is = i;
}
void HuffmanCallable::setOutputStream(std::ofstream *o)
{
    if (o != nullptr)
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

std::ifstream *HuffmanCallable::getInputStream()
{
    return is;
}

std::ofstream *HuffmanCallable::getOutputStream()
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
    if (is != nullptr && os != nullptr)
    {
        if (!is->is_open())
            throw std::invalid_argument("Invalid input file\n");
        if (!os->is_open())
            throw std::invalid_argument("Invalid output file\n");
        if (treeS != nullptr && !treeS->is_open())
            throw std::invalid_argument("Invalid tree file\n");

        HuffmanCode code(*is, *os, treeS);
        code(mode);

        if (treeViz != nullptr)
            code.visualizeTree(*treeViz);
    }
    else if (is == nullptr)
        throw std::logic_error("Input not provided!\n");
    else
        throw std::logic_error("Output not provided!\n");
}

HuffmanCallable::~HuffmanCallable()
{
    if (is != nullptr)
    {
        is->close();
        delete is;
    }
    if (os != &std::cout)
    {
        os->close();
        delete os;
    }
    if (treeS != nullptr)
    {
        treeS->close();
        delete treeS;
    }
    if (treeViz != nullptr)
    {
        treeViz->close();
        delete treeViz;
    }
}