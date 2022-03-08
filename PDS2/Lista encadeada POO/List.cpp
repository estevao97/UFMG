#include "List.hpp"

    List::List(): _head(nullptr), _end(nullptr), _size(0){}

    void List::insert(int value) {
      Node* node = new Node(value,nullptr);
      if (_head == nullptr)
      {
        _head = node;
        _end = node;
      }
      else
      {
        node->setNext(_head);
        _head = node;
      }
     _size++;
    }
    int List::remove() {
      if(_size>0)
      {
        Node* current = _head;
        int aux = _head->getData();
        _head = _head->getNext();
        _size--;
        delete current;
        return aux;
      }
      return 0;
    }
    bool List::isEmpty() {
      if (_head==nullptr) { return true;}
      return false;
    }

    unsigned List::size() const {
      return _size;
    }

    int List::middle() const {
      Node* current = new Node();
      current = _head;
      for(int i =0;i<_size/2;++i) {
        current = current->getNext();
      }
      return current->getData();
    }

    int List::last() const { 
        return _end->getData();
    }

    void List::rotate() {
      Node* nodo = new Node(_head->getData(),nullptr);
      _end->setNext(nodo);
      _end = nodo;
      _size++;
      remove();
    }
