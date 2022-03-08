#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int* trans_vetor(string num);
int maxDiff(int* numeros);

int tamanho = 0;

int main()
{
    string num;
    getline(cin,num);
    cout << maxDiff(trans_vetor(num)) << endl;

    return 0;
}


//Transforma os dados da string em inteiros e aloca eles num vetor
int* trans_vetor(string num)
{
    fstream numeros;
    numeros.open("Numeros.txt",ios::out);

    for (int i = 0; i < num.length(); i++)
    {
        if (num[i] == ' ')
        {
            num[i]='\n';
            tamanho++;
        }
    }
    if(num[num.length()-1]=='\n')
        tamanho--;
    if(num[0]=='\n')
        tamanho--;

    numeros << num << endl;
    numeros.close();

    int* vetor = new int[++tamanho];

    numeros.open("Numeros.txt",ios::in);
    if(numeros.is_open())
    {
        for(int i=0;i < tamanho;++i)
        {
            numeros >> vetor[i];
        }
    }
    else
    {
        cout <<"Erro ao abrir o arquivo" << endl;
    }
    numeros.close();

    return vetor;
    delete vetor;

}


// Calcula a maxima diferença entre os numeros do vetor
int maxDiff(int* numeros)
{
    int i=0,j=0, diferenca=0, maior=0;


    for (i=0; i < tamanho; ++i)
    {
        for(j=0; j < tamanho; ++j)
        {
            diferenca= numeros[i]-numeros[j];
            if (diferenca<0)// Caso a diferen�a seja um n�mero negativo, o mesmo eh transformado em positivo.
                diferenca=-diferenca;
            if (diferenca>maior)
            {
                maior=diferenca;
            }
        }

    }
    return maior;
}
