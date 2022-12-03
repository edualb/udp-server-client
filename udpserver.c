#include<stdio.h>
#include<netdb.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
/* Datagram Server, Runs Forever */

void printError(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sock, length, fromlen, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];

    if (argc<2) {
        fprintf(stderr, "No Port Err\n");
        exit(0);
    }

    sock=socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        printError("Opening Socket");
    }

    length=sizeof(server);
    bzero(&server, length);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr * )&server, length) < 0) {
        printError("Binding");
    }

    fromlen=sizeof(struct sockaddr_in);

    while(1) {
        n=recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);

        if (n < 0) {
            printError("recvfrom");
        }

        write(1, "Received a datagram: ", 21);
        write(1, buf, n);
        n=sendto(sock, "Received your Message\n", 22, 0, (struct sockaddr *)&from, fromlen);

        if (n < 0) {
            printError("recvfrom");
        }
    }
}