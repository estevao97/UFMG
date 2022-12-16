#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSZ 500

void func(int s);
char *add(const char *messageReceived);
char *remov(const char *messageReceived);
char *list(const char *messageReceived);
char *reader(const char *messageReceived);
void clear_bd();

int bd[5][5];
int countSensors = 0;

void usage(int argc, char **argv)
{
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
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

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);
    func(s);
    close(s);
    exit(EXIT_SUCCESS);
}

void func(int s)
{
    char messageReceive[BUFSZ];
    char messageSend[BUFSZ];
    char *command;
    clear_bd();

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

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("[log] connection from %s\n", caddrstr);

        size_t count = recv(csock, messageReceive, BUFSZ - 1, 0);
        printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count,
               messageReceive);

        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);

        if (strncmp(messageReceive, "add", 3) == 0)
        {
            bzero(messageSend, BUFSZ);
            strcpy(messageSend, add(messageReceive));

            count = send(csock, messageSend, strlen(messageSend), 0);
            if (count != strlen(messageSend))
            {
                logexit("send");
            }
            close(csock);
        }

        else if (strncmp(messageReceive, "remove", 6) == 0)
        {
            bzero(messageSend, BUFSZ);
            strcat(messageSend, remov(messageReceive));
            count = send(csock, messageSend, strlen(messageSend), 0);
            if (count != strlen(messageSend))
            {
                logexit("send");
            }
            close(csock);
        }
        else if (strncmp(messageReceive, "list", 4) == 0)
        {
            bzero(messageSend, BUFSZ);
            strcat(messageSend, list(messageReceive));
            count = send(csock, messageSend, strlen(messageSend), 0);
            if (count != strlen(messageSend))
            {
                logexit("send");
            }
            close(csock);
        }
        else if (strncmp(messageReceive, "read", 4) == 0)
        {
            bzero(messageSend, BUFSZ);
            strcat(messageSend, reader(messageReceive));
            count = send(csock, messageSend, strlen(messageSend), 0);
            if (count != strlen(messageSend))
            {
                logexit("send");
            }
            close(csock);
        }
        else if (strncmp(messageReceive, "kill", 4) ==
                 0)
        { // if msg contains "kill" then server exit and chat
          // ended.
            close(csock);
            break;
        }
        else
        {
            break;
        }
    }
}

char *add(const char *messageReceived)
{

    char *response = (char *)malloc(BUFSZ);
    char copy_message[BUFSZ];
    char *command;
    char *aux1;
    char *sensor_number_1, *sensor_number_2, *sensor_number_3;
    char *equipament_number;
    int sensor_1, sensor_2, sensor_3, equipament;

    memset(copy_message, 0, BUFSZ);
    strcpy(copy_message, messageReceived);

    if (countSensors == 15)
    {
        strcat(response, "limit exceeded");
        return response;
    }

    command = strtok(copy_message, " ");
    aux1 = strtok(NULL, " ");
    sensor_number_1 = strtok(NULL, " ");
    sensor_1 = atoi(sensor_number_1);
    if (!(sensor_1 == 1 || sensor_1 == 2 || sensor_1 == 3 || sensor_1 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }

    sensor_number_2 = strtok(NULL, " ");
    if (strcmp(sensor_number_2, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 0)
        {
            sprintf(response, "sensor %s added", sensor_number_1);
            bd[equipament][sensor_1] = 1;
            countSensors++;
            return response;
        }
        else
        {
            sprintf(response, "sensor %s already exists in %s", sensor_number_1,
                    equipament_number);
            return response;
        }
    }

    sensor_2 = atoi(sensor_number_2);
    if (!(sensor_2 == 1 || sensor_2 == 2 || sensor_2 == 3 || sensor_2 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    sensor_number_3 = strtok(NULL, " ");
    if (strcmp(sensor_number_3, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 0 && bd[equipament][sensor_2] == 0)
        {

            sprintf(response, "sensor %s %s added", sensor_number_1,
                    sensor_number_2);
            bd[equipament][sensor_1] = 1;
            bd[equipament][sensor_2] = 1;
            countSensors += 2;
            return response;
        }
        else
        {
            if (bd[equipament][sensor_1] == 1)
            {
                sprintf(response, "sensor %s already exists in %s",
                        sensor_number_1, equipament_number);
                return response;
            }
            else
            {
                sprintf(response, "sensor %s already exists in %s",
                        sensor_number_2, equipament_number);
                return response;
            }
        }
    }
    sensor_3 = atoi(sensor_number_3);
    if (!(sensor_3 == 1 || sensor_3 == 2 || sensor_3 == 3 || sensor_3 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    aux1 = strtok(NULL, " ");
    equipament_number = strtok(NULL, " ");
    equipament = atoi(equipament_number);
    if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
          equipament == 4))
    {
        strcat(response, "invalid equipment");
        return response;
    }
    if (bd[equipament][sensor_1] == 0 && bd[equipament][sensor_2] == 0 &&
        bd[equipament][sensor_3] == 0)
    {

        sprintf(response, "sensor %s %s %s added", sensor_number_1,
                sensor_number_2, sensor_number_3);
        bd[equipament][sensor_1] = 1;
        bd[equipament][sensor_2] = 1;
        bd[equipament][sensor_3] = 1;
        countSensors += 3;
        return response;
    }
    else
    {
        if (bd[equipament][sensor_1] == 1)
        {
            sprintf(response, "sensor %s already exists in %s", sensor_number_1,
                    equipament_number);
            return response;
        }
        else if (bd[equipament][sensor_2] == 1)
        {
            sprintf(response, "sensor %s already exists in %s", sensor_number_2,
                    equipament_number);
            return response;
        }
        else
        {
            sprintf(response, "sensor %s already exists in %s", sensor_number_3,
                    equipament_number);
            return response;
        }
    }

    return response;
}

char *remov(const char *messageReceived)
{

    char *response = (char *)malloc(BUFSZ);
    char *sensorNotExist = (char *)malloc(BUFSZ);
    int flag = 0;
    char copy_message[BUFSZ];
    char *command;
    char *aux1;
    char *sensor_number_1, *sensor_number_2, *sensor_number_3, *sensor_number_4;
    char *equipament_number;
    int sensor_1, sensor_2, sensor_3, sensor_4, equipament;

    memset(copy_message, 0, BUFSZ);
    strcpy(copy_message, messageReceived);

    strcat(response, "sensor ");

    command = strtok(copy_message, " ");
    aux1 = strtok(NULL, " ");

    sensor_number_1 = strtok(NULL, " ");
    sensor_1 = atoi(sensor_number_1);
    if (!(sensor_1 == 1 || sensor_1 == 2 || sensor_1 == 3 || sensor_1 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }

    sensor_number_2 = strtok(NULL, " ");
    if (strcmp(sensor_number_2, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            sprintf(response, "sensor %s removed", sensor_number_1);
            bd[equipament][sensor_1] = 0;
            countSensors--;
            return response;
        }
        else
        {
            sprintf(response, "%s does not exist in %.2d", sensor_number_1,
                    equipament);
            return response;
        }
    }

    sensor_2 = atoi(sensor_number_2);
    if (!(sensor_2 == 1 || sensor_2 == 2 || sensor_2 == 3 || sensor_2 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    sensor_number_3 = strtok(NULL, " ");
    if (strcmp(sensor_number_3, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 0 && bd[equipament][sensor_2] == 0)
        {
            sprintf(response, "%s %s does not exist in %.2d", sensor_number_1,
                    sensor_number_2, equipament);
            strncpy(response, response, sizeof(response) - 1);
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            strcat(response, sensor_number_1);
            strcat(response, " ");
            bd[equipament][sensor_1] = 0;
            countSensors--;
        }
        else
        {
            strcat(sensorNotExist, sensor_number_1);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_2] == 1)
        {
            strcat(response, sensor_number_2);
            strcat(response, " ");
            bd[equipament][sensor_2] = 0;
            countSensors--;
        }
        else
        {
            strcat(sensorNotExist, sensor_number_2);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (flag)
        {
            strcat(response, "removed ");
            strcat(response, sensorNotExist);
            strcat(response, "does not exist in ");
            sprintf(sensorNotExist, "%.2d", equipament);
            strcat(response, sensorNotExist);
            strncpy(response, response, sizeof(response) - 1);
            return response;
        }
        else
        {
            strcat(response, "removed");
            return response;
        }
    }
    sensor_3 = atoi(sensor_number_3);
    if (!(sensor_3 == 1 || sensor_3 == 2 || sensor_3 == 3 || sensor_3 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    sensor_number_4 = strtok(NULL, " ");
    if (strcmp(sensor_number_4, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 0 && bd[equipament][sensor_2] == 0 &&
            bd[equipament][sensor_3] == 0)
        {
            sprintf(response, "%s %s %s does not exist in %.2d",
                    sensor_number_1, sensor_number_2, sensor_number_3,
                    equipament);
            strncpy(response, response, sizeof(response) - 1);
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            strcat(response, sensor_number_1);
            strcat(response, " ");
            bd[equipament][sensor_1] = 0;
            countSensors--;
        }
        else
        {
            strcat(sensorNotExist, sensor_number_1);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_2] == 1)
        {
            strcat(response, sensor_number_2);
            strcat(response, " ");
            bd[equipament][sensor_2] = 0;
            countSensors--;
        }
        else
        {
            strcat(sensorNotExist, sensor_number_2);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_3] == 1)
        {
            strcat(response, sensor_number_3);
            strcat(response, " ");
            bd[equipament][sensor_3] = 0;
            countSensors--;
        }
        else
        {
            strcat(sensorNotExist, sensor_number_3);
            strcat(sensorNotExist, " ");
            flag = 1;
        }

        if (flag)
        {
            strcat(response, "removed ");
            strcat(response, sensorNotExist);
            strcat(response, "does not exist in ");
            sprintf(sensorNotExist, "%.2d", equipament);
            strcat(response, sensorNotExist);
            strncpy(response, response, sizeof(response) - 1);
            return response;
        }
        else
        {
            strcat(response, "removed");
            return response;
        }
    }
    sensor_4 = atoi(sensor_number_4);
    if (!(sensor_4 == 1 || sensor_4 == 2 || sensor_4 == 3 || sensor_4 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    aux1 = strtok(NULL, " ");

    equipament_number = strtok(NULL, " ");
    equipament = atoi(equipament_number);
    if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
          equipament == 4))
    {
        strcat(response, "invalid equipment");
        return response;
    }

    if (bd[equipament][sensor_1] == 0 && bd[equipament][sensor_2] == 0 &&
        bd[equipament][sensor_3] == 0 && bd[equipament][sensor_4] == 0)
    {
        sprintf(response, "%s %s %s %s does not exist in %.2d", sensor_number_1,
                sensor_number_2, sensor_number_3, sensor_number_4, equipament);
        strncpy(response, response, sizeof(response) - 1);
        return response;
    }

    if (bd[equipament][sensor_1] == 1)
    {
        strcat(response, sensor_number_1);
        strcat(response, " ");
        bd[equipament][sensor_1] = 0;
        countSensors--;
    }
    else
    {
        strcat(sensorNotExist, sensor_number_1);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_2] == 1)
    {
        strcat(response, sensor_number_2);
        strcat(response, " ");
        bd[equipament][sensor_2] = 0;
        countSensors--;
    }
    else
    {
        strcat(sensorNotExist, sensor_number_2);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_3] == 1)
    {
        strcat(response, sensor_number_3);
        strcat(response, " ");
        bd[equipament][sensor_3] = 0;
        countSensors--;
    }
    else
    {
        strcat(sensorNotExist, sensor_number_3);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_4] == 1)
    {
        strcat(response, sensor_number_4);
        strcat(response, " ");
        bd[equipament][sensor_4] = 0;
        countSensors--;
    }
    else
    {
        strcat(sensorNotExist, sensor_number_4);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (flag)
    {
        strcat(response, "removed ");
        strcat(response, sensorNotExist);
        strcat(response, "does not exist in ");
        sprintf(sensorNotExist, "%.2d", equipament);
        strcat(response, sensorNotExist);
        strncpy(response, response, sizeof(response) - 1);
        return response;
    }
    else
    {
        strcat(response, "removed");
        return response;
    }
}

char *list(const char *messageReceived)
{

    char *response = (char *)malloc(BUFSZ);
    char copy_message[BUFSZ];
    char *command;
    char *aux1;
    char *equipament_number;
    int equipament;

    memset(copy_message, 0, BUFSZ);

    strcpy(copy_message, messageReceived);
    command = strtok(copy_message, " ");

    aux1 = strtok(NULL, " ");
    aux1 = strtok(NULL, " ");

    equipament_number = strtok(NULL, " ");
    equipament = atoi(equipament_number);
    if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
          equipament == 4))
    {
        strcat(response, "invalid equipment");
        return response;
    }

    if (bd[equipament][1] == 1)
    {
        strcat(response, "01");
    }
    if (bd[equipament][2] == 1 && bd[equipament][1] == 1)
    {
        strcat(response, " 02");
    }
    if (bd[equipament][2] == 1 && bd[equipament][1] == 0)
    {
        strcat(response, "02");
    }
    if (bd[equipament][3] == 1 && bd[equipament][2] == 1)
    {
        strcat(response, " 03");
    }
    if (bd[equipament][3] == 1 && bd[equipament][2] == 0)
    {
        strcat(response, "03");
    }
    if (bd[equipament][4] == 1 && bd[equipament][3] == 1)
    {
        strcat(response, " 04");
    }
    if (bd[equipament][4] == 1 && bd[equipament][3] == 0)
    {
        strcat(response, "04");
    }
    if (bd[equipament][1] == 0 && bd[equipament][2] == 0 &&
        bd[equipament][3] == 0 && bd[equipament][4] == 0)
    {
        strcat(response, "none");
    }
    return response;
}

char *reader(const char *messageReceived)
{

    char *response = (char *)malloc(BUFSZ);
    char *sensorExist = (char *)malloc(BUFSZ);
    char *sensorNotExist = (char *)malloc(BUFSZ);
    int flag = 0;
    char copy_message[BUFSZ];
    char *command;
    char *aux1;
    char *sensor_number_1, *sensor_number_2, *sensor_number_3, *sensor_number_4;
    char *equipament_number;
    int sensor_1, sensor_2, sensor_3, sensor_4, equipament;
    float a1, a2, a3, a4, ale = 0;

    memset(copy_message, 0, BUFSZ);
    strcpy(copy_message, messageReceived);
    srand((unsigned)time(NULL));

    command = strtok(copy_message, " ");
    sensor_number_1 = strtok(NULL, " ");
    sensor_1 = atoi(sensor_number_1);
    if (!(sensor_1 == 1 || sensor_1 == 2 || sensor_1 == 3 || sensor_1 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }

    sensor_number_2 = strtok(NULL, " ");
    if (strcmp(sensor_number_2, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            sprintf(response, "%.2f", ale);
            return response;
        }
        else
        {
            sprintf(response, "sensor(s) %s not instaled", sensor_number_1);
            return response;
        }
    }

    sensor_2 = atoi(sensor_number_2);
    if (!(sensor_2 == 1 || sensor_2 == 2 || sensor_2 == 3 || sensor_2 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    sensor_number_3 = strtok(NULL, " ");
    if (strcmp(sensor_number_3, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            a1 = ale;
            sprintf(sensorExist, "%.2f ", a1);
            strcat(response, sensorExist);
        }
        else
        {
            strcat(sensorNotExist, sensor_number_1);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_2] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            a2 = ale;
            sprintf(sensorExist, "%.2f ", a2);
            strcat(response, sensorExist);
        }
        else
        {
            strcat(sensorNotExist, sensor_number_2);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (flag)
        {
            strcat(response, "and sensor ");
            strcat(response, sensorNotExist);
            strcat(response, "not installed");
            return response;
        }
        return response;
    }
    sensor_3 = atoi(sensor_number_3);
    if (!(sensor_3 == 1 || sensor_3 == 2 || sensor_3 == 3 || sensor_3 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    sensor_number_4 = strtok(NULL, " ");
    if (strcmp(sensor_number_4, "in") == 0)
    {
        equipament_number = strtok(NULL, " ");
        equipament = atoi(equipament_number);
        if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
              equipament == 4))
        {
            strcat(response, "invalid equipment");
            return response;
        }
        if (bd[equipament][sensor_1] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            a1 = ale;
            sprintf(sensorExist, "%.2f ", a1);
            strcat(response, sensorExist);
        }
        else
        {
            strcat(sensorNotExist, sensor_number_1);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_2] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            a2 = ale;
            sprintf(sensorExist, "%.2f ", a2);
            strcat(response, sensorExist);
        }
        else
        {
            strcat(sensorNotExist, sensor_number_2);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (bd[equipament][sensor_3] == 1)
        {
            ale = rand() % 100001;
            ale = ale / 10000;
            a3 = ale;
            sprintf(sensorExist, "%.2f ", a3);
            strcat(response, sensorExist);
        }
        else
        {
            strcat(sensorNotExist, sensor_number_3);
            strcat(sensorNotExist, " ");
            flag = 1;
        }
        if (flag)
        {
            strcat(response, "and sensor ");
            strcat(response, sensorNotExist);
            strcat(response, "not installed");
            return response;
        }
        return response;
    }
    sensor_4 = atoi(sensor_number_4);
    if (!(sensor_4 == 1 || sensor_4 == 2 || sensor_4 == 3 || sensor_4 == 4))
    {
        strcat(response, "invalid sensor");
        return response;
    }
    aux1 = strtok(NULL, " ");

    equipament_number = strtok(NULL, " ");
    equipament = atoi(equipament_number);
    if (!(equipament == 1 || equipament == 2 || equipament == 3 ||
          equipament == 4))
    {
        strcat(response, "invalid equipment");
        return response;
    }

    if (bd[equipament][sensor_1] == 1)
    {
        ale = rand() % 100001;
        ale = ale / 10000;
        a1 = ale;
        sprintf(sensorExist, "%.2f ", a1);
        strcat(response, sensorExist);
    }
    else
    {
        strcat(sensorNotExist, sensor_number_1);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_2] == 1)
    {
        ale = rand() % 100001;
        ale = ale / 10000;
        a2 = ale;
        sprintf(sensorExist, "%.2f ", a2);
        strcat(response, sensorExist);
    }
    else
    {
        strcat(sensorNotExist, sensor_number_2);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_3] == 1)
    {
        ale = rand() % 100001;
        ale = ale / 10000;
        a3 = ale;
        sprintf(sensorExist, "%.2f ", a3);
        strcat(response, sensorExist);
    }
    else
    {
        strcat(sensorNotExist, sensor_number_3);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (bd[equipament][sensor_4] == 1)
    {
        ale = rand() % 100001;
        ale = ale / 10000;
        a4 = ale;
        sprintf(sensorExist, "%.2f ", a4);
        strcat(response, sensorExist);
    }
    else
    {
        strcat(sensorNotExist, sensor_number_4);
        strcat(sensorNotExist, " ");
        flag = 1;
    }
    if (flag)
    {
        strcat(response, "and sensor ");
        strcat(response, sensorNotExist);
        strcat(response, "not installed");
        return response;
    }
    return response;
}

void clear_bd()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            bd[i][j] = 0;
        }
    }
}
