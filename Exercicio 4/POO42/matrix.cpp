#include "matrix.h"

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
Matrix::Matrix(){
  nCols=0;
  nRows=0;
}
    

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0.0 (double)
Matrix::Matrix(int rows, int cols, const double &value){
  nRows = rows;
  nCols= cols;
	m = new double *[nRows];
	for (int i = 0; i < nRows; i++){
	  m[i]= new double [nCols];
		for (int j = 0; j < nCols; j++) {
      m[i][j]=value;
    }  
  }
}

// contrutor parametrico 2 - cria uma matriz com os dados fornecidos pelo arquivo texto myFile.
Matrix::Matrix(std::ifstream &myFile){
  std::string linha;
    nCols = 0;
    nRows = 0;
    int i = 0;

    myFile >> linha;
    nRows = stoi(linha);

    myFile >> linha;
    nCols = stoi(linha);

    m = new double *[nRows];

    for (int i = 0; i < nRows; i++) {
        m[i] = new double[nCols];
    }

    for (i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            myFile >> linha;
            m[i][j] = stod(linha);
        }
    }
}


// contrutor de copia
Matrix::Matrix(const Matrix &that){
	nRows = that.getRows();
  nCols = that.getCols();
  m = new double *[nRows];
    
  for (int i = 0; i < nRows; i++) {
        m[i] = new double[nRows];
    }
  
  for (int i = 0; i < nRows; i++) {
    for (int j = 0; j < nRows; j++) {
            m[i][j] = that.m[i][j];
        }
    }
}


// destrutor
Matrix::~Matrix() {
    for(int i = 0; i <getRows() ; ++i) {
    delete [] m[i];
  }
  delete []m;
}

// obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
double Matrix::get(int row, int col) const {
    if(row <= getRows() && row > 0 && col > 0 && col <= getCols()) {
        return m[row-1][col-1];
    } 
    else {exit(1); }
}

// imprime o conteudo da matriz
void Matrix::print() const {
    for (int i = 0; i < getRows(); i++){
      for (int j = 0; j < getCols(); j++){
        std::cout <<m[i][j]<< " ";
      }
    std::cout << std::endl;
  }
}

// faz com que a matriz torne-se uma matriz identidade
void Matrix::unit(){
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
      if(i==j) {m[i][j]=1;}
      else {m[i][j]=0;}
    }
  }
}

// faz com que a matriz torne-se uma matriz nula
void Matrix::zeros() {
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
       m[i][j]=0;
    }
  }
} 

// faz com que a matriz torne-se uma matriz cujos elementos sao iguaia a 1
void Matrix::ones(){
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
     m[i][j]=1;
    }
  }
}