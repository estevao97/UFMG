#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

template <class TValor> class Matrix;

template <class TValor> 
std::ostream& operator<<(std::ostream&, const Matrix<TValor>&);
template <class TValor> 
Matrix<TValor> operator~ (Matrix<TValor>& C);

template <class TValor>
class Matrix {
  private:
  double** m; // m é um array 2D a ser implementado como um pointer de pointers
  int nRows; // numero de linhas
  int nCols; // numero de colunas
  
  public:
  // Construtores
  Matrix();
  Matrix(int linhas, int colunas);
  Matrix(int linhas, int colunas, const TValor& valor);
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

  double& operator() (int a, int b);
  Matrix operator+ (const Matrix& A) const;
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
  //friend std::ostream& operator<< (std::ostream& op, const Matrix& A);
  friend std::istream& operator>> (std::istream& op, Matrix& A);
};

//friend std::ostream& operator<< (std::ostream& op,  Matrix<TValor>& A);
//friend std::istream& operator>> (std::istream& op, Matrix<TValor>& A);
//Matrix<TValor> operator~ (Matrix<TValor>& C);

#endif

// ------------------------------------------------------------------- //
template <class TValor>
double Matrix<TValor>::get(int row, int col) const{
    if (nRows <= row || nCols <= col) throw std::invalid_argument("Index out of bounds.");
    return m[row][col];
}

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
template <class Tvalor>
Matrix<Tvalor>::Matrix() {
    nRows = 0;
    nCols = 0;
    m = NULL;
}
    
// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0.0 (double)
template <class Tvalor>
Matrix<Tvalor>::Matrix(int rows, int cols, const Tvalor &value){
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
template <class Tvalor>
Matrix<Tvalor>::Matrix(std::ifstream &myFile){
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
template <class Tvalor>
Matrix<Tvalor>::Matrix(const Matrix &that){
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
template <class Tvalor>
Matrix<Tvalor>::~Matrix() {
    for(int i = 0; i <getRows() ; ++i) {
    delete [] m[i];
  }
  delete []m;
}

// imprime o conteudo da matriz
template <class Tvalor>
void Matrix<Tvalor>::print() const {
    for (int i = 0; i < getRows(); i++){
      for (int j = 0; j < getCols(); j++){
        std::cout <<m[i][j]<< " ";
      }
    std::cout << std::endl;
  }
}

// faz com que a matriz torne-se uma matriz identidade
template <class Tvalor>
void Matrix<Tvalor>::unit(){
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
      if(i==j) {m[i][j]=1;}
      else {m[i][j]=0;}
    }
  }
}

// faz com que a matriz torne-se uma matriz nula
template <class Tvalor>
void Matrix<Tvalor>::zeros() {
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
      m[i][j]=0;
    }
  }
} 

// faz com que a matriz torne-se uma matriz cujos elementos sao iguaia a 1
template <class Tvalor>
void Matrix<Tvalor>::ones(){
  for (int i = 0; i < getRows(); i++){
    for (int j = 0; j < getCols(); j++){
      m[i][j]=1;
    }
  }
}

// altera o valor de uma posição de uma matriz
template <class Tvalor>
double &Matrix<Tvalor>::operator()(int a, int b) {
  if(a <= getRows() && a > 0 && b > 0 && b <= getCols()) {
        return this->m[a-1][b-1];
    } 
    else { 
      throw ("Erro: Indíces inválidos");
			
    }
}

// Soma duas matrizes e atribui o valor a uma terceira
template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator+(const Matrix &A) const {
  Matrix C(nRows, nCols);

    if ((nRows == A.nRows) && (nCols == A.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
             C.m[i][j] = A.m[i][j] + m[i][j];
            }
        }
    return C;
    }
    else { 
      throw "Erro: Matrizes de tamanhos diferentes";
    }
    
}

// Subtrai uma matriz pela outra e atribui o valor a primeira
template <class Tvalor>
Matrix<Tvalor> &Matrix<Tvalor>::operator-=(const Matrix &A) {
    if ((nRows == A.nRows) && (nCols == A.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
               this-> m[i][j] = this->m[i][j] - A.m[i][j];
            }
        }
        return *this;
    }
    else exit(1);
}

// Subtrai duas matrizes e atribui o valor a uma terceira
template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator-(const Matrix& A) const {
  Matrix C(nRows, nCols);

    if ((nRows == A.nRows) && (nCols == A.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                C.m[i][j] = this->m[i][j] - A.m[i][j];
            }
        }
    return C;
    }
    else { 
    throw"Erro: Matrizes de tamanhos diferentes";
    }
}

//Soma uma matriz pela outra e atribui o valor a primeira
template <class Tvalor>
Matrix<Tvalor> &Matrix<Tvalor>::operator+=(const Matrix &A) {
    if ((nRows == A.nRows) && (nCols == A.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                this->m[i][j] = this->m[i][j] + A.m[i][j];
            }
        }
        return *this;
    }
    else { 
      throw"Erro: Matrizes de tamanhos diferentes";
    }
}

//Multiplica uma matriz pela outra e atribui o valor a primeira
template <class Tvalor>
Matrix<Tvalor> &Matrix<Tvalor>::operator*=(const Matrix &X)  {
    if (nCols == X.nRows) {
        Matrix A(nRows,X.nCols);
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j<X.nCols; j++) {
                for (int k = 0; k<X.nRows; k++) {
                    A.m[i][j] += (m[i][k] * X.m[k][j]);
                }
            }
        }
        return *this;
    }
    else { 
      throw"Erro: Impossível realizar a multiplicação das matrizes";
    }
}

// Multiplica duas matrizes e atribui o valor a uma terceira
template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*(const Matrix& X) const {
    if (nCols == X.nRows) {
        Matrix A(nRows,X.nCols);
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j<X.nCols; j++) {
                for (int k = 0; k<X.nRows; k++) {
                    A.m[i][j] += (m[i][k] * X.m[k][j]);
                }
            }
        }
        return A;
    }
    else { 
      throw "Erro: Impossível realizar a multiplicação das matrizes";
    }
}

//Multiplica uma matriz pela outra (ou uma constante) e atribui o valor a primeira
template <class Tvalor>
Matrix<Tvalor> &Matrix<Tvalor>::operator*=(double d) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            this->m[i][j] = this->m[i][j] * d;
        }
    }
    return *this;
}

//Indica se duas matrizes são iguais
template <class Tvalor>
bool Matrix<Tvalor>::operator==(const Matrix &C) const {
    if ((nRows == C.nRows) && (nCols == C.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++)  {
                if (m[i][j] != C.m[i][j])
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}

//Indica se duas matrizes são diferentes
template <class Tvalor>
bool Matrix<Tvalor>::operator!=(const Matrix &C) const {
    if ((nRows == C.nRows) && (nCols == C.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                if (m[i][j] != C.m[i][j])
                    return 1;
            }
        }
        return 0;
    }
    return 1;
}

//Leitura de dados da matriz
template <class TValor>
std::ostream &operator<<(std::ostream &op, const Matrix<TValor> &A) {
    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getCols(); j++) {
            op << A.get(i,j) << ' ';
        }
        op << '\n';
    }

    return op;
}

//Leitura de dados para dentro da matriz
template <class TValor>
std::istream &operator>>(std::istream &op, Matrix<TValor> &A) {
    int lin;
    int col;
    op >> lin;
    op >> col;
    A.~Matrix();
    Matrix< TValor> B(lin, col);

    for (int i = 0; i < B.nRows; i++) {
        for (int j = 0; j < B.nCols; j++) {
            op >> B.m[i][j];
        }
    }
    A = B;
    return op;
}

//Transposta
template <class Tvalor>
Matrix<Tvalor> operator~(const Matrix<class TValor> &C) {
    Matrix<class TValor> A(C.nCols, C.nRows);

    for (int i = 0; i < C.nRows; i++) {
            for (int j = 0; j < C.nCols; j++) {
                A.m[j][i] = C.m[i][j];
            }
        }
    return A;
}

template <class Tvalor>
void Matrix<Tvalor>::operator=(const Matrix &A) {
    if(nCols==A.nCols && nRows==A.nRows) {
       for(int i=0;i<nRows;i++) {
        for(int j=0;j<nCols;j++) {
            m[i][j]=A.m[i][j];
        }
      }      
     }
      else { 
        throw "Erro: Impossível realizar a atribuição das matrizes";
    }
}