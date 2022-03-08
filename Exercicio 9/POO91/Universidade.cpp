#include "Universidade.hpp"


Universidade:: Universidade(std::string n) : nome(n) {};

void Universidade::AddProfessor(Professor &prof){
  list.push_back(&prof);
  }

double Universidade::TotalPago(){
  double sum=0;
  for(Professor* x : list) {
    sum += x->getSalario();}
  return sum;
}

std::vector<Professor*> Universidade:: list;