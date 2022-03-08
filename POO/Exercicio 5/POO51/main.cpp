#include <iostream>

#include "Ponto2D.hpp" 

int main() {
  Ponto2D p1; 
  Ponto2D p2(3.0, 4.0);
  Ponto2D p3(p2);
  Ponto2D p4 = p2;
  Ponto2D p5; 
  
  p1.print();
  p2.print();
  p3.print();
  p4.print();
  p5.print();

  double d1 = p1.distToOrig();
  double d2 = p1.distTo(p2);
  std::cout << d1 << std::endl << d2 << std::endl;
  p5 = p1.sumOf(p4);
  p5.print();
  p5.sum(p2);
  p5.print();
  std::cout << p1.getId() << std::endl ;
  std::cout << p5.getId() << std::endl ;
  
  Ponto2D a(1.,4.), b(3.,2.), c;

  c = a+b;
  c.print();
  
  --c;
  c.print();

}