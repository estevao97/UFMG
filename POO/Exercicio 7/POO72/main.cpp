#include <iostream>
#include "Box.hpp"

int main() {
  double x, y, z;
  std::cout << "Indique os valores de altura, largura e profundidade, respectivamente" << std::endl; 
  std::cin >> x >> y >> z;

  Box b1 = Box(x,y,z);

  std::cout << "O valor da área é " << b1.area() << std::endl;
  std::cout << "O valor do volume é " << b1.volume() << std::endl;

  Ponto3D p1(0,1,0);
  Ponto3D p2(0,0,0);
  Ponto3D p3(0,0,0);
  Ponto3D p4(1,0,0);
  Ponto3D p5(0,0,-1);
  Ponto3D p6(0,0,0);
  Ponto3D p7(0,0,0);
  Ponto3D p8(0,0,0);

  Box b2(p1, p2, p3, p4, p5, p6, p7, p8);
  std::cout << "O valor da área é " << b2.area() << std::endl;
  std::cout << "O valor do volume é " << b2.volume() << std::endl;

}