#include <iostream>
class Tempo {
  private:
    int dia;
    int hora;
    int min;
    int seg;
    void checagem();
  
  public:
    Tempo(int d=0, int h=0, int m=0, int s=0);
    Tempo somar(Tempo &t1, Tempo &t2);
    void incremento();
    void decremento();
    int getDia();
    int getHora();
    int getMin();
    int getSeg();  
};