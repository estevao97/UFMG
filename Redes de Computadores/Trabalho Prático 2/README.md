# Trabalho Prático 2

O segundo trabalho prático da disciplina de Redes de Computadore tinha como objetivo proporcionar aos alunos um aprendizado mais prático sobre protocolo de comunicação de múltiplas conexões, em que cadda aluno teria que desenvolver um sistema que coordene múltiplas conexões simultâneas entre os equipamentos e permita a comunicação entre eles. Foi desenvolvido um servidor, responsável por coordenar as múltiplas conexões à medida em que os equipamentos entram e saem da rede, e os equipamentos (os clientes), que solicitam informações de outros equipamentos por intermédio do servidor. Na implementação do servidor e do cliente foi utilizada a interface de sockets na linguagem C. Mais detalhes sobre a proposta do trabalho prático pode ser encontrada no arquivo "Trabalho Prático 2.pdf". Além disso, detalhes sobre a implementação do projeto pode ser encontrado no arquivo "Docuumentação TP_2.pdf".

## Compilação

Para realizar a compilação foi criado um arquivo Makefile, bastanto apenas estar na pasta raiz do programa e executar o seguinte comando no terminal :

```
make
```

## Execução

Para executar o programa o servidor deve receber um número de porta na linha de comando especificando em qual porta ele vai receber conexões (foi utilizada a porta 51511 para efeitos de padronização do trabalho). O equipamento (cliente) deve receber, estritamente nessa ordem, o endereço IP e a porta do servidor para
estabelecimento da conexão. Para realizar multiplas conexões de equipamentos com o servidor basta
executar multiplas vezes o código do equipamento.

Exemplo:

```
Terminal 1: ./server 51511
Terminal 2: ./equipment 127.0.0.1 51511
Terminal 3: ./equipment 127.0.0.1 51511
```
