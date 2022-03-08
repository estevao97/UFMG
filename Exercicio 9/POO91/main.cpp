#include <iostream>
#include "Professor.hpp"
#include "ProfIntegral.hpp"
#include "ProfHorista.hpp"
#include "Universidade.hpp"

int main() {

  ProfHorista p1("Pans",200,50.0);
  ProfHorista p2("Ana",200,70.0);
  ProfIntegral p3("Paulo",2600);

  std::cout << "Professor: " << p1.getName() << " >> salário: " << p1.getSalario()<< std::endl;
  std::cout << "Professor: " << p2.getName() << " >> salário: " << p2.getSalario()<< std::endl;
  std::cout << "Professor: " << p3.getName() << " >>salário: " << p3.getSalario()<< std::endl;
  

  Universidade u1("UFMG");
  u1.AddProfessor(p1);
  u1.AddProfessor(p2);
  u1.AddProfessor(p3);

  std::cout << "Valor total mensal: " << u1.TotalPago()<< std::endl;
  return 0;
}