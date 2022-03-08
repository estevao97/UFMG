#include "Estudante.hpp"

float Estudante::calcularRSG(){
  float result = 0.0;
  for(int i=0;i<5;++i){
    result += notas[i];
  }
  return (result/5);
}