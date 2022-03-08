#include <iostream>

#include "Ponto2D.hpp" 

int main() {
  Ponto2D p1; 
  std::cout <<p1.getId()<< std::endl;
  Ponto2D p2(3.0, 4.0);
  std::cout <<p2.getId()<< std::endl;
  Ponto2D p3;
  std::cout <<p3.getId()<< std::endl;


  p1.print();
  p2.print();
  p3.print();
  
  double d1 = p1.distToOrig();
  double d2 = p1.distTo(p2);
  std::cout << d1 << std::endl << d2 << std::endl;
  p3 = p1.sumOf(p2);
  p3.print();
  p1.sum(p2);
  p1.print();



}