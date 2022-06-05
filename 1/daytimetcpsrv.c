#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "../unp.h"


int main(int arg, char *argv[])
{
    int    listen_fd, conn_fd;
    struct sockaddr_in serv_addr;
    char   buffer[MAXLINE];
    time_t ticks;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        err_quit("error socket()");
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(8000);

    if ((bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0)
    {
        err_quit("error bind()");
    }

    if (listen(listen_fd, LISTENQ) < 0)
    {
        err_quit("error listen()");
    }

    for (;;)
    {
        conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\n", ctime(&ticks));
        write(conn_fd, buffer, strlen(buffer));

        close(conn_fd);
    }

    return EXIT_SUCCESS;
}