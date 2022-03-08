#ifndef QUADRATICA_HPP
#define QUADRATICA_HPP

#include "Funcao.hpp"

class Quadratica : public Funcao
{
private:
    double a, b, c;

public:
    Quadratica(double A, double B, double C)
    {
        a = A;
        b = B;
        c = C;
    }
    double getIntegral(double limiteInferior, double limiteSuperior, double intervalos);
    double func(double input)
    {
        double p1, p2, p3;
        p1 = a * input * input;
        p2 = b * input;
        p3 = c;
        return a + b + c;
    }
};

#endif