#ifndef __CLI
#define __CLI
#include "Builder.h"
#include "HuffmanCode.h"

class CLI
{
private:
    unsigned argc;
    char **argv;
    unsigned i;

    std::string getStr();
    void parseCommand(Builder &builder);

public:
    CLI(unsigned c, char *v[]);
    ~CLI() = default;
    void run();
};

#endif