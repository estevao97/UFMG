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
    else exit(1);
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

// altera o valor de uma posição de uma matriz
double &Matrix::operator()(int a, int b) {
  if(a <= getRows() && a > 0 && b > 0 && b <= getCols()) {
        return this->m[a-1][b-1];;
    } 
    else { 
      std::cout << "Erro: Indíces inválidos" <<std::endl;
      exit(1);
    }
}

// Soma duas matrizes e atribui o valor a uma terceira
Matrix Matrix::operator+(const Matrix &A) {
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
      std::cout << "Erro: Matrizes de tamanhos diferentes" <<std::endl;
      exit(1);
    }
    
}

// Subtrai uma matriz pela outra e atribui o valor a primeira
Matrix &Matrix::operator-=(const Matrix &A) {
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
Matrix Matrix::operator-(const Matrix& A) const {
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
      std::cout << "Erro: Matrizes de tamanhos diferentes" <<std::endl;
      exit(1);
    }
}

//Soma uma matriz pela outra e atribui o valor a primeira
Matrix &Matrix::operator+=(const Matrix &A) {
    if ((nRows == A.nRows) && (nCols == A.nCols)) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                this->m[i][j] = this->m[i][j] + A.m[i][j];
            }
        }
        return *this;
    }
    else { 
      std::cout << "Erro: Matrizes de tamanhos diferentes" <<std::endl;
      exit(1);
    }
}

//Multiplica uma matriz pela outra e atribui o valor a primeira
Matrix &Matrix::operator*=(double d) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            this->m[i][j] = this->m[i][j] * d;
        }
    }
    return *this;
}

// Multiplica duas matrizes e atribui o valor a uma terceira
Matrix Matrix::operator*(const Matrix& X) const {
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
      std::cout << "Erro: Impossível realizar a multiplicação das matrizes" <<std::endl;
      exit(1);
    }
}

//Multiplica uma matriz pela outra (ou uma constante) e atribui o valor a primeira
Matrix &Matrix::operator*=(const Matrix &X) {
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
      std::cout << "Erro: Impossível realizar a multiplicação das matrizes" <<std::endl;
      exit(1);
    }
}

//Indica se duas matrizes são iguais
bool Matrix::operator==(const Matrix &C) const {
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
bool Matrix::operator!=(const Matrix &C) const {
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
std::ostream &operator<<(std::ostream &op, const Matrix &A) {
    for (int i = 0; i < A.nRows; i++) {
        for (int j = 0; j < A.nCols; j++) {
            op << A.m[i][j] << ' ';
        }
        op << '\n';
    }

    return op;
}

//Leitura de dados para dentro da matriz
std::istream &operator>>(std::istream &op, Matrix &A) {
    int lin;
    int col;
    op >> lin;
    op >> col;
    A.~Matrix();
    Matrix B(lin, col);

    for (int i = 0; i < B.nRows; i++) {
        for (int j = 0; j < B.nCols; j++) {
            op >> B.m[i][j];
        }
    }
    A = B;
    return op;
}

//Transposta
Matrix operator~(const Matrix &C) {
    Matrix A(C.nCols, C.nRows);

    for (int i = 0; i < C.nRows; i++) {
            for (int j = 0; j < C.nCols; j++) {
                A.m[j][i] = C.m[i][j];
            }
        }
    return A;
}

void Matrix::operator=(const Matrix &A) {
    if(nCols==A.nCols && nRows==A.nRows) {
       for(int i=0;i<nRows;i++) {
        for(int j=0;j<nCols;j++) {
            m[i][j]=A.m[i][j];
        }
      }      
     }
      else { 
      std::cout << "Erro: Impossível realizar a atribuição das matrizes" <<std::endl;
      exit(1);
    }
}