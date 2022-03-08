#include "Node.hpp"

Node::Node(): _next(nullptr), _data(0) {}
Node::Node(int data, Node* next): _next(next), _data(data) {}

void Node::setData(int data) {this->_data = data;}
void Node::setNext(Node *next) {this->_next = next;}
int Node::getData() const {return this->_data;}
Node* Node::getNext() const {return this->_next;}