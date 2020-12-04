#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "../include/Node.h"
#include "../include/PriorityQueue.h"
#include "../include/HuffmanTree.h"
#include "../include/HuffmanCode.h"

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
    std::string encodedA = tree.getEncoded('A');
    char decodedA = tree.getDecoded(encodedA.c_str());
    std::string encodedB = tree.getEncoded('B');
    char decodedB = tree.getDecoded(encodedB.c_str());
    std::string encodedC = tree.getEncoded('C');
    char decodedC = tree.getDecoded(encodedC.c_str());
    std::string encodedR = tree.getEncoded('R');
    char decodedR = tree.getDecoded(encodedR.c_str());
    std::string encodedD = tree.getEncoded('D');
    char decodedD = tree.getDecoded(encodedD.c_str());
    CHECK(encodedA == "0");
    CHECK(encodedB == "110");
    CHECK(encodedC == "1110");
    CHECK(encodedD == "1111");
    CHECK(encodedR == "10");
    CHECK(decodedA == 'A');
    CHECK(decodedB == 'B');
    CHECK(decodedC == 'C');
    CHECK(decodedD == 'D');
    CHECK(decodedR == 'R');

    std::ofstream out("scheme.txt");
    tree.toScheme(out);
    out.close();
    std::ifstream in("scheme.txt");
    tree.fromScheme(in);
    in.close();
}

//TEST_CASE("Huffman code")
//{
//    HuffmanCode hc("ABRACADABRA");
//}

TEST_CASE("Huffman code")
{
    std::ifstream in("test.txt");
    std::ofstream out("testOut.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code2")
{
    std::ifstream in("test2.txt");
    std::ofstream out("testOut2.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code3")
{
    std::ifstream in("test3.txt");
    std::ofstream out("testOut3.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code4")
{
    std::ifstream in("test4.txt");
    std::ofstream out("testOut4.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();
}