#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


#include "../unp.h"


int main(int argc, char *argv[])
{
    int    sock_fd, n;
    char   recv_line[MAXLINE + 1];
    struct sockaddr_in serv_addr;

    if (argc != 2)
    {
        err_quit("usage : a.out <ip_address>");
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        err_quit("socket() error");
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(8000);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0)
    {
        err_quit("inet_pton() error for %s", argv[1]);
    }

    if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        err_quit("connect() error");
    }

    while ((n = read(sock_fd, recv_line, MAXLINE)) > 0)
    {
        recv_line[n] = 0;

        if (fputs(recv_line, stdout) == EOF)
        {
            err_quit("fputs() error");
        }
    }

    if (n < 0)
    {
        err_quit("read() error");
    }

    return EXIT_SUCCESS;
}