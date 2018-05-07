#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <mutex>
#include <string>
#include "policy/Node.h"
#include "policy/LRUQueue.h"
using namespace std;

class LRUCache{
private:
  int memoryMax, size;
  LRUQueue *lruQueue;
  unordered_map<int, Node*> hashtable;
  mutable mutex cacheMutex;

public:
  LRUCache(int memoryMax);
  string get(int key);
  void put(int key, string value);
  void erase(int key);
  ~LRUCache();
};

#endif
