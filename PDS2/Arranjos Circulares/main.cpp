#include <iostream>

#include "RingArray.h"

void fer_assert(const bool expr, const char* msg) {
  if (!expr) {
    std::cout << msg << std::endl;
    exit(1);
  }
}

template <class T, unsigned N>
void RingArray<T, N>::add(T value) {
  
  if(isFull()) { fer_assert(0, "Erro: anel cheio.");}
  else {
    buf[_last] = value;
    _last++;
  }
}

template <class T, unsigned N>
T RingArray<T, N>::get() {
  if (isEmpty()) {fer_assert(0, "Erro: anel vazio.");}
  else {
    T aux =buf[_first];
    for(int i= 0;i<_last-1; ++i) {
      buf[i]=buf[i+1];
    }
    _last--;
    return aux;
  }  
}

template <class T, unsigned N>
bool RingArray<T, N>::isFull() const {
  return (_last >= N-1);
}

template <class T, unsigned N>
bool RingArray<T, N>::isEmpty() const {
  return (_last == _first);
}

template <class T>
void test_add_then_get() {
  RingArray<T, 8> r;
  T value;
  while (std::cin >> value) {
    r.add(value);
  }
  while (!r.isEmpty()) {
    std::cout << r.get() << std::endl;
  }
}

template <class T>
void test_add_or_get() {
  RingArray<T, 8> r;
  T value;
  char c;
  while (std::cin >> c) {
    if (c == '+') {
      std::cin >> value;
      r.add(value);
    } else if (c == '-') {
      std::cout << r.get() << std::endl;
    } else {
      std::cout << "Invalid operation\n";
    }
  }
}

int main () {
  char data;
  while (std::cin >> data) {
    switch (data) {
      case 'd': test_add_then_get<double>();
                break;
      case 's': test_add_then_get<std::string>();
                break;
      case 'D': test_add_or_get<double>();
                break;
      case 'S': test_add_or_get<std::string>();
                break;
      default: std::cout << "Invalid type\n";
    }
  }
  return 0;
}