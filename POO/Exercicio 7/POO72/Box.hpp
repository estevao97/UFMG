#ifndef BOX_HPP
#define BOX_HPP

#include "Ponto3D.hpp"

#include <iostream>
#include <math.h>


class Box {
  public:
    Box(double a, double l, double p);
    double area();
    double volume();
    friend double distTo(Ponto3D& P1, Ponto3D& P2);
    Box(Ponto3D pp1, Ponto3D pp2, Ponto3D pp3, Ponto3D pp4, Ponto3D pp5, Ponto3D pp6, Ponto3D pp7, Ponto3D pp8);

  private:
    double _largura;
    double _altura;
    double _profundidade;
};

#endif

double distTo(Ponto3D& P1, Ponto3D& P2){
    return (sqrt(pow((P2.get_x()-P1.get_x()),2)+pow((P2.get_y()-P1.get_y()),2)+pow((P2.get_z()-P1.get_z()),2)));
}    

Box::Box(double a, double l, double p){
  _altura = a;
  _largura = l;
  _profundidade = p;
}

Box::Box(Ponto3D pp1, Ponto3D pp2, Ponto3D pp3, Ponto3D pp4, Ponto3D pp5, Ponto3D pp6, Ponto3D pp7, Ponto3D pp8){
    _largura = distTo(pp3, pp4);
    _altura = distTo(pp3, pp5);
    _profundidade = distTo(pp3, pp1);
}

double Box::area(){
  return (2*(_largura * _altura + _largura * _profundidade + _altura * _profundidade));
}

double Box::volume(){
  return (_largura * _altura * _profundidade);
}