#include "LRUCache.h"
#define ERROR_NO_KEY "Key does not exist"
using cacheLock = lock_guard<mutex>;

LRUCache::LRUCache(int memoryMax):size(0), memoryMax(memoryMax) {
    this->lruQueue = new LRUQueue();
    this->hashtable = unordered_map<int, Node*>();
}

string LRUCache::get(int key) {
    cacheLock guard(cacheMutex);
    if(hashtable.find(key)==hashtable.end())
      return ERROR_NO_KEY;

    string val = hashtable[key]->value;
    lruQueue->touch(hashtable[key]);
    return val;
}

void LRUCache::erase(int key) {
    cacheLock guard(cacheMutex);
    if(hashtable.find(key)==hashtable.end())
      return;

    lruQueue->erase(hashtable[key]);
    hashtable.erase(key);
    size--;
}

void LRUCache::put(int key, string value) {
    cacheLock guard(cacheMutex);
    if(hashtable.find(key)!=hashtable.end()) {
        hashtable[key]->value = value;
        lruQueue->touch(hashtable[key]);
        return;
    }

    if(size == memoryMax) {
      int k = lruQueue->getLast()->key;
      hashtable.erase(k);
      lruQueue->evict();
      size--;
    }

    Node *valueNode = lruQueue->insert(key, value);
    size++;
    hashtable[key] = valueNode;
}

LRUCache::~LRUCache() {
    unordered_map<int, Node*>::iterator index;
    index = hashtable.begin();
    while(index!=hashtable.end()){
        delete index->second;
        index++;
    }
    delete lruQueue;
}
