#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>

typedef struct{
  double** m;
  int nLinhas;
  int nColunas;
} Matriz;

void inicializaMatriz(Matriz &X, int ls, int cs, const double elem) { 
  X.nLinhas = ls;
  X.nColunas = cs;
	X.m = new double *[ls];

	for (int i = 0; i < X.nLinhas; i++){
		X.m[i]= new double [X.nColunas];
		for (int j = 0; j < X.nColunas; j++)
     X.m[i][j]=elem;
  }
}

void apagaMatriz(Matriz &X){
  for(int i = 0; i <X.nLinhas ; ++i) {
    delete [] X.m[i];
  }

  delete []X.m;
}

Matriz transposta(Matriz &X){
  int nova_linha = X.nColunas;
  int nova_coluna = X.nLinhas;
  double elem = X.m[0][0];
  apagaMatriz(X);
  Matriz trans;
  inicializaMatriz(trans, nova_linha, nova_coluna, elem);
  return trans;
}

Matriz multiplica_por_cte(Matriz &X, double k){
  for (int i = 0; i < X.nColunas; i++){
		for (int j = 0; j < X.nLinhas; j++)
      X.m[i][j] *= k;
  }
  
  return X;
}

void imprimeMatriz(Matriz &X){
  for (int i = 0; i < X.nLinhas; i++){
    for (int j = 0; j < X.nColunas; j++){
      std::cout <<X.m[i][j]<< " ";
    }
    std::cout << std::endl;
  }
}

#endif