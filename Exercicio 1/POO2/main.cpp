#include "Matriz.h"

#include <iostream>

int main() {
	Matriz A, B, T, R;

	std::cout << "A:: " << std::endl;
	inicializaMatriz(A, 2, 3, 7.0);
	imprimeMatriz(A);

	std::cout << "Transposta de A:: " << std::endl;
	T = transposta(A);
	imprimeMatriz(T);
	apagaMatriz(T);

	std::cout << std::endl << "B:: " << std::endl;
	inicializaMatriz(B,4,4,5.0);
	imprimeMatriz(B);

	std::cout << std::endl << "R = k*B " << std::endl;
	R = multiplica_por_cte(B,5);
	imprimeMatriz(R);

	apagaMatriz(B);
	apagaMatriz(R);

	return 0;
}