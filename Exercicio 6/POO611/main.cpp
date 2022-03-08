#include <iostream>

template <class T>
    T Fibonacci(int n, T &seq){
        T j=0;
        T k=1;
        if(n == 1)
            return j;
        if(n == 2)
            return k;
        for(int i=0; i<(n-2); i++){
            seq = j + k;
            j = k;
            k = seq;            
        }
        return seq;
    }


int main(){
    int F, n;
    std::cout << "Digite o n-ésimo termo da série de Fibonacci que deseja descobrir" << std::endl;
    std::cin >> n;
    std::cout << Fibonacci(n, F) << std::endl;
    return 0;
}