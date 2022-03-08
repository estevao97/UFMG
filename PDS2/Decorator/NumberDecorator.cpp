#include <sstream>
#include <iostream>
#include <cctype>
#include <cstdlib>

#include "NumberDecorator.hpp"

std::string NumberDecorator::toString() {
  std::stringstream sso;
  std::string input = StreamDecorator::toString();
  std::string temp;
  std::string result;

  sso<<input;

  while(sso>>temp){
    std::stringstream sso2(temp);
    float tempFloat; int tempInt;
    
    sso2>>tempFloat; tempInt=tempFloat;
    float resto = tempFloat-tempInt;


    if (!resto && tempFloat && tempInt){
      if (tempInt>0) result += " +" + std::to_string(tempInt);
      else result+= " "+std::to_string(tempInt);
    }
    else result += " "+temp;
  }
  return result;
}