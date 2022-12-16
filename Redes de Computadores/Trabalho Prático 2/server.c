#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024
#define MAX 16 // Núemro máximo de quipamentos - 1

int list_csock[MAX] = {0}; // Banco de dados dos equipamentos conectados
int flag_remove = 0;       // Flag para fechar conexão

char *add_equipment(int csock, int *id);
char *list_equipments(int id);
char *remove_equipment(int id);
char *request_information(int id_ori, int id_dest);
char *res_information(int id_ori, int id_dest, char *payload);

void usage(int argc, char **argv)
{
    printf("usage: %s <v4> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

struct client_data
{
    int csock;
    struct sockaddr_storage storage;
};

void *client_thread(void *data)
{

    struct client_data *cdata = (struct client_data *)data;
    char messageReceive[BUFSZ];
    char messageToSend[BUFSZ];
    char *id_msg, *id_ori, *id_dest;
    size_t count;
    int id = 0;

    while (1)
    {
        memset(messageReceive, 0, BUFSZ);
        count = recv(cdata->csock, messageReceive, BUFSZ - 1, 0);

        id_msg = strtok(messageReceive, " "); // Segmentação da mensagem recebida dos equipamentos
        id_ori = strtok(NULL, " ");
        id_dest = strtok(NULL, " ");

        switch (atoi(id_msg))
        {
        case 1:
            sprintf(messageToSend, "%s", add_equipment(cdata->csock, &id)); // Mensagem com novo Id ou erro
            break;
        case 2:
            sprintf(messageToSend, "%s", remove_equipment(atoi(id_ori))); // Mensagem com resposta da remoção
            break;
        case 4:
            sprintf(messageToSend, "%s", list_equipments(atoi(id_ori))); // Mensagem com lista
            break;
        case 5:
            sprintf(messageToSend, "%s", request_information(atoi(id_ori), atoi(id_dest))); // Solicitar informação
            break;

        default:
            break;
        }

        count = send(cdata->csock, messageToSend, strlen(messageToSend), 0); // Envia mensagem ao cliente
        if (count != strlen(messageToSend))
        {
            logexit("send");
        }

        memset(messageToSend, 0, BUFSZ);

        if (flag_remove) // Quando verdadeira, quando o equipamento é removido, quebra o loop
        {
            break;
        }
    }
    close(cdata->csock);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;

    if (0 != server_sockaddr_init("v4", argv[1], &storage))
    {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1)
    {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
    {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage)))
    {
        logexit("bind");
    }

    if (0 != listen(s, 10))
    {
        logexit("listen");
    }

    while (1)
    {

        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1)
        {
            logexit("accept");
        }

        struct client_data *cdata = malloc(sizeof(*cdata));
        if (!cdata)
        {
            logexit("malloc");
        }
        cdata->csock = csock;
        memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));

        pthread_t tid;
        pthread_create(&tid, NULL, client_thread, cdata);
    }

    exit(EXIT_SUCCESS);
}

char *add_equipment(int csock, int *id)
{

    char *response = (char *)malloc(BUFSZ);
    char *lista = (char *)malloc(BUFSZ);

    for (int i = 1; i < MAX; i++)
    {
        if (list_csock[i] == 0)
        {
            list_csock[i] = csock;
            *id = i;
            sprintf(response, "3 - - %.2d", *id); // Mensagem de conexão feita e Id
            printf("Equipment %.2d added \n", *id);

            for (int i = 1; i < MAX; i++)
            {
                if (list_csock[i] != 0 && i != *id)
                {
                    send(list_csock[i], response, strlen(response), 0);
                }
            }

            sprintf(lista, "%s", list_equipments(i));
            return response;
        }
    }
    sprintf(response, "%s", "7 - - 4"); // Idenditicador de limite excedido
    flag_remove = 1;
    return response;
}

char *list_equipments(int id)
{
    char *response = (char *)malloc(BUFSZ);
    char *aux = (char *)malloc(BUFSZ);
    int flag_vazio = 1;

    sprintf(response, "4 - - "); // Mensagem de aquisição de identificadores

    for (int i = 1; i < MAX; i++)
    {
        if (list_csock[i] != 0 && i != id)
        {
            sprintf(aux, "%.2d ", i);
            strcat(response, aux);
            flag_vazio = 0;
        }
    }

    if (flag_vazio)
    {
        sprintf(response, "4 - - Lista vazia"); // Mensagem de lista "vazia"
    }
    return response;
}

char *request_information(int id_ori, int id_dest)
{

    char *response = (char *)malloc(BUFSZ);
    srand((unsigned)time(NULL));

    if (id_ori < MAX && list_csock[id_ori])
    {
        if (id_dest < MAX && list_csock[id_dest])
        {

            float ale = 0;
            ale = rand() % 100001;
            ale = ale / 10000;

            sprintf(response, "5 %.2d %.2d -", id_ori, id_dest);
            send(list_csock[id_dest], response, strlen(response), 0);
            sprintf(response, "6 %.2d %.2d %.2f", id_ori, id_dest, ale);
            return response;
        }
        else
        {
            printf("Equipment %.2d not found\n", id_dest);
            sprintf(response, "%s", "7 - - 3"); // Identificador de Id target não encontrado
            return response;
        }
    }
    else
    {
        printf("Equipment %.2d not found\n", id_ori);
        sprintf(response, "%s", "7 - - 2"); // Identificador de Id source não encontrado
    }

    return response;
}

char *remove_equipment(int id)
{

    char *response = (char *)malloc(BUFSZ);
    if (list_csock[id])
    {
        sprintf(response, "2 %d - -", id); // Identificador de equipamento removido
        for (int i = 1; i < MAX; i++)
        {
            if (list_csock[i] != 0 && i != id)
            {
                send(list_csock[i], response, strlen(response), 0); // broadcast com mensagem de remoção
            }
        }
        sprintf(response, "8 %d - 1", id); // Identificador de equipamento removido
        list_csock[id] = 0;                // Remove equipamento da base de dados
        printf("Equipment %.2d removed \n", id);
        flag_remove = 1;
    }
    else
    {
        sprintf(response, "%s", "7 - - 1"); // Identificador de equipamento não encontrado
    }

    return response;
}
