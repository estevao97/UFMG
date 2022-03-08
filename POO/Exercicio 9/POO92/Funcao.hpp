#ifndef FUNCAO_HPP
#define FUNCAO_HPP

#include <cmath>

class Funcao
{
public:
    //funcao que obtem a integral da funcao pela regra do trapezio
    double getIntegral(double limiteInferior, double limiteSuperior, double intervalos)
    {
        double soma = 0, h = (limiteSuperior - limiteInferior) / intervalos;
        double baseInferior = limiteInferior, baseSuperior = baseInferior + h;
        for (int i = 0; i < intervalos; i++){
            soma += ((func(baseInferior) + func(baseSuperior)) *h/2);
            baseInferior = baseSuperior;
            baseSuperior = baseInferior + h;
        }
        return soma;
    }

    // funcao virtual representando a funcao cuja integral deve ser calculada
    virtual double func(double input) = 0;

    virtual ~Funcao(){}
};

#endif