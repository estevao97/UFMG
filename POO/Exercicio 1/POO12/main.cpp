#include <iostream>
#include <vector>

int main() {
  int num = 0;
  int count = 1;
  std::vector<int> vetor;

  while (num >= 0){
    std::cin >> num;
    if (num >= 0) vetor.push_back(num);
  }

  for (int i = 0; i < vetor.size(); i++){
    if(vetor[i] == vetor[i+1]) count++;
    else {
      std::cout << count << " " << vetor[i] << " ";
      count = 1;
    }
  }

  return 0;
}