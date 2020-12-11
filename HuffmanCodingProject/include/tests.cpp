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
    char decodedA = tree.getDecoded(encodedA);
    std::string encodedB = tree.getEncoded('B');
    char decodedB = tree.getDecoded(encodedB);
    std::string encodedC = tree.getEncoded('C');
    char decodedC = tree.getDecoded(encodedC);
    std::string encodedR = tree.getEncoded('R');
    char decodedR = tree.getDecoded(encodedR);
    std::string encodedD = tree.getEncoded('D');
    char decodedD = tree.getDecoded(encodedD);
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

    std::ofstream out("../tests/scheme.txt");
    tree.toScheme(out);
    out.close();
    std::ifstream in("../tests/scheme.txt");
    tree.fromScheme(in);
    in.close();
}

TEST_CASE("Tree Iterator")
{
    std::vector<Node *> leafs = {new Node{'?', 6, nullptr, nullptr}, new Node{'?', 2, nullptr, nullptr}, new Node{'?', 3, nullptr, nullptr}};
    PriorityQueue pq(leafs);
    HuffmanTree tree(pq);
    std::cout << "ITERATOR: \n";
    for (Node *el : tree)
    {
        std::cout << el->key << ' ';
    }
    std::cout << '\n';
}

TEST_CASE("Huffman code")
{
    std::ifstream in("../tests/test1.txt");
    std::ofstream out("../tests/testOut1.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    hc.visualizeTree();
    in.close();
    out.close();

    in.open("../tests/testOut1.txt");
    out.open("../tests/testIn1.txt");
    HuffmanCode hcD(in, out);
    hcD.decode();

    in.close();
    out.close();
}

TEST_CASE("Huffman code2")
{
    std::ifstream in("../tests/test2.txt");
    std::ofstream out("../tests/testOut2.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    hc.visualizeTree();
    in.close();
    out.close();

    in.open("../tests/testOut2.txt");
    out.open("../tests/testIn2.txt");
    HuffmanCode hc2(in, out);
    hc2.decode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code3")
{
    std::ifstream in("../tests/test3.txt");
    std::ofstream out("../tests/testOut3.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();

    in.open("../tests/testOut3.txt");
    out.open("../tests/testIn3.txt");
    HuffmanCode hc2(in, out);
    hc2.decode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code4")
{
    std::ifstream in("../tests/test4.txt");
    std::ofstream out("../tests/testOut4.txt");
    HuffmanCode hc(in, out);
    hc.encode();
    in.close();
    out.close();

    in.open("../tests/testOut4.txt");
    out.open("../tests/testIn4.txt");
    HuffmanCode hc2(in, out);
    hc2.decode();
    in.close();
    out.close();
}

TEST_CASE("Huffman code with separated tree file")
{
    std::ifstream in("../tests/test2.txt");
    std::ofstream out("../tests/treeTestOut.txt");
    std::fstream treeStream("../tests/tree.txt", std::ios::out);

    HuffmanCode hc(in, out, &treeStream);
    hc.encode();
    in.close();
    out.close();
    treeStream.close();

    in.open("../tests/treeTestOut.txt");
    out.open("../tests/treeTestIn.txt");
    treeStream.open("../tests/tree.txt", std::ios::in);

    HuffmanCode hc2(in, out, &treeStream);
    hc.decode();
    in.close();
    out.close();
    treeStream.close();
}
