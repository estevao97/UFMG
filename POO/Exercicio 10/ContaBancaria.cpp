#include <iostream>
#include <string>
#include <vector>
#include "ContaBancaria.hpp"

ContaBancaria::ContaBancaria(string Senha) {
    senha = Senha;
    numero = 0;
    saldo = 0.0;
    transacoes[0] = 0.0;
}

bool ContaBancaria::saca(double valor) {
     if(this->getSaldo()>=valor){
        setSaldo(this->getSaldo() - valor);
        this->transacoes.push_back(-valor);
        return true;
    }else{
        return false;
    }
}

void ContaBancaria::deposita(double valor) {
    this->setSaldo(this->getSaldo() + valor);
    this->transacoes.push_back(valor);
}

void ContaBancaria::tiraExtrato() {
    for(int i = 0; i < this->transacoes.size(); i++){
        std::cout << this->transacoes[i] << std::endl;
        std::cout << "---------------------" << std::endl;
    }
}

bool ContaBancaria::alteraSenha(string nova) {
    string prova;
    std::cout << "Insira a senha atual : ";
    std::cin >> prova;
    if(this->getSenha() == prova){
        setSenha(nova);
        return true;
    }
    else
        return false;
}

string ContaBancaria::getSenha() const {
    return this->senha;
}

int ContaBancaria::getNumero() const {
    return this->numero;
}

double ContaBancaria::getSaldo() const {
    return this->saldo;
}

int ContaBancaria::getNumTransacoes() const {
    return this->transacoes.size();
}
int ContaBancaria:: getTransacoes(int pos) const{
    return this->transacoes[pos];
}

void ContaBancaria::setSenha(string Senha) {
    this->senha = Senha;
}

void ContaBancaria::setNumero(int Numero) {
    this->numero = Numero;
}

void ContaBancaria::setSaldo(double Saldo) {
    this->saldo = Saldo;
}

void ContaBancaria::setTransacoes(double valor) {
    this->transacoes.push_back(valor);
}
double ContaBancaria::getRendimento()
{
    return 0;
}
void ContaBancaria::setRendimento(double newTaxaRendimento) 
{

}
