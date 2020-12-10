#include "../include/Builder.h"

void HuffmanCodeBuilder::buildMode(Mode m)
{
    if (hcallable.getMode() != Mode::Empty)
        throw std::logic_error("Multiple modes provided. Select only only one mode\n");
    hcallable.setMode(m);
}

void HuffmanCodeBuilder::buildInput(const std::string &f)
{
    if (hcallable.getInputStream() != &std::cin)
        throw std::logic_error("Multiple input files provided. Rerun the program with only one -i or none \n");
    hcallable.setInputStream(new std::ifstream(f));
}

void HuffmanCodeBuilder::buildOutput(const std::string &f)
{
    if (hcallable.getOutputStream() != &std::cout)
        throw std::logic_error("Multiple output files provided. Rerun the program with only one-o or none \n");
    hcallable.setOutputStream(new std::ofstream(f));
}

void HuffmanCodeBuilder::buildTreeStream(const std::string &f)
{
    if (hcallable.getTreeStream() != nullptr)
        throw std::logic_error("Multiple tree files provided. Rerun the program with only one -t or none \n");
    if (hcallable.getMode() == Mode::Empty)
        throw std::logic_error("Set coding mode(-c | -d) before using -t flag\n");
    else if (hcallable.getMode() == Mode::Compression)
        hcallable.setTreeStream(new std::fstream(f, std::ios::out));
    else
        hcallable.setTreeStream(new std::fstream(f, std::ios::in));
}

void HuffmanCodeBuilder::buildTreeVizStream(const std::string &f)
{
    if (hcallable.getTreeVizStream() != nullptr)
        throw std::logic_error("Multiple tree visualization files provided. Restart the program using one -v or none \n");
    hcallable.setTreeVizStream(new std::ofstream(f));
}

HuffmanCallable &HuffmanCodeBuilder::getBuilt()
{
    return hcallable;
}