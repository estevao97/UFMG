#include "tempo.h"


Tempo::Tempo(int d, int h, int m, int s) : dia(d), hora(h), min(m), seg(s){
  checagem();
}
  
void Tempo::checagem(){
  if (seg > 59){
    min += seg/60;
    seg = seg%60;
  } else if (seg < 0){
    std::cout << "Erro: Segundo não pode ser negativo";
    exit(0);
  }

  if(min > 59){
    hora += min/60;
    min = min%60;
  } else if (min < 0){
    std::cout << "Erro: Minuto não pode ser negativo";
    exit(0);
  }

  if (hora > 23){
    dia += hora/24;
    hora = hora%24;
  } else if (hora < 0){
    std::cout << "Erro: Hora não pode ser negativo";
    exit(0);
  }

  if(dia < 0){
    std::cout << "Erro: Dia não pode ser negativo";
    exit(0);
  }
}

Tempo Tempo::somar(Tempo &t1, Tempo &t2){
  Tempo tempo_final;

  tempo_final.dia = t1.dia + t2.dia;
  tempo_final.hora = t1.hora + t2.hora;
  tempo_final.min = t1.min + t2.min;
  tempo_final.seg = t1.seg + t2.seg;
  tempo_final.checagem();

  return tempo_final;
}

void Tempo::incremento(){
  seg++;
  checagem();
}

void Tempo::decremento(){
  seg--;
  checagem();
}

int Tempo::getDia(){
  return dia;
}

int Tempo::getHora(){
  return hora;
}

int Tempo::getMin(){
  return min;
}

int Tempo::getSeg(){
  return seg;
} 
