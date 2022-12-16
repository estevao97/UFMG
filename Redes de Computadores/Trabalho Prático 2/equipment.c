#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 500
#define MAX 16 // Núemro máximo de quipamentos - 1

struct client_data
{
    int csock;
};

int flag_remove = 0; // Flag para fechar conexão
int id = 0;          // Id do equipamento

void *client_thread(void *data);
void mensagens_erro(char *code);
char *mapeamento_mensagens(char *buf, int id, int s);
void entrada_equipamento(int newId);
void remove_equipment(int equipment);
void request_info(int id_ori, int id_dest, int s);

void usage(int argc, char **argv)
{
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s  127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{

    char buf[BUFSZ];
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage))
    {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1)
    {
        logexit("socket");
    }
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(storage)))
    {
        logexit("connect");
    }

    struct client_data *cdata = malloc(sizeof(*cdata));
    if (!cdata)
    {
        logexit("malloc");
    }
    cdata->csock = s;

    pthread_t tid;
    pthread_create(&tid, NULL, client_thread, cdata);

    memset(buf, 0, BUFSZ);
    sprintf(buf, "%s", "1 - - -"); // Mensagem para o equipamento se conectar ao servidor

    send(cdata->csock, buf, strlen(buf), 0);
    memset(buf, 0, BUFSZ);
    while (1)
    {

        fflush(stdin);
        fgets(buf, BUFSZ - 1, stdin);
        sprintf(buf, "%s", mapeamento_mensagens(buf, id, cdata->csock)); // Mapeamento mensagem terminal para mensagem enviada ao servidor
        send(cdata->csock, buf, strlen(buf), 0);

        memset(buf, 0, BUFSZ);
    }
    exit(EXIT_SUCCESS);
}

void *client_thread(void *data)
{
    struct client_data *cdata = (struct client_data *)data;
    char messageReceive[BUFSZ];
    char *id_msg, *id_ori, *id_dest, *payload;

    while (1)
    {
        memset(messageReceive, 0, BUFSZ);
        recv(cdata->csock, messageReceive, BUFSZ, 0); // Recebe a mensagem do servidor
        if (strlen(messageReceive) != 0)
        {
            id_msg = strtok(messageReceive, " "); // Segmenta a mensagem nos 4 campos principais
            id_ori = strtok(NULL, " ");
            id_dest = strtok(NULL, " ");
            payload = strtok(NULL, "-");

            switch (atoi(id_msg))
            {
            case 2:
                remove_equipment(atoi(id_ori)); // Remove equipamento do banco de dados
                break;
            case 3:
                entrada_equipamento(atoi(payload)); // Recebe novo Id ou menagem de erro
                break;
            case 4:
                printf("%s\n", payload); // Lista de equipamentos
                break;
            case 5:
                puts("requested informationn"); // Mensagem de informação requisitada
                break;
            case 6:
                printf("Value from %s: %s\n", id_dest, payload); // Informação requerida
                break;
            case 7:
                mensagens_erro(payload); // Mensagns de erro trasnmitida pelos servidor
                break;
            case 8:
                puts("Successful removal"); // Remoção do equipamento ok
                flag_remove = 1;
                break;

            default:
                break;
            }

            if (flag_remove)
            {
                break;
            }
        }
    }
    close(cdata->csock);
    exit(EXIT_SUCCESS);
}

char *mapeamento_mensagens(char *buf, int id, int s)
{
    char *response = (char *)malloc(BUFSZ);
    char *request = (char *)malloc(BUFSZ);
    char *equipment = (char *)malloc(BUFSZ);

    if (strcmp(buf, "close connection\n") == 0)
    {
        sprintf(response, "2 %.2d - -", id); // Mensagem para fechar conecção
        return response;
    }

    if (strcmp(buf, "list equipment\n") == 0) // Listar equipamentos
    {
        sprintf(response, "4 %.2d - ", id);
        return response;
    }

    request = strtok(buf, " ");

    if (strcmp(request, "request") == 0)
    {
        equipment = strtok(NULL, " ");
        equipment = strtok(NULL, " ");
        equipment = strtok(NULL, "\n");

        sprintf(response, "5 %.2d %.2d -", id, atoi(equipment)); // Mensagem de aquisição de informação
        return response;
    }
    return response;
}

void mensagens_erro(char *code)
{

    char *response = (char *)malloc(BUFSZ);
    if (strcmp(code, "1") == 0)
        sprintf(response, "%s", "Equipment not found");
    else if (strcmp(code, "2") == 0)
        sprintf(response, "%s", "Source equipment not found");
    else if (strcmp(code, "3") == 0)
        sprintf(response, "%s", "Target equipment not found");
    else if (strcmp(code, "4") == 0)
    {
        sprintf(response, "%s", "Equipment limit exceeded");
        flag_remove = 1;
    }
    printf("%s\n", response);
}

void entrada_equipamento(int newId)
{

    char *response = (char *)malloc(BUFSZ);

    if (!id)
    {
        id = newId;
        sprintf(response, "New ID: %.2d", id);
    }
    else
    {
        sprintf(response, "Equipment %.2d added", newId);
    }
    printf("%s\n", response);
}

void remove_equipment(int equipment)
{
    printf("Equipment %.2d removed \n", equipment);
}
