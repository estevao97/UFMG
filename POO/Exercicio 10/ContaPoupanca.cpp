#include <iostream>
#include "ContaPoupanca.hpp"

ContaPoupanca::ContaPoupanca(string Senha) : ContaBancaria(Senha)
{
    this->taxaRendimento = 0.0;
}
bool ContaPoupanca::saca(double valor)
{
     if(this->getSaldo()>=valor){
        setSaldo(this->getSaldo() - valor);
        this->setTransacoes(-valor);
        return true;
    }else{
        return false;
    }
}
void ContaPoupanca::deposita(double valor)
{
    setSaldo(this->getSaldo() + valor);
    this->setTransacoes(valor);
}
void ContaPoupanca::tiraExtrato()
{
    for(int i = 0; i < this->getNumTransacoes(); i++){
        std::cout << this->getTransacoes(i) << std::endl;
        std::cout << "---------------------" << std::endl;
    }   
}

double ContaPoupanca::getRendimento()
{
    return this->taxaRendimento;
}
void ContaPoupanca::setRendimento(double newTaxaRendimento) 
{
    this->taxaRendimento = newTaxaRendimento;
}
