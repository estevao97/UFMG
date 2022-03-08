#include "Stack.h"

struct Node {
  unsigned elem;
  Node* next;
};

Stack::Stack() {
  _count = 0;
  _top = nullptr;
}

void Stack::push(unsigned elem) {
  
    
    Node* node = new Node();
    node->elem= elem;
    node-> next = nullptr;
    if (_top != nullptr) {
      node->next = _top;
    } 
    _top = node;
    _count++;
}

void Stack::pop() {
  if( _count == 0) { throw EmptyException ();}
    
        Node* node = _top;
        if (node->next != nullptr) {
          _top = _top->next;
        }
        _count--;
        delete node; 
  
    
}

unsigned Stack::top() const {
  if( _count == 0) { throw EmptyException ();}
  return _top->elem; // TODO.
}

unsigned Stack::count() const {
  return _count; 
}