#ifndef AGENDA_HPP
#define AGENDA_HPP

#include "Pessoa.hpp"
#include "Amigo.hpp"
#include "Conhecido.hpp"
#include <vector>
#include <ctime>

class Agenda {
  public:
    Agenda(int Pessoas);
    ~Agenda() { };
    int getAmigos() { return _quantAmigos; }
    int getConhecidos() { return _quantConhecidos; }
    void addInformacoes();
    void imprimeAniversarios();
    void imprimeEmail();

  private:
    int _quantAmigos = 0;
    int _quantConhecidos = 0;
    std::vector<Pessoa> _colecaoPessoas;
    std::vector<Amigo> _colecaoAmigo;
    std::vector<Conhecido> _colecaoConhecido;

};

#endif

Agenda::Agenda(int Pessoas) {
  srand((unsigned int) time (NULL));

  for (int i = 0; i < Pessoas; i++){
    int a = rand()%2 + 1;

    if(a == 1) {
      _quantAmigos++;
    } else if (a == 2) {
      _quantConhecidos++;
    }
  }
  
}

void Agenda::addInformacoes(){
  std::cout << "Entre com as informações dos amigos (nome, idade e aniversário)\n";
  for (int i = 0; i < _quantAmigos; i++){
    std:: string nome;
    int idade;
    std:: string niver;

    std::cin >> nome >> idade >> niver;
     Amigo aux;
     aux.setNome(nome);
     aux.setIdade(idade);
     aux.setAniversario(niver);
     _colecaoPessoas.push_back(aux);
     _colecaoAmigo.push_back(aux);
    
  }

  std::cout << "Entre com as informações dos conhecidos (nome, idade e email)\n";
  for (int i = 0; i < _quantConhecidos; i++){
    std:: string nome;
    int idade;
    std:: string email;

    std::cin >> nome >> idade >> email;
     Conhecido aux;
     aux.setNome(nome);
     aux.setIdade(idade);
     aux.setEmail(email);
     _colecaoPessoas.push_back(aux);
     _colecaoConhecido.push_back(aux);
    
  }
  
}

void Agenda::imprimeAniversarios(){
   for(Amigo x : _colecaoAmigo){
    std::cout << x.getAniversario() <<"\n";
  }
}

void Agenda::imprimeEmail(){
  for(Conhecido x : _colecaoConhecido){
    std::cout << x.getEmail() <<"\n";
  }
}