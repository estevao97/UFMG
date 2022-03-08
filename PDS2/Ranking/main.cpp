#include "Estudante.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

bool Comparacao(Estudante, Estudante);

int main() {

  Estudante p1;
  std::vector<Estudante> lista;

  for(int i=0;i<10;++i){
    std::cin >> p1.matricula >> p1.nome >> p1.notas[0] >> p1.notas[1] >> p1.notas[2] >> p1.notas[3]>> p1.notas[4];
    lista.push_back(p1);
  }
  std::sort(lista.begin(),lista.end(),Comparacao);
  
  for(int i= 0;i<3;++i){
    std:: cout << lista[i].matricula << " " << lista[i].nome << " " << std:: fixed << std::setprecision(2) << lista[i].calcularRSG() << std::endl; 
  }

  return 0;
}

bool Comparacao(Estudante p1, Estudante p2){
    if(p1.calcularRSG() != p2.calcularRSG()){
      return(p1.calcularRSG() > p2.calcularRSG());
    }
    else{
      return(p1.matricula < p2.matricula);
    }
}
