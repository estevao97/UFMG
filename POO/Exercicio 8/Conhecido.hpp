#ifndef CONHECIDO_HPP
#define CONHECIDO_HPP

#include "Pessoa.hpp"

class Conhecido: public Pessoa {
  public:
    Conhecido() { _email = "indefinido"; }
    ~Conhecido() { };
    virtual std::string getEmail() { return _email; }
    virtual void setEmail(std::string email) { _email = email; } 

  private:
    std::string _email;
};

#endif