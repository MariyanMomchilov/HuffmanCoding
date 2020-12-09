#ifndef __CLI
#define __CLI
#include "HuffmanCode.h"

enum class FlagType
{
    Compression,
    Decompression,
    Alternative,

    Input,
    Output,
    Tree,
    TreeViz,

    Empty,
    Invalid
};

class CLI
{
private:
    unsigned argc;
    char **argv;
    unsigned i;

    FlagType mode;
    std::ifstream *input;
    std::ofstream *output;
    std::fstream *treeStream;
    std::ofstream *treeVizStream;

    inline bool streamFlag(FlagType t) const;
    void handleStream(FlagType t);
    FlagType getNext();
    std::string getStr();
    void createInputStream(std::string &f);
    void createOutputStream(std::string &f);
    void createTreeStream(std::string &f);
    void createTreeVizStream(std::string &f);
    void parseCommand();

public:
    CLI(unsigned c, char *v[]);
    ~CLI();
    void run();
};

#endif