#include "../utils.h"



int main(int argc, char **argv)
{
    int socket_fd, n;
    char recv_line[MAXLINE + 1];
    struct sockaddr_in server_address;

    if (argc != 2)
    {
        error_quit("usage: a.out <IP_Address>");
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error_quit("error: socket");
    }

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);

    if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
    {
        error_quit("inet_pton error for %s", argv[1]);
    }

    if (connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        error_quit("connect error");
    }

    while ((n = read(socket_fd, recv_line, MAXLINE)) > 0)
    {
        recv_line[n] = 0;
        if (fputs(recv_line, stdout) == EOF)
        {
            error_quit("fputs error");
        }
    }

    if (n < 0)
    {
        error_quit("read error");
    }

    return EXIT_SUCCESS;
}