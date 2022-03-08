#include "ProfIntegral.hpp"

ProfIntegral:: ProfIntegral(std::string n, double sm):
Professor(n),salarioMensal(sm){} 

double ProfIntegral:: getSalario() {
  return salarioMensal;}

