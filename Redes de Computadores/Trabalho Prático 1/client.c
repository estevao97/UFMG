#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

void func(int s);
char *add(const char *menssage);

void usage(int argc, char **argv) {
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

#define BUFSZ 500

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(storage))) {
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    func(s);
    close(s);
    exit(EXIT_SUCCESS);
}

void func(int sockfd) {
    char buf[BUFSZ];
    char messageReceive[BUFSZ];
    char messageToSend[BUFSZ];

    /* Get message from terminal */
    memset(buf, 0, BUFSZ);
    memset(messageToSend, 0, BUFSZ);

    fgets(buf, BUFSZ - 1, stdin);
    strcat(messageToSend, buf);

    size_t count = send(sockfd, messageToSend, strlen(messageToSend), 0);
    if (count != strlen(messageToSend)) {
        logexit("send");
    }

    memset(messageReceive, 0, BUFSZ);
    unsigned total = 0;
    while (1) {
        count = recv(sockfd, messageReceive + total, BUFSZ - total, 0);
        if (count == 0) {
            // Connection terminated.
            break;
        }
        total += count;
    }

    printf("%s\n", messageReceive);
    memset(messageReceive, 0, BUFSZ);
}
