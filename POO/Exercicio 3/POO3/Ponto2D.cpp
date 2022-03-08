#include "Ponto2D.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

  Ponto2D::Ponto2D(): _x(0),_y(0){ _id=getNextId(); }
  Ponto2D::Ponto2D(double a, double b): _x(a),_y(b){ _id=getNextId(); }

    Ponto2D::~Ponto2D(){
    list_ids.remove(_id);
  }

  int Ponto2D::getId() {
    return _id;
  }

  int Ponto2D::getNextId() {
    std::random_device rd; // gerador de números aleatórios não-determinístico
    std::mt19937 mt(rd()); // gerador de números aleatórios cuja semente é rd()
    std::uniform_int_distribution<int> rand(0, 1000); //valores inteiros uniformemente distribuídos em um intervalo 
    _id = rand( mt ); 

    //verifica se o novo id está na lista.Caso positivo gera um novo id
    auto result = std::find(list_ids.begin(),list_ids.end(), _id);
    if(result != list_ids.end()) {
      _id = rand( mt );
    }
    list_ids.push_front(_id);
    return _id;
  }

  void Ponto2D::print() const{
    std::cout << "X: " << _x << std::endl;
    std::cout << "Y: " << _y << std::endl;
  }

  double Ponto2D::distToOrig(){
    return (sqrt(pow(_x, 2)+pow(_y, 2)));
  }

  double Ponto2D::distTo(const Ponto2D &p1){
    return (sqrt(pow((_x - p1._x), 2)+pow((_y - p1._y), 2)));
  }

  Ponto2D Ponto2D::sumOf(const Ponto2D &p2){
    Ponto2D p3((_x + p2._x),( _y + p2._y));
    return p3;
  }
  void Ponto2D::sum(const Ponto2D &p3){
    _x += p3._x;
    _y += p3._y;
  }

 std::list<int> Ponto2D::list_ids;  /*static*/ 