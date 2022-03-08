#ifndef CONTAPOUPANCA_HPP
#define CONTAPOUPANCA_HPP
#include "ContaBancaria.hpp"

class ContaPoupanca : public ContaBancaria
{
private:
    double taxaRendimento; // Taxa de Rendimento da Conta Poupança
public:
    ContaPoupanca(string);
    bool saca(double);
    void deposita(double);
    void tiraExtrato();
    double getRendimento();
    void setRendimento(double);
};

#endif
