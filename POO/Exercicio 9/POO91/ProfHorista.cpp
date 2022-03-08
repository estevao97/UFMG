#include "ProfHorista.hpp"

ProfHorista::ProfHorista(std::string n, double nht, double vh): 
      Professor(n), nrNorasTrabalhadas(nht), valorHora(vh) {};

 double ProfHorista:: getSalario()  {
  return valorHora*nrNorasTrabalhadas;
  }