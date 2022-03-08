#ifndef PONTO3D_HPP
#define PONTO3D_HPP

#include "Ponto2D.hpp"

class Ponto3D: public Ponto2D{
    
  public:
    Ponto3D(double xx = 0, double yy = 0, double zz=0): Ponto2D(xx,yy), z(zz) { };
    friend std::ostream& operator<< (std::ostream &op, Ponto3D &p);
    ~Ponto3D() { };
    Ponto3D& operator= (const Ponto2D &p);
    void set(double nx = 0, double ny = 0, double nz=0) { Ponto2D::set(nx, ny); z = nz; }
    double get_z() { return z; }
            
  private:
    double z;
}; 

#endif

std::ostream& operator<< (std::ostream &op, Ponto3D &p){
Ponto2D aux=p;
  op << aux ;
  op << "z = " << p.get_z() << std::endl;
  return op;
}

Ponto3D& Ponto3D::operator= (const Ponto2D &p) {
  Ponto2D::operator=(p);
  this->z = 0;
  return *this;
}