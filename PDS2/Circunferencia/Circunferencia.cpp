#include "Circunferencia.hpp"
#include <cmath>

 Circunferencia::Circunferencia(double cx, double cy, double r){

    xc= cx;
    yc= cy;
    raio = r;
 }
 
 double Circunferencia::calcularArea(){
        double area;
        area = PI*(pow(raio,2));
        return area;
    }

  bool Circunferencia::possuiIntersecao(Circunferencia *c){
    double distancia;
    double cord_x = xc-c->xc;
    double cord_y = yc-c->yc;
    double diam = raio+c->raio;
    distancia = sqrt(pow(cord_x,2)+pow(cord_y,2));
    
    if(distancia<= diam)
      return true;
      return false;
  }