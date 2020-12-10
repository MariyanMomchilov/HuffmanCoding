#ifndef _HUFFCALLABLE
#define _HUFFCALLABLE
#include "HuffmanCode.h"

class HuffmanCallable
{
private:
    Mode mode;
    std::istream *is;
    std::ostream *os;
    std::fstream *treeS;
    std::ofstream *treeViz;

public:
    HuffmanCallable(std::istream *i = &std::cin, std::ostream *o = &std::cout, std::fstream *t = nullptr, std::ofstream *v = nullptr);
    void setMode(Mode m);
    void setInputStream(std::istream *i);
    void setOutputStream(std::ostream *o);
    void setTreeStream(std::fstream *t);
    void setTreeVizStream(std::ofstream *v);

    Mode getMode() const;
    std::istream *getInputStream();
    std::ostream *getOutputStream();
    std::fstream *getTreeStream();
    std::ofstream *getTreeVizStream();

    void operator()();
    ~HuffmanCallable();
};

#endif