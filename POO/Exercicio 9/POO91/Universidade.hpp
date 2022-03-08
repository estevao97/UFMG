#ifndef UNIVERSIDADE_HPP
#define UNIVERSIDADE_HPP

#include "Professor.hpp"
#include "ProfHorista.hpp"
#include "ProfIntegral.hpp"
#include <vector>


class Universidade{
    private:
        static std::vector<Professor*> list;
        std::string nome;
    public:
        Universidade(std::string n);
        void AddProfessor(Professor &prof);
        double TotalPago();
       
};


#endif