#include "../utils.h"

int main(int argc, char *argv)
{
    int listen_fd, conn_fd;
    struct sockaddr_in server_addr;
    char buffer[MAXLINE];
    time_t ticks;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(listen_fd, LISTENQ);

    for (;;) {
        conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
        write(conn_fd, buffer, strlen(buffer));

        close(conn_fd);
    }

    return EXIT_SUCCESS;
}