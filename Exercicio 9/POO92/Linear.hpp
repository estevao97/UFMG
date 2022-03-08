#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "Funcao.hpp"

class Linear : public Funcao
{
private:
    double a, b;

public:
    Linear(double A, double B){
        a = A;
        b = B;
    }
    double getIntegral(double limiteInferior, double limiteSuperior, double intervalos);
    double func(double input)
    {
        double p1 = a * input;
        double p2 = b;
        return p1 + p2;
    }
};

#endif