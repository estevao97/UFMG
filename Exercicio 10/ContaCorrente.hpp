#ifndef CONTACORRENTE_HPP
#define CONTACORRENTE_HPP
#include "ContaBancaria.hpp"
#include <vector>
class ContaCorrente : public ContaBancaria
{
private:
    int quantTransacoes; // Quantidade de Transações da Conta Corrente
public:
    ContaCorrente(string);
    bool saca(double);
    void deposita(double);
    void tiraExtrato();
    int getQuant();
};

#endif
