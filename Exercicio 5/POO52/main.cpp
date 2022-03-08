#include "matrix.h"
#include <iostream>

int main() {
  std::ifstream in("myMatrix.txt");
  Matrix Y;
  Matrix X(3,1,2);
  Matrix Z(3,2,7.0);
  Matrix W(in);

  /*std::cout << "Y: " << std::endl;
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
	B.print();*/
  
  Matrix A(3,3,1);

  A(2,1) = 10; // altera o valor de uma posição de A
	std::cout << "\nMatriz A:" << std::endl;
	A.print();

  Matrix C = A + A; // Soma
	std::cout << "\nMatriz C = A + A:" << std::endl;
	C.print();
  
  C -= A; // Subtração
  std::cout << "\nMatriz C -= A:" << std::endl;
	C.print();
  
  A = C - A; // Subtração
	std::cout << "\nMatriz A = C - A:" << std::endl;
	A.print();

  A += C; // Soma
	std::cout << "\nMatriz A += C:" << std::endl;
	std::cout<<A;

  A = ~C; // A é igual a transposta de C
	std::cout << "\nMatriz C Transposta" << std::endl;
	std::cout<<A;

  X *= 2; // multiplicação por uma constante
	std::cout << "\nMatriz X * 2:" << std::endl;
	std::cout<<X;

  Matrix D = A*X; // multiplicação de matrizes
	std::cout << "\nMatriz D = A * X:" << std::endl;
	std::cout<<D;

  Matrix E(1,3,2);
  E*=X; // multiplicação de matrizes
	std::cout << "\nMatriz E *= X:" << std::endl;
	std::cout<<E;

	std::cout << "\nA == C:" << std::endl;
  if (A == C) // verifica a igualdade entre A e C
  std::cout << "A é igual a C" << std::endl;

	std::cout << "\nX != Y" << std::endl;
  if(X != Y) // verifica a desigualdade entre A e C
  std::cout << "X é diferente de Y" << std::endl;

  std::cout << "\nZ:" << std::endl;
  std::cout << Z << std::endl; // impressão de matrizes
  std::cin >> W; // leitura de dados para dentro da matriz Y*/

return 0;
}