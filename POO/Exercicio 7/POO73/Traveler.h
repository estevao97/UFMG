#ifndef TRAVELER_H
#define TRAVELER_H
#include <string.h>
#include <iostream>

class Traveler{
    std::string nome;
    public:
    Traveler(std::string& s): nome(s){}
    Traveler(const Traveler& that): nome(that.nome){}
    Traveler& operator=(const Traveler& T){nome(T.nome); return *this;}
    ~Traveler(){}
};

#endif