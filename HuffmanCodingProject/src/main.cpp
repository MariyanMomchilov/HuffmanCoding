#define TEST_MODE 0
#define DEBUG_MODE 0

#if DEBUG_MODE
#include "PriorityQueue.cpp"
#include "HuffmanTree.cpp"
#include "HuffmanCode.cpp"
#include "HuffmanCallable.cpp"
#include "Builder.cpp"
#include "CLI.cpp"
#else
#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#include "../include/HuffmanTree.h"
#include "../include/HuffmanCode.h"
#include "../include/CLI.h"
#endif

#if TEST_MODE
#include "../include/tests.cpp"
#endif

int main(int argc, char *argv[])
{
#if TEST_MODE
    doctest::Context().run();
#else
    CLI cmd(argc, argv);
    try
    {
        cmd.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
#endif

    return 0;
}