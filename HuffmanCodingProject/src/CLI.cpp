#include "../include/CLI.h"
#include "../include/HuffmanCallable.h"
#include <cstring>

std::string CLI::getStr()
{
    i++;
    const char *str = argv[i];
    if (*str == '-')
    {
        std::string errorMsg = "Expected filename, but command" + std::string(str) + " was given\n";
        throw std::logic_error(errorMsg);
    }

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

void CLI::parseCommand(Builder &builder)
{

    while (argv[i] != nullptr)
    {
        if (!strcmp(argv[i], "-c"))
            builder.buildMode(Mode::Compression);
        else if (!strcmp(argv[i], "-d"))
            builder.buildMode(Mode::Decompression);
        else if (!strcmp(argv[i], "-i"))
            builder.buildInput(getStr());
        else if (!strcmp(argv[i], "-o"))
            builder.buildOutput(getStr());
        else if (!strcmp(argv[i], "-t"))
            builder.buildTreeStream(getStr());
        else if (!strcmp(argv[i], "-v"))
            builder.buildTreeVizStream(getStr());
        else
            throw std::logic_error("Unrecognized flag " + std::string(argv[i]) + "\n");
        i++;
    }
}

CLI::CLI(unsigned c, char *v[]) : argc(c), argv(v), i(1) {}

void CLI::run()
{
    if (!strcmp(argv[i], "huffman"))
    {
        i++;
        HuffmanCodeBuilder builder;
        parseCommand(builder);
        builder.getBuilt()();
    }
    else
        throw std::logic_error("Only Huffman coding functionality so far\n");
}