#include "tempo.h"
#include <iostream>

int main() {
	Tempo t;
	Tempo t1(72);
	Tempo t2(90, 3);
	Tempo t3(4, 7, 55);
	Tempo t4(45, 30, 56, 55);
	Tempo t5;

	t5 = t5.somar(t1, t2);

	std::cout << "Dia: " << t4.getDia() << std::endl;
	std::cout << "Hora: " << t4.getHora() << std::endl;
	std::cout << "Minuto: " << t4.getMin() << std::endl;
	std::cout << "Segundo: " << t4.getSeg() << std::endl;

	t.incremento();
	t.decremento();


}