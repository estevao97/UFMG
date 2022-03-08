#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>

class Matrix {
  private:
  double** m; // m é um array 2D a ser implementado como um pointer de pointers
  int nRows; // numero de linhas
  int nCols; // numero de colunas
  
  public:
  // Construtores
  Matrix();
  Matrix(int rows, int cols, const double &value = 0.0);
  Matrix(std::ifstream &myFile);
  Matrix(const Matrix &that);
  // destrutor
  ~Matrix();
  // basic getters
  inline int getRows() const {return nRows;};
  inline int getCols() const {return nCols;};
  double get(int row, int col) const;
  // other methods
  void print() const;
  void unit();
  void zeros();
  void ones();

  double& operator() (int, int);
  Matrix operator+ (const Matrix& A);
  Matrix& operator-= (const Matrix &A);
  Matrix operator- (const Matrix& A) const;
  Matrix& operator+= (const Matrix& A);
  Matrix& operator*= (double d);
  Matrix operator* (const Matrix& X) const;
  Matrix& operator*= (const Matrix& X);
  bool operator== (const Matrix& C) const;
  bool operator!= (const Matrix& C) const;
  void operator=(const Matrix &other );
  friend Matrix operator~ (const Matrix& C);
  friend std::ostream& operator<< (std::ostream& op, const Matrix& A);
  friend std::istream& operator>> (std::istream& op, Matrix& A);
};

std::ostream& operator<< (std::ostream& op, const Matrix& A);
std::istream& operator>> (std::istream& op, Matrix& A);
Matrix operator~ (const Matrix& C);

#endif