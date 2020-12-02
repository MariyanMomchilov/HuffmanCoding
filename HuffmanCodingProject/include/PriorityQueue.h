#ifndef __PQUEUE
#define __PQUEUE
#include <vector>
#include "Node.h"

class PriorityQueue
{
private:
    std::vector<Node *> buffer;

    inline unsigned parent(unsigned i);
    inline unsigned left(unsigned i);
    inline unsigned right(unsigned i);
    inline void swap(unsigned i, unsigned j);
    void heapify(unsigned i);

public:
    PriorityQueue(std::vector<Node *> &arr);
    void insert(Node *);
    Node *peekPop();
    Node *peek();
    bool empty() const;
    ~PriorityQueue() = default;
};

#endif