#ifndef PROFHORISTA_HPP
#define PROFHORISTA_HPP

#include "Professor.hpp"


class ProfHorista: public Professor {
      double nrNorasTrabalhadas;
      double valorHora;
    public:
      ProfHorista(std::string n, double nht, double vh);
      double getSalario() override;
     
      
};

#endif