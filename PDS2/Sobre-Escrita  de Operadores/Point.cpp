#include <iostream>
#include "Point.h"

Point::Point(double xx,double yy): x(xx),y(yy) {}
Point::Point(): x(0.0),y(0.0) {}

double Point:: getX() const {return x;}
double Point:: getY() const {return y;}

Point Point::operator + (const Point &p) {
  Point aux;
  aux.x = x + p.x;
  aux.y = y + p.y;
  return aux;
}

Point& Point::operator += (const Point &p) {
  Point aux;
  x = x + p.x;
  y = y + p.y;
  return *this ;
}
std::ostream & operator << (std::ostream &out, const Point &p) {
  out << "(";
  out << p.getX();
  out << ", ";
  out << p.getY();
  out << ")";
  return out;
}

std::istream & operator >> (std::istream &aux,  Point &p) {
 return aux >> p.x >> p.y;
}