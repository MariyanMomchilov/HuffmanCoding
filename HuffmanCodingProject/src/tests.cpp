#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#include "../include/HuffmanTree.h"

TEST_CASE("Priority Q")
{
    std::vector<Node *> buff{new Node{'a', 7, nullptr, nullptr}, new Node{'a', 8, nullptr, nullptr}, new Node{'a', 5, nullptr, nullptr}, new Node{'a', 9, nullptr, nullptr}, new Node{'a', 4, nullptr, nullptr}, new Node{'a', 2, nullptr, nullptr}};
    PriorityQueue pq(buff);

    CHECK(pq.peek()->key == 2);
    pq.peekPop();
    CHECK(pq.peek()->key == 4);
    pq.insert(new Node{'a', 0, nullptr, nullptr});
    CHECK(pq.peek()->key == 0);
    while (!pq.empty())
    {
        pq.peekPop();
    }
    pq.insert(new Node{'a', 10, nullptr, nullptr});
    pq.insert(new Node{'a', 5, nullptr, nullptr});
    CHECK(pq.peek()->key == 5);
}

TEST_CASE("Huffman tree")
{
    std::vector<Node *> buff{new Node{'A', 5, nullptr, nullptr}, new Node{'B', 2, nullptr, nullptr}, new Node{'R', 2, nullptr, nullptr}, new Node{'C', 1, nullptr, nullptr}, new Node{'D', 1, nullptr, nullptr}};
    PriorityQueue pq(buff);
    HuffmanTree tree(pq);
}

TEST_CASE("Huffman code")
{
    HuffmanCode hc("ABRACADABRA");
}

TEST_CASE("Huffman code2")
{
    std::ifstream in("test.txt");
    bool op = in.is_open();
    HuffmanCode hc(in);
}