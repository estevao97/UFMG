# Trabalho Prático 1

O primeiro trabalho prático da disciplina de Redes de Computadore tinha como objetivo proporcionar aos alunos um aprendizado mais prático sobre protocolo de comunicação, em que cada aluno teria que cria um sistema modelo cliente-servidor e simular a interação entre uma estação remota (servidor) e a central de monitoramento (cliente), em que essas duas entidades trocam mensagens entre si. Na implementação do servidor e do cliente foi utilizado o protocolo TCP, criado com [socket(AF_INET, SOCK_STREAM, 0)] e com [socket(AF_INET6, SOCK_STREAM, 0)], sendo possível utilizar tanto o IPv4 quanto o IPv6. Mais detalhes sobre a proposta do trabalho prático pode ser encontrada no arquivo "Trabalho Prático 1.pdf". Além disso, detalhes sobre a implementação do projeto pode ser encontrado no arquivo "Docuumentação TP_1.pdf". O trabalho foi implementado usando a linguagem C.

## Compilação

Para realizar a compilação foi criado um arquivo Makefile, bastanto apenas estar na pasta raiz do programa e executar o seguinte comando no terminal :

```
make
```

## Execução

Para executar o programa o servidor deve receber, estritamente nessa ordem, o tipo de endereço que será utilizado (v4 para IPv4 ou v6 para IPv6) e um número de porta na linha de comando especificando em qual porta ele vai receber conexões (foi utilizada a porta 51511 para efeitos de padronização do trabalho). O cliente deve receber, estritamente nessa ordem, o endereço IP e a porta do servidor para estabelecimento da conexão.

Exemplo IPv4:

```
no terminal 1: ./server v4 51511
no terminal 2: ./client 127.0.0.1 51511
```

Exemplo IPv6:

```
no terminal 1: ./server v6 51511
no terminal 2: ./client ::1 51511
```
