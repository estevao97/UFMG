#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include <string>

class Pessoa {
  public:
    Pessoa(std::string nome, int idade) { _nome = nome; _idade = idade; }
    Pessoa() { _nome = "indefinido"; _idade = 0; }
    ~Pessoa() { };
    virtual std::string getNome() { return _nome; }
    virtual void setNome(std::string nome) { _nome = nome; }
    virtual int getIdade() { return _idade; }
    virtual void setIdade(int idade) { _idade = idade; }

  private:
    std::string _nome;
    int _idade;
};

#endif