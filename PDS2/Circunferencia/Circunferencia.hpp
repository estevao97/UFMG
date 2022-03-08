#define PI 3.14
#include <cmath>

struct Circunferencia{
    double xc;
    double yc;
    double raio;
    
    Circunferencia(double , double , double );
    double calcularArea();
    bool possuiIntersecao(Circunferencia* c);

};
