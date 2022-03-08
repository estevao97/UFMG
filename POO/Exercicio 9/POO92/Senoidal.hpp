#ifndef SENOIDAL_HPP
#define SENOIDAL_HPP

#include "Funcao.hpp"

class Senoide : public Funcao
{
public:
    Senoide(){};
    double getIntegral(double limiteInferior, double limiteSuperior, double intervalos);
    double func(double input)
    {
        double p1 = sin(input);
        double p2 = input;
        return p1 / p2;
    }
};

#endif