#include "matrix.h"

  Matrix::Matrix(){
    nCols = 0;
    nRows = 0;
    m = 0;
  }

  Matrix::Matrix(int rows, int cols, double elem){
    nCols = cols;
    nRows = rows;
    m = new double *[rows];

    for (int i = 0; i < nRows; i++){
		  m[i]= new double [nCols];
		  for (int j = 0; j < nCols; j++) m[i][j]=elem;
    }
  }

  Matrix::~Matrix() {
    for(int i = 0; i < nRows; ++i) {
      delete [] m[i];
    }
    delete []m;
  }

  int Matrix::getRows() const {
    return nRows;
  }

  int Matrix::getCols() const {
    return nCols;
  }

  Matrix Matrix::transpose() {
    double elem = m[0][0];
    Matrix nova_matriz = Matrix(nCols, nRows, elem);
    return nova_matriz;
  }

  void Matrix::print() const {
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nCols; j++){
        std::cout << m[i][j] << " ";
      }
    std::cout << std::endl;
    }
  }