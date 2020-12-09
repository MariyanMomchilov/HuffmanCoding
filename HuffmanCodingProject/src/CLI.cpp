#include "../include/CLI.h"

// много тромав дизай, измисли по-добро...

inline bool CLI::streamFlag(FlagType t) const
{
    return t == FlagType::Input || t == FlagType::Output || t == FlagType::Tree || t == FlagType::TreeViz;
}

void CLI::createInputStream(std::string &f)
{
    if (input != nullptr)
        throw std::logic_error("Multiple filenames are provided for input\n");

    input = new std::ifstream(f);
}

void CLI::createOutputStream(std::string &f)
{
    if (output != nullptr)
        throw std::logic_error("Multiple filenames are provided for output\n");
    output = new std::ofstream(f);
}

void CLI::createTreeStream(std::string &f)
{
    if (treeStream != nullptr)
        throw std::logic_error("Multiple filenames are provided for file that contains tree\n");
    if (mode == FlagType::Compression)
        treeStream = new std::fstream(f, std::fstream::out);
    else
        treeStream = new std::fstream(f, std::fstream::in);
}

void CLI::createTreeVizStream(std::string &f)
{
    if (treeStream != nullptr)
        throw std::logic_error("Multiple filenames are provided for .dot file\n");
    treeVizStream = new std::ofstream(f);
}

void CLI::handleStream(FlagType t)
{
    std::string filename = getStr();
    switch (t)
    {
    case FlagType::Input:
        createInputStream(filename);
        return;
    case FlagType::Output:
        createOutputStream(filename);
        return;
    case FlagType::Tree:
        createTreeStream(filename);
        return;
    case FlagType::TreeViz:
        createTreeVizStream(filename);
        return;
    }
}

FlagType CLI::getNext()
{
    const char *str = argv[i];
    if (*str != '-')
        throw std::logic_error("Invalid flag");
    str++;
    if (*str == 'c' && *(str + 1) == 0)
        return FlagType::Compression;
    if (*str == 'd' && *(str + 1) == 0)
        return FlagType::Decompression;
    if (*str == 'a' && *(str + 1) == 0)
        return FlagType::Alternative;
    if (*str == 'i' && *(str + 1) == 0)
        return FlagType::Input;
    if (*str == 'o' && *(str + 1) == 0)
        return FlagType::Output;
    if (*str == 't' && *(str + 1) == 0)
        return FlagType::Tree;
    if (*str == 'v' && *(str + 1) == 0)
        return FlagType::TreeViz;

    throw std::logic_error("Unrecognised flag");
}

std::string CLI::getStr()
{
    const char *str = argv[i];
    if (*str == '-')
    {
        std::string errorMsg = "Expected filename, but command" + std::string(str) + " was given\n";
        throw std::logic_error(errorMsg);
    }
    i++;
    if (*str == '\'' || *str == '\"')
    {
        char quote = *str;
        str++;
        std::string res;
        while (*str != quote || (*str == quote && *(str + 1) == 0))
        {
            res += *str;
            str++;
        }
        return res;
    }
    return std::string(str);
}

void CLI::parseCommand()
{
    FlagType flag;
    while (argv[i] != nullptr)
    {
        flag = getNext();
        i++;
        if (streamFlag(flag))
            handleStream(flag);
        else if (mode == FlagType::Empty)
            mode = flag;
        else
            throw std::logic_error("Multiple encoding flags are set\n");
    }
}

CLI::CLI(unsigned c, char *v[]) : argc(c), argv(v), i(1), mode(FlagType::Empty), input(nullptr), output(nullptr), treeStream(nullptr), treeVizStream(nullptr) {}

CLI::~CLI()
{
    if (input != nullptr)
    {
        input->close();
        delete input;
    }
    if (output != nullptr)
    {
        output->close();
        delete output;
    }
    if (treeStream != nullptr)
    {
        treeStream->close();
        delete treeStream;
    }
    if (treeVizStream != nullptr)
    {
        treeVizStream->close();
        delete treeVizStream;
    }
}
void CLI::run()
{
    parseCommand();
    //specified
    std::cout << treeStream->is_open() << '\n';
    HuffmanCode code(*input, *output, treeStream);
    if (mode == FlagType::Compression)
        code.encode();
    else
        code.decode();
}