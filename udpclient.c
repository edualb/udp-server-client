#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

/* Datagram Client, Internet Space */

void printError(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sock, length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *ht;
    char buf[512];

    if (argc != 3) {
        printf("Usage: Server Port\n");
        exit(1);
    }

    sock=socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        printError("Opening Socket");
    }

    server.sin_family=AF_INET;

    ht=gethostbyname(argv[1]);
    if (ht == 0) {
        printError("Unknown Host");
    }

    bcopy((char *)ht->h_addr, (char *)&server.sin_addr, ht->h_length);
    server.sin_port=htons(atoi(argv[2]));

    length=sizeof(struct sockaddr_in);
    
    printf("Enter your message: \n");
    
    bzero(buf, 512);
    fgets(buf, 511, stdin);

    n=sendto(sock, buf, strlen(buf), 0, &server, length);

    if (n < 0) {
        printError("sendto");
    }

    n=recvfrom(sock, buf, 512, 0, &from, &length);

    if (n < 0) {
        printError("recvfrom");
    }

    write(1, "Received an Ack: ", 17);
    write(1, buf, n);
}