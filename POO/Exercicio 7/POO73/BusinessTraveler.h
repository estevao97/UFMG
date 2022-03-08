#ifndef BUSINESSTRAVELER_H
#define BUSINESSTRAVELER_H
#include "Traveler.h"
#include "Pager.h"
#include <string.h>
#include <iostream>

class BusinessTraveler: public Traveler{
    Pager P;
    public:
    BusinessTraveler(): nome("1"), P.set("1"){}
    BusinessTraveler(std::string& s): nome(s), P.set(s){}
    BusinessTraveler(const BusinessTraveler& that): nome(that.nome), P.set(that.P.get()){}
    BusinessTraveler& operator=(const BusinessTaveler& T){nome(T.nome); P.set(T.P.get()); return *this}
    ~BusinessTraveler(){}
}

#endif