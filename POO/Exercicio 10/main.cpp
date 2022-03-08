#include "ContaCorrente.hpp"
#include "ContaPoupanca.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int main()
{
    int numContas, verifica;
    cout << "Insira a quantidade de contas bancarias que deseja criar : ";
    cin >> numContas;
    vector<ContaBancaria *> contas(numContas);
    string auxsenha;
    double auxsaldo;
    vector<int> cp; //armazena qual conta eh poupanca e qual e conrrente

    for (int i = 0; i < numContas; i++) //lendo as contas, senhas e saldo
    {
        cout << "Insira 1 para conta corrente \nInsira 2 para conta poupança\n";
        cin >> verifica;
        if (verifica == 1) //para corrente
        {
            cout << "Insira a senha da conta corrente " << i << " : ";
            cin >> auxsenha;
            ContaCorrente *auxCorrente = new ContaCorrente(auxsenha);
            cout << "kmkdmskf";
            auxCorrente->setNumero(i); //usando i para o numero da conta
            cp.push_back(verifica);
            cout << "insira o saldo da conta " << i << " : ";
            cin >> auxsaldo;
            auxCorrente->setSaldo(auxsaldo);
            contas.push_back(auxCorrente);
        }
        else if (verifica == 2) //pra poupanca
        {
            cout << "Insira a senha da conta poupança " << i << " : ";
            cin >> auxsenha;
            ContaPoupanca* auxPoupanca = new ContaPoupanca(auxsenha);
            auxPoupanca->setNumero(i);
            cp.push_back(verifica);
            double auxrend = ((rand() % 0, 05) + 0, 11); //rentabilidade de cada conta variando de 0,11 a 0,16 ao mes
            auxPoupanca->setRendimento(auxrend);
            cout << "insira o saldo da conta " << i << " : ";
            cin >> auxsaldo;
            auxPoupanca->setSaldo(auxsaldo);
            contas.push_back(auxPoupanca);
        }
        else
            cout << "entrada invalida!" << endl;
    }

    for (int i = 0; i < numContas; i++)
    {
        if (cp[i] == 2)
        {
            cout << "Conta poupança " << contas[i]->getNumero();
            cout << "rendimento ao mes : " << contas[i]->getRendimento() << endl; //erro aqui no rendimento
        }
    }

    for (int i = 0; i < numContas; i++) //brincando com as contas
    {
        double x = (rand() % 1000) + 500;
        double y = (rand() % 500) + 300;
        contas[i]->deposita(x);
        contas[i]->saca(y);
        if (i % 2 == 0)
        {
            double z = (rand() % 800) + 200;
            contas[i]->deposita(z);
        }
    }

    for (int i = 0; i < numContas; i+=2)
    {
        contas[i]->tiraExtrato();
    }

    //ultimo item do pdf
    for (int i = 0; i < numContas; i+=2)
    {
        if (cp[i] == 1)
        {
            cout << "Quantidade de transacoes feitas na conta " << contas[i]->getNumero() << " : " << contas[i]->getNumTransacoes() << endl;
        }
    }
    for (int i = 0; i < numContas; i+=2)
    {
        if (cp[i] == 2)
        {
            cout << "Rendimento da conta " << contas[i]->getNumero() << " na poupanca (saldo*taxa_rend):" << ((contas[i]->getSaldo()) * (contas[i]->getRendimento())) << endl;
        }
    }

    return 0;
}
