#include "ContaCorrente.hpp"

ContaCorrente::ContaCorrente(string Senha) : ContaBancaria(Senha)
{
    this->quantTransacoes = 0;
    this->setTransacoes(0.0);
}
bool ContaCorrente::saca(double valor)
{
    if(this->getSaldo()>=valor){
        setSaldo(this->getSaldo() - valor);
        this->setTransacoes(-valor);
        this->quantTransacoes++;
        return true;
    }else{
        return false;
    }
}
void ContaCorrente::deposita(double valor)
{
    this->setSaldo(this->getSaldo() + valor);
    this->setTransacoes(valor);
    this->quantTransacoes++;
}
void ContaCorrente::tiraExtrato()
{
    for(int i = 0; i < this->getNumTransacoes(); i++){
        std::cout << this->getTransacoes(i) << std::endl;
        std::cout << "---------------------" << std::endl;
    }
}
