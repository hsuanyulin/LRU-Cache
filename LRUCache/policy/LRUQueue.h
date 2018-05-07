#ifndef LPR_QUEUE_H
#define LPR_QUEUE_H

#include <string>
#include "Node.h"
using namespace std;

class LRUQueue {
public:
    LRUQueue();

    void touch(Node *valueNode);
    void erase(Node *valueNode);
    void evict();

    Node* insert(int key, string value);
    Node* getLast();
private:
  Node *front, *back;
  bool isEmpty();
};

#endif
