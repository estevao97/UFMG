#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include <iostream>

class Professor{
        std::string nome;
    public:
        Professor(std::string n) : nome(n) {};
        std::string getName() const {return nome;};
        virtual double getSalario() =0;
      
    
};

#endif