#include "matrix.h"
#include <iostream>

int main() {
  std::ifstream in("myMatrix.txt");
  Matrix Y;
  Matrix X(3,1);
  Matrix Z(3,2,7.0);
  Matrix W(in);

  std::cout << "Y: " << std::endl;
  Y.print();
  std::cout << "Numero de linhas de Y: " << Y.getRows() << std::endl;
  std::cout << "Numero de colunas de Y: " << Y.getCols() << std::endl;

  std::cout << "X: " << std::endl;
  X.print();
  std::cout << "Numero de linhas de X: " << X.getRows() << std::endl;
  std::cout << "Numero de colunas de X: " << X.getCols() << std::endl;

  std::cout << "Z: " << std::endl;
  Z.print();
  std::cout << "Numero de linhas de Z: " << Z.getRows() << std::endl;
  std::cout << "Numero de colunas de Z: " << Z.getCols() << std::endl;

  std::cout << "W: " << std::endl;
  W.print();
  std::cout << "Numero de linhas de W: " << W.getRows() << std::endl;
  std::cout << "Numero de colunas de W: " << W.getCols() << std::endl;

  Matrix A(3,3,3);
  std::cout << std::endl << "A: " << std::endl;
  A.print();

  double elem = A.get(1,2);
  std::cout << std::endl << "Elemento: " << elem << std::endl;

  std::cout << std::endl << "A identidade: " << std::endl;
  A.unit();
  A.print();

  std::cout << std::endl << "A de zeros: " << std::endl;
  A.zeros();
  A.print();

  std::cout << std::endl << "A de uns: " << std::endl;
  A.ones();
  A.print();

  std::cout << std::endl << "B: " << std::endl;
  Matrix B(A);
	B.print();

return 0;
}