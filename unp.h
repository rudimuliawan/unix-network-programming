#ifndef UNP_H

#include <stdio.h>
#include <stdlib.h>

#define LISTENQ 1024
#define MAXLINE 4096

void err_quit(char *error_message, ...)
{
    printf("%s\n", error_message);
    exit(EXIT_FAILURE);
}

#endif
