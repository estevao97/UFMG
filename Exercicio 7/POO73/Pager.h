#ifndef PAGER_H
#define PAGER_H
#include <string.h>
#include <iostream>


class Pager{
    std::string n;
    public:
    Pager(std::string& s): n(s){}
    Pager(const Pager& that): n(that.n){}
    Pager& operator=(const Pager& T){n(T.n); return *this;}
    ~Pager(){}
    string& get(){return n;}
    void set(string& s){n(s);}
};

#endif