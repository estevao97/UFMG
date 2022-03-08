#ifndef PROFINTEGRAL_HPP
#define PROFINTEGRAL_HPP

#include "Professor.hpp"

class ProfIntegral: public Professor {
        double salarioMensal;
    public:
       ProfIntegral(std::string n, double sm);
       double getSalario() override;
      
    
};

#endif

