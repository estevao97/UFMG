#include <sstream>
#include<iostream>

#include "CommaDecorator.hpp"

std::string CommaDecorator::toString() {

  std::istringstream ss(StreamDecorator::toString());
  std::string aux;
  std::string str; 
  while(ss >> str) {
    aux += str;
    aux += " , " ;
  }
  aux = aux.substr (0,aux.length()-3);
  return aux;
}