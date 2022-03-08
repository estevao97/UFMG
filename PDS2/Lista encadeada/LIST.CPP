#include "List.hpp"

List::List()
{
    _size = 0;
    _head = nullptr;
    _end = nullptr;
}

void List::insert(int value)
{
    Node* node = new Node();
    node->_value = value;
    node->_next = nullptr;
    if (_head == nullptr)
    {
        _head = node;
        _end = node;
    }
    else
    {
        _end->_next = node;
        _end = node;
    }
    _size++;
}

void List::clearList()
{
    while(_head != nullptr)
    {
        Node *_auxiliar = _head;
        _head = _head->_next ;
        delete _auxiliar;
    }
}

void List::print()
{
    Node* head = _head;
    if (_size > 0)
    {
        while(head != nullptr)
        {
            std::cout << head->_value << " ";
            head = head->_next;
        }
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<"-"<<std::endl;
    }
}

int List::removeFirst()
{
    if(_size>0)
    {
        Node* current = _head;
        _head = _head->_next;
        _size--;
        delete current;
        return 1;
    }
    return 0;
}

int List::indexOf(int value)
{
    if (_size > 0)
    {
        Node* head = _head;
        int index = 0;
        while(head->_next != nullptr)
        {
            if (head->_value == value)
            {
                return 1;
            }
            index++;
            head = head->_next;
        }
        return 0;
    }
    return 0;
}

void List::remove(int value)
{
    if(_size == 0 || value < 0)
    {
        return;
    }
    else if(_head->_value == value)
    {
        Node* current = _head;
        _head = _head->_next;
        _size--;
        delete current;
    }
    else
    {
        Node* previous = _head;
        Node* current = _head->_next;
        while(current != nullptr)
        {
            if(current->_value == value)
            {
                break;
            }
            else
            {
                previous = current;
                current = current->_next;
            }
        }
        if(current->_next == nullptr)
        {
            previous->_next = nullptr;
            _end = previous;
            _size--;
            delete current;
        }
        else
        {
            previous->_next = current->_next;
            _size--;
            delete current;
        }
    }
}
