#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node {
  public:
  int key;
  string value;
  Node *prev, *next;
  Node(int k, string v);
};

#endif
