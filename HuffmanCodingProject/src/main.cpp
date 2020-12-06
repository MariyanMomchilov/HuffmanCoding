#define TEST_MODE 1
#define DEBUG_MODE 0

#if DEBUG_MODE
#include "PriorityQueue.cpp"
#include "HuffmanTree.cpp"
#include "HuffmanCode.cpp"
#else
#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#include "../include/HuffmanTree.h"
#include "../include/HuffmanCode.h"
#endif

#if TEST_MODE
#include "../include/tests.cpp"
#endif

int main()
{
#if TEST_MODE
    doctest::Context().run();
#else
    // "production" code
    00;
#endif

    return 0;
}