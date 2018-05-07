#include "LRUQueue.h"

LRUQueue::LRUQueue(): front(NULL), back(NULL) {}

bool LRUQueue::isEmpty() {
  return back==NULL;
}

Node* LRUQueue::insert(int key, string value) {
    Node *valueNode = new Node(key, value);
    if(!front && !back) {
        front = back = valueNode;
    }
    else {
        valueNode->next = front;
        front->prev = valueNode;
        front = valueNode;
    }
    return valueNode;
}

void LRUQueue::touch(Node *valueNode) {
    if(valueNode==front)
        return;

    if(valueNode==back) {
        back = back->prev;
        back->next = NULL;
    } else {
        valueNode->prev->next = valueNode->next;
        valueNode->next->prev = valueNode->prev;
    }

    valueNode->next = front;
    valueNode->prev = NULL;
    front->prev = valueNode;
    front = valueNode;
}

void LRUQueue::erase(Node *valueNode) {
    if(valueNode==front){
        front = valueNode->next;
        if(front!=NULL)
            front->prev = NULL;
    } else {
        valueNode->prev->next = valueNode->next;
    }
    if(valueNode==back){
        back = back->prev;
        if(back!=NULL)
            back->next = NULL;
    } else {
        valueNode->next->prev = valueNode->prev;
    }
    valueNode = NULL;
    delete valueNode;
}

void LRUQueue::evict() {
    if(isEmpty())
        return;

    if(front==back) {
        delete back;
        front = back = NULL;
    } else {
        Node *temp = back;
        back = back->prev;
        back->next = NULL;
        delete temp;
    }
}

Node* LRUQueue::getLast() {
    return back;
}
