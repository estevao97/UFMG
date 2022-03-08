#include <iostream>
#include <string>
#include <fstream>

int main() {
  std::string str1;
  std::ifstream arquivo ("texto.txt"); 

  if (arquivo.is_open()) {
    while (!arquivo.eof()) {
      getline (arquivo,str1); 
    }
    arquivo.close();
  } else std::cout << "Não foi possível abrir o arquivo" << std::endl; 

  int count = 0;
  for (int i = 0; i < str1.length(); i++) {
    if (isspace(str1.at(i))) count++;
  }

  std::cout << "O número de espaços é " << count << std::endl; 

  return 0;
}