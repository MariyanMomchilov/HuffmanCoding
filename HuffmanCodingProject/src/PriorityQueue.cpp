#include "../include/PriorityQueue.h"
#include <stdexcept>

void PriorityQueue::swap(unsigned i, unsigned j)
{
    Node *tmp = buffer[i];
    buffer[i] = buffer[j];
    buffer[j] = tmp;
}

unsigned PriorityQueue::parent(unsigned i) { return (i - 1) / 2; }
unsigned PriorityQueue::left(unsigned i) { return 2 * i + 1; }
unsigned PriorityQueue::right(unsigned i) { return 2 * (i + 1); }

bool PriorityQueue::empty() const
{
    return buffer.size() == 0;
}

void PriorityQueue::heapify(unsigned i)
{
    unsigned size = buffer.size();
    if (i >= size)
        return;

    unsigned min = i;
    unsigned l = left(i);
    unsigned r = right(i);

    if (l < size && buffer[l]->key < buffer[min]->key)
        min = l;
    if (r < size && buffer[r]->key < buffer[min]->key)
        min = r;

    if (min != i)
    {
        if (min == l)
        {
            swap(i, l);
            heapify(l);
        }
        else
        {
            swap(i, r);
            heapify(r);
        }
    }
}

PriorityQueue::PriorityQueue(std::vector<Node *> &arr) : buffer(arr)
{
    for (int i = (buffer.size() / 2 - 1); i > -1; i--)
    {
        heapify(i);
    }
}

void PriorityQueue::insert(Node *node)
{
    if (buffer.size() >= buffer.capacity())
        throw std::overflow_error("Heap overflow. Capacity of 256 exceeded\n");

    unsigned i = buffer.size();
    buffer.push_back(node);

    while (i > 0 && buffer[i]->key < buffer[parent(i)]->key)
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

Node *PriorityQueue::peek()
{
    if (buffer.size() == 0)
        throw std::underflow_error("Read/Write from an empty heap\n");
    return buffer[0];
}

Node *PriorityQueue::peekPop()
{
    unsigned size = buffer.size();
    if (size == 0)
        throw std::underflow_error("Heap underflow. Popping from an empty heap\n");

    Node *result = buffer[0];
    buffer[0] = buffer[size - 1];
    buffer.pop_back();
    heapify(0);

    return result;
}
