#include <iostream>
#include "List.hpp"

int main()
{
    int k,n;
    int j = 0;
    List lista = List();
    std::cin >> k >> n ;
    int par[(k/2)];
    for(int i=k ; i>=0; --i)
    {
        lista.insert(i);
        if(i%2 == 0)
        {
            par[j]=i;
            j++;
        }
    }
    lista.print();
    std::cout<<lista._size<<std::endl;
    for(int i =0; i<n; ++i)
    {
        lista.removeFirst();
    }
    for(int i = 0; i<j-1; ++i)
    {
        if(!lista.indexOf(par[i]))
        {
            par[i]=-1;
        }
    }
    lista.print();
    std::cout<<lista._size<<std::endl;
    for(int i = 0; i<=sizeof(par)/4; ++i)
    {
        lista.remove(par[i]);
    }
    lista.print();
    std::cout<<lista._size<<std::endl;
    lista.clearList();
    return 0;
}

