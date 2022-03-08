#include <iostream>
#include "Agenda.hpp"

int main() {
  int num;

  std::cout << "Quantas pessoas você deseja incluir na agenda?\n";
  std::cin >> num;

  Agenda a(num);

  std::cout << "Você tem " << a.getAmigos() << " amigos\n";
  std::cout << "Você tem " << a.getConhecidos() << " conhecidos\n";

  std::cout << "Adicione as informações correspondentes a cada amigo ou conhecido\n";
  a.addInformacoes();

  std::cout << "Todos aniversários armazenados dos amigos:\n";
  a.imprimeAniversarios();

  std::cout << "Todos e-mails armazenados dos conhecidos:\n";
  a.imprimeEmail();


}