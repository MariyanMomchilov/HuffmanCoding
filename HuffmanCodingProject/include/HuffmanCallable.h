#ifndef _HUFFCALLABLE
#define _HUFFCALLABLE
#include "HuffmanCode.h"

class HuffmanCallable
{
private:
    Mode mode;
    std::ifstream *is;
    std::ofstream *os;
    std::fstream *treeS;
    std::ofstream *treeViz;

public:
    HuffmanCallable(std::ifstream *i = nullptr, std::ofstream *o = nullptr, std::fstream *t = nullptr, std::ofstream *v = nullptr);
    void setMode(Mode m);
    void setInputStream(std::ifstream *i);
    void setOutputStream(std::ofstream *o);
    void setTreeStream(std::fstream *t);
    void setTreeVizStream(std::ofstream *v);

    Mode getMode() const;
    std::ifstream *getInputStream();
    std::ofstream *getOutputStream();
    std::fstream *getTreeStream();
    std::ofstream *getTreeVizStream();

    void operator()();
    ~HuffmanCallable();
};

#endif