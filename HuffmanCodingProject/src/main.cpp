#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#include "../include/HuffmanTree.h"
#include "../include/HuffmanCode.h"
#include "../include/CLI.h"

int main(int argc, char *argv[])
{
    CLI cmd(argc, argv);
    try
    {
        cmd.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}