#include <iostream>

class Excecoes {
  private:
   const std::string _msg;
  public:
  Excecoes (std::string msg): _msg(msg) {}
  std::string getMsg () const {
    return _msg;
  }
};

template <class T, int N> class BoundedArray {
  private:
    T buf[N];
    int list[N]={1,1,1,1,1,1,1,1};
  public:
    void set(int index, T value) {
      if( index > N-1) { throw Excecoes("Erro: indice maior que arranjo.");}
      if( index < 0) { throw Excecoes("Erro: indice negativo.");}
      buf[index] = value;
      list[index] =0;
    }
    T get(int index) {
      if( index > N-1) { throw Excecoes("Erro: indice maior que arranjo.");}
      if( index < 0) { throw Excecoes("Erro: indice negativo.");}
      if( list[index]) { throw Excecoes("Erro: indice nao inicializado.");}
      return buf[index];
    }
};

template <class T> void testArray() {
  BoundedArray<T, 8> a;
  char action;
  while (std::cin >> action) {
    int index;
    std::cin >> index;
    try {
      if (action == 's') {
        T value;
        std::cin >> value;
        a.set(index, value);
      } else if (action == 'g') {
        std::cout << a.get(index) << std::endl;
      }
    } catch (Excecoes e) {
      std::cerr << e.getMsg() << std::endl;
      
    }
  }
}

int main() {
  char type;
  std::cin >> type;
  switch(type) {
    case 'd':
      testArray<double>();
      break;
    case 'i':
      testArray<int>();
      break;
    case 's':
      testArray<std::string>();
      break;
  }
  return 0;
}