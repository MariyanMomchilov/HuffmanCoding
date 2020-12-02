#define TESTS 1
#define DEBUG 1

#if DEBUG
#include "PriorityQueue.cpp"
#else
#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#endif

#if TESTS
#include "tests.cpp"
#endif

int main()
{
#if TESTS
    doctest::Context().run();
#else
    // "production" code
    00;
#endif

    return 0;
}