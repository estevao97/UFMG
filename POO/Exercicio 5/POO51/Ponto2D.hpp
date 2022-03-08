#ifndef PONTO_2D
#define PONTO_2D

#include<list>
#include <cmath>

class Ponto2D {  
  private:
    double _x;
    double _y;
    int _id ;
    static std::list<int> list_ids;
  
  public:
    Ponto2D();
    Ponto2D(double a, double b);
    Ponto2D(Ponto2D const &p1);
    ~Ponto2D();
    Ponto2D sumOf(const Ponto2D &p2);
    void sum(const Ponto2D &p3);
    void print() const;
    double distTo(const Ponto2D &p1);
    inline double distToOrig() { return (sqrt(pow(_x, 2)+pow(_y, 2)));}
    inline int getId() const {return _id;};
    int getNextId();
    Ponto2D& operator-- ();
    Ponto2D operator+ (const Ponto2D& P);

    Ponto2D& operator = (const Ponto2D &p1);
};

#endif