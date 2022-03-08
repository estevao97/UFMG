#ifndef AMIGO_HPP
#define AMIGO_HPP

#include "Pessoa.hpp"

class Amigo: public Pessoa {
  public:
    Amigo() { _aniversario = "indefinido"; }
    ~Amigo() { };
    virtual std::string getAniversario() { return _aniversario; }
    virtual void setAniversario(std::string aniversario) { _aniversario = aniversario; } 

  private:
    std::string _aniversario;
};

#endif